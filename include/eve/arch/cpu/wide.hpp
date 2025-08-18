//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/arch/cpu/base.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/spec.hpp>
#include <eve/concept/invocable.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/range.hpp>
#include <eve/concept/scalar.hpp>
#include <eve/conditional.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/fill.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/subscript.hpp>
#include <eve/module/core/regular/rem.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/regular/mul.hpp>
#include <eve/module/core/regular/div.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/logical_not.hpp>
#include <eve/module/core/regular/shl.hpp>
#include <eve/module/core/regular/shr.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_greater_equal.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_less_equal.hpp>
#include <eve/memory/soa_ptr.hpp>
#include <eve/traits/product_type.hpp>
#include <eve/traits/as_translation.hpp>

#include <concepts>
#include <ostream>
#include <utility>

#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  struct wide_split_type_helper
  { };

  template<typename T, typename N>
  requires(N::value > 1)
  struct wide_split_type_helper<T, N>
  {
    //! Type representing a wide of the same type but with a cardinal half the size
    using split_type = wide<T, typename N::split_type>;
  };
}

#if !defined(EVE_DOXYGEN_INVOKED)
namespace eve
{
inline namespace EVE_ABI_NAMESPACE
{
#else
namespace eve
{
#endif

  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief Wrapper for SIMD registers
  //!
  //! **Required header:** `#include <eve/wide.hpp>`
  //!
  //! eve::wide is an architecture-agnostic representation of a SIMD register and provides
  //! standardized API to access informations, compute values and manipulate such register.
  //!
  //! @tparam Type      Type of value to store in the register
  //! @tparam Cardinal  Cardinal of the register. By default, the best cardinal for current
  //!                    architecture is selected.
  //================================================================================================
  template<arithmetic_scalar_value Type, typename Cardinal>
  struct EVE_MAY_ALIAS wide
      : detail::wide_storage<as_register_t<translate_t<Type>, Cardinal, abi_t<translate_t<Type>, Cardinal>>>,
        detail::wide_split_type_helper<Type, Cardinal>
  {
    using storage_base = detail::wide_storage<as_register_t<translate_t<Type>, Cardinal, abi_t<translate_t<Type>, Cardinal>>>;

    //! The type stored in the register.
    using value_type = Type;

    //! The type resulting from translating the current wide's elements type.
    using translated_element_type = translate_t<Type>;

    //! The type resulting from translating the current wide type.
    using translated_type = wide<translated_element_type, Cardinal>;

    //! The ABI tag for this register.
    using abi_type = abi_t<translated_element_type, Cardinal>;

    //! The type used for this register storage
    using storage_type = typename storage_base::storage_type;

    //! Type describing the number of lanes of current wide
    using cardinal_type = Cardinal;

    //! Type representing the size of the current wide
    using size_type = std::ptrdiff_t;

    //! Opt-in for like concept
    using is_like = value_type;

    //! Type representing a wide of the same type but with a cardinal twice the size
    using combined_type = wide<Type, typename Cardinal::combined_type>;

    //! @brief Generates a eve::wide from a different type `T` and cardinal `N`.
    //! If unspecified, `N` is computed as `expected_cardinal_t<T>`.
    template<typename T, typename N = expected_cardinal_t<T>> using rebind = wide<T, N>;

    //! Generates a eve::wide type from a different cardinal `N`.
    template<typename N> using rescale = wide<Type, N>;

    static EVE_FORCEINLINE constexpr auto alignment() noexcept
    {
      return sizeof(Type) * Cardinal {};
    }

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================

    //! @brief Default constructor
    //! This operation is a no-op unless `Type` satisfies eve::product_type and has a non trivial
    //! default constructor.
    EVE_FORCEINLINE wide() requires(std::is_trivially_constructible_v<Type>) {}

    //! @overload
    EVE_FORCEINLINE wide() requires(!std::is_trivially_constructible_v<Type>) : wide(Type {}) {}

    //! Constructs from ABI-specific storage
    EVE_FORCEINLINE wide(storage_type const& r) noexcept : storage_base(r) {}

    //! @brief Constructs a eve::wide from a @container.
    //! Construction is done piecewise unless the @iterator{s} extracted from `r` are
    //! @raiterator{s}.
    template<detail::range Range>
    EVE_FORCEINLINE explicit wide(Range&& r) noexcept
    requires (std::same_as<value_type_t<Range>, Type> && !std::same_as<storage_type, Range>)
        : wide(std::begin(EVE_FWD(r)))
    {
      EVE_ASSERT(std::distance(std::begin(r), std::end(r)) == Cardinal::value,
                 "eve::wide: Range size does not match the expected cardinal.");
    }

    //! Constructs a eve::wide from a SIMD compatible pointer
    template<simd_compatible_ptr<wide> Ptr>
    EVE_FORCEINLINE explicit wide(Ptr ptr) noexcept : storage_base(load(ptr, Cardinal {}))
    {}

    //! Constructs a eve::wide from a SIMD compatible pointer
    template<detail::data_source... Ptr>
    requires(kumi::product_type<Type>)
    EVE_FORCEINLINE explicit wide(eve::soa_ptr<Ptr...> ptr) noexcept
        : storage_base(load(ptr, Cardinal {}))
    {}

    //! Constructs a eve::wide by splatting a scalar value in all lanes
    template<typename S>
    requires std::constructible_from<Type,S>
    EVE_FORCEINLINE explicit wide(S const& v) noexcept
        : storage_base(detail::make(eve::as<translated_type>{}, static_cast<translated_element_type>(translate(v))))
    {}

    //! Constructs a eve::wide from a sequence of scalar values of proper size
    template<scalar_value S0, scalar_value S1, scalar_value... Ss>
    EVE_FORCEINLINE wide(S0 v0, S1 v1, Ss... vs) noexcept
        requires( (Cardinal::value == 2 + sizeof...(vs))
                  && std::is_convertible_v<S0,Type>
                  && (std::is_convertible_v<S1, Type> && ... && std::is_convertible_v<Ss, Type>)
                )
        : storage_base(detail::make(eve::as<translated_type> {},
                                    static_cast<translated_element_type>(translate(v0)),
                                    static_cast<translated_element_type>(translate(v1)),
                                    static_cast<translated_element_type>(translate(vs))...))
    {}

    //! Constructs a eve::wide from a sequence of values
    template<typename S0, typename... Ss>
    explicit EVE_FORCEINLINE wide(S0 const& v0, Ss const&...vs) noexcept
    requires(kumi::sized_product_type_or_more<Type,1+sizeof...(Ss)>)
    {
      storage_base::storage() = [&]<std::size_t... I>(std::index_sequence<I...>)
        {
          constexpr auto K = sizeof...(Ss);
          return kumi::map([]<typename N, typename W>(N const& n, W const&)
                            {
                              if constexpr(scalar_value<N>) return W( typename W::value_type(n) );
                              else                          return W(n);
                            }
                          , kumi::make_tuple(v0, vs..., kumi::element_t<K+I,Type>{}...)
                          , *this
                          );
        }(std::make_index_sequence<kumi::size_v<Type> - (1+sizeof...(Ss))>{});
    }


    //==============================================================================================
    //! @brief Constructs a eve::wide from a @callable.
    //!
    //! The @callable must satisfy the following prototype:
    //!
    //! @code
    //! T generator(std::ptrdiff_t index, std::ptrdiff_t cardinal);
    //! @endcode
    //! <br/>
    //!
    //! and is supposed to return the value computed from the current index and the cardinal to
    //! store at said index.
    //!
    //! @param g  The @callable to use as a value generator
    //!
    //! **Example:**
    //!
    //! @code
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the wide [N-1 ... 0]
    //!   eve::wide<int> r = [](auto i, auto c) { return c - i - 1;};
    //!   std::cout << r << "\n";
    //! }
    //! @endcode
    //!
    //==============================================================================================
    template<eve::invocable<size_type, size_type> Generator>
    EVE_FORCEINLINE wide(Generator&& g) noexcept
        : storage_base(detail::fill(eve::as<wide> {}, EVE_FWD(g)))
    {}

    //! @brief Constructs a eve::wide by combining two eve::wide of half the current cardinal.
    //! Does not participate in overload resolution if `Cardinal::value != 2 * Half::value`.
    template<typename Half>
    EVE_FORCEINLINE wide(wide<Type, Half> const& l, wide<Type, Half> const& h) noexcept
    requires(Cardinal::value == 2 * Half::value)
        : storage_base(detail::combine(eve::current_api, l, h))
    {}

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================

    //! @brief Assignment of an architecture-specific SIMD register
    wide& operator=(storage_type const& r)
    {
      storage_base::data_ = r;
      return *this;
    }

    //! @brief Assignment of a scalar value by splatting it in all lanes
    template<scalar_value S> EVE_FORCEINLINE wide& operator=(S v) noexcept
    {
      wide that(v);
      swap(that);
      return *this;
    }
    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Modifiers
    //! @{
    //==============================================================================================
    //! Set the value of a given lane
    EVE_FORCEINLINE void set(std::size_t i, scalar_value auto v) noexcept
    {
      detail::insert(*this, i, v);
    }

    //! Retrieve the value from a given lane
    EVE_FORCEINLINE Type get(std::size_t i) const noexcept { return detail::extract(*this, i); }

    //! Retrieve the value from the last lane
    EVE_FORCEINLINE Type back() const noexcept { return get(Cardinal::value - 1); }

    //! Retrieve the value from the first lane
    EVE_FORCEINLINE Type front() const noexcept { return get(0); }

    //==============================================================================================
    //! @brief Slice a eve::wide into two eve::wide of half cardinal.
    //! Does not participate in overload resolution if `Cardinal::value == 1`.
    //!
    //! **Example:**
    //!
    //! @code
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the wide [1 ... N]
    //!   eve::wide<int> r = [](auto i, auto c) { return i + 1;};
    //!   std::cout << r << "\n";
    //!
    //!   auto[lo,hi] = r.slice();
    //!   std::cout << lo << " " << hi << "\n";
    //! }
    //! @endcode
    //!
    //==============================================================================================
    EVE_FORCEINLINE auto slice() const requires(Cardinal::value > 1)
    {
      return detail::slice(*this);
    }

    //==============================================================================================
    //! @brief Return the upper or lower half-sized slice of a eve::wide.
    //! Does not participate in overload resolution if `Cardinal::value == 1`.
    //!
    //! @see eve::upper_
    //! @see eve::lower_
    //!
    //! @param s A tag indicating which slice is required
    //!
    //! **Example:**
    //!
    //! @code
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the wide [1 ... N]
    //!   eve::wide<int> r = [](auto i, auto c) { return i + 1;};
    //!   std::cout << r << "\n";
    //!
    //!   auto lo = r.slice(eve::lower_);
    //!   auto hi = r.slice(eve::upper_);
    //!   std::cout << lo << " " << hi << "\n";
    //! }
    //! @endcode
    //
    //==============================================================================================
    template<std::size_t Slice>
    EVE_FORCEINLINE auto slice(slice_t<Slice> s) const requires(Cardinal::value > 1)
    {
      return detail::slice(*this, s);
    }

    //! Exchange this value with another eve::wide
    void swap(wide& other) { std::swap(this->storage(), other.storage()); }

    //! Pre-incrementation operator
    EVE_FORCEINLINE wide& operator++() noexcept
    {
      return *this += wide{1};
    }

    //! Pre-decrementation operator
    EVE_FORCEINLINE wide& operator--() noexcept
    {
      return *this -= wide{1};
    }

    //! Post-incrementation operator
    EVE_FORCEINLINE wide operator++(int) noexcept
    {
      auto  that(*this);
      this->operator++();
      return that;
    }

    //! Post-decrementation operator
    EVE_FORCEINLINE wide operator--(int) noexcept
    {
      auto  that(*this);
      this->operator--();
      return that;
    }

    //==============================================================================================
    //! @}
    //==============================================================================================
    //! @brief Swaps the contents of `lhs` and `rhs` by calling `lhs.swap(rhs)`.
    friend EVE_FORCEINLINE void swap(wide& lhs, wide& rhs) noexcept { lhs.swap(rhs); }

    //==============================================================================================
    //! @name Indexing and reordering
    //! @{
    //=============================================================================================

    //! @brief Size of the wide in number of lanes
    static EVE_FORCEINLINE constexpr size_type size() noexcept { return Cardinal::value; }

    //! @brief Maximal number of lanes for a given wide
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return Cardinal::value; }

    //! @brief Check if a wide contains 0 lanes
    static EVE_FORCEINLINE constexpr bool empty() noexcept { return false; }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    // Bitwise operators
    //==============================================================================================

    //! @brief Performs a bitwise complement on all the wide lanes
    friend EVE_FORCEINLINE wide operator~(wide const& v) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type>)
#endif
    {
      return bit_not(v);
    }

    //! @brief Performs a compound bitwise and on all the wide lanes and assign the result to the current
    //! one
    template<value V>
    friend EVE_FORCEINLINE wide& operator&=(wide& w, V o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires (!kumi::product_type<Type> && supports_bitwise_call<wide, V>)
#endif
    {
      w = bit_and(w, o);
      return w;
    }

    //! @brief Performs a bitwise and between all lanes of two wide instances.
    //! Do not participate to overload resolution if both wide doesnot have the same `sizeof`
    template<scalar_value U, typename M>
    friend EVE_FORCEINLINE wide operator&(wide const& a, wide<U, M> const& b) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires (!kumi::product_type<Type> && supports_bitwise_call<wide, wide<U, M>>)
#endif
    {
      return bit_and(a, b);
    }

    //! @brief Performs a bitwise and between all lanes of a eve::wide and a scalar
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE wide operator&(wide const& w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && supports_bitwise_call<wide, S>)
#endif
    {
      return bit_and(w, bit_cast(s, as<Type> {}));
    }

    //! @brief Performs a bitwise and between all lanes of a scalar and a eve::wide
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE wide<S, Cardinal> operator&(S s, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && supports_bitwise_call<S, wide>)
#endif
    {
      return bit_and(bit_cast(w, as<wide<S, Cardinal>>()), s);
    }

    //! @brief Performs a Compound bitwise or on all the wide lanes and assign the result to the current
    //! one
    template<value V>
    friend EVE_FORCEINLINE wide& operator|=(wide& w, V o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && supports_bitwise_call<wide, V>)
#endif
    {
      w = bit_or(w, o);
      return w;
    }

    //! @brief Performs a bitwise or between all lanes of two wide instances.
    //! Do not participate to overload resolution if both wide doesn't has the same `sizeof`
    template<scalar_value U, typename M>
    friend EVE_FORCEINLINE wide operator|(wide const& a, wide<U, M> const& b) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && supports_bitwise_call<wide, wide<U, M>>)
#endif
    {
      return bit_or(a, b);
    }

    //! @brief Performs a bitwise or between all lanes of a scalar and a eve::wide
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE wide operator|(wide const& w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && supports_bitwise_call<wide, S>)
#endif
    {
      return bit_or(w, bit_cast(s, as<Type>{}));
    }

    //! @brief Performs a bitwise or between all lanes of a scalar and a eve::wide
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE wide<S, Cardinal> operator|(S s, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && supports_bitwise_call<S, wide>)
#endif
    {
      return bit_or(bit_cast(w, as<wide<S, Cardinal>>{}), s);
    }

    //! @brief Performs a bitwise xor on all the wide lanes and assign the result to the current one
    template<value V>
    friend EVE_FORCEINLINE wide& operator^=(wide& w, V o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && supports_bitwise_call<wide, V>)
#endif
    {
      w = bit_xor(w, o);
      return w;
    }

    //! @brief Performs a bitwise xor between all lanes of two wide instances.
    //! Do not participate to overload resolution if both wide doesn't has the same `sizeof`
    template<scalar_value U, typename M>
    friend EVE_FORCEINLINE wide operator^(wide const& a, wide<U, M> const& b) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && supports_bitwise_call<wide, wide<U, M>>)
#endif
    {
      return bit_xor(a, b);
    }

