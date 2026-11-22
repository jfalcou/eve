//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// Implementation and tests heavily inspired by libc++
// (LLVM Project, Apache-2.0 WITH LLVM-exception).

#include <eve/assert.hpp>

#include <compare>
#include <concepts>
#include <functional>
#include <memory>
#include <optional>
#include <utility>

#include <initializer_list>
#include <type_traits>

EVE_NAMESPACE::_
{
  struct nullopt_t
  {
    struct tag
    {};
    constexpr explicit nullopt_t(tag) noexcept {}
  };

  inline constexpr nullopt_t nullopt {nullopt_t::tag {}};

  template<typename T> struct optional_tombstone
  {};

  template<typename T, typename Tombstone = optional_tombstone<T>> class optional;

  template<typename T> inline constexpr bool is_optional_v = false;

  template<typename T, typename Tombstone>
  inline constexpr bool is_optional_v<optional<T, Tombstone>> = true;

  template<typename N>
  concept optional_empty_tag = std::same_as<N, nullopt_t> || std::same_as<N, std::nullopt_t>;

  struct optional_invoke_tag
  {};

  template<typename T, typename Tombstone>
  concept optional_has_tombstone = requires {
    { Tombstone::value } -> std::convertible_to<T const&>;
  };

  template<typename T>
  concept optional_trivial_value =
      std::is_trivially_copyable_v<T> && std::is_trivially_destructible_v<T> && !std::is_const_v<T>
      && !std::is_volatile_v<T>;

  template<typename T, typename Tombstone> struct optional_tombstone_storage
  {
    T val_ = Tombstone::value;

    constexpr optional_tombstone_storage() noexcept = default;

    template<typename... Args>
    constexpr explicit optional_tombstone_storage(std::in_place_t, Args&&...args)
        : val_(std::forward<Args>(args)...)
    {
      check();
    }

    template<typename F, typename... Args>
    constexpr optional_tombstone_storage(optional_invoke_tag, F&& f, Args&&...args)
        : val_(std::invoke(std::forward<F>(f), std::forward<Args>(args)...))
    {
      check();
    }

    constexpr void check() const noexcept
    {
      EVE_ASSERT(has_value(), "eve::_::optional: the tombstone can not be stored as a value");
    }

    constexpr bool has_value() const noexcept
    {
      return !static_cast<bool>(val_ == Tombstone::value);
    }

    constexpr T&       get() noexcept { return val_; }
    constexpr T const& get() const noexcept { return val_; }

    template<typename... Args> constexpr void construct(Args&&...args)
    {
      std::construct_at(std::addressof(val_), std::forward<Args>(args)...);
      check();
    }

    template<typename V> constexpr void assign(V&& v)
    {
      val_ = std::forward<V>(v);
      check();
    }

    constexpr void reset() noexcept { std::construct_at(std::addressof(val_), Tombstone::value); }
  };

  template<typename T> struct optional_plain_storage
  {
    T    val_ {};
    bool engaged_ = false;

    constexpr optional_plain_storage() noexcept = default;

    template<typename... Args>
    constexpr explicit optional_plain_storage(std::in_place_t, Args&&...args)
        : val_(std::forward<Args>(args)...)
        , engaged_(true)
    {}

    template<typename F, typename... Args>
    constexpr optional_plain_storage(optional_invoke_tag, F&& f, Args&&...args)
        : val_(std::invoke(std::forward<F>(f), std::forward<Args>(args)...))
        , engaged_(true)
    {}

    constexpr bool has_value() const noexcept { return engaged_; }

    constexpr T&       get() noexcept { return val_; }
    constexpr T const& get() const noexcept { return val_; }

    template<typename... Args> constexpr void construct(Args&&...args)
    {
      std::construct_at(std::addressof(val_), std::forward<Args>(args)...);
      engaged_ = true;
    }

    template<typename V> constexpr void assign(V&& v) { val_ = std::forward<V>(v); }

    constexpr void reset() noexcept { engaged_ = false; }
  };

  template<typename Storage, typename Value>
  constexpr void optional_assign_from(Storage & self, bool engaged, Value&& value)
  {
    if( self.has_value() == engaged )
    {
      if( engaged ) self.assign(value());
    }
    else if( engaged ) self.construct(value());
    else self.reset();
  }

  template<typename T> struct optional_union_storage
  {
    union
    {
      char                null_;
      std::remove_cv_t<T> val_;
    };
    bool engaged_;

    constexpr optional_union_storage() noexcept : null_(), engaged_(false) {}

    template<typename... Args>
    constexpr explicit optional_union_storage(std::in_place_t, Args&&...args)
        : val_(std::forward<Args>(args)...)
        , engaged_(true)
    {}

    template<typename F, typename... Args>
    constexpr optional_union_storage(optional_invoke_tag, F&& f, Args&&...args)
        : val_(std::invoke(std::forward<F>(f), std::forward<Args>(args)...))
        , engaged_(true)
    {}

    constexpr optional_union_storage(optional_union_storage const&)
    requires std::is_trivially_copy_constructible_v<T>
    = default;

    constexpr optional_union_storage(optional_union_storage const& other)
    requires(std::is_copy_constructible_v<T> && !std::is_trivially_copy_constructible_v<T>)
        : optional_union_storage()
    {
      if( other.has_value() ) construct(other.get());
    }

    optional_union_storage(optional_union_storage const&)
    requires(!std::is_copy_constructible_v<T>)
    = delete;

    constexpr optional_union_storage(optional_union_storage&&)
    requires std::is_trivially_move_constructible_v<T>
    = default;

    constexpr optional_union_storage(optional_union_storage&& other) noexcept(
        std::is_nothrow_move_constructible_v<T>)
    requires(std::is_move_constructible_v<T> && !std::is_trivially_move_constructible_v<T>)
        : optional_union_storage()
    {
      if( other.has_value() ) construct(std::move(other.get()));
    }

    optional_union_storage(optional_union_storage&&)
    requires(!std::is_move_constructible_v<T>)
    = delete;

    constexpr optional_union_storage& operator=(optional_union_storage const&)
    requires(std::is_trivially_destructible_v<T> && std::is_trivially_copy_constructible_v<T>
             && std::is_trivially_copy_assignable_v<T>)
    = default;

    constexpr optional_union_storage& operator=(optional_union_storage const& other)
    requires(std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>
             && !(std::is_trivially_destructible_v<T> && std::is_trivially_copy_constructible_v<T>
                  && std::is_trivially_copy_assignable_v<T>))
    {
      optional_assign_from(*this, other.engaged_, [&]() -> T const& { return other.val_; });
      return *this;
    }

    optional_union_storage& operator=(optional_union_storage const&)
    requires(!(std::is_copy_constructible_v<T> && std::is_copy_assignable_v<T>))
    = delete;

    constexpr optional_union_storage& operator=(optional_union_storage&&)
    requires(std::is_trivially_destructible_v<T> && std::is_trivially_move_constructible_v<T>
             && std::is_trivially_move_assignable_v<T>)
    = default;

    constexpr optional_union_storage&
    operator=(optional_union_storage&& other) noexcept(std::is_nothrow_move_assignable_v<T>
                                                       && std::is_nothrow_move_constructible_v<T>)
    requires(std::is_move_constructible_v<T> && std::is_move_assignable_v<T>
             && !(std::is_trivially_destructible_v<T> && std::is_trivially_move_constructible_v<T>
                  && std::is_trivially_move_assignable_v<T>))
    {
      optional_assign_from(*this, other.engaged_, [&]() -> T&& { return std::move(other.val_); });
      return *this;
    }

    optional_union_storage& operator=(optional_union_storage&&)
    requires(!(std::is_move_constructible_v<T> && std::is_move_assignable_v<T>))
    = delete;

    constexpr ~optional_union_storage()
    requires std::is_trivially_destructible_v<T>
    = default;

    constexpr ~optional_union_storage()
    requires(!std::is_trivially_destructible_v<T>)
    {
      reset();
    }

    constexpr bool has_value() const noexcept { return engaged_; }

    constexpr T&       get() noexcept { return val_; }
    constexpr T const& get() const noexcept { return val_; }

    template<typename... Args> constexpr void construct(Args&&...args)
    {
      std::construct_at(std::addressof(val_), std::forward<Args>(args)...);
      engaged_ = true;
    }

    template<typename V> constexpr void assign(V&& v) { val_ = std::forward<V>(v); }

    constexpr void reset() noexcept
    {
      if( engaged_ )
      {
        if constexpr( !std::is_trivially_destructible_v<T> ) std::destroy_at(std::addressof(val_));
        engaged_ = false;
      }
    }
  };

  template<typename T, typename Tombstone> struct optional_storage_select
  {
    using type = optional_union_storage<T>;
  };

  template<typename T, typename Tombstone>
  requires(!optional_has_tombstone<T, Tombstone> && optional_trivial_value<T>
           && std::is_trivially_default_constructible_v<T>)
  struct optional_storage_select<T, Tombstone>
  {
    using type = optional_plain_storage<T>;
  };

  template<typename T, typename Tombstone>
  requires optional_has_tombstone<T, Tombstone>
  struct optional_storage_select<T, Tombstone>
  {
    static_assert(
        optional_trivial_value<T> && std::equality_comparable<T>,
        "eve::_::optional: a tombstone requires a trivially copyable, equality comparable T");
    using type = optional_tombstone_storage<T, Tombstone>;
  };

  template<typename T, typename Tombstone>
  using optional_storage_t = typename optional_storage_select<T, Tombstone>::type;

  template<typename T, typename W>
  inline constexpr bool optional_converts_from_any_cvref =
      std::is_constructible_v<T, W&> || std::is_convertible_v<W&, T>
      || std::is_constructible_v<T, W> || std::is_convertible_v<W, T>
      || std::is_constructible_v<T, W const&> || std::is_convertible_v<W const&, T>
      || std::is_constructible_v<T, W const> || std::is_convertible_v<W const, T>;

  template<typename T, typename W>
  inline constexpr bool optional_assigns_from_any_cvref =
      std::is_assignable_v<T&, W&> || std::is_assignable_v<T&, W>
      || std::is_assignable_v<T&, W const&> || std::is_assignable_v<T&, W const>;

  template<typename T, typename Tombstone> class optional : private optional_storage_t<T, Tombstone>
  {
    using storage = optional_storage_t<T, Tombstone>;

    template<typename U, typename B> friend class optional;

    static_assert(!std::is_reference_v<T>, "eve::_::optional: T can not be a reference");
    static_assert(!std::is_array_v<T>, "eve::_::optional: T can not be an array");
    static_assert(std::is_destructible_v<T>, "eve::_::optional: T must be destructible");
    static_assert(!std::same_as<std::remove_cv_t<T>, std::in_place_t>,
                  "eve::_::optional: T can not be in_place_t");
    static_assert(!optional_empty_tag<std::remove_cv_t<T>>,
                  "eve::_::optional: T can not be a nullopt tag");

    template<typename U>
    static constexpr bool from_value =
        std::is_constructible_v<T, U> && !std::same_as<std::remove_cvref_t<U>, std::in_place_t>
        && !std::same_as<std::remove_cvref_t<U>, optional>
        && !optional_empty_tag<std::remove_cvref_t<U>>
        && !(std::same_as<std::remove_cv_t<T>, bool> && is_optional_v<std::remove_cvref_t<U>>);

    template<typename U, typename B, typename QualU>
    static constexpr bool from_optional =
        !std::same_as<optional, optional<U, B>> && std::is_constructible_v<T, QualU>
        && (std::same_as<std::remove_cv_t<T>, bool>
            || !optional_converts_from_any_cvref<T, optional<U, B>>);

    template<typename U, typename B, typename QualU>
    static constexpr bool assign_optional =
        from_optional<U, B, QualU> && std::is_assignable_v<T&, QualU>
        && !optional_converts_from_any_cvref<T, optional<U, B>>
        && !optional_assigns_from_any_cvref<T, optional<U, B>>;

    template<typename Self, typename F> static constexpr auto and_then_impl(Self&& self, F&& f)
    {
      using U = std::remove_cvref_t<std::invoke_result_t<F, decltype(*std::forward<Self>(self))>>;
      static_assert(is_optional_v<U>,
                    "eve::_::optional::and_then: f must return an eve::_::optional");
      if( self.has_value() ) return std::invoke(std::forward<F>(f), *std::forward<Self>(self));
      return U {};
    }

    template<typename Self, typename F> static constexpr auto transform_impl(Self&& self, F&& f)
    {
      using U = std::remove_cv_t<std::invoke_result_t<F, decltype(*std::forward<Self>(self))>>;
      if( self.has_value() )
        return optional<U>(optional_invoke_tag {}, std::forward<F>(f), *std::forward<Self>(self));
      return optional<U> {};
    }

    constexpr T& checked() noexcept
    {
      EVE_ASSERT(has_value(), "eve::_::optional: accessing a disengaged optional");
      return this->get();
    }

    constexpr T const& checked() const noexcept
    {
      EVE_ASSERT(has_value(), "eve::_::optional: accessing a disengaged optional");
      return this->get();
    }

    template<typename Other> constexpr void assign_optional_from(Other&& other)
    {
      optional_assign_from(static_cast<storage&>(*this),
                           other.has_value(),
                           [&]() -> decltype(auto) { return *std::forward<Other>(other); });
    }

    public:
    using value_type     = T;
    using tombstone_type = Tombstone;

    constexpr optional() noexcept       = default;
    constexpr optional(optional const&) = default;
    constexpr optional(optional&&)      = default;

    template<optional_empty_tag N> constexpr optional(N) noexcept {}

    template<typename... Args>
    requires std::is_constructible_v<T, Args...>
    constexpr explicit optional(std::in_place_t, Args&&...args)
        : storage(std::in_place, std::forward<Args>(args)...)
    {}

    template<typename U, typename... Args>
    requires std::is_constructible_v<T, std::initializer_list<U>&, Args...>
    constexpr explicit optional(std::in_place_t, std::initializer_list<U> il, Args&&...args)
        : storage(std::in_place, il, std::forward<Args>(args)...)
    {}

    template<typename U = std::remove_cv_t<T>>
    requires from_value<U>
    constexpr explicit(!std::is_convertible_v<U, T>)
        optional(U&& v) noexcept(std::is_nothrow_constructible_v<T, U>)
        : storage(std::in_place, std::forward<U>(v))
    {}

    template<typename U, typename B>
    requires from_optional<U, B, U const&>
    constexpr explicit(!std::is_convertible_v<U const&, T>) optional(optional<U, B> const& other)
    {
      if( other.has_value() ) this->construct(*other);
    }

    template<typename U, typename B>
    requires from_optional<U, B, U&&>
    constexpr explicit(!std::is_convertible_v<U&&, T>) optional(optional<U, B>&& other)
    {
      if( other.has_value() ) this->construct(*std::move(other));
    }

    template<typename F, typename... Args>
    constexpr explicit optional(optional_invoke_tag, F&& f, Args&&...args)
        : storage(optional_invoke_tag {}, std::forward<F>(f), std::forward<Args>(args)...)
    {}

    template<optional_empty_tag N> constexpr optional& operator=(N) noexcept
    {
      reset();
      return *this;
    }

    constexpr optional& operator=(optional const&) = default;
    constexpr optional& operator=(optional&&)      = default;

    template<typename U = std::remove_cv_t<T>>
    requires(!std::same_as<std::remove_cvref_t<U>, optional>
             && !optional_empty_tag<std::remove_cvref_t<U>>
             && (!std::same_as<std::remove_cvref_t<U>, T> || !std::is_scalar_v<T>)
             && std::is_constructible_v<T, U> && std::is_assignable_v<T&, U>)
    constexpr optional& operator=(U&& v)
    {
      if( has_value() ) this->assign(std::forward<U>(v));
      else this->construct(std::forward<U>(v));
      return *this;
    }

    template<typename U, typename B>
    requires assign_optional<U, B, U const&>
    constexpr optional& operator=(optional<U, B> const& other)
    {
      assign_optional_from(other);
      return *this;
    }

    template<typename U, typename B>
    requires assign_optional<U, B, U&&>
    constexpr optional& operator=(optional<U, B>&& other)
    {
      assign_optional_from(std::move(other));
      return *this;
    }

    template<typename... Args>
    requires std::is_constructible_v<T, Args...>
    constexpr T& emplace(Args&&...args)
    {
      reset();
      this->construct(std::forward<Args>(args)...);
      return this->get();
    }

    template<typename U, typename... Args>
    requires std::is_constructible_v<T, std::initializer_list<U>&, Args...>
    constexpr T& emplace(std::initializer_list<U> il, Args&&...args)
    {
      reset();
      this->construct(il, std::forward<Args>(args)...);
      return this->get();
    }

    constexpr void swap(optional& other) noexcept(std::is_nothrow_move_constructible_v<T>
                                                  && std::is_nothrow_swappable_v<T>)
    {
      using std::swap;
      if( has_value() == other.has_value() )
      {
        if( has_value() ) swap(this->get(), other.get());
      }
      else if( has_value() )
      {
        other.construct(std::move(this->get()));
        reset();
      }
      else
      {
        this->construct(std::move(other.get()));
        other.reset();
      }
    }

    constexpr T const *operator->() const noexcept { return std::addressof(checked()); }
    constexpr T       *operator->() noexcept { return std::addressof(checked()); }

    constexpr T const&  operator*() const& noexcept { return checked(); }
    constexpr T&        operator*() & noexcept { return checked(); }
    constexpr T&&       operator*() && noexcept { return std::move(checked()); }
    constexpr T const&& operator*() const&& noexcept { return std::move(checked()); }

    constexpr explicit operator bool() const noexcept { return has_value(); }
    constexpr bool     has_value() const noexcept { return storage::has_value(); }

    constexpr T const&  value() const& { return **this; }
    constexpr T&        value() & { return **this; }
    constexpr T&&       value() && { return std::move(**this); }
    constexpr T const&& value() const&& { return std::move(**this); }

    template<typename U = std::remove_cv_t<T>> constexpr T value_or(U&& v) const&
    {
      static_assert(std::is_copy_constructible_v<T> && std::is_convertible_v<U, T>);
      return has_value() ? this->get() : static_cast<T>(std::forward<U>(v));
    }

    template<typename U = std::remove_cv_t<T>> constexpr T value_or(U&& v) &&
    {
      static_assert(std::is_move_constructible_v<T> && std::is_convertible_v<U, T>);
      return has_value() ? std::move(this->get()) : static_cast<T>(std::forward<U>(v));
    }

    template<typename F> constexpr auto and_then(F&& f) &
    {
      return and_then_impl(*this, std::forward<F>(f));
    }
    template<typename F> constexpr auto and_then(F&& f) const&
    {
      return and_then_impl(*this, std::forward<F>(f));
    }
    template<typename F> constexpr auto and_then(F&& f) &&
    {
      return and_then_impl(std::move(*this), std::forward<F>(f));
    }
    template<typename F> constexpr auto and_then(F&& f) const&&
    {
      return and_then_impl(std::move(*this), std::forward<F>(f));
    }

    template<typename F> constexpr auto transform(F&& f) &
    {
      return transform_impl(*this, std::forward<F>(f));
    }
    template<typename F> constexpr auto transform(F&& f) const&
    {
      return transform_impl(*this, std::forward<F>(f));
    }
    template<typename F> constexpr auto transform(F&& f) &&
    {
      return transform_impl(std::move(*this), std::forward<F>(f));
    }
    template<typename F> constexpr auto transform(F&& f) const&&
    {
      return transform_impl(std::move(*this), std::forward<F>(f));
    }

    template<std::invocable F>
    requires std::is_copy_constructible_v<T>
    constexpr optional or_else(F&& f) const&
    {
      static_assert(std::same_as<std::remove_cvref_t<std::invoke_result_t<F>>, optional>,
                    "eve::_::optional::or_else: f must return the same optional type");
      if( has_value() ) return *this;
      return std::forward<F>(f)();
    }

    template<std::invocable F>
    requires std::is_move_constructible_v<T>
    constexpr optional or_else(F&& f) &&
    {
      static_assert(std::same_as<std::remove_cvref_t<std::invoke_result_t<F>>, optional>,
                    "eve::_::optional::or_else: f must return the same optional type");
      if( has_value() ) return std::move(*this);
      return std::forward<F>(f)();
    }

    constexpr void reset() noexcept
    {
      if( has_value() ) storage::reset();
    }

    constexpr std::optional<std::remove_cv_t<T>> to_std() const&
    {
      if( has_value() ) return std::optional<std::remove_cv_t<T>>(std::in_place, this->get());
      return std::nullopt;
    }

    constexpr std::optional<std::remove_cv_t<T>> to_std() &&
    {
      if( has_value() )
        return std::optional<std::remove_cv_t<T>>(std::in_place, std::move(this->get()));
      return std::nullopt;
    }
  };

  template<typename T> optional(T) -> optional<T>;

  template<typename T, typename A, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t == u } -> std::convertible_to<bool>;
  }
  constexpr bool operator==(optional<T, A> const& x, optional<U, B> const& y)
  {
    if( x.has_value() != y.has_value() ) return false;
    if( !x.has_value() ) return true;
    return *x == *y;
  }

  template<typename T, typename A, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t != u } -> std::convertible_to<bool>;
  }
  constexpr bool operator!=(optional<T, A> const& x, optional<U, B> const& y)
  {
    if( x.has_value() != y.has_value() ) return true;
    if( !x.has_value() ) return false;
    return *x != *y;
  }

  template<typename T, typename A, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t < u } -> std::convertible_to<bool>;
  }
  constexpr bool operator<(optional<T, A> const& x, optional<U, B> const& y)
  {
    if( !y.has_value() ) return false;
    if( !x.has_value() ) return true;
    return *x < *y;
  }

  template<typename T, typename A, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t > u } -> std::convertible_to<bool>;
  }
  constexpr bool operator>(optional<T, A> const& x, optional<U, B> const& y)
  {
    if( !x.has_value() ) return false;
    if( !y.has_value() ) return true;
    return *x > *y;
  }

  template<typename T, typename A, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t <= u } -> std::convertible_to<bool>;
  }
  constexpr bool operator<=(optional<T, A> const& x, optional<U, B> const& y)
  {
    if( !x.has_value() ) return true;
    if( !y.has_value() ) return false;
    return *x <= *y;
  }

  template<typename T, typename A, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t >= u } -> std::convertible_to<bool>;
  }
  constexpr bool operator>=(optional<T, A> const& x, optional<U, B> const& y)
  {
    if( !y.has_value() ) return true;
    if( !x.has_value() ) return false;
    return *x >= *y;
  }

  template<typename T, typename A, std::three_way_comparable_with<T> U, typename B>
  constexpr std::compare_three_way_result_t<T, U> operator<=>(optional<T, A> const& x,
                                                              optional<U, B> const& y)
  {
    if( x.has_value() && y.has_value() ) return *x <=> *y;
    return x.has_value() <=> y.has_value();
  }

  template<typename T, typename A, optional_empty_tag N>
  constexpr bool operator==(optional<T, A> const& x, N) noexcept
  {
    return !x.has_value();
  }

  template<typename T, typename A, optional_empty_tag N>
  constexpr std::strong_ordering operator<=>(optional<T, A> const& x, N) noexcept
  {
    return x.has_value() <=> false;
  }

  template<typename U>
  concept optional_compared_value = !is_optional_v<U> && !optional_empty_tag<U>;

  template<typename T, typename A, optional_compared_value U>
  requires requires(T const& t, U const& u) {
    { t == u } -> std::convertible_to<bool>;
  }
  constexpr bool operator==(optional<T, A> const& x, U const& v)
  {
    return x.has_value() ? static_cast<bool>(*x == v) : false;
  }

  template<optional_compared_value T, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t == u } -> std::convertible_to<bool>;
  }
  constexpr bool operator==(T const& v, optional<U, B> const& x)
  {
    return x.has_value() ? static_cast<bool>(v == *x) : false;
  }

  template<typename T, typename A, optional_compared_value U>
  requires requires(T const& t, U const& u) {
    { t != u } -> std::convertible_to<bool>;
  }
  constexpr bool operator!=(optional<T, A> const& x, U const& v)
  {
    return x.has_value() ? static_cast<bool>(*x != v) : true;
  }

  template<optional_compared_value T, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t != u } -> std::convertible_to<bool>;
  }
  constexpr bool operator!=(T const& v, optional<U, B> const& x)
  {
    return x.has_value() ? static_cast<bool>(v != *x) : true;
  }

  template<typename T, typename A, optional_compared_value U>
  requires requires(T const& t, U const& u) {
    { t < u } -> std::convertible_to<bool>;
  }
  constexpr bool operator<(optional<T, A> const& x, U const& v)
  {
    return x.has_value() ? static_cast<bool>(*x < v) : true;
  }

  template<optional_compared_value T, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t < u } -> std::convertible_to<bool>;
  }
  constexpr bool operator<(T const& v, optional<U, B> const& x)
  {
    return x.has_value() ? static_cast<bool>(v < *x) : false;
  }

  template<typename T, typename A, optional_compared_value U>
  requires requires(T const& t, U const& u) {
    { t <= u } -> std::convertible_to<bool>;
  }
  constexpr bool operator<=(optional<T, A> const& x, U const& v)
  {
    return x.has_value() ? static_cast<bool>(*x <= v) : true;
  }

  template<optional_compared_value T, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t <= u } -> std::convertible_to<bool>;
  }
  constexpr bool operator<=(T const& v, optional<U, B> const& x)
  {
    return x.has_value() ? static_cast<bool>(v <= *x) : false;
  }

  template<typename T, typename A, optional_compared_value U>
  requires requires(T const& t, U const& u) {
    { t > u } -> std::convertible_to<bool>;
  }
  constexpr bool operator>(optional<T, A> const& x, U const& v)
  {
    return x.has_value() ? static_cast<bool>(*x > v) : false;
  }

  template<optional_compared_value T, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t > u } -> std::convertible_to<bool>;
  }
  constexpr bool operator>(T const& v, optional<U, B> const& x)
  {
    return x.has_value() ? static_cast<bool>(v > *x) : true;
  }

  template<typename T, typename A, optional_compared_value U>
  requires requires(T const& t, U const& u) {
    { t >= u } -> std::convertible_to<bool>;
  }
  constexpr bool operator>=(optional<T, A> const& x, U const& v)
  {
    return x.has_value() ? static_cast<bool>(*x >= v) : false;
  }

  template<optional_compared_value T, typename U, typename B>
  requires requires(T const& t, U const& u) {
    { t >= u } -> std::convertible_to<bool>;
  }
  constexpr bool operator>=(T const& v, optional<U, B> const& x)
  {
    return x.has_value() ? static_cast<bool>(v >= *x) : true;
  }

  template<typename T, typename A, optional_compared_value U>
  requires std::three_way_comparable_with<T, U>
  constexpr std::compare_three_way_result_t<T, U> operator<=>(optional<T, A> const& x, U const& v)
  {
    return x.has_value() ? *x <=> v : std::strong_ordering::less;
  }

  template<typename T, typename A>
  requires std::is_move_constructible_v<T> && std::is_swappable_v<T>
  constexpr void swap(optional<T, A> & x, optional<T, A> & y) noexcept(noexcept(x.swap(y)))
  {
    x.swap(y);
  }

  template<typename T> constexpr optional<std::decay_t<T>> make_optional(T && v)
  {
    return optional<std::decay_t<T>>(std::forward<T>(v));
  }

  template<typename T, typename... Args> constexpr optional<T> make_optional(Args && ...args)
  {
    return optional<T>(std::in_place, std::forward<Args>(args)...);
  }

  template<typename T, typename U, typename... Args>
  constexpr optional<T> make_optional(std::initializer_list<U> il, Args && ...args)
  {
    return optional<T>(std::in_place, il, std::forward<Args>(args)...);
  }
}