    //! @brief Performs a bitwise xor between all lanes of a scalar and a eve::wide
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE wide operator^(wide const& w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && supports_bitwise_call<wide, S>)
#endif
    {
      return bit_xor(w, bit_cast(s, as<Type>{}));
    }

    //! @brief Performs a bitwise xor between all lanes of a scalar and a eve::wide
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE wide<S, Cardinal> operator^(S s, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && supports_bitwise_call<S, wide>)
#endif
    {
      return bit_xor(bit_cast(w, as<wide<S, Cardinal>>()), s);
    }

    //==============================================================================================
    // Arithmetic operators
    //==============================================================================================
    //! Unary plus operator
    friend EVE_FORCEINLINE wide operator+(wide const& v) noexcept { return v; }

    //! Unary minus operator. See also: eve::minus
    friend EVE_FORCEINLINE wide operator-(wide const& v) noexcept
        requires(!kumi::product_type<Type>)
    {
      return minus(v);
    }

    //! @brief Performs the compound addition on all the wide lanes and assign the result
    //! to the current one. See also: eve::add
    template<value V>
    friend EVE_FORCEINLINE wide& operator+=(wide& w, V v) noexcept
      requires(!kumi::product_type<Type>)
    {
      w = add(w, v);
      return w;
    }

    //! @brief Performs the addition between all lanes of its parameters
    //! See also: eve::add
    friend EVE_FORCEINLINE wide operator+(wide const& a, wide const& b) noexcept
    requires(!kumi::product_type<Type>)
    {
      return add(a, b);
    }

    //! @brief Performs the addition between a scalar and all lanes of a eve::wide
    //! See also: eve::add
    friend EVE_FORCEINLINE wide operator+(plain_scalar_value auto s, wide const& v) noexcept
    requires(!kumi::product_type<Type>)
    {
      return add(v, wide{s});
    }

    //! @brief Performs the addition between all lanes of a eve::wide and a scalar
    //! See also: eve::add
    friend EVE_FORCEINLINE wide operator+(wide const& v, plain_scalar_value auto s) noexcept
    requires(!kumi::product_type<Type>)
    {
      return add(v, wide{s});
    }

    //! @brief Performs the compound difference on all the wide lanes and assign
    //! the result to the current one. See also: eve::sub
    template<value V>
    friend EVE_FORCEINLINE wide& operator-=(wide& w, V v) noexcept
      requires(!kumi::product_type<Type>)
    {
      w = sub(w, v);
      return w;
    }

    //! @brief Performs the difference between all lanes of its parameters
    //! See also: eve::sub
    friend EVE_FORCEINLINE wide operator-(wide const& a, wide const& b) noexcept
    requires(!kumi::product_type<Type>)
    {
      return sub(a, b);
    }

    //! @brief Performs the difference between a scalar and all lanes of a eve::wide
    //! See also: eve::sub
    friend EVE_FORCEINLINE wide operator-(plain_scalar_value auto s, wide const& w) noexcept
        requires(!kumi::product_type<Type>)
    {
      return sub(wide{s}, w);
    }

    //! @brief Performs the difference between all lanes of a eve::wide and a scalar
    //! See also: eve::sub
    friend EVE_FORCEINLINE wide operator-(wide const& w, plain_scalar_value auto s) noexcept
        requires(!kumi::product_type<Type>)
    {
      return sub(w, wide{s});
    }

    //! @brief Performs the compound product on all the wide lanes and assign
    //! the result to the current one. See also: eve::mul
    template<value V>
    friend EVE_FORCEINLINE wide& operator*=(wide& w, V o) noexcept
        requires(!kumi::product_type<Type>)
    {
      w = mul(w, o);
      return w;
    }

    //! @brief Performs the product between all lanes of its parameters
    //! See also: eve::mul
    friend EVE_FORCEINLINE wide operator*(wide const& a, wide const& b) noexcept
      requires(!kumi::product_type<Type>)
    {
      return mul(a, b);
    }

    //! @brief Performs the product between a scalar and all lanes of a eve::wide
    //! See also: eve::mul
    friend EVE_FORCEINLINE wide operator*(plain_scalar_value auto s, wide const& w) noexcept
        requires(!kumi::product_type<Type>)
    {
      return mul(s, w);
    }

    //! @brief Performs the product between all lanes of a eve::wide and a scalar
    //! See also: eve::mul
    friend EVE_FORCEINLINE wide operator*(wide const& w, plain_scalar_value auto s) noexcept
      requires(!kumi::product_type<Type>)
    {
      return mul(w, s);
    }

    //! @brief Performs the compound division on all the wide lanes and assign
    //! the result to the current one. See also: eve::div
    template<value V>
    friend EVE_FORCEINLINE wide& operator/=(wide& w, V o) noexcept
        requires(!kumi::product_type<Type>)
    {
      w = div(w, o);
      return w;
    }

    //! @brief Performs the division between all lanes of its parameters
    //! See also: eve::div
    friend EVE_FORCEINLINE wide operator/(wide const& a, wide const& b) noexcept
        requires(!kumi::product_type<Type>)
    {
      return div(a, b);
    }

    //! @brief Performs the division between a scalar and all lanes of a eve::wide
    //! See also: eve::div
    friend EVE_FORCEINLINE wide operator/(plain_scalar_value auto s, wide const& w) noexcept
        requires(!kumi::product_type<Type>)
    {
      return div(wide{s}, w);
    }

    //! @brief Performs the division between all lanes of a eve::wide and a scalar
    //! See also: eve::div
    friend EVE_FORCEINLINE wide operator/(wide const& v, plain_scalar_value auto s) noexcept
        requires(!kumi::product_type<Type>)
    {
      return div(v, wide{s});
    }

    //! @brief Performs the compound modulo on all the wide lanes and assign
    //! the result to the current one. Does not participate in overload resolution
    //! if `Type` does not models integral_scalar_value
    template<integral_value V>
    friend EVE_FORCEINLINE wide& operator%=(wide& w, V o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && integral_scalar_value<Type>)
#endif
    {
      w = rem(w, o);
      return w;
    }

    //! @brief Performs the modulo between all lanes of its parameters.
    //! Does not participate in overload resolution if `Type` does not models
    //! integral_scalar_value
    friend EVE_FORCEINLINE wide operator%(wide const& a, wide const& b) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && integral_scalar_value<Type>)
#endif
    {
      return rem(a, b);
    }

    //! @brief Performs the modulo between a scalar and all lanes of a eve::wide
    //! Does not participate in overload resolution if `Type` does not models
    //! integral_scalar_value
    template<integral_scalar_value S>
    friend EVE_FORCEINLINE auto operator%(S s, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && integral_scalar_value<Type>)
#endif
    {
      return rem(wide{s}, w);
    }

    //! @brief Performs the modulo between all lanes of a eve::wide and a scalar
    //! Does not participate in overload resolution if `Type` does not models
    //! integral_scalar_value
    friend EVE_FORCEINLINE auto operator%(wide const& w, integral_scalar_value auto s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type> && integral_scalar_value<Type>)
#endif
    {
      return rem(w, wide{s});
    }

    //! @brief Performs the compound left-shift on all the eve::wide lanes and assign
    //! the result to current one.
    template<integral_value S>
    friend EVE_FORCEINLINE wide& operator<<=(wide& w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type>)
#endif
    {
      w = shl(w, s);
      return w;
    }

    //! @brief Performs the compound left-shift on all the eve::wide lanes with a constant and assign
    //! the result to current one.
    template<std::ptrdiff_t V>
    friend EVE_FORCEINLINE wide& operator<<=(wide& w, index_t<V> const& s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type>)
#endif
    {
      w = shl(w, s);
      return w;
    }

    //! @brief Performs the left-shift between all lanes of a eve::wide and an integral scalar.
    template<integral_value S>
    friend EVE_FORCEINLINE wide operator<<(wide w, S s) noexcept
    {
      return shl(w, s);
    }

    //! @brief Performs the left-shift between all lanes of a eve::wide and an integral constant.
    template<std::ptrdiff_t V>
    friend EVE_FORCEINLINE wide operator<<(wide w, index_t<V> const& s) noexcept
    {
      return shl(w, s);
    }

    //! @brief Performs the compound right-shift on all the eve::wide lanes and assign
    //! the result to current one.
    template<integral_value S>
    friend EVE_FORCEINLINE wide& operator>>=(wide& w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type>)
#endif
    {
      w = shr(w, s);
      return w;
    }

    //! @brief Performs the compound right-shift on all the eve::wide lanes and assign
    //! the result to current one.
    template<std::ptrdiff_t V>
    friend EVE_FORCEINLINE wide& operator>>=(wide& w, index_t<V> const& s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type>)
#endif
    {
      w = shr(w, s);
      return w;
    }

    //! @brief Performs the right-shift between all lanes of a eve::wide and an integral scalar.
    template<integral_value S>
    friend EVE_FORCEINLINE wide operator>>(wide w, S s) noexcept
    {
      return shr(w, s);
    }

    //! @brief Performs the right-shift between all lanes of a eve::wide and an integral constant.
    template<std::ptrdiff_t V>
    friend EVE_FORCEINLINE auto operator>>(wide w, index_t<V> const& s) noexcept
    {
      return shr(w, s);
    }

    //==============================================================================================
    // Logical operations
    //==============================================================================================
    //! @brief Element-wise equality comparison of two eve::wide
    friend EVE_FORCEINLINE auto operator==(wide v, wide w) noexcept
    {
      return detail::self_eq(v, w);
    }

    //! @brief Element-wise equality comparison of a eve::wide and a scalar value
    template<scalar_value S>
    requires requires(S s) { wide {s}; }
    friend EVE_FORCEINLINE auto operator==(wide v, S w) noexcept { return v == wide {w}; }

    //! @brief Element-wise equality comparison of a scalar value and a eve::wide
    template<scalar_value S>
    requires requires(S s) { wide {s}; }
    friend EVE_FORCEINLINE auto operator==(S v, wide w) noexcept { return w == v; }

    //! @brief Element-wise inequality comparison of two eve::wide
    friend EVE_FORCEINLINE auto operator!=(wide v, wide w) noexcept
    {
      return detail::self_neq(v, w);
    }

    //! @brief Element-wise inequality comparison of a eve::wide and a scalar value
    template<scalar_value S>
    requires requires(S s) { wide {s}; }
    friend EVE_FORCEINLINE auto operator!=(wide v, S w) noexcept { return v != wide {w}; }

    //! @brief Element-wise inequality comparison of a scalar value and a eve::wide
    template<scalar_value S>
    requires requires(S s) { wide {s}; }
    friend EVE_FORCEINLINE auto operator!=(S v, wide w) noexcept { return w != v; }

    //! @brief Element-wise less-than comparison between eve::wide
    friend EVE_FORCEINLINE auto operator<(wide a, wide b) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_less(a, b);
    }

    //! @brief Element-wise less-than comparison between a eve::wide and a scalar
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator<(wide w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_less(w, s);
    }

    //! @brief Element-wise less-than comparison between a scalar and a eve::wide
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator<(S s, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_less(s, w);
    }

    //! @brief Element-wise greater-than comparison between eve::wide
    friend EVE_FORCEINLINE auto operator>(wide a, wide b) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_greater(a, b);
    }

    //! @brief Element-wise greater-than comparison between a eve::wide and a scalar
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator>(wide w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_greater(w, s);
    }

    //! @brief Element-wise greater-than comparison between a scalar and a eve::wide
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator>(S s, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_greater(s, w);
    }

    //! @brief Element-wise greater-or-equal comparison between eve::wide
    friend EVE_FORCEINLINE auto operator>=(wide a, wide b) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_greater_equal(a, b);
    }

    //! @brief Element-wise greater-or-equal comparison between a eve::wide and a scalar
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator>=(wide w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_greater_equal(w, s);
    }

    //! @brief Element-wise greater-or-equal comparison between a scalar and a eve::wide
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator>=(S s, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_greater_equal(s, w);
    }

    //! @brief Element-wise less-or-equal comparison between eve::wide
    friend EVE_FORCEINLINE auto operator<=(wide a, wide b) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_less_equal(a, b);
    }

    //! @brief Element-wise less-or-equal comparison between a eve::wide and a scalar
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator<=(wide w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_less_equal(w, s);
    }

    //! @brief Element-wise less-or-equal comparison between a scalar and a eve::wide
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator<=(S s, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(supports_ordering_v<Type>)
#endif
    {
      return is_less_equal(s, w);
    }

    //! Computes the logical negation of its parameter
    friend EVE_FORCEINLINE logical<wide> operator!(wide v) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
        requires(!kumi::product_type<Type>)
#endif
    {
      return logical_not(v);
    }

    //! Inserts a eve::wide into a output stream
    friend std::ostream& operator<<(std::ostream& os, wide p)
    {
      if constexpr( kumi::product_type<Type> )
      {
        if constexpr( requires(Type t) { os << t; } )
        {
          // If said product_type is streamable, we stream each parts
          os << '(' << p.get(0);
          for( size_type i = 1; i != p.size(); ++i ) os << ", " << p.get(i);
          return os << ')';
        }
        else
        {
          // Else we just stream the internal tuple
          return os << p.storage();
        }
      }
      else
      {
        constexpr auto sz   = sizeof(storage_type) / sizeof(Type);
        auto           that = bit_cast(p, as<std::array<Type, sz>>());

        auto as_printable = [](Type v)
        {
          if constexpr (std::same_as<translate_t<Type>, eve::float16_t>) return static_cast<float>(translate(v));
          else if constexpr (std::integral<Type> && sizeof(Type) == 1) return +v;
          else if constexpr (requires { os << v; })                    return v;
          else                                                         return translate(v);
        };

        os << '(' << as_printable(that[0]);
        for( size_type i = 1; i != p.size(); ++i ) os << ", " << as_printable(that[i]);
        return os << ')';
      }
    }
  };
  //================================================================================================
  //! @}
  //================================================================================================

  //====================================================================================================================
  //! @name Deduction Guides
  //! @{
  //====================================================================================================================

  /// Allows deduction from a single eve::scalar_value
  template<scalar_value S> wide(S const&) -> wide<S, expected_cardinal_t<S>>;

  /// Allows deduction from variadic pack of eve::scalar_value
  template<scalar_value S, std::same_as<S>... Ss>
  wide(S, Ss...) -> wide<S,fixed<1+sizeof...(Ss)>>;

  //====================================================================================================================
  //! @}
  //====================================================================================================================

  //==============================================================================================
  // Product type Support
  //==============================================================================================
  template<std::size_t I, kumi::product_type T, typename N>
  EVE_FORCEINLINE auto& get(wide<T, N>& w) noexcept
  {
    return kumi::get<I>(w.storage());
  }

  template<std::size_t... Idx, kumi::product_type T, typename N>
#if !defined(EVE_DOXYGEN_INVOKED)
  requires((Idx < kumi::size<T>::value) && ...)
#endif
      EVE_FORCEINLINE auto get(eve::wide<T, N> const& w) noexcept
  {
    if constexpr( sizeof...(Idx) == 1 ) { return kumi::get<Idx...>(w.storage()); }
    else
    {
      using U = kumi::tuple<std::tuple_element_t<Idx, T>...>;
      return eve::wide<U, N>(get<Idx>(w)...);
    }
  }

#if !defined(EVE_DOXYGEN_INVOKED)
}
}
#else
}
#endif

#if !defined(EVE_DOXYGEN_INVOKED)
//================================================================================================
// Product type Support
//================================================================================================
template<typename T, typename N>
struct kumi::is_product_type<eve::wide<T, N>> : kumi::is_product_type<T>
{};

template<std::size_t I, kumi::product_type T, typename N>
struct std::tuple_element<I, eve::wide<T, N>>
    : std::tuple_element<I, typename eve::wide<T, N>::storage_type>
{};

template<kumi::product_type T, typename N>
struct std::tuple_size<eve::wide<T, N>> : std::tuple_size<typename eve::wide<T, N>::storage_type>
{};
#endif
