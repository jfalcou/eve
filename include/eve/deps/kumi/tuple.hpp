//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
namespace kumi
{
}
namespace kumi
{
  template<typename T> struct as
  {
    using type = T;
    constexpr as() noexcept {}
    explicit constexpr as(T const&) noexcept {}
  };
  template<> struct as<void>
  {
    using type = void;
    constexpr as() noexcept {}
  };
}
#include <cstddef>
#if defined(_MSC_VER)
#if _MSVC_LANG < 202002L
#error "Kumi requires C++20 or higher. Use /std:c++20 or higher to enable C++20 features."
#endif
#else
#if __cplusplus < 202002L
#error "KUMI requires C++20 or higher. Use -std=c++20 or higher to enable C++20 features."
#endif
#endif
#define KUMI_FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#if defined(__CUDACC__)
#define KUMI_CUDA __host__ __device__
#else
#define KUMI_CUDA
#endif
#if defined(KUMI_DEBUG)
#define KUMI_ABI
#elif defined(__GNUC__) ||                                                                                             \
  defined(__clang__)
#define KUMI_ABI [[using gnu: always_inline, flatten, artificial]] KUMI_CUDA inline
#elif defined(_MSC_VER)
#define KUMI_ABI [[using msvc: forceinline, flatten]] KUMI_CUDA inline
#endif
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wmissing-braces"
#endif
#include <iosfwd>
#include <utility>
namespace kumi
{
  struct str
  {
    static constexpr std::size_t max_size = 64;
    char data_[max_size + 1];
    unsigned int size_;
    template<std::size_t N, std::size_t... Is>
    requires(N <= max_size)
    constexpr str(char const (&s)[N], std::index_sequence<Is...>) : data_{s[Is]...}, size_(N - 1)
    {
    }
    template<std::size_t N>
    requires(N <= max_size)
    constexpr str(char const (&s)[N]) : str{s, std::make_index_sequence<N>{}}
    {
    }
    KUMI_ABI constexpr std::size_t size() const noexcept { return size_; }
    KUMI_ABI constexpr auto data() const noexcept { return data_; }
    template<typename T>
    requires requires { T{data_, size_}; }
    KUMI_ABI constexpr auto as() const
    {
      return T{data_, size_};
    }
    KUMI_ABI friend constexpr auto operator<=>(str const&, str const&) noexcept = default;
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, str const& s) noexcept
    {
      os << '\'';
      for (std::size_t i = 0; i < s.size(); ++i) os << s.data_[i];
      return os << '\'';
    }
  };
  template<str... Strs>
  requires((Strs.size() + ... + sizeof...(Strs)) < str::max_size)
  [[nodiscard]] KUMI_ABI constexpr auto concatenate_str()
  {
    constexpr auto nb_strs = sizeof...(Strs);
    struct
    {
      unsigned int count = {};
      char t[(Strs.size() + ... + sizeof...(Strs))];
    } that;
    auto fill = [&]<std::size_t... N>(str current, std::index_sequence<N...>) {
      ((that.t[that.count++] = current.data_[N]), ...);
    };
    [&]<std::size_t... I>(std::index_sequence<I...>) {
      ((fill(Strs, std::make_index_sequence<Strs.size()>{}),
        (I + 1 < nb_strs ? (that.t[that.count++] = '.', 0) : (that.t[that.count++] = '\0', 0))),
       ...);
    }(std::make_index_sequence<nb_strs>{});
    return str{that.t};
  };
}
#include <iosfwd>
namespace kumi::_
{
  template<typename T> auto make_streamable(T const& e)
  {
    if constexpr (requires(std::ostream& os) { os << e; }) return e;
    else if constexpr (requires { as_streamable(e); }) return as_streamable(e);
    else return "(unknown)";
  }
}
namespace kumi
{
  template<str ID, typename T> struct field_capture
  {
    using type = T;
    T value;
    static constexpr auto name = ID;
    static constexpr bool is_field_capture = true;
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         field_capture const& w) noexcept
    {
      return os << ID << " : " << _::make_streamable(w.value);
    }
  };
  namespace _
  {
    template<kumi::str ID, typename T> KUMI_ABI constexpr T& get_field(field_capture<ID, T>& a) noexcept
    {
      return a.value;
    }
    template<kumi::str ID, typename T> KUMI_ABI constexpr T&& get_field(field_capture<ID, T>&& a) noexcept
    {
      return static_cast<T&&>(a.value);
    }
    template<kumi::str ID, typename T> KUMI_ABI constexpr T const&& get_field(field_capture<ID, T> const&& a) noexcept
    {
      return static_cast<T const&&>(a.value);
    }
    template<kumi::str ID, typename T> KUMI_ABI constexpr T const& get_field(field_capture<ID, T> const& a) noexcept
    {
      return a.value;
    }
  }
  template<str Name, typename T> [[nodiscard]] KUMI_ABI constexpr decltype(auto) capture_field(T&& t) noexcept
  {
    return field_capture<Name, T>{KUMI_FWD(t)};
  }
  template<typename U, typename T> [[nodiscard]] KUMI_ABI constexpr decltype(auto) field_cast(T&& t) noexcept
  {
    using W = std::remove_cvref_t<U>;
    if constexpr (requires { W::is_field_capture; })
      return field_capture<name_of(as<T>{}), typename W::type>{
        static_cast<typename W::type>(field_value_of(KUMI_FWD(t)))};
    else if constexpr (!requires { std::remove_cvref_t<T>::is_field_capture; })
      return static_cast<typename W::type>(KUMI_FWD(t));
    else return field_capture<name_of(as<T>{}), U>{static_cast<U>(field_value_of(KUMI_FWD(t)))};
  }
  namespace result
  {
    template<str Name, typename T> struct capture_field
    {
      using type = decltype(kumi::capture_field<Name>(std::declval<T>()));
    };
    template<typename U, typename T> struct field_cast
    {
      using type = decltype(kumi::field_cast<U, T>(std::declval<T>()));
    };
    template<str Name, typename T> using capture_field_t = typename capture_field<Name, T>::type;
    template<typename U, typename T> using field_cast_t = typename field_cast<U, T>::type;
  }
}
#include <iosfwd>
#include <cstddef>
#include <utility>
namespace kumi::_
{
  template<int I, typename T> struct leaf
  {
    T value;
  };
  template<int I, kumi::str Name, typename T> struct leaf<I, field_capture<Name, T>>
  {
    field_capture<Name, T> value;
  };
  template<int I, typename T> KUMI_ABI constexpr T& get_leaf(leaf<I, T>& a) noexcept
  {
    return a.value;
  }
  template<int I, typename T> KUMI_ABI constexpr T&& get_leaf(leaf<I, T>&& a) noexcept
  {
    return static_cast<T&&>(a.value);
  }
  template<int I, typename T> KUMI_ABI constexpr T const&& get_leaf(leaf<I, T> const&& a) noexcept
  {
    return static_cast<T const&&>(a.value);
  }
  template<int I, typename T> KUMI_ABI constexpr T const& get_leaf(leaf<I, T> const& a) noexcept
  {
    return a.value;
  }
  template<typename T, int I> KUMI_ABI constexpr T& get_leaf(leaf<I, T>& a) noexcept
  {
    return a.value;
  }
  template<typename T, int I> KUMI_ABI constexpr T&& get_leaf(leaf<I, T>&& a) noexcept
  {
    return static_cast<T&&>(a.value);
  }
  template<typename T, int I> KUMI_ABI constexpr T const&& get_leaf(leaf<I, T> const&& a) noexcept
  {
    return static_cast<T const&&>(a.value);
  }
  template<typename T, int I> KUMI_ABI constexpr T const& get_leaf(leaf<I, T> const& a) noexcept
  {
    return a.value;
  }
  template<kumi::str Name, int I, typename T>
  KUMI_ABI constexpr T& get_leaf(leaf<I, field_capture<Name, T>>& a) noexcept
  {
    return a.value.value;
  }
  template<kumi::str Name, int I, typename T>
  KUMI_ABI constexpr T&& get_leaf(leaf<I, field_capture<Name, T>>&& a) noexcept
  {
    return static_cast<T&&>(a.value.value);
  }
  template<kumi::str Name, int I, typename T>
  KUMI_ABI constexpr T const&& get_leaf(leaf<I, field_capture<Name, T>> const&& a) noexcept
  {
    return static_cast<T const&&>(a.value.value);
  }
  template<kumi::str Name, int I, typename T>
  KUMI_ABI constexpr T const& get_leaf(leaf<I, field_capture<Name, T>> const& a) noexcept
  {
    return a.value.value;
  }
  template<typename ISeq, typename... Ts> struct binder;
  template<int... Is, typename... Ts> struct binder<std::integer_sequence<int, Is...>, Ts...> : leaf<Is, Ts>...
  {
    static constexpr bool is_homogeneous = false;
  };
  template<typename ISeq, typename... Ts> struct make_binder
  {
    using type = binder<ISeq, Ts...>;
  };
  template<typename ISeq, typename... Ts> using make_binder_t = typename make_binder<ISeq, Ts...>::type;
}
#include <cstddef>
#include <utility>
#include <concepts>
#if defined(__ANDROID__) || defined(__APPLE__)
#include <type_traits>
namespace kumi
{
  template<typename From, typename To>
  concept convertible_to = std::is_convertible_v<From, To> && requires { static_cast<To>(std::declval<From>()); };
}
#else
#include <concepts>
namespace kumi
{
  using std::convertible_to;
}
#endif
#include <cstddef>
#include <type_traits>
#include <utility>
#include <cstddef>
namespace kumi::_
{
  template<auto NTTP> struct value_as
  {
    using type = decltype(NTTP);
    static constexpr auto value = NTTP;
  };
  template<std::size_t I, typename T> consteval auto make_value_as()
  {
    if constexpr (requires { std::remove_cvref_t<T>::is_field_capture; }) return value_as<name_of(as<T>{})>{};
    else return value_as<I>{};
  }
  template<std::size_t, typename T> struct unique
  {
    operator T();
  };
  template<std::size_t I, typename T> struct unique_name
  {
    operator value_as<I>();
  };
  template<std::size_t I, kumi::str Name, typename T> struct unique_name<I, kumi::field_capture<Name, T>>
  {
    operator value_as<Name>();
  };
  inline std::true_type true_fn(...);
}
namespace kumi
{
  namespace _
  {
    template<typename T>
    concept non_empty_tuple = requires(T const& t) {
      typename std::tuple_element<0, std::remove_cvref_t<T>>::type;
      typename std::tuple_size<std::remove_cvref_t<T>>::type;
    };
    template<typename T>
    concept empty_tuple = (std::tuple_size<std::remove_cvref_t<T>>::value == 0);
    template<typename T>
    concept std_tuple_compatible = _::empty_tuple<T> || _::non_empty_tuple<T>;
    template<typename T>
    concept container_like = requires(T const& t) {
      typename T::value_type;
      typename T::size_type;
      { t.size() } -> kumi::convertible_to<std::size_t>;
      { t.begin() };
      { t.end() };
      { t.data() };
    };
  }
  template<typename T> struct is_product_type : std::false_type
  {
  };
  template<typename T> inline constexpr auto is_product_type_v = is_product_type<T>::value;
  template<typename T, typename Enable = void> struct is_record_type : std::false_type
  {
  };
  template<typename T> struct is_record_type<T, typename T::is_record_type> : std::true_type
  {
  };
  template<typename T> inline constexpr auto is_record_type_v = is_record_type<T>::value;
  template<typename T> struct size : std::tuple_size<T>
  {
  };
  template<typename T> struct size<T&> : size<T>
  {
  };
  template<typename T> struct size<T&&> : size<T>
  {
  };
  template<typename T> struct size<T const> : size<T>
  {
  };
  template<typename T> struct size<T const&> : size<T>
  {
  };
  template<typename T> struct size<T const&&> : size<T>
  {
  };
  template<typename T> inline constexpr auto size_v = size<T>::value;
  template<std::size_t I, typename T> struct element : std::tuple_element<I, T>
  {
  };
  template<std::size_t I, typename T> struct element<I, T&> : element<I, T>
  {
  };
  template<std::size_t I, typename T> struct element<I, T&&> : element<I, T>
  {
  };
  template<std::size_t I, typename T> struct element<I, T const&> : element<I, T>
  {
  };
  template<std::size_t I, typename T> struct element<I, T const&&> : element<I, T>
  {
  };
  template<std::size_t I, typename T> using element_t = typename element<I, T>::type;
  template<std::size_t I, typename T> struct member
  {
    using type = decltype(get<I>(std::declval<T&&>()));
  };
  template<std::size_t I, typename T> using member_t = typename member<I, T>::type;
}
namespace kumi
{
  template<typename T> struct is_static_container : std::false_type
  {
  };
  template<template<class, std::size_t> typename Container, typename T, std::size_t N>
  requires _::container_like<Container<T, N>> && (N != static_cast<std::size_t>(-1))
  struct is_static_container<Container<T, N>> : std::true_type
  {
    using value_type = T;
    using size = std::integral_constant<std::size_t, N>;
  };
  template<typename T> inline constexpr auto is_static_container_v = is_static_container<T>::value;
  template<typename T> struct container_size : is_static_container<T>::size
  {
  };
  template<typename T> struct container_size<T&> : container_size<T>
  {
  };
  template<typename T> struct container_size<T&&> : container_size<T>
  {
  };
  template<typename T> struct container_size<T const&> : container_size<T>
  {
  };
  template<typename T> struct container_size<T const&&> : container_size<T>
  {
  };
  template<typename T> inline constexpr auto container_size_v = container_size<T>::value;
  template<typename T> struct container_type : is_static_container<T>::value_type
  {
  };
  template<typename T> struct container_type<T&> : container_type<T>
  {
  };
  template<typename T> struct container_type<T&&> : container_type<T>
  {
  };
  template<typename T> struct container_type<T const&> : container_type<T>
  {
  };
  template<typename T> struct container_type<T const&&> : container_type<T>
  {
  };
  template<typename T> using container_type_t = typename container_type<T>::type;
}
namespace kumi
{
  template<typename T> struct is_homogeneous;
  template<typename T>
  requires(requires { T::is_homogeneous; })
  struct is_homogeneous<T> : std::bool_constant<T::is_homogeneous>
  {
  };
  template<typename T> inline constexpr auto is_homogeneous_v = is_homogeneous<T>::value;
  template<typename T> inline constexpr auto is_index_map_v = requires { T::is_index_map; };
  template<typename T> struct is_index_map : std::bool_constant<is_index_map_v<T>>
  {
  };
  template<typename T> inline constexpr bool is_field_capture_v = requires { T::is_field_capture; };
  template<typename T> struct is_field_capture : std::bool_constant<is_field_capture_v<T>>
  {
  };
  template<std::size_t I, typename T> struct raw_member
  {
    using type = member_t<I, T>;
  };
  template<std::size_t I, typename T>
  requires(is_record_type<std::remove_cvref_t<T>>::value)
  struct raw_member<I, T>
  {
    using type = decltype(field_value_of(get<I>(std::declval<T&&>())));
  };
  template<std::size_t I, typename T> using raw_member_t = typename raw_member<I, T>::type;
  template<std::size_t I, typename T> struct raw_element
  {
    using type = element_t<I, T>;
  };
  template<std::size_t I, typename T>
  requires(is_record_type<std::remove_cvref_t<T>>::value)
  struct raw_element<I, T>
  {
    using type = typename element_t<I, T>::type;
  };
  template<std::size_t I, typename T> using raw_element_t = typename raw_element<I, T>::type;
  template<typename Ints, typename... Ts> struct all_uniques;
  template<> struct all_uniques<std::index_sequence<>>
  {
    using type = std::true_type;
  };
  template<std::size_t... Ints, typename... Ts> struct all_uniques<std::index_sequence<Ints...>, Ts...>
  {
    struct all_uniques_inner : _::unique<Ints, Ts>...
    {
    };
    template<typename... Us> static auto is_set(Us...) -> decltype(_::true_fn(static_cast<Us>(all_uniques_inner())...));
    static std::false_type is_set(...);
    using type = decltype(is_set(as<Ts>{}...));
  };
  template<typename... Ts> using all_uniques_t = typename all_uniques<std::index_sequence_for<Ts...>, Ts...>::type;
  template<typename... Ts> inline constexpr auto all_uniques_v = all_uniques_t<Ts...>::value;
  template<typename Ints, typename... Ts> struct all_unique_names;
  template<> struct all_unique_names<std::index_sequence<>>
  {
    using type = std::true_type;
  };
  template<std::size_t... Ints, typename... Ts> struct all_unique_names<std::index_sequence<Ints...>, Ts...>
  {
    struct all_uniques_inner : _::unique_name<Ints, Ts>...
    {
    };
    template<typename... Us> static auto is_set(Us...) -> decltype(_::true_fn(static_cast<Us>(all_uniques_inner())...));
    static std::false_type is_set(...);
    using type = decltype(is_set(_::make_value_as<Ints, Ts>()...));
  };
  template<typename... Ts>
  using all_unique_names_t = typename all_unique_names<std::index_sequence_for<Ts...>, Ts...>::type;
  template<typename... Ts> inline constexpr auto all_unique_names_v = all_unique_names_t<Ts...>::value;
  template<typename... Ts> struct tuple;
  template<typename... Ts> struct record;
  template<typename T>
  requires(_::std_tuple_compatible<T>)
  struct is_product_type<T> : std::true_type
  {
  };
  template<typename T>
  requires(is_static_container_v<T> && _::std_tuple_compatible<T>)
  struct is_product_type<T> : std::true_type
  {
  };
}
#include <cstddef>
#include <utility>
namespace kumi::_
{
  template<typename From, typename To> struct is_piecewise_constructible;
  template<typename From, typename To> struct is_piecewise_convertible;
  template<typename From, typename To> struct is_piecewise_ordered;
  template<template<class...> class Box, typename... From, typename... To>
  struct is_piecewise_convertible<Box<From...>, Box<To...>>
  {
    static constexpr bool value = (... && kumi::convertible_to<From, To>);
  };
  template<template<class...> class Box, typename... From, typename... To>
  struct is_piecewise_constructible<Box<From...>, Box<To...>>
  {
    static constexpr bool value = (... && std::is_constructible_v<To, From>);
  };
  template<typename From, typename To>
  concept ordered = requires(From const& a, To const& b) {
    { a < b };
  };
  template<template<class...> class Box, typename... From, typename... To>
  struct is_piecewise_ordered<Box<From...>, Box<To...>>
  {
    static constexpr bool value = (... && ordered<From, To>);
  };
  template<typename From, typename To>
  concept piecewise_convertible =
    (size_v<From> == size_v<To>) &&
    _::is_piecewise_convertible<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename From, typename To>
  concept piecewise_constructible =
    (size_v<From> == size_v<To>) &&
    _::is_piecewise_constructible<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename From, typename To>
  concept piecewise_ordered = _::is_piecewise_ordered<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename T, typename... Args>
  concept implicit_constructible = requires(Args... args) { T{args...}; };
  struct bottom;
  using invalid = std::integral_constant<std::size_t, static_cast<std::size_t>(-1)>;
  template<typename Ref, typename Field> struct check_type
  {
    static consteval Field get(Ref)
    requires std::is_same_v<Field, Ref>;
    static consteval bottom get(...);
  };
  template<std::size_t I, typename Ref, typename Field> struct get_index
  {
    using constant = std::integral_constant<std::size_t, I>;
    static consteval constant get(Ref)
    requires std::is_same_v<Ref, Field>;
    static consteval invalid get(...);
  };
  template<typename Ref, typename... Fields> struct get_field_by_type : check_type<Ref, Fields>...
  {
    using check_type<Ref, Fields>::get...;
    using type = decltype(get(std::declval<Ref>()));
  };
  template<typename Ref, typename Seq, typename... Fields> struct get_index_by_type;
  template<typename Ref, std::size_t... I, typename... Fields>
  struct get_index_by_type<Ref, std::index_sequence<I...>, Fields...> : get_index<I, Ref, Fields>...
  {
    using get_index<I, Ref, Fields>::get...;
    using type = decltype(get(std::declval<Ref>()));
    static constexpr auto value = decltype(get(std::declval<Ref>()))::value;
  };
  template<typename Ref, typename... Fields>
  using get_field_by_type_t = typename get_field_by_type<Ref, Fields...>::type;
  template<typename Ref, typename... Fields>
  inline constexpr auto get_index_by_type_v =
    get_index_by_type<Ref, std::index_sequence_for<Fields...>, Fields...>::value;
  template<typename Ref, typename... Fields>
  concept can_get_field_by_type = !std::is_same_v<get_field_by_type_t<Ref, Fields...>, bottom>;
  template<std::size_t I, typename Ref, typename Field> struct check_name
  {
    using constant = std::integral_constant<std::size_t, I>;
    static consteval Field get(Ref)
    requires(Ref::value == Field::name);
    static consteval bottom get(...);
    static consteval constant get_index(Ref)
    requires(Ref::value == Field::name);
    static consteval invalid get_index(...);
  };
  template<typename Ref, typename Seq, typename... Fields> struct get_field_by_name;
  template<typename Ref, std::size_t... I, typename... Fields>
  struct get_field_by_name<Ref, std::index_sequence<I...>, Fields...> : check_name<I, Ref, Fields>...
  {
    using check_name<I, Ref, Fields>::get...;
    using check_name<I, Ref, Fields>::get_index...;
    using type = decltype(get(std::declval<Ref>()));
    static constexpr auto value = decltype(get_index(std::declval<Ref>()))::value;
  };
  template<typename Ref, typename... Fields>
  using get_field_by_name_t = typename get_field_by_name<Ref, std::index_sequence_for<Fields...>, Fields...>::type;
  template<typename Ref, typename... Fields>
  inline constexpr auto get_index_by_name_v =
    get_field_by_name<Ref, std::index_sequence_for<Fields...>, Fields...>::value;
  template<typename Ref, typename... Fields>
  concept can_get_field_by_name = !std::is_same_v<get_field_by_name_t<Ref, Fields...>, bottom>;
  template<auto Name, typename... Ts> KUMI_ABI constexpr auto contains_field()
  {
    if constexpr (!std::integral<std::remove_cvref_t<decltype(Name)>>)
      return can_get_field_by_name<value_as<Name>, Ts...>;
    else return false;
  };
  template<typename From, typename To> struct is_fieldwise_constructible;
  template<typename From, typename To> struct is_fieldwise_convertible;
  template<template<class...> class Box, typename... From, typename... To>
  struct is_fieldwise_convertible<Box<From...>, Box<To...>>
  {
    static constexpr bool value = ([]() {
      using F_field = std::remove_cvref_t<From>;
      using T_field = std::remove_cvref_t<get_field_by_name_t<value_as<F_field::name>, To...>>;
      return kumi::convertible_to<typename F_field::type, typename T_field::type>;
    }() && ...);
  };
  template<template<class...> class Box, typename... From, typename... To>
  struct is_fieldwise_constructible<Box<From...>, Box<To...>>
  {
    static constexpr bool value = ([]() {
      using F_field = std::remove_cvref_t<From>;
      using T_field = std::remove_cvref_t<get_field_by_name_t<value_as<F_field::name>, To...>>;
      return std::is_constructible_v<typename F_field::type, typename T_field::type>;
    }() && ...);
  };
  template<typename From, typename To>
  concept fieldwise_convertible =
    _::is_fieldwise_convertible<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename From, typename To>
  concept fieldwise_constructible =
    _::is_fieldwise_constructible<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename F, typename T>
  concept supports_apply = []<std::size_t... N>(std::index_sequence<N...>) {
    return std::invocable<F, raw_member_t<N, T>...>;
  }(std::make_index_sequence<size<T>::value>{});
  template<typename F, typename T>
  concept supports_nothrow_apply = []<std::size_t... N>(std::index_sequence<N...>) {
    return std::is_nothrow_invocable<F, raw_member_t<N, T>...>::value;
  }(std::make_index_sequence<size<T>::value>{});
  template<typename F, typename... Ts>
  concept supports_call = []<std::size_t... I>(std::index_sequence<I...>) {
    return ([]<std::size_t J>(std::integral_constant<std::size_t, J>) {
      return std::invocable<F, raw_member_t<J, Ts>...>;
    }(std::integral_constant<std::size_t, I>{}) &&
            ...);
  }(std::make_index_sequence<(size<Ts>::value, ...)>{});
  template<typename T>
  concept supports_transpose =
    (size<T>::value <= 1) || ([]<std::size_t... N>(std::index_sequence<N...>) {
      return ((kumi::size_v<raw_member_t<0, T>> == kumi::size_v<raw_member_t<N + 1, T>>) && ...);
    }(std::make_index_sequence<size<T>::value - 1>{}));
  template<typename T, typename U>
  concept comparable = requires(T t, U u) {
    { t == u };
  };
}
namespace kumi::_
{
  template<typename... Ts> inline constexpr bool no_references = (true && ... && !std::is_reference_v<Ts>);
  template<typename T0, typename... Ts> inline constexpr bool all_the_same = (true && ... && std::is_same_v<T0, Ts>);
  template<typename T0, int N> struct binder_n
  {
    static constexpr bool is_homogeneous = true;
    T0 members[N];
  };
  template<int... Is, typename T0, typename T1, typename... Ts>
  requires(all_the_same<T0, T1, Ts...> && no_references<T0, T1, Ts...>)
  struct make_binder<std::integer_sequence<int, Is...>, T0, T1, Ts...>
  {
    using type = binder_n<T0, 2 + sizeof...(Ts)>;
  };
  template<std::size_t I, typename T0, int N> KUMI_ABI constexpr auto& get_leaf(binder_n<T0, N>& arg) noexcept
  {
    return arg.members[I];
  }
  template<std::size_t I, typename T0, int N>
  KUMI_ABI constexpr auto const& get_leaf(binder_n<T0, N> const& arg) noexcept
  {
    return arg.members[I];
  }
  template<std::size_t I, typename T0, int N> KUMI_ABI constexpr auto&& get_leaf(binder_n<T0, N>&& arg) noexcept
  {
    return static_cast<T0&&>(arg.members[I]);
  }
  template<std::size_t I, typename T0, int N>
  KUMI_ABI constexpr auto const&& get_leaf(binder_n<T0, N> const&& arg) noexcept
  {
    return static_cast<T0 const&&>(arg.members[I]);
  }
  template<> struct binder<std::integer_sequence<int>>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
  };
  template<typename T>
  requires(no_references<T>)
  struct binder<std::integer_sequence<int, 0>, T>
  {
    static constexpr bool is_homogeneous = true;
    using kumi_specific_layout = void;
    using member0_type = T;
    member0_type member0;
  };
  template<typename T0, typename T1>
  requires(no_references<T0, T1>)
  struct binder<std::integer_sequence<int, 0, 1>, T0, T1>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
    using member0_type = T0;
    using member1_type = T1;
    member0_type member0;
    member1_type member1;
  };
  template<typename T0, typename T1, typename T2>
  requires(no_references<T0, T1, T2>)
  struct binder<std::integer_sequence<int, 0, 1, 2>, T0, T1, T2>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
    using member0_type = T0;
    using member1_type = T1;
    using member2_type = T2;
    member0_type member0;
    member1_type member1;
    member2_type member2;
  };
  template<typename T0, typename T1, typename T2, typename T3>
  requires(no_references<T0, T1, T2, T3>)
  struct binder<std::integer_sequence<int, 0, 1, 2, 3>, T0, T1, T2, T3>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
    using member0_type = T0;
    using member1_type = T1;
    using member2_type = T2;
    using member3_type = T3;
    member0_type member0;
    member1_type member1;
    member2_type member2;
    member3_type member3;
  };
  template<typename T0, typename T1, typename T2, typename T3, typename T4>
  requires(no_references<T0, T1, T2, T3, T4>)
  struct binder<std::integer_sequence<int, 0, 1, 2, 3, 4>, T0, T1, T2, T3, T4>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
    using member0_type = T0;
    using member1_type = T1;
    using member2_type = T2;
    using member3_type = T3;
    using member4_type = T4;
    member0_type member0;
    member1_type member1;
    member2_type member2;
    member3_type member3;
    member4_type member4;
  };
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
  requires(no_references<T0, T1, T2, T3, T4, T5>)
  struct binder<std::integer_sequence<int, 0, 1, 2, 3, 4, 5>, T0, T1, T2, T3, T4, T5>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
    using member0_type = T0;
    using member1_type = T1;
    using member2_type = T2;
    using member3_type = T3;
    using member4_type = T4;
    using member5_type = T5;
    member0_type member0;
    member1_type member1;
    member2_type member2;
    member3_type member3;
    member4_type member4;
    member5_type member5;
  };
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
  requires(no_references<T0, T1, T2, T3, T4, T5, T6>)
  struct binder<std::integer_sequence<int, 0, 1, 2, 3, 4, 5, 6>, T0, T1, T2, T3, T4, T5, T6>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
    using member0_type = T0;
    using member1_type = T1;
    using member2_type = T2;
    using member3_type = T3;
    using member4_type = T4;
    using member5_type = T5;
    using member6_type = T6;
    member0_type member0;
    member1_type member1;
    member2_type member2;
    member3_type member3;
    member4_type member4;
    member5_type member5;
    member6_type member6;
  };
  template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
  requires(no_references<T0, T1, T2, T3, T4, T5, T6, T7>)
  struct binder<std::integer_sequence<int, 0, 1, 2, 3, 4, 5, 6, 7>, T0, T1, T2, T3, T4, T5, T6, T7>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
    using member0_type = T0;
    using member1_type = T1;
    using member2_type = T2;
    using member3_type = T3;
    using member4_type = T4;
    using member5_type = T5;
    using member6_type = T6;
    using member7_type = T7;
    member0_type member0;
    member1_type member1;
    member2_type member2;
    member3_type member3;
    member4_type member4;
    member5_type member5;
    member6_type member6;
    member7_type member7;
  };
  template<typename T0,
           typename T1,
           typename T2,
           typename T3,
           typename T4,
           typename T5,
           typename T6,
           typename T7,
           typename T8>
  requires(no_references<T0, T1, T2, T3, T4, T5, T6, T7, T8>)
  struct binder<std::integer_sequence<int, 0, 1, 2, 3, 4, 5, 6, 7, 8>, T0, T1, T2, T3, T4, T5, T6, T7, T8>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
    using member0_type = T0;
    using member1_type = T1;
    using member2_type = T2;
    using member3_type = T3;
    using member4_type = T4;
    using member5_type = T5;
    using member6_type = T6;
    using member7_type = T7;
    using member8_type = T8;
    member0_type member0;
    member1_type member1;
    member2_type member2;
    member3_type member3;
    member4_type member4;
    member5_type member5;
    member6_type member6;
    member7_type member7;
    member8_type member8;
  };
  template<typename T0,
           typename T1,
           typename T2,
           typename T3,
           typename T4,
           typename T5,
           typename T6,
           typename T7,
           typename T8,
           typename T9>
  requires(no_references<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>)
  struct binder<std::integer_sequence<int, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9>, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
    using member0_type = T0;
    using member1_type = T1;
    using member2_type = T2;
    using member3_type = T3;
    using member4_type = T4;
    using member5_type = T5;
    using member6_type = T6;
    using member7_type = T7;
    using member8_type = T8;
    using member9_type = T9;
    member0_type member0;
    member1_type member1;
    member2_type member2;
    member3_type member3;
    member4_type member4;
    member5_type member5;
    member6_type member6;
    member7_type member7;
    member8_type member8;
    member9_type member9;
  };
  template<std::size_t I, typename Binder>
  requires requires(Binder) { typename Binder::kumi_specific_layout; }
  KUMI_ABI constexpr auto& get_leaf(Binder& arg) noexcept
  {
    if constexpr (I == 0) return arg.member0;
    if constexpr (I == 1) return arg.member1;
    if constexpr (I == 2) return arg.member2;
    if constexpr (I == 3) return arg.member3;
    if constexpr (I == 4) return arg.member4;
    if constexpr (I == 5) return arg.member5;
    if constexpr (I == 6) return arg.member6;
    if constexpr (I == 7) return arg.member7;
    if constexpr (I == 8) return arg.member8;
    if constexpr (I == 9) return arg.member9;
  }
  template<std::size_t I, typename Binder>
  requires requires(Binder) { typename Binder::kumi_specific_layout; }
  KUMI_ABI constexpr auto&& get_leaf(Binder&& arg) noexcept
  {
    if constexpr (I == 0) return static_cast<typename Binder::member0_type&&>(arg.member0);
    if constexpr (I == 1) return static_cast<typename Binder::member1_type&&>(arg.member1);
    if constexpr (I == 2) return static_cast<typename Binder::member2_type&&>(arg.member2);
    if constexpr (I == 3) return static_cast<typename Binder::member3_type&&>(arg.member3);
    if constexpr (I == 4) return static_cast<typename Binder::member4_type&&>(arg.member4);
    if constexpr (I == 5) return static_cast<typename Binder::member5_type&&>(arg.member5);
    if constexpr (I == 6) return static_cast<typename Binder::member6_type&&>(arg.member6);
    if constexpr (I == 7) return static_cast<typename Binder::member7_type&&>(arg.member7);
    if constexpr (I == 8) return static_cast<typename Binder::member8_type&&>(arg.member8);
    if constexpr (I == 9) return static_cast<typename Binder::member9_type&&>(arg.member9);
  }
  template<std::size_t I, typename Binder>
  requires requires(Binder) { typename Binder::kumi_specific_layout; }
  KUMI_ABI constexpr auto const&& get_leaf(Binder const&& arg) noexcept
  {
    if constexpr (I == 0) return static_cast<typename Binder::member0_type const&&>(arg.member0);
    if constexpr (I == 1) return static_cast<typename Binder::member1_type const&&>(arg.member1);
    if constexpr (I == 2) return static_cast<typename Binder::member2_type const&&>(arg.member2);
    if constexpr (I == 3) return static_cast<typename Binder::member3_type const&&>(arg.member3);
    if constexpr (I == 4) return static_cast<typename Binder::member4_type const&&>(arg.member4);
    if constexpr (I == 5) return static_cast<typename Binder::member5_type const&&>(arg.member5);
    if constexpr (I == 6) return static_cast<typename Binder::member6_type const&&>(arg.member6);
    if constexpr (I == 7) return static_cast<typename Binder::member7_type const&&>(arg.member7);
    if constexpr (I == 8) return static_cast<typename Binder::member8_type const&&>(arg.member8);
    if constexpr (I == 9) return static_cast<typename Binder::member9_type const&&>(arg.member9);
  }
  template<std::size_t I, typename Binder>
  requires requires(Binder) { typename Binder::kumi_specific_layout; }
  KUMI_ABI constexpr auto const& get_leaf(Binder const& arg) noexcept
  {
    if constexpr (I == 0) return arg.member0;
    if constexpr (I == 1) return arg.member1;
    if constexpr (I == 2) return arg.member2;
    if constexpr (I == 3) return arg.member3;
    if constexpr (I == 4) return arg.member4;
    if constexpr (I == 5) return arg.member5;
    if constexpr (I == 6) return arg.member6;
    if constexpr (I == 7) return arg.member7;
    if constexpr (I == 8) return arg.member8;
    if constexpr (I == 9) return arg.member9;
  }
  template<typename T, typename ISeq, typename... Ts>
  requires(sizeof...(Ts) <= 10) && can_get_field_by_type<T, Ts...> &&
          requires(binder<ISeq, Ts...>) { typename binder<ISeq, Ts...>::kumi_specific_layout; }
  KUMI_ABI constexpr auto& get_leaf(binder<ISeq, Ts...>& arg) noexcept
  {
    constexpr std::size_t idx = get_index_by_type_v<T, Ts...>;
    return get_leaf<idx>(KUMI_FWD(arg));
  }
  template<typename T, typename ISeq, typename... Ts>
  requires(sizeof...(Ts) <= 10) && can_get_field_by_type<T, Ts...> &&
          requires(binder<ISeq, Ts...>) { typename binder<ISeq, Ts...>::kumi_specific_layout; }
  KUMI_ABI constexpr auto&& get_leaf(binder<ISeq, Ts...>&& arg) noexcept
  {
    constexpr std::size_t idx = get_index_by_type_v<T, Ts...>;
    return get_leaf<idx>(KUMI_FWD(arg));
  }
  template<typename T, typename ISeq, typename... Ts>
  requires(sizeof...(Ts) <= 10) && can_get_field_by_type<T, Ts...> &&
          requires(binder<ISeq, Ts...>) { typename binder<ISeq, Ts...>::kumi_specific_layout; }
  KUMI_ABI constexpr auto const&& get_leaf(binder<ISeq, Ts...> const&& arg) noexcept
  {
    constexpr std::size_t idx = get_index_by_type_v<T, Ts...>;
    return get_leaf<idx>(KUMI_FWD(arg));
  }
  template<typename T, typename ISeq, typename... Ts>
  requires(sizeof...(Ts) <= 10) && can_get_field_by_type<T, Ts...> &&
          requires(binder<ISeq, Ts...>) { typename binder<ISeq, Ts...>::kumi_specific_layout; }
  KUMI_ABI constexpr auto const& get_leaf(binder<ISeq, Ts...> const& arg) noexcept
  {
    constexpr std::size_t idx = get_index_by_type_v<T, Ts...>;
    return get_leaf<idx>(KUMI_FWD(arg));
  }
  template<kumi::str Name, typename ISeq, typename... Ts>
  requires(sizeof...(Ts) <= 10) && (contains_field<Name, Ts...>()) &&
          requires(binder<ISeq, Ts...>) { typename binder<ISeq, Ts...>::kumi_specific_layout; }
  KUMI_ABI constexpr auto& get_leaf(binder<ISeq, Ts...>& arg) noexcept
  {
    constexpr std::size_t idx = get_index_by_name_v<value_as<Name>, Ts...>;
    if constexpr (idx == 0) return arg.member0.value;
    if constexpr (idx == 1) return arg.member1.value;
    if constexpr (idx == 2) return arg.member2.value;
    if constexpr (idx == 3) return arg.member3.value;
    if constexpr (idx == 4) return arg.member4.value;
    if constexpr (idx == 5) return arg.member5.value;
    if constexpr (idx == 6) return arg.member6.value;
    if constexpr (idx == 7) return arg.member7.value;
    if constexpr (idx == 8) return arg.member8.value;
    if constexpr (idx == 9) return arg.member9.value;
  }
  template<kumi::str Name, typename ISeq, typename... Ts>
  requires(sizeof...(Ts) <= 10) && (contains_field<Name, Ts...>()) &&
          requires(binder<ISeq, Ts...>) { typename binder<ISeq, Ts...>::kumi_specific_layout; }
  KUMI_ABI constexpr auto&& get_leaf(binder<ISeq, Ts...>&& arg) noexcept
  {
    constexpr std::size_t idx = get_index_by_name_v<value_as<Name>, Ts...>;
    if constexpr (idx == 0) return static_cast<typename binder<ISeq, Ts...>::member0_type::type&&>(arg.member0.value);
    if constexpr (idx == 1) return static_cast<typename binder<ISeq, Ts...>::member1_type::type&&>(arg.member1.value);
    if constexpr (idx == 2) return static_cast<typename binder<ISeq, Ts...>::member2_type::type&&>(arg.member2.value);
    if constexpr (idx == 3) return static_cast<typename binder<ISeq, Ts...>::member3_type::type&&>(arg.member3.value);
    if constexpr (idx == 4) return static_cast<typename binder<ISeq, Ts...>::member4_type::type&&>(arg.member4.value);
    if constexpr (idx == 5) return static_cast<typename binder<ISeq, Ts...>::member5_type::type&&>(arg.member5.value);
    if constexpr (idx == 6) return static_cast<typename binder<ISeq, Ts...>::member6_type::type&&>(arg.member6.value);
    if constexpr (idx == 7) return static_cast<typename binder<ISeq, Ts...>::member7_type::type&&>(arg.member7.value);
    if constexpr (idx == 8) return static_cast<typename binder<ISeq, Ts...>::member8_type::type&&>(arg.member8.value);
    if constexpr (idx == 9) return static_cast<typename binder<ISeq, Ts...>::member9_type::type&&>(arg.member9.value);
  }
  template<kumi::str Name, typename ISeq, typename... Ts>
  requires(sizeof...(Ts) <= 10) && (contains_field<Name, Ts...>()) &&
          requires(binder<ISeq, Ts...>) { typename binder<ISeq, Ts...>::kumi_specific_layout; }
  KUMI_ABI constexpr auto const&& get_leaf(binder<ISeq, Ts...> const&& arg) noexcept
  {
    constexpr std::size_t idx = get_index_by_name_v<value_as<Name>, Ts...>;
    if constexpr (idx == 0)
      return static_cast<typename binder<ISeq, Ts...>::member0_type::type const&&>(arg.member0.value);
    if constexpr (idx == 1)
      return static_cast<typename binder<ISeq, Ts...>::member1_type::type const&&>(arg.member1.value);
    if constexpr (idx == 2)
      return static_cast<typename binder<ISeq, Ts...>::member2_type::type const&&>(arg.member2.value);
    if constexpr (idx == 3)
      return static_cast<typename binder<ISeq, Ts...>::member3_type::type const&&>(arg.member3.value);
    if constexpr (idx == 4)
      return static_cast<typename binder<ISeq, Ts...>::member4_type::type const&&>(arg.member4.value);
    if constexpr (idx == 5)
      return static_cast<typename binder<ISeq, Ts...>::member5_type::type const&&>(arg.member5.value);
    if constexpr (idx == 6)
      return static_cast<typename binder<ISeq, Ts...>::member6_type::type const&&>(arg.member6.value);
    if constexpr (idx == 7)
      return static_cast<typename binder<ISeq, Ts...>::member7_type::type const&&>(arg.member7.value);
    if constexpr (idx == 8)
      return static_cast<typename binder<ISeq, Ts...>::member8_type::type const&&>(arg.member8.value);
    if constexpr (idx == 9)
      return static_cast<typename binder<ISeq, Ts...>::member9_type::type const&&>(arg.member9.value);
  }
  template<kumi::str Name, typename ISeq, typename... Ts>
  requires(sizeof...(Ts) <= 10) && (contains_field<Name, Ts...>()) &&
          requires(binder<ISeq, Ts...>) { typename binder<ISeq, Ts...>::kumi_specific_layout; }
  KUMI_ABI constexpr auto const& get_leaf(binder<ISeq, Ts...> const& arg) noexcept
  {
    constexpr std::size_t idx = get_index_by_name_v<value_as<Name>, Ts...>;
    if constexpr (idx == 0) return arg.member0.value;
    if constexpr (idx == 1) return arg.member1.value;
    if constexpr (idx == 2) return arg.member2.value;
    if constexpr (idx == 3) return arg.member3.value;
    if constexpr (idx == 4) return arg.member4.value;
    if constexpr (idx == 5) return arg.member5.value;
    if constexpr (idx == 6) return arg.member6.value;
    if constexpr (idx == 7) return arg.member7.value;
    if constexpr (idx == 8) return arg.member8.value;
    if constexpr (idx == 9) return arg.member9.value;
  }
}
#include <cstddef>
#include <type_traits>
#include <utility>
namespace kumi
{
  template<typename T>
  concept product_type = is_product_type<std::remove_cvref_t<T>>::value;
  template<typename T>
  concept record_type = product_type<T> && is_record_type<std::remove_cvref_t<T>>::value;
  template<typename T>
  concept static_container = is_static_container_v<std::remove_cvref_t<T>>;
  template<typename T>
  concept unit_type = (product_type<T> && (size_v<T> == 0)) || std::is_same_v<std::remove_cvref_t<T>, std::nullptr_t>;
  template<typename T, std::size_t N>
  concept sized_product_type = product_type<T> && (size_v<T> == N);
  template<typename T, std::size_t N>
  concept sized_product_type_or_more = product_type<T> && (size_v<T> >= N);
  template<typename T>
  concept empty_product_type = product_type<T> && (size_v<T> == 0);
  template<typename T>
  concept non_empty_product_type = product_type<T> && (size_v<T> != 0);
  template<typename T>
  concept index_map = product_type<T> && is_index_map_v<std::remove_cvref_t<T>>;
  template<typename T>
  concept indexer = index_map<T> || std::integral<std::remove_cvref_t<T>>;
  template<typename T>
  concept homogeneous_product_type = product_type<T> && is_homogeneous_v<std::remove_cvref_t<T>>;
  namespace _
  {
    template<typename T, typename U> KUMI_ABI constexpr auto check_equality()
    {
      return []<std::size_t... I>(std::index_sequence<I...>) {
        return (_::comparable<member_t<I, T>, member_t<I, U>> && ...);
      }(std::make_index_sequence<size_v<T>>{});
    }
    template<typename T, typename U> KUMI_ABI constexpr auto has_same_field_names()
    {
      return []<std::size_t... I>(std::index_sequence<I...>) {
        return (can_get_field_by_name<value_as<name_of(as<element_t<I, T>>{})>, element_t<I, U>...> && ...);
      }(std::make_index_sequence<size_v<T>>{});
    }
    template<typename T, typename U> KUMI_ABI constexpr auto check_named_equality()
    {
      return []<std::size_t... I>(std::index_sequence<I...>) {
        return (
          _::comparable<raw_element_t<I, T>, typename get_field_by_name_t<value_as<name_of(as<element_t<I, T>>{})>,
                                                                          element_t<I, U>...>::type> &&
          ...);
      }(std::make_index_sequence<size_v<T>>{});
    }
  }
  template<typename T, typename U>
  concept equality_comparable =
    (size_v<T> == size_v<U>) && _::check_equality<std::remove_cvref_t<T>, std::remove_cvref_t<U>>();
  template<typename... Ts>
  concept has_named_fields = (... || is_field_capture_v<std::remove_cvref_t<Ts>>);
  template<typename... Ts>
  concept is_fully_named = (... && is_field_capture_v<std::remove_cvref_t<Ts>>);
  template<typename... Ts>
  concept uniquely_typed = (!has_named_fields<Ts...>) && all_uniques_v<std::remove_cvref_t<Ts>...>;
  template<typename... Ts>
  concept uniquely_named = (has_named_fields<Ts...>) && all_unique_names_v<std::remove_cvref_t<Ts>...>;
  template<typename... Ts>
  concept entirely_uniquely_named = (sizeof...(Ts) == 0) || (is_fully_named<Ts...> && uniquely_named<Ts...>);
  template<typename T, typename... Ts>
  concept contains_type = _::can_get_field_by_type<T, Ts...>;
  template<auto Name, typename... Ts>
  concept contains_field = _::contains_field<Name, Ts...>();
  namespace _
  {
    template<typename Type, product_type T> consteval bool typed_get_compliant()
    {
      if constexpr (sized_product_type<T, 0>) return false;
      else
        return []<std::size_t... I>(std::index_sequence<I...>) {
          if constexpr (uniquely_typed<element_t<I, T>...>) return _::can_get_field_by_type<Type, element_t<I, T>...>;
          else return false;
        }(std::make_index_sequence<size_v<T>>{});
    }
    template<str Name, product_type T> consteval bool named_get_compliant()
    {
      if constexpr (sized_product_type<T, 0>) return false;
      else
        return []<std::size_t... I>(std::index_sequence<I...>) {
          if constexpr (uniquely_named<element_t<I, T>...>) return _::contains_field<Name, element_t<I, T>...>();
          else return false;
        }(std::make_index_sequence<size_v<T>>{});
    }
  }
  template<typename T, typename U>
  concept equivalent =
    (size_v<T> == size_v<U>) && _::has_same_field_names<std::remove_cvref_t<T>, std::remove_cvref_t<U>>();
  template<typename T, typename U>
  concept named_equality_comparable =
    equivalent<T, U> && _::check_named_equality<std::remove_cvref_t<T>, std::remove_cvref_t<U>>();
  template<typename... Ts>
  concept follows_same_semantic = ((product_type<Ts> && !record_type<Ts>) && ...) || ((record_type<Ts> && ...));
  template<typename T, typename... Us>
  concept compatible_product_types =
    (follows_same_semantic<T, Us...> &&
     ((!record_type<T>) || (equivalent<std::remove_cvref_t<T>, std::remove_cvref_t<Us>> && ...)));
  template<typename T>
  concept monoid = []() {
    using M = std::remove_cvref_t<T>;
    return requires(M m) {
      { M::identity };
      { M{}(M::identity, M::identity) };
    };
  }();
}
namespace kumi
{
  template<indexer... V> struct indexes_t
  {
    using binder_t = _::make_binder_t<std::make_integer_sequence<int, sizeof...(V)>, V...>;
    static constexpr bool is_homogeneous = binder_t::is_homogeneous;
    static constexpr bool is_index_map = true;
    binder_t impl;
    [[nodiscard]] KUMI_ABI static constexpr auto size() noexcept { return sizeof...(V); };
    [[nodiscard]] KUMI_ABI static constexpr auto empty() noexcept { return sizeof...(V) == 0; };
    template<std::size_t I>
    requires(I < sizeof...(V))
    KUMI_ABI constexpr decltype(auto) get_index() const noexcept
    {
      return _::get_leaf<I>(impl);
    }
    template<std::size_t I>
    requires(I < sizeof...(V))
    [[nodiscard]] KUMI_ABI friend constexpr decltype(auto) get(indexes_t& i) noexcept
    {
      return i.get_index<I>();
    }
    template<std::size_t I>
    requires(I < sizeof...(V))
    [[nodiscard]] KUMI_ABI friend constexpr decltype(auto) get(indexes_t const& i) noexcept
    {
      return i.get_index<I>();
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         indexes_t const& i) noexcept
    {
      os << "( ";
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        using std::get;
        [[maybe_unused]] auto call = [&]<typename M>(M) { os << get<M::value>(i); };
        (call(std::integral_constant<std::size_t, I>{}), ...);
      }(std::make_index_sequence<sizeof...(V)>());
      os << ")";
      return os;
    }
  };
  template<indexer... Ts> KUMI_CUDA indexes_t(Ts...) -> indexes_t<Ts...>;
  template<indexer... Ts> [[nodiscard]] KUMI_ABI consteval auto indexes(Ts... ts) noexcept
  {
    return indexes_t{ts...};
  }
}
namespace kumi
{
  template<std::size_t N> struct index_t
  {
    static constexpr auto value = N;
    constexpr inline operator std::size_t() const noexcept { return N; }
  };
  template<std::size_t N> inline constexpr index_t<N> const index = {};
  template<str ID> struct field_name
  {
    static constexpr auto name = ID;
    constexpr inline operator str() const noexcept { return ID; }
    template<typename T> constexpr field_capture<ID, std::unwrap_ref_decay_t<T>> operator=(T v) const noexcept
    {
      return {std::move(v)};
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         field_name const& f) noexcept
    {
      return os << f.name;
    }
  };
  template<str ID> inline constexpr auto field = field_name<ID>{};
  inline namespace literals
  {
    template<char... c> constexpr auto b10()
    {
      auto value = 0ULL;
      ((value = value * 10 + (c - '0')), ...);
      return value;
    }
    template<char... c> constexpr auto operator""_c() noexcept
    {
      return index<b10<c...>()>;
    }
    template<kumi::str ID> constexpr auto operator""_f() noexcept
    {
      return field<ID>;
    }
  }
  template<template<class> class Pred> [[nodiscard]] constexpr auto predicate() noexcept
  {
    return []<typename T>(T const&) constexpr { return Pred<T>::value; };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T>
    inline constexpr bool is_reference_wrapper_v =
      !std::is_same_v<std::decay_t<typename std::unwrap_reference<T&&>::type>,
                      typename std::unwrap_ref_decay<T&&>::type>;
    template<typename T> struct apply_object_unwrap
    {
      using type = T&&;
    };
    template<typename T>
    requires is_reference_wrapper_v<T>
    struct apply_object_unwrap<T>
    {
      using type = typename std::remove_cvref_t<T>::type&;
    };
    template<typename T>
    requires std::is_pointer_v<std::remove_cvref_t<T>>
    struct apply_object_unwrap<T>
    {
      using type = std::remove_pointer_t<std::remove_cvref_t<T>>&;
    };
    template<typename T> using apply_object_unwrap_t = typename apply_object_unwrap<T>::type;
  }
  template<typename Function, product_type Tuple>
  KUMI_ABI constexpr decltype(auto) apply(Function&& f, Tuple&& t)
    noexcept(_::supports_nothrow_apply<Function&&, Tuple&&>)
  requires _::supports_apply<Function, Tuple>
  {
    if constexpr (sized_product_type<Tuple, 0>) return KUMI_FWD(f)();
    else if constexpr (record_type<Tuple>) return apply(KUMI_FWD(f), KUMI_FWD(t).values());
    else if constexpr (std::is_member_pointer_v<std::decay_t<Function>>)
      return [&]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto) {
        auto&& w = [](auto&& y) -> decltype(auto) {
          if constexpr (_::is_reference_wrapper_v<decltype(y)>) return y.get();
          else if constexpr (std::is_pointer_v<std::remove_cvref_t<decltype(y)>>) return *y;
          else return KUMI_FWD(y);
        }(get<0>(KUMI_FWD(t)));
        if constexpr (std::is_member_object_pointer_v<std::remove_cvref_t<decltype(f)>>) return KUMI_FWD(w).*f;
        else return (KUMI_FWD(w).*f)(get<I + 1>(KUMI_FWD(t))...);
      }(std::make_index_sequence<size<Tuple>::value - 1>());
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto) {
        return KUMI_FWD(f)(get<I>(KUMI_FWD(t))...);
      }(std::make_index_sequence<size<Tuple>::value>());
  }
  namespace result
  {
    template<typename Function, product_type Tuple> struct apply
    {
      using type = decltype(kumi::apply(std::declval<Function>(), std::declval<Tuple>()));
    };
    template<typename Function, product_type Tuple> using apply_t = typename apply<Function, Tuple>::type;
  }
  namespace _
  {
    template<typename Function, record_type Record>
    KUMI_ABI constexpr decltype(auto) apply_field(Function&& f, Record&& t)
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto) {
        return KUMI_FWD(f)(get<I>(KUMI_FWD(t))...);
      }(std::make_index_sequence<size<Record>::value>());
      ;
    }
    namespace result
    {
      template<typename Function, record_type Record> struct apply_field
      {
        using type = decltype(kumi::_::apply_field(std::declval<Function>(), std::declval<Record>()));
      };
      template<typename Function, record_type Record>
      using apply_field_t = typename apply_field<Function, Record>::type;
    }
  }
}
#include <iosfwd>
namespace kumi
{
  struct unit
  {
    using is_product_type = void;
    KUMI_ABI friend constexpr auto operator<=>(unit, unit) noexcept = default;
    template<typename T>
    requires(unit_type<T>)
    [[nodiscard]] KUMI_ABI constexpr operator T() const noexcept
    {
      return {};
    };
    template<typename T>
    requires(unit_type<T>)
    [[nodiscard]] KUMI_ABI constexpr operator T() noexcept
    {
      return {};
    };
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, unit) noexcept
    {
      return os << '\'' << "none" << '\'';
    }
  };
  inline constexpr unit none = {};
}
#include <type_traits>
#include <utility>
#if !defined(KUMI_DOXYGEN_INVOKED)
template<std::size_t I, typename Head, typename... Tail>
struct std::tuple_element<I, kumi::tuple<Head, Tail...>> : std::tuple_element<I - 1, kumi::tuple<Tail...>>
{
};
template<std::size_t I, typename... Ts> struct std::tuple_element<I, kumi::tuple<Ts...> const>
{
  using type = typename tuple_element<I, kumi::tuple<Ts...>>::type const;
};
template<typename Head, typename... Tail> struct std::tuple_element<0, kumi::tuple<Head, Tail...>>
{
  using type = Head;
};
template<typename... Ts> struct std::tuple_size<kumi::tuple<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>
{
};
template<std::size_t I, typename Head, typename... Tail>
struct std::tuple_element<I, kumi::record<Head, Tail...>> : std::tuple_element<I - 1, kumi::record<Tail...>>
{
};
template<std::size_t I, typename... Ts> struct std::tuple_element<I, kumi::record<Ts...> const>
{
  using type = typename tuple_element<I, kumi::record<Ts...>>::type const;
};
template<typename Head, typename... Tail> struct std::tuple_element<0, kumi::record<Head, Tail...>>
{
  using type = Head;
};
template<typename... Ts>
struct std::tuple_size<kumi::record<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>
{
};
template<typename... V>
struct std::tuple_size<kumi::indexes_t<V...>> : std::integral_constant<std::size_t, sizeof...(V)>
{
};
template<std::size_t I, typename... V>
struct std::tuple_element<I, kumi::indexes_t<V...>> : std::tuple_element<I, kumi::tuple<V...>>
{
};
template<> struct std::tuple_size<kumi::unit> : std::integral_constant<std::size_t, 0>
{
};
template<std::size_t I> struct std::tuple_element<I, kumi::unit> : std::tuple_element<I, kumi::tuple<>>
{
};
#if !defined(__ANDROID__)
template<typename... Ts, typename... Us, template<class> class TQual, template<class> class UQual>
requires(sizeof...(Ts) == sizeof...(Us))
struct std::basic_common_reference<kumi::tuple<Ts...>, kumi::tuple<Us...>, TQual, UQual>
{
  using type = kumi::tuple<std::common_reference_t<TQual<Ts>, UQual<Us>>...>;
};
#endif
#endif
#include <cstddef>
namespace kumi
{
  struct numeric_add
  {
    static constexpr auto identity{0};
    template<typename T1, typename T2>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T1&& a, T2&& b) const noexcept(noexcept(KUMI_FWD(a) + KUMI_FWD(b)))
    requires requires { KUMI_FWD(a) + KUMI_FWD(b); }
    {
      return KUMI_FWD(a) + KUMI_FWD(b);
    };
  };
  struct numeric_prod
  {
    static constexpr auto identity{1};
    template<typename T1, typename T2>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T1&& a, T2&& b) const noexcept(noexcept(KUMI_FWD(a) * KUMI_FWD(b)))
    requires requires { KUMI_FWD(a) * KUMI_FWD(b); }
    {
      return KUMI_FWD(a) * KUMI_FWD(b);
    };
  };
  struct boolean_and
  {
    static constexpr bool identity{true};
    template<typename T1, typename T2>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T1&& a, T2&& b) const noexcept(noexcept(KUMI_FWD(a) & KUMI_FWD(b)))
    requires requires { KUMI_FWD(a) & KUMI_FWD(b); }
    {
      return KUMI_FWD(a) & KUMI_FWD(b);
    };
  };
  struct boolean_or
  {
    static constexpr bool identity{false};
    template<typename T1, typename T2>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T1&& a, T2&& b) const noexcept(noexcept(KUMI_FWD(a) | KUMI_FWD(b)))
    requires requires { KUMI_FWD(a) | KUMI_FWD(b); }
    {
      return KUMI_FWD(a) | KUMI_FWD(b);
    };
  };
  struct boolean_xor
  {
    static constexpr bool identity{false};
    template<typename T1, typename T2>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T1&& a, T2&& b) const noexcept(noexcept(KUMI_FWD(a) ^ KUMI_FWD(b)))
    requires requires { KUMI_FWD(a) ^ KUMI_FWD(b); }
    {
      return KUMI_FWD(a) ^ KUMI_FWD(b);
    };
  };
  namespace function
  {
    inline constexpr numeric_add plus{};
    inline constexpr numeric_prod multiplies{};
    inline constexpr boolean_and bit_and{};
    inline constexpr boolean_or bit_or{};
    inline constexpr boolean_xor bit_xor{};
  }
}
namespace kumi
{
  template<typename T> [[nodiscard]] KUMI_ABI constexpr auto name_of(as<T>) noexcept
  {
    if constexpr (is_field_capture_v<std::remove_cvref_t<T>>) return std::remove_cvref_t<T>::name;
    else return kumi::none;
  };
  template<typename T> [[nodiscard]] KUMI_ABI constexpr decltype(auto) field_value_of(T&& t) noexcept
  {
    if constexpr (is_field_capture_v<std::remove_cvref_t<T>>) return _::get_field(KUMI_FWD(t));
    else return KUMI_FWD(t);
  };
  template<typename Target, product_type T>
  requires(_::typed_get_compliant<Target, T>())
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(T&& t) noexcept
  {
    constexpr std::size_t Idx = [&]<std::size_t... I>(std::index_sequence<I...>) {
      return _::get_index_by_type_v<Target, element_t<I, T>...>;
    }(std::make_index_sequence<size_v<T>>{});
    return get<Idx>(KUMI_FWD(t));
  }
  template<str Name, product_type T>
  requires(_::named_get_compliant<Name, T>())
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(T&& t) noexcept
  {
    constexpr std::size_t Idx = [&]<std::size_t... I>(std::index_sequence<I...>) {
      return _::get_index_by_name_v<_::value_as<Name>, element_t<I, T>...>;
    }(std::make_index_sequence<size_v<T>>{});
    return field_value_of(get<Idx>(KUMI_FWD(t)));
  }
  namespace result
  {
    template<typename T> struct name_of
    {
      using type = decltype(kumi::name_of(as<T>{}));
    };
    template<typename T> struct field_value_of
    {
      using type = decltype(kumi::field_value_of(std::declval<T>()));
    };
    template<typename T> using name_of_t = typename name_of<T>::type;
    template<typename T> using field_value_of_t = typename field_value_of<T>::type;
  }
}
namespace kumi
{
}
#include <iosfwd>
#include <type_traits>
namespace kumi
{
  template<typename... Ts> struct tuple
  {
    using binder_t = _::make_binder_t<std::make_integer_sequence<int, sizeof...(Ts)>, Ts...>;
    static constexpr bool is_homogeneous = binder_t::is_homogeneous;
    binder_t impl;
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] index_t<I> i) & noexcept
    {
      return _::get_leaf<I>(impl);
    }
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) && noexcept
    {
      return _::get_leaf<I>(static_cast<decltype(impl)&&>(impl));
    }
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) const&& noexcept
    {
      return _::get_leaf<I>(static_cast<decltype(impl) const&&>(impl));
    }
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) const& noexcept
    {
      return _::get_leaf<I>(impl);
    }
    template<typename T>
    requires(uniquely_typed<Ts...> && contains_type<T, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](as<T>) & noexcept
    {
      return _::get_leaf<T>(impl);
    }
    template<typename T>
    requires(uniquely_typed<Ts...> && contains_type<T, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](as<T>) && noexcept
    {
      return _::get_leaf<T>(static_cast<decltype(impl)&&>(impl));
    }
    template<typename T>
    requires(uniquely_typed<Ts...> && contains_type<T, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](as<T>) const&& noexcept
    {
      return _::get_leaf<T>(static_cast<decltype(impl) const&&>(impl));
    }
    template<typename T>
    requires(uniquely_typed<Ts...> && contains_type<T, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](as<T>) const& noexcept
    {
      return _::get_leaf<T>(impl);
    }
    template<str Name>
    requires(uniquely_named<Ts...> && contains_field<Name, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](field_name<Name>) & noexcept
    {
      return _::get_leaf<Name>(impl);
    }
    template<str Name>
    requires(uniquely_named<Ts...> && contains_field<Name, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](field_name<Name>) && noexcept
    {
      return _::get_leaf<Name>(static_cast<decltype(impl)&&>(impl));
    }
    template<str Name>
    requires(uniquely_named<Ts...> && contains_field<Name, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](field_name<Name>) const&& noexcept
    {
      return _::get_leaf<Name>(static_cast<decltype(impl) const&&>(impl));
    }
    template<str Name>
    requires(uniquely_named<Ts...> && contains_field<Name, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](field_name<Name>) const& noexcept
    {
      return _::get_leaf<Name>(impl);
    }
    [[nodiscard]] KUMI_ABI static constexpr auto size() noexcept { return sizeof...(Ts); }
    [[nodiscard]] KUMI_ABI static constexpr bool empty() noexcept { return sizeof...(Ts) == 0; }
    [[nodiscard]] KUMI_ABI static constexpr auto names() noexcept -> tuple<decltype(name_of(as<Ts>{}))...>
    {
      return {name_of(as<Ts>{})...};
    };
    template<typename... Us>
    requires(_::piecewise_convertible<tuple, tuple<Us...>> && (sizeof...(Us) == sizeof...(Ts)) &&
             (!std::same_as<Ts, Us> && ...))
    [[deprecated("Will be replaced by free functions")]] [[nodiscard]] inline constexpr auto cast() const
    {
      return apply([](auto&&... elems) { return tuple<Us...>{static_cast<Us>(elems)...}; }, *this);
    }
    template<typename... Us>
    requires((sizeof...(Us) == sizeof...(Ts)) && (!std::same_as<tuple<Ts...>, tuple<Us...>>) &&
             _::piecewise_constructible<tuple<Ts const&...>, tuple<Us...>>)
    [[nodiscard]] KUMI_ABI explicit(!_::piecewise_convertible<tuple<Ts const&...>, tuple<Us...>>) constexpr
    operator tuple<Us...>() const
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<Us...>{static_cast<Us>(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    requires((sizeof...(Us) == sizeof...(Ts)) && (!std::same_as<tuple<Ts...>, tuple<Us...>>) &&
             _::piecewise_constructible<tuple<Ts&...>, tuple<Us...>>)
    [[nodiscard]] KUMI_ABI explicit(!_::piecewise_convertible<tuple<Ts&...>, tuple<Us...>>) constexpr operator tuple<
      Us...>()
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<Us...>{static_cast<Us>(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    requires(_::piecewise_convertible<tuple, tuple<Us...>>)
    KUMI_ABI constexpr tuple& operator=(tuple<Us...> const& other)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((get<I>(*this) = get<I>(other)), ...);
      }(std::make_index_sequence<sizeof...(Ts)>());
      return *this;
    }
    template<typename... Us>
    requires(_::piecewise_convertible<tuple, tuple<Us...>>)
    KUMI_ABI constexpr tuple& operator=(tuple<Us...>&& other)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((get<I>(*this) = get<I>(KUMI_FWD(other))), ...);
      }(std::make_index_sequence<sizeof...(Ts)>());
      return *this;
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator==(tuple const& self, tuple<Us...> const& other) noexcept
    requires(equality_comparable<tuple, tuple<Us...>>)
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return ((get<I>(self) == get<I>(other)) && ...);
      }(std::make_index_sequence<sizeof...(Ts)>());
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator!=(tuple const& self, tuple<Us...> const& other) noexcept
    requires(equality_comparable<tuple, tuple<Us...>>)
    {
      return !(self == other);
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator<(tuple const& lhs, tuple<Us...> const& rhs) noexcept
    requires(sizeof...(Ts) == sizeof...(Us) && _::piecewise_ordered<tuple, tuple<Us...>>)
    {
      auto res = get<0>(lhs) < get<0>(rhs);
      auto const order = [&]<typename Index>(Index i) {
        auto y_less_x_prev = rhs[i] < lhs[i];
        auto x_less_y = lhs[index_t<Index::value + 1>{}] < rhs[index_t<Index::value + 1>{}];
        return x_less_y && !y_less_x_prev;
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (res || ... || order(index_t<I>{}));
      }(std::make_index_sequence<sizeof...(Ts) - 1>());
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator<=(tuple const& lhs, tuple<Us...> const& rhs) noexcept
    requires requires { rhs < lhs; }
    {
      return !(rhs < lhs);
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator>(tuple const& lhs, tuple<Us...> const& rhs) noexcept
    requires requires { rhs < lhs; }
    {
      return rhs < lhs;
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator>=(tuple const& lhs, tuple<Us...> const& rhs) noexcept
    requires requires { lhs < rhs; }
    {
      return !(lhs < rhs);
    }
    template<typename Function>
    [[deprecated("Use apply() instead")]] KUMI_ABI constexpr auto operator()(Function&& f) const& noexcept(
      noexcept(kumi::apply(KUMI_FWD(f), *this))) -> decltype(kumi::apply(KUMI_FWD(f), *this))
    {
      return kumi::apply(KUMI_FWD(f), *this);
    }
#if !defined(KUMI_DOXYGEN_INVOKED)
    template<typename Function>
    [[deprecated("Use apply() instead")]] KUMI_ABI constexpr auto operator()(Function&& f) & noexcept(
      noexcept(kumi::apply(KUMI_FWD(f), *this))) -> decltype(kumi::apply(KUMI_FWD(f), *this))
    {
      return kumi::apply(KUMI_FWD(f), *this);
    }
    template<typename Function>
    [[deprecated("Use apply() instead")]] KUMI_ABI constexpr auto operator()(Function&& f) const&& noexcept(
      noexcept(kumi::apply(KUMI_FWD(f), static_cast<tuple const&&>(*this))))
      -> decltype(kumi::apply(KUMI_FWD(f), static_cast<tuple const&&>(*this)))
    {
      return kumi::apply(KUMI_FWD(f), static_cast<tuple const&&>(*this));
    }
    template<typename Function>
    [[deprecated("Use apply() instead")]] KUMI_ABI constexpr auto operator()(Function&& f) && noexcept(
      noexcept(kumi::apply(KUMI_FWD(f), static_cast<tuple&&>(*this))))
      -> decltype(kumi::apply(KUMI_FWD(f), static_cast<tuple&&>(*this)))
    {
      return kumi::apply(KUMI_FWD(f), static_cast<tuple&&>(*this));
    }
#endif
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, tuple const& t) noexcept
    {
      os << "( ";
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((os << _::make_streamable(t[index<I>]) << " "), ...);
      }(std::make_index_sequence<size_v<decltype(t)>>{});
      os << ')';
      return os;
    }
  };
  template<> struct tuple<>
  {
    static constexpr bool is_homogeneous = false;
    static constexpr auto size() noexcept { return std::size_t{0}; }
    static constexpr auto empty() noexcept { return true; }
    static constexpr auto names() noexcept { return tuple{}; }
    KUMI_ABI friend constexpr auto operator<=>(tuple<>, tuple<>) noexcept = default;
    template<typename T>
    requires(unit_type<T>)
    [[nodiscard]] KUMI_ABI constexpr operator T() const noexcept
    {
      return {};
    };
    template<typename T>
    requires(unit_type<T>)
    [[nodiscard]] KUMI_ABI constexpr operator T() noexcept
    {
      return {};
    };
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, tuple<>) noexcept
    {
      return os << "()";
    }
  };
  template<typename... Ts> KUMI_CUDA tuple(Ts&&...) -> tuple<std::unwrap_ref_decay_t<Ts>...>;
  template<typename... Ts> [[nodiscard]] KUMI_ABI constexpr auto tie(Ts&... ts) -> tuple<Ts&...>
  {
    return {ts...};
  }
  template<typename... Ts> [[nodiscard]] KUMI_ABI constexpr auto forward_as_tuple(Ts&&... ts) -> tuple<Ts&&...>
  {
    return {KUMI_FWD(ts)...};
  }
  template<typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto make_tuple(Ts&&... ts) -> tuple<std::unwrap_ref_decay_t<Ts>...>
  {
    return {KUMI_FWD(ts)...};
  }
  template<product_type Type> [[nodiscard]] KUMI_ABI constexpr auto to_ref(Type&& t)
  {
    return apply([](auto&&... elems) { return kumi::forward_as_tuple(KUMI_FWD(elems)...); }, KUMI_FWD(t));
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts))
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  {
    return t[index<I>];
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts))
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& arg) noexcept
  {
    return static_cast<tuple<Ts...>&&>(arg)[index<I>];
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts))
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& arg) noexcept
  {
    return arg[index<I>];
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts))
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& arg) noexcept
  {
    return static_cast<tuple<Ts...> const&&>(arg)[index<I>];
  }
  template<std::integral auto I, typename... Ts>
  requires((I >= sizeof...(Ts)) || (I < 0))
  constexpr auto get(tuple<Ts...>& t) = delete;
  template<std::integral auto I, typename... Ts>
  requires((I >= sizeof...(Ts)) || (I < 0))
  constexpr auto get(tuple<Ts...> const& t) = delete;
  template<std::integral auto I, typename... Ts>
  requires((I >= sizeof...(Ts)) || (I < 0))
  constexpr auto get(tuple<Ts...>&& t) = delete;
  template<std::integral auto I, typename... Ts>
  requires((I >= sizeof...(Ts)) || (I < 0))
  constexpr auto get(tuple<Ts...> const&& t) = delete;
  template<str Name, typename... Ts>
  requires(uniquely_named<Ts...> && contains_field<Name, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  {
    return t[field<Name>];
  }
  template<str Name, typename... Ts>
  requires(uniquely_named<Ts...> && contains_field<Name, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& t) noexcept
  {
    return static_cast<tuple<Ts...>&&>(t)[field<Name>];
  }
  template<str Name, typename... Ts>
  requires(uniquely_named<Ts...> && contains_field<Name, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& t) noexcept
  {
    return t[field<Name>];
  }
  template<str Name, typename... Ts>
  requires(uniquely_named<Ts...> && contains_field<Name, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& t) noexcept
  {
    return static_cast<tuple<Ts...> const&&>(t)[field<Name>];
  }
  template<str Name, product_type T>
  requires(!record_type<T> && !(_::named_get_compliant<Name, T>()))
  constexpr auto get(T&& t) = delete;
  template<typename T, typename... Ts>
  requires(uniquely_typed<Ts...> && contains_type<T, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  {
    return t[as<T>{}];
  }
  template<typename T, typename... Ts>
  requires(uniquely_typed<Ts...> && contains_type<T, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& t) noexcept
  {
    return static_cast<tuple<Ts...>&&>(t)[as<T>{}];
  }
  template<typename T, typename... Ts>
  requires(uniquely_typed<Ts...> && contains_type<T, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& t) noexcept
  {
    return t[as<T>{}];
  }
  template<typename T, typename... Ts>
  requires(uniquely_typed<Ts...> && contains_type<T, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& t) noexcept
  {
    return static_cast<tuple<Ts...> const&&>(t)[as<T>{}];
  }
  template<typename U, product_type T>
  requires(!record_type<T> && !(_::typed_get_compliant<U, T>()))
  constexpr auto get(T&& t) = delete;
}
namespace kumi
{
  template<typename... Ts>
  requires((entirely_uniquely_named<Ts...>))
  struct record<Ts...>
  {
    using is_record_type = void;
    using binder_t = _::make_binder_t<std::make_integer_sequence<int, sizeof...(Ts)>, Ts...>;
    static constexpr bool is_homogeneous = false;
    binder_t impl;
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) & noexcept
    {
      return _::get_leaf<I>(impl);
    }
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) && noexcept
    {
      return _::get_leaf<I>(static_cast<decltype(impl)&&>(impl));
    }
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) const&& noexcept
    {
      return _::get_leaf<I>(static_cast<decltype(impl) const&&>(impl));
    }
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) const& noexcept
    {
      return _::get_leaf<I>(impl);
    }
    template<str Name>
    requires(contains_field<Name, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](field_name<Name>) & noexcept
    {
      return _::get_leaf<Name>(impl);
    }
    template<str Name>
    requires(contains_field<Name, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](field_name<Name>) && noexcept
    {
      return _::get_leaf<Name>(static_cast<decltype(impl)&&>(impl));
    }
    template<str Name>
    requires(contains_field<Name, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](field_name<Name>) const&& noexcept
    {
      return _::get_leaf<Name>(static_cast<decltype(impl) const&&>(impl));
    }
    template<str Name>
    requires(contains_field<Name, Ts...>)
    KUMI_ABI constexpr decltype(auto) operator[](field_name<Name>) const& noexcept
    {
      return _::get_leaf<Name>(impl);
    }
    [[nodiscard]] KUMI_ABI static constexpr auto size() noexcept { return sizeof...(Ts); }
    [[nodiscard]] KUMI_ABI static constexpr bool empty() noexcept { return sizeof...(Ts) == 0; }
    [[nodiscard]] KUMI_ABI static constexpr auto names() noexcept { return tuple{name_of(as<Ts>{})...}; };
    [[nodiscard]] KUMI_ABI constexpr auto values() noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<raw_member_t<I, decltype(*this)>...>{field_value_of(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    };
    [[nodiscard]] KUMI_ABI constexpr auto values() const noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<raw_member_t<I, decltype(*this)>...>{field_value_of(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    };
    template<typename... Us>
    requires(equivalent<record, record<Us...>> && _::fieldwise_convertible<record, record<Us...>>)
    KUMI_ABI constexpr record& operator=(record<Us...> const& other)
    {
      ((get<name_of(as<Ts>{})>(*this) = get<name_of(as<Ts>{})>(KUMI_FWD(other))), ...);
      return *this;
    }
    template<typename... Us>
    requires(equivalent<record, record<Us...>> && _::fieldwise_convertible<record, record<Us...>>)
    KUMI_ABI constexpr record& operator=(record<Us...>&& other)
    {
      ((get<name_of(as<Ts>{})>(*this) = get<name_of(as<Ts>{})>(KUMI_FWD(other))), ...);
      return *this;
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator==(record const& self, record<Us...> const& other) noexcept
    requires(named_equality_comparable<record, record<Us...>>)
    {
      return ((get<name_of(as<Ts>{})>(self) == get<name_of(as<Ts>{})>(other)) && ...);
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator!=(record const& self, record<Us...> const& other) noexcept
    requires(named_equality_comparable<record, record<Us...>>)
    {
      return !(self == other);
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         record const& t) noexcept
    {
      os << "( ";
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((os << t[index<I>] << " "), ...);
      }(std::make_index_sequence<size_v<decltype(t)>>{});
      os << ')';
      return os;
    }
  };
  template<> struct record<>
  {
    using is_record_type = void;
    static constexpr bool is_homogeneous = false;
    static constexpr auto size() noexcept { return std::size_t{0}; }
    static constexpr auto empty() noexcept { return true; }
    static constexpr auto names() noexcept { return tuple{}; }
    static constexpr auto values() noexcept { return tuple{}; }
    KUMI_ABI friend constexpr auto operator<=>(record<>, record<>) noexcept = default;
    template<typename T>
    requires(unit_type<T>)
    [[nodiscard]] KUMI_ABI constexpr operator T() const noexcept
    {
      return {};
    };
    template<typename T>
    requires(unit_type<T>)
    [[nodiscard]] KUMI_ABI constexpr operator T() noexcept
    {
      return {};
    };
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, record<>) noexcept
    {
      return os << "()";
    }
  };
  template<typename... Ts> KUMI_CUDA record(Ts&&...) -> record<std::unwrap_ref_decay_t<Ts>...>;
  template<str... Fields, typename... Ts>
  requires(sizeof...(Fields) == sizeof...(Ts))
  KUMI_ABI constexpr auto tie(Ts&... ts) -> record<field_capture<Fields, Ts&>...>
  {
    return {ts...};
  }
  template<str... Fields, typename... Ts>
  requires(sizeof...(Fields) == sizeof...(Ts))
  [[nodiscard]] KUMI_ABI constexpr auto forward_as_record(Ts&&... ts) -> record<field_capture<Fields, Ts&&>...>
  {
    return {KUMI_FWD(ts)...};
  }
  template<typename... Ts>
  requires(entirely_uniquely_named<Ts...>)
  [[nodiscard]] KUMI_ABI constexpr auto make_record(Ts&&... ts) -> record<std::unwrap_ref_decay_t<Ts>...>
  {
    return {KUMI_FWD(ts)...};
  }
  template<record_type Type> [[nodiscard]] KUMI_ABI constexpr auto to_ref(Type&& r)
  {
    return _::apply_field(
      [](auto&&... elems) {
        return kumi::forward_as_record<name_of(as<decltype(elems)>{})...>(field_value_of(KUMI_FWD(elems))...);
      },
      KUMI_FWD(r));
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts))
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>& r) noexcept
  {
    return r[index<I>];
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts))
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>&& r) noexcept
  {
    return static_cast<record<Ts...>&&>(r)[index<I>];
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts))
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const& r) noexcept
  {
    return r[index<I>];
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts))
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const&& r) noexcept
  {
    return static_cast<record<Ts...> const&&>(r)[index<I>];
  }
  template<std::integral auto I, typename... Ts>
  requires((I >= sizeof...(Ts)) || (I < 0))
  constexpr auto get(record<Ts...>& t) = delete;
  template<std::integral auto I, typename... Ts>
  requires((I >= sizeof...(Ts)) || (I < 0))
  constexpr auto get(record<Ts...> const& t) = delete;
  template<std::integral auto I, typename... Ts>
  requires((I >= sizeof...(Ts)) || (I < 0))
  constexpr auto get(record<Ts...>&& t) = delete;
  template<std::integral auto I, typename... Ts>
  requires((I >= sizeof...(Ts)) || (I < 0))
  constexpr auto get(record<Ts...> const&& t) = delete;
  template<str Name, typename... Ts>
  requires(contains_field<Name, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>& r) noexcept
  {
    return r[field<Name>];
  }
  template<str Name, typename... Ts>
  requires(contains_field<Name, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>&& r) noexcept
  {
    return static_cast<record<Ts...>&&>(r)[field<Name>];
  }
  template<str Name, typename... Ts>
  requires(contains_field<Name, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const& r) noexcept
  {
    return r[field<Name>];
  }
  template<str Name, typename... Ts>
  requires(contains_field<Name, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const&& r) noexcept
  {
    return static_cast<record<Ts...> const&&>(r)[field<Name>];
  }
  template<str Name, record_type R>
  requires(!(_::named_get_compliant<Name, R>()))
  constexpr auto get(R&& r) = delete;
  template<typename U, record_type T> constexpr auto get(T&& t) = delete;
}
namespace kumi
{
}
namespace kumi
{
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto members_of(as<T>) noexcept
  {
    if constexpr (sized_product_type<T, 0>) return tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple{name_of(as<element_t<I, T>>{})...};
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto values_of(T&& t) noexcept
  {
    if constexpr (sized_product_type<T, 0>) return tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<result::field_value_of_t<member_t<I, T>>...>{field_value_of(get<I>(KUMI_FWD(t)))...};
      }(std::make_index_sequence<size_v<T>>{});
  }
  namespace result
  {
    template<product_type T> struct members_of
    {
      using type = decltype(kumi::members_of(as<T>{}));
    };
    template<product_type T> struct values_of
    {
      using type = decltype(kumi::values_of(std::declval<T>()));
    };
    template<product_type T> using members_of_t = typename members_of<T>::type;
    template<product_type T> using values_of_t = typename values_of<T>::type;
  }
}
namespace kumi
{
  template<product_type Tuple>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) front(Tuple&& t)
  requires(size_v<Tuple> != 0)
  {
    if constexpr (record_type<Tuple>) return front(values_of(KUMI_FWD(t)));
    else return get<0>(KUMI_FWD(t));
  }
  template<product_type Tuple>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) back(Tuple&& t)
  requires(size_v<Tuple> != 0)
  {
    if constexpr (record_type<Tuple>) return back(values_of(KUMI_FWD(t)));
    else return get<size_v<Tuple> - 1>(KUMI_FWD(t));
  }
  namespace result
  {
    template<product_type Tuple> struct front : raw_member<0, Tuple>
    {
    };
    template<product_type Tuple> struct back : raw_member<size_v<Tuple> - 1, Tuple>
    {
    };
    template<product_type Tuple> using front_t = typename front<Tuple>::type;
    template<product_type Tuple> using back_t = typename back<Tuple>::type;
  }
}
namespace kumi
{
  template<product_type... Ts> [[nodiscard]] KUMI_ABI constexpr auto common_product_type(Ts...)
  {
    if constexpr ((record_type<Ts> && ...)) return kumi::record{};
    else return kumi::tuple{};
  }
  namespace result
  {
    template<product_type... Ts> struct common_product_type
    {
      using type = decltype(kumi::common_product_type(std::declval<Ts>()...));
    };
    template<typename... Ts> using common_product_type_t = typename common_product_type<Ts...>::type;
  }
  namespace _
  {
    template<typename T> struct builder_impl
    {
    };
    template<product_type Tuple>
    requires(!record_type<Tuple>)
    struct builder_impl<Tuple>
    {
      using type = Tuple;
      template<typename... Us> using to = kumi::tuple<Us...>;
    };
    template<record_type Record> struct builder_impl<Record>
    {
      using type = Record;
      template<typename... Us> using to = kumi::record<Us...>;
    };
    template<kumi::product_type T> struct builder : builder_impl<std::remove_cvref_t<T>>
    {
      template<typename... Args> static constexpr auto make(Args&&... args)
      {
        if constexpr (record_type<T>) return kumi::make_record(KUMI_FWD(args)...);
        else return kumi::make_tuple(KUMI_FWD(args)...);
      }
      template<typename... Args> static constexpr auto build(Args&&... args)
      {
        if constexpr (record_type<T>) return kumi::record{KUMI_FWD(args)...};
        else return kumi::tuple{KUMI_FWD(args)...};
      }
    };
    template<kumi::product_type T> using builder_t = typename builder<T>::type;
    template<kumi::product_type T, typename... Args> using builder_make_t = typename builder<T>::template to<Args...>;
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t N, std::size_t... S> struct digits
    {
      KUMI_ABI constexpr auto operator()(std::size_t v) noexcept
      {
        struct
        {
          std::size_t data[N];
        } values = {};
        std::size_t shp[N] = {S...};
        std::size_t i = 0;
        while (v != 0)
        {
          values.data[i] = v % shp[i];
          v /= shp[i++];
        }
        return values;
      }
    };
  }
  template<product_type... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto cartesian_product(Ts&&... ts)
  requires(follows_same_semantic<Ts...>)
  {
    using res_type = result::common_product_type_t<std::remove_cvref_t<Ts>...>;
    if constexpr (sizeof...(Ts) == 0) return tuple{};
    else
    {
      constexpr auto idx = [&]<std::size_t... I>(std::index_sequence<I...>) {
        kumi::_::digits<sizeof...(Ts), kumi::size_v<Ts>...> dgt{};
        using t_t = decltype(dgt(0));
        struct
        {
          t_t data[sizeof...(I)];
        } that = {dgt(I)...};
        return that;
      }(std::make_index_sequence<(kumi::size_v<Ts> * ...)>{});
      auto maps = [&]<std::size_t... I>(auto k, std::index_sequence<I...>) {
        auto tps = kumi::forward_as_tuple(ts...);
        using res_t =
          _::builder_make_t<res_type,
                            element_t<idx.data[k].data[I], std::remove_cvref_t<element_t<I, decltype(tps)>>>...>;
        return res_t{get<idx.data[k].data[I]>(get<I>(tps))...};
      };
      return [&]<std::size_t... N>(std::index_sequence<N...>) {
        std::make_index_sequence<sizeof...(Ts)> ids;
        return kumi::make_tuple(maps(index<N>, ids)...);
      }(std::make_index_sequence<(size_v<Ts> * ...)>{});
    }
  }
  namespace result
  {
    template<typename... T> struct cartesian_product
    {
      using type = decltype(kumi::cartesian_product(std::declval<T>()...));
    };
    template<typename... T> using cartesian_product_t = typename cartesian_product<T...>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, auto> struct repeat
    {
      using type = T;
    };
    template<typename T, auto I> using repeat_t = typename repeat<T, I>::type;
    template<typename T, auto N> struct as_homogeneous
    {
      template<std::size_t... I>
      static consteval auto homogeneify(std::index_sequence<I...>) -> tuple<repeat_t<T, I>...>;
      using type = std::remove_cvref_t<decltype(homogeneify(std::make_index_sequence<N>{}))>;
    };
    template<typename T, auto N> using as_homogeneous_t = typename as_homogeneous<T, N>::type;
  }
  template<typename Target, product_type T> [[nodiscard]] KUMI_ABI constexpr auto member_cast(T&& t)
  {
    if constexpr (sized_product_type<T, 0>) return t;
    else if constexpr (record_type<T>)
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = _::builder_make_t<T, result::field_cast_t<Target, element_t<I, T>>...>;
        return type{field_cast<Target>(get<I>(KUMI_FWD(t)))...};
      }(std::make_index_sequence<size_v<T>>{});
    else
    {
      using type = _::as_homogeneous_t<Target, size_v<T>>;
      return static_cast<type>(KUMI_FWD(t));
    }
  }
  namespace result
  {
    template<typename Target, product_type T> struct member_cast
    {
      using type = decltype(kumi::member_cast<Target, T>(std::declval<T>()));
    };
    template<typename Target, product_type T> using member_cast_t = typename member_cast<Target, T>::type;
  }
}
namespace kumi
{
  template<product_type... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto cat(Ts&&... ts)
  requires(follows_same_semantic<Ts...>)
  {
    if constexpr (sizeof...(Ts) == 0) return tuple{};
    else
    {
      constexpr auto count = (1ULL + ... + size_v<Ts>);
      constexpr auto pos = [&]() {
        struct
        {
          std::size_t t[count], e[count];
        } that{};
        std::size_t k = 0, offset = 0;
        auto locate = [&]<std::size_t... I>(std::index_sequence<I...>) {
          (((that.t[I + offset] = k), (that.e[I + offset] = I)), ...);
          offset += sizeof...(I);
          k++;
        };
        (locate(std::make_index_sequence<size_v<Ts>>{}), ...);
        return that;
      }();
      using res_type = result::common_product_type_t<std::remove_cvref_t<Ts>...>;
      return [&]<std::size_t... N>(auto&& tuples, std::index_sequence<N...>) {
        using rts = std::remove_cvref_t<decltype(tuples)>;
        using type = _::builder_make_t<res_type, element_t<pos.e[N], std::remove_cvref_t<element_t<pos.t[N], rts>>>...>;
        return type{get<pos.e[N]>(get<pos.t[N]>(KUMI_FWD(tuples)))...};
      }(kumi::forward_as_tuple(KUMI_FWD(ts)...), std::make_index_sequence<count - 1>{});
    }
  }
  namespace result
  {
    template<product_type... Ts> struct cat
    {
      using type = decltype(kumi::cat(std::declval<Ts>()...));
    };
    template<product_type... Ts> using cat_t = typename cat<Ts...>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<product_type Tuple, typename IndexSequence, template<typename...> class Meta = std::type_identity>
    struct as_tuple;
    template<product_type Tuple, std::size_t... I> struct as_tuple<Tuple, std::index_sequence<I...>>
    {
      using type = kumi::tuple<element_t<I, Tuple>...>;
    };
    template<product_type Tuple, std::size_t... I, template<typename...> class Meta>
    struct as_tuple<Tuple, std::index_sequence<I...>, Meta>
    {
      using type = kumi::tuple<typename Meta<element_t<I, Tuple>>::type...>;
    };
  }
  template<typename T>
  requires(!requires { T::is_homogeneous; })
  struct is_homogeneous<T> : is_homogeneous<typename _::as_tuple<T, std::make_index_sequence<size_v<T>>>::type>
  {
  };
  template<typename Type, typename... Ts>
  requires(!product_type<Type> && _::implicit_constructible<Type, Ts...>)
  [[nodiscard]] KUMI_ABI constexpr auto from_tuple(tuple<Ts...> const& t)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return Type{get<I>(t)...};
    }(std::make_index_sequence<sizeof...(Ts)>());
  }
  template<record_type Type, typename... Ts>
  requires(equivalent<Type, record<Ts...>>)
  [[nodiscard]] KUMI_ABI constexpr auto from_record(record<Ts...> const& r)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return Type{get<name_of(as<element_t<I, Type>>{})>(r)...};
    }(std::make_index_sequence<size_v<Type>>());
  }
  template<product_type Type> [[nodiscard]] KUMI_ABI constexpr auto to_tuple(Type&& t)
  {
    return apply([](auto&&... elems) { return tuple{elems...}; }, KUMI_FWD(t));
  }
  template<static_container S>
  [[nodiscard]] KUMI_ABI constexpr auto to_tuple(S&& s)
  requires(!product_type<S>)
  {
    constexpr auto N = container_size_v<S>;
    if constexpr (N == 0) return tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple{KUMI_FWD(s)[I]...};
      }(std::make_index_sequence<N>{});
  }
  template<record_type Type> [[nodiscard]] KUMI_ABI constexpr auto to_record(Type&& r)
  {
    if constexpr (sized_product_type<Type, 0>) return kumi::record{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return record{field<name_of(as<element_t<I, Type>>{})> =
                        get<name_of(as<element_t<I, Type>>{})>(KUMI_FWD(r))...};
      }(std::make_index_sequence<size_v<Type>>{});
  }
  template<typename T, template<typename...> class Meta = std::type_identity> struct as_tuple;
  template<typename T, template<typename...> class Meta>
  requires(product_type<T>)
  struct as_tuple<T, Meta> : _::as_tuple<T, std::make_index_sequence<size_v<T>>, Meta>
  {
  };
  template<typename T, template<typename...> class Meta>
  requires(!product_type<T>)
  struct as_tuple<T, Meta>
  {
    using type = kumi::tuple<typename Meta<T>::type>;
  };
  template<typename T, template<typename...> class Meta = std::type_identity>
  using as_tuple_t = typename as_tuple<T, Meta>::type;
}
namespace kumi
{
  template<std::size_t I0, std::size_t I1, product_type Tuple>
  requires((I0 <= size_v<Tuple>) && (I1 <= size_v<Tuple>))
  [[nodiscard]] KUMI_ABI constexpr auto extract(Tuple&& t,
                                                [[maybe_unused]] index_t<I0> i0,
                                                [[maybe_unused]] index_t<I1> i1) noexcept
  {
    return [&]<std::size_t... N>(std::index_sequence<N...>) {
      using final_t = _::builder_make_t<Tuple, element_t<N + I0, Tuple>...>;
      return final_t{get<N + I0>(KUMI_FWD(t))...};
    }(std::make_index_sequence<I1 - I0>());
  }
  template<std::size_t I0, product_type Tuple>
  requires(I0 <= size_v<Tuple>)
  [[nodiscard]] KUMI_ABI constexpr auto extract(Tuple&& t, index_t<I0> i0) noexcept
  {
    return extract(KUMI_FWD(t), i0, index<size_v<Tuple>>);
  }
  template<std::size_t I0, product_type Tuple>
  requires(I0 <= size_v<Tuple>)
  [[nodiscard]] KUMI_ABI constexpr auto split(Tuple&& t, [[maybe_unused]] index_t<I0> i0) noexcept
  {
    auto select = [&]<typename O, std::size_t... I>(O, std::index_sequence<I...>) {
      using type = _::builder_make_t<Tuple, element_t<O::value + I, Tuple>...>;
      return type{get<O::value + I>(KUMI_FWD(t))...};
    };
    return kumi::tuple{select(kumi::index<0>, std::make_index_sequence<I0>{}),
                       select(kumi::index<I0>, std::make_index_sequence<size_v<Tuple> - I0>{})};
  }
  namespace result
  {
    template<product_type T, std::size_t I0, std::size_t I1 = std::size_t(-1)> struct extract
    {
      using type = decltype(kumi::extract(std::declval<T>(), kumi::index_t<I0>{}, kumi::index_t<I1>{}));
    };
    template<product_type T, std::size_t I0> struct extract<T, I0>
    {
      using type = decltype(kumi::extract(std::declval<T>(), kumi::index_t<I0>{}));
    };
    template<product_type T, std::size_t I0> struct split
    {
      using type = decltype(kumi::split(std::declval<T>(), kumi::index_t<I0>{}));
    };
    template<product_type T, std::size_t I0, std::size_t I1 = std::size_t(-1)>
    using extract_t = typename extract<T, I0, I1>::type;
    template<product_type T, std::size_t I0> using split_t = typename split<T, I0>::type;
  }
}
namespace kumi
{
  template<typename Function, product_type Tuple, product_type... Tuples>
  KUMI_ABI constexpr void for_each(Function f, Tuple&& t, Tuples&&... ts)
  requires((compatible_product_types<Tuple, Tuples...>) && (_::supports_call<Function&, Tuple, Tuples...>))
  {
    if constexpr (sized_product_type<Tuple, 0>) return;
    else if constexpr (record_type<Tuple>)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        constexpr auto fields = members_of(as<Tuple>{});
        [[maybe_unused]] auto call = [&]<typename M>(M) {
          constexpr auto field = get<M::value>(fields);
          f(get<field>(KUMI_FWD(t)), get<field>(KUMI_FWD(ts))...);
        };
        (call(std::integral_constant<std::size_t, I>{}), ...);
      }(std::make_index_sequence<size_v<Tuple>>{});
    }
    else
    {
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        [[maybe_unused]] auto call = [&]<typename M>(M) {
          f(get<M::value>(KUMI_FWD(t)), get<M::value>(KUMI_FWD(ts))...);
        };
        (call(std::integral_constant<std::size_t, I>{}), ...);
      }(std::make_index_sequence<size<Tuple>::value>());
    }
  }
  template<typename Function, product_type Tuple, product_type... Tuples>
  requires(!record_type<Tuple> && (!record_type<Tuples> && ...))
  KUMI_ABI constexpr void for_each_index(Function f, Tuple&& t, Tuples&&... ts)
  {
    if constexpr (sized_product_type<Tuple, 0>) return;
    else
    {
      auto const invoker{[&, f](auto const i) { f(i, get<i.value>(KUMI_FWD(t)), get<i.value>(KUMI_FWD(ts))...); }};
      [=]<std::size_t... I>(std::index_sequence<I...>) {
        (invoker(std::integral_constant<unsigned, I>{}), ...);
      }(std::make_index_sequence<size<Tuple>::value>());
    }
  }
  template<typename Function, record_type Tuple, record_type... Tuples>
  requires(compatible_product_types<std::remove_cvref_t<Tuple>, std::remove_cvref_t<Tuples>...>)
  KUMI_ABI constexpr void for_each_field(Function f, Tuple&& t, Tuples&&... ts)
  {
    if constexpr (sized_product_type<Tuple, 0>) return;
    else
    {
      constexpr auto fields = members_of(as<Tuple>{});
      auto const invoker = [&]<std::size_t I>(std::integral_constant<std::size_t, I>) {
        constexpr auto field = get<I>(fields);
        f(field, get<field>(KUMI_FWD(t)), get<field>(KUMI_FWD(ts))...);
      };
      [=]<std::size_t... I>(std::index_sequence<I...>) {
        (invoker(std::integral_constant<std::size_t, I>{}), ...);
      }(std::make_index_sequence<size<Tuple>::value>());
    }
  }
}
namespace kumi
{
  template<typename Pred, product_type Tuple> [[nodiscard]] KUMI_ABI constexpr auto locate(Tuple&& t, Pred p) noexcept
  {
    return kumi::apply(
      [&](auto&&... m) {
        bool checks[] = {p(m)...};
        for (std::size_t i = 0; i < size_v<Tuple>; ++i)
          if (checks[i]) return i;
        return size_v<Tuple>;
      },
      KUMI_FWD(t));
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T> KUMI_ABI constexpr auto flat_one(T&& t)
    {
      if constexpr (sized_product_type<T, 0>) return KUMI_FWD(t);
      else
        return [&]<std::size_t... I>(std::index_sequence<I...>) {
          auto v_or_r = [&]<typename V>(V&& v) {
            using FV = kumi::result::field_value_of_t<V>;
            constexpr auto name = name_of(as<V>{});
            if constexpr (record_type<FV>)
            {
              return [&]<std::size_t... J>(std::index_sequence<J...>) {
                return record{field<concatenate_str<name, name_of(as<element_t<J, FV>>{})>()> =
                                (field_value_of(get<J>(field_value_of(KUMI_FWD(v)))))...};
              }(std::make_index_sequence<size_v<FV>>{});
            }
            else return record{KUMI_FWD(v)};
          };
          return cat(v_or_r(get<I>(KUMI_FWD(t)))...);
        }(std::make_index_sequence<size_v<T>>{});
    }
    template<auto Prefix, typename T> KUMI_ABI constexpr auto flat(T&& t)
    {
      using Prefix_type = std::remove_cvref_t<decltype(Prefix)>;
      if constexpr (sized_product_type<T, 0>) return KUMI_FWD(t);
      else
        return [&]<std::size_t... I>(std::index_sequence<I...>) {
          auto v_or_r = [&]<typename V>(V&& v) {
            constexpr auto name = [&] {
              if constexpr (std::is_same_v<Prefix_type, unit>) return name_of(as<V>{});
              else return concatenate_str<Prefix, name_of(as<V>{})>();
            }();
            if constexpr (record_type<kumi::result::field_value_of_t<V>>)
              return flat<name>(field_value_of(KUMI_FWD(v)));
            else return record{field<name> = (field_value_of(KUMI_FWD(v)))};
          };
          return cat(v_or_r(get<I>(KUMI_FWD(t)))...);
        }(std::make_index_sequence<size_v<T>>{});
    }
    template<auto Prefix, typename T, typename F> KUMI_ABI constexpr auto flat_map(T&& t, F&& f)
    {
      if constexpr (sized_product_type<T, 0>) return KUMI_FWD(t);
      else
        return [&]<std::size_t... I>(std::index_sequence<I...>) {
          using Prefix_type = std::remove_cvref_t<decltype(Prefix)>;
          auto v_or_r = [&]<typename V>(V&& v) {
            constexpr auto name = [&] {
              if constexpr (std::is_same_v<Prefix_type, unit>) return name_of(as<V>{});
              else return concatenate_str<Prefix, name_of(as<V>{})>();
            }();
            if constexpr (record_type<kumi::result::field_value_of_t<V>>)
              return flat_map<name>(field_value_of(KUMI_FWD(v)), KUMI_FWD(f));
            else return record{field<name> = KUMI_FWD(f)(field_value_of(v))};
          };
          return cat(v_or_r(get<I>(KUMI_FWD(t)))...);
        }(std::make_index_sequence<size_v<T>>{});
    }
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto flatten(T&& t)
  {
    if constexpr (sized_product_type<T, 0>) return t;
    else if constexpr (record_type<T>) return _::flat_one(KUMI_FWD(t));
    else
    {
      return kumi::apply(
        [](auto&&... m) {
          auto v_or_t = []<typename V>(V&& v) {
            if constexpr (product_type<V>) return KUMI_FWD(v);
            else return kumi::tuple{KUMI_FWD(v)};
          };
          return cat(v_or_t(KUMI_FWD(m))...);
        },
        KUMI_FWD(t));
    }
  }
  template<product_type T, typename Func> [[nodiscard]] KUMI_ABI constexpr auto flatten_all(T&& t, Func&& f)
  {
    if constexpr (sized_product_type<T, 0>) return t;
    else if constexpr (record_type<T>) return _::flat_map<none>(KUMI_FWD(t), KUMI_FWD(f));
    else
    {
      return kumi::apply(
        [&](auto&&... m) {
          auto v_or_t = [&]<typename V>(V&& v) {
            if constexpr (product_type<V>) return flatten_all(KUMI_FWD(v), KUMI_FWD(f));
            else return kumi::tuple{KUMI_FWD(f)(v)};
          };
          return cat(v_or_t(KUMI_FWD(m))...);
        },
        KUMI_FWD(t));
    }
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto flatten_all(T&& t)
  {
    if constexpr (sized_product_type<T, 0>) return t;
    else if constexpr (record_type<T>) return _::flat<none>(KUMI_FWD(t));
    else
    {
      return kumi::apply(
        [](auto&&... m) {
          auto v_or_t = []<typename V>(V&& v) {
            if constexpr (product_type<V>) return flatten_all(KUMI_FWD(v));
            else return kumi::tuple{KUMI_FWD(v)};
          };
          return cat(v_or_t(KUMI_FWD(m))...);
        },
        KUMI_FWD(t));
    }
  }
  namespace result
  {
    template<product_type T> struct flatten
    {
      using type = decltype(kumi::flatten(std::declval<T>()));
    };
    template<product_type T, typename Func = void> struct flatten_all
    {
      using type = decltype(kumi::flatten_all(std::declval<T>(), std::declval<Func>()));
    };
    template<product_type T> struct flatten_all<T>
    {
      using type = decltype(kumi::flatten_all(std::declval<T>()));
    };
    template<product_type T> using flatten_t = typename flatten<T>::type;
    template<product_type T, typename Func = void> using flatten_all_t = typename flatten_all<T, Func>::type;
  }
  template<product_type T> [[nodiscard]] KUMI_ABI auto as_flat_ptr(T&& t) noexcept
  {
    return kumi::flatten_all(KUMI_FWD(t), [](auto& m) { return &m; });
  }
  namespace result
  {
    template<product_type T> struct as_flat_ptr
    {
      using type = decltype(kumi::as_flat_ptr(std::declval<T>()));
    };
    template<product_type T> using as_flat_ptr_t = typename as_flat_ptr<T>::type;
  }
}
namespace kumi
{
  template<std::size_t N, typename T> [[nodiscard]] KUMI_ABI constexpr auto fill(T const& v) noexcept
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      auto eval = [](auto, auto const& vv) { return vv; };
      return kumi::tuple{eval(index<I>, v)...};
    }(std::make_index_sequence<N>{});
  }
  template<std::size_t N, typename Function> [[nodiscard]] KUMI_ABI constexpr auto generate(Function const& f) noexcept
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::tuple{f(index<I>)...};
    }(std::make_index_sequence<N>{});
  }
  template<std::size_t N, typename T> [[nodiscard]] KUMI_ABI constexpr auto iota(T v) noexcept
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::tuple{static_cast<T>(v + I)...};
    }(std::make_index_sequence<N>{});
  }
  namespace result
  {
    template<std::size_t N, typename T> struct fill
    {
      using type = decltype(kumi::fill<N>(std::declval<T>()));
    };
    template<std::size_t N, typename Function> struct generate
    {
      using type = decltype(kumi::generate<N>(std::declval<Function>()));
    };
    template<std::size_t N, typename T> struct iota
    {
      using type = decltype(kumi::iota<N>(std::declval<T>()));
    };
    template<std::size_t N, typename T> using fill_t = typename fill<N, T>::type;
    template<std::size_t N, typename Function> using generate_t = typename generate<N, Function>::type;
    template<std::size_t N, typename T> using iota_t = typename iota<N, T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename F, typename T> struct foldable
    {
      F func;
      T value;
      template<typename W> KUMI_ABI friend constexpr decltype(auto) operator>>(foldable&& x, foldable<F, W>&& y)
      {
        return _::foldable{x.func, x.func(x.value, y.value)};
      }
      template<typename W> KUMI_ABI friend constexpr decltype(auto) operator<<(foldable&& x, foldable<F, W>&& y)
      {
        return _::foldable{x.func, x.func(x.value, y.value)};
      }
    };
    template<class F, class T> foldable(F const&, T&&) -> foldable<F, T>;
  }
  template<product_type S1, sized_product_type<size_v<S1>> S2, typename T, typename Sum, typename Prod>
  requires(compatible_product_types<S1, S2>)
  [[nodiscard]] KUMI_ABI constexpr auto inner_product(S1&& s1, S2&& s2, T init, Sum sum, Prod prod) noexcept
  {
    if constexpr (sized_product_type<S1, 0>) return init;
    else if constexpr (record_type<S1>)
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (_::foldable{sum, prod(get<name_of(as<element_t<I, S1>>{})>(KUMI_FWD(s1)),
                                      get<name_of(as<element_t<I, S1>>{})>(KUMI_FWD(s2)))} >>
                ... >> _::foldable{sum, init})
          .value;
      }(std::make_index_sequence<size<S1>::value>());
    }
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (_::foldable{sum, prod(get<I>(KUMI_FWD(s1)), get<I>(KUMI_FWD(s2)))} >> ... >> _::foldable{sum, init})
          .value;
      }(std::make_index_sequence<size<S1>::value>());
    }
  }
  template<product_type S1, sized_product_type<size_v<S1>> S2, typename T>
  requires(compatible_product_types<S1, S2>)
  [[nodiscard]] KUMI_ABI constexpr auto inner_product(S1&& s1, S2&& s2, T init) noexcept
  {
    if constexpr (sized_product_type<S1, 0>) return init;
    else if constexpr (record_type<S1>)
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (
          init + ... +
          (get<name_of(as<element_t<I, S1>>{})>(KUMI_FWD(s1)) * get<name_of(as<element_t<I, S1>>{})>(KUMI_FWD(s2))));
      }(std::make_index_sequence<size<S1>::value>());
    }
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (init + ... + (get<I>(KUMI_FWD(s1)) * get<I>(KUMI_FWD(s2))));
      }(std::make_index_sequence<size<S1>::value>());
    }
  }
  namespace result
  {
    template<product_type S1, sized_product_type<S1::size()> S2, typename T, typename Sum, typename Prod>
    struct inner_product
    {
      using type = decltype(kumi::inner_product(
        std::declval<S1>(), std::declval<S2>(), std::declval<T>(), std::declval<Sum>(), std::declval<Prod>()));
    };
    template<product_type S1, sized_product_type<S1::size()> S2, typename T> struct inner_product<S1, S2, T, void, void>
    {
      using type = decltype(kumi::inner_product(std::declval<S1>(), std::declval<S2>(), std::declval<T>()));
    };
    template<product_type S1, sized_product_type<S1::size()> S2, typename T, typename Sum = void, typename Prod = void>
    using inner_product_t = typename inner_product<S1, S2, T, Sum, Prod>::type;
  }
}
namespace kumi
{
  template<product_type Tuple, typename Function, sized_product_type<size_v<Tuple>>... Tuples>
  [[nodiscard]] KUMI_ABI constexpr auto map(Function f, Tuple&& t0, Tuples&&... others)
  requires(compatible_product_types<Tuple, Tuples...> && _::supports_call<Function, Tuple &&, Tuples && ...>)
  {
    if constexpr (sized_product_type<Tuple, 0>) return _::builder<Tuple>::make();
    else
    {
      auto const call = [&]<std::size_t N, typename... Ts>(index_t<N>, Ts&&... args) {
        if constexpr (record_type<Tuple>)
        {
          constexpr auto field = name_of(as<element_t<N, Tuple>>{});
          return field_name<field>{} = f(get<field>(args)...);
        }
        else return f(get<N>(KUMI_FWD(args))...);
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return _::builder<Tuple>::make(call(index<I>, KUMI_FWD(t0), KUMI_FWD(others)...)...);
      }(std::make_index_sequence<size_v<Tuple>>());
    }
  }
  namespace result
  {
    template<typename Function, product_type T, sized_product_type<size<T>::value>... Ts> struct map
    {
      using type = decltype(kumi::map(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    };
    template<typename Function, product_type T, sized_product_type<size<T>::value>... Ts>
    using map_t = typename map<Function, T, Ts...>::type;
  }
  template<product_type Tuple, typename Function, sized_product_type<size_v<Tuple>>... Tuples>
  [[nodiscard]] KUMI_ABI constexpr auto map_index(Function f, Tuple&& t0, Tuples&&... others)
  requires(!record_type<Tuple> && (!record_type<Tuples> && ...))
  {
    if constexpr (sized_product_type<Tuple, 0>) return _::builder<Tuple>::make();
    else
    {
      auto const call = [&]<std::size_t N, typename... Ts>(index_t<N> idx, Ts&&... args) {
        return f(idx, get<N>(KUMI_FWD(args))...);
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return _::builder<Tuple>::make(call(index<I>, KUMI_FWD(t0), KUMI_FWD(others)...)...);
      }(std::make_index_sequence<size_v<Tuple>>());
    }
  }
  namespace result
  {
    template<typename Function, product_type T, sized_product_type<size<T>::value>... Ts> struct map_index
    {
      using type = decltype(kumi::map_index(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    };
    template<typename Function, product_type T, sized_product_type<size<T>::value>... Ts>
    using map_index_t = typename map_index<Function, T, Ts...>::type;
  }
  template<record_type Tuple, typename Function, sized_product_type<size<Tuple>::value>... Tuples>
  requires(compatible_product_types<Tuple, Tuples...>)
  constexpr auto map_field(Function f, Tuple&& t0, Tuples&&... others)
  {
    if constexpr (sized_product_type<Tuple, 0>) return _::builder<Tuple>::make();
    else
    {
      auto const call = [&]<std::size_t N, typename... Ts>(index_t<N>, Ts&&... args) {
        constexpr auto field = name_of(as<element_t<N, Tuple>>{});
        return field_name<field>{} = f(field, (get<field>(args))...);
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return _::builder<Tuple>::make(call(index<I>, KUMI_FWD(t0), KUMI_FWD(others)...)...);
      }(std::make_index_sequence<size<Tuple>::value>());
    }
  }
  namespace result
  {
    template<typename Function, record_type T, sized_product_type<size<T>::value>... Ts> struct map_field
    {
      using type = decltype(kumi::map_field(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    };
    template<typename Function, record_type T, sized_product_type<size<T>::value>... Ts>
    using map_field_t = typename map_field<Function, T, Ts...>::type;
  }
}
namespace kumi
{
  template<product_type Tuple, typename T> [[nodiscard]] KUMI_ABI constexpr auto push_front(Tuple&& t, T&& v)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return _::builder<Tuple>::make(KUMI_FWD(v), get<I>(KUMI_FWD(t))...);
    }(std::make_index_sequence<size_v<Tuple>>());
  }
  template<product_type Tuple> [[nodiscard]] KUMI_ABI constexpr auto pop_front(Tuple&& t)
  {
    if constexpr (sized_product_type_or_more<Tuple, 1>) return extract(KUMI_FWD(t), index<1>);
    else return _::builder<Tuple>::make();
  }
  template<product_type Tuple, typename T> [[nodiscard]] KUMI_ABI constexpr auto push_back(Tuple&& t, T&& v)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return _::builder<Tuple>::make(get<I>(KUMI_FWD(t))..., KUMI_FWD(v));
    }(std::make_index_sequence<size_v<Tuple>>());
  }
  template<product_type Tuple> [[nodiscard]] KUMI_ABI constexpr auto pop_back(Tuple&& t)
  {
    if constexpr (sized_product_type_or_more<Tuple, 1>) return extract(KUMI_FWD(t), index<0>, index<size_v<Tuple> - 1>);
    else return _::builder<Tuple>::make();
  }
  namespace result
  {
    template<product_type Tuple, typename T> struct push_front
    {
      using type = decltype(kumi::push_front(std::declval<Tuple>(), std::declval<T>()));
    };
    template<product_type Tuple> struct pop_front
    {
      using type = decltype(kumi::pop_front(std::declval<Tuple>()));
    };
    template<product_type Tuple, typename T> struct push_back
    {
      using type = decltype(kumi::push_back(std::declval<Tuple>(), std::declval<T>()));
    };
    template<product_type Tuple> struct pop_back
    {
      using type = decltype(kumi::pop_back(std::declval<Tuple>()));
    };
    template<product_type Tuple, typename T> using push_front_t = typename push_front<Tuple, T>::type;
    template<product_type Tuple> using pop_front_t = typename pop_front<Tuple>::type;
    template<product_type Tuple, typename T> using push_back_t = typename push_back<Tuple, T>::type;
    template<product_type Tuple> using pop_back_t = typename pop_back<Tuple>::type;
  }
}
namespace kumi
{
  template<typename Function, product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto fold_left(Function f, T&& t, Value init)
  {
    if constexpr (record_type<T>) return fold_left(f, values_of(KUMI_FWD(t)), init);
    else if constexpr (sized_product_type<T, 0>) return init;
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (_::foldable{f, init} >> ... >> _::foldable{f, get<I>(KUMI_FWD(t))}).value;
      }(std::make_index_sequence<size_v<T>>());
    }
  }
  template<typename Function, sized_product_type_or_more<1> T>
  [[nodiscard]] KUMI_ABI constexpr auto fold_left(Function f, T&& t)
  {
    if constexpr (record_type<T>) return fold_left(f, values_of(KUMI_FWD(t)));
    else if constexpr (sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
    else
    {
      auto&& [heads, tail] = split(KUMI_FWD(t), index<2>);
      return fold_left(f, tail, kumi::apply(f, heads));
    }
  }
  template<typename Function, product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto fold_right(Function f, T&& t, Value init)
  {
    if constexpr (record_type<T>) return fold_right(f, values_of(KUMI_FWD(t)), init);
    else if constexpr (sized_product_type<T, 0>) return init;
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (_::foldable{f, get<I>(KUMI_FWD(t))} << ... << _::foldable{f, init}).value;
      }(std::make_index_sequence<size_v<T>>());
    }
  }
  template<typename Function, sized_product_type_or_more<1> T>
  [[nodiscard]] KUMI_ABI constexpr auto fold_right(Function f, T&& t)
  {
    if constexpr (record_type<T>) return fold_right(f, values_of(KUMI_FWD(t)));
    else if constexpr (sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
    else
    {
      auto&& [head, tails] = split(KUMI_FWD(t), index<size_v<T> - 2>);
      return fold_right(f, head, kumi::apply(f, tails));
    }
  }
  namespace result
  {
    template<typename Function, product_type T, typename Value = void> struct fold_right
    {
      using type = decltype(kumi::fold_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, product_type T> struct fold_right<Function, T>
    {
      using type = decltype(kumi::fold_right(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, product_type T, typename Value = void> struct fold_left
    {
      using type = decltype(kumi::fold_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, product_type T> struct fold_left<Function, T>
    {
      using type = decltype(kumi::fold_left(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, product_type T, typename Value = void>
    using fold_right_t = typename fold_right<Function, T, Value>::type;
    template<typename Function, product_type T, typename Value = void>
    using fold_left_t = typename fold_left<Function, T, Value>::type;
  }
}
namespace kumi
{
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto max(T&& t) noexcept
  {
    if constexpr (record_type<T>) return max(values_of(KUMI_FWD(t)));
    else if constexpr (sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
    else
    {
      auto base = get<0>(KUMI_FWD(t));
      return kumi::fold_left([]<typename U>(auto cur, U u) { return cur > u ? cur : u; }, KUMI_FWD(t), base);
    }
  }
  template<product_type T, typename F> [[nodiscard]] KUMI_ABI constexpr auto max(T&& t, F f) noexcept
  {
    if constexpr (record_type<T>) return max(values_of(KUMI_FWD(t)), f);
    else if constexpr (sized_product_type<T, 1>) return f(get<0>(KUMI_FWD(t)));
    else
    {
      auto base = f(get<0>(KUMI_FWD(t)));
      return kumi::fold_left([f]<typename U>(auto cur, U const& u) { return cur > f(u) ? cur : f(u); }, KUMI_FWD(t),
                             base);
    }
  }
  template<product_type T, typename F> [[nodiscard]] KUMI_ABI constexpr auto max_flat(T&& t, F f) noexcept
  {
    auto flat_t = kumi::flatten_all(KUMI_FWD(t));
    return max(flat_t, f);
  }
  namespace result
  {
    template<typename T, typename F = void> struct max
    {
      using type = decltype(kumi::max(std::declval<T>(), std::declval<F>()));
    };
    template<typename T> struct max<T, void>
    {
      using type = decltype(kumi::max(std::declval<T>()));
    };
    template<typename T, typename F> struct max_flat
    {
      using type = decltype(kumi::max_flat(std::declval<T>(), std::declval<F>()));
    };
    template<typename T, typename F = void> using max_t = typename max<T, F>::type;
    template<typename T, typename F> using max_flat_t = typename max_flat<T, F>::type;
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto min(T&& t) noexcept
  {
    if constexpr (record_type<T>) return min(values_of(KUMI_FWD(t)));
    else if constexpr (sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
    else
    {
      auto base = get<0>(KUMI_FWD(t));
      return kumi::fold_left([]<typename U>(auto cur, U u) { return cur < u ? cur : u; }, KUMI_FWD(t), base);
    }
  }
  template<product_type T, typename F> [[nodiscard]] KUMI_ABI constexpr auto min(T&& t, F f) noexcept
  {
    if constexpr (record_type<T>) return min(values_of(KUMI_FWD(t)), f);
    else if constexpr (sized_product_type<T, 1>) return f(get<0>(KUMI_FWD(t)));
    else
    {
      auto base = f(get<0>(KUMI_FWD(t)));
      return kumi::fold_left([f]<typename U>(auto cur, U const& u) { return cur < f(u) ? cur : f(u); }, KUMI_FWD(t),
                             base);
    }
  }
  template<product_type T, typename F> [[nodiscard]] KUMI_ABI constexpr auto min_flat(T&& t, F f) noexcept
  {
    auto flat_t = kumi::flatten_all(KUMI_FWD(t));
    return min(flat_t, f);
  }
  namespace result
  {
    template<typename T, typename F = void> struct min
    {
      using type = decltype(kumi::min(std::declval<T>(), std::declval<F>()));
    };
    template<typename T> struct min<T, void>
    {
      using type = decltype(kumi::min(std::declval<T>()));
    };
    template<typename T, typename F> struct min_flat
    {
      using type = decltype(kumi::min_flat(std::declval<T>(), std::declval<F>()));
    };
    template<typename T, typename F = void> using min_t = typename min<T, F>::type;
    template<typename T, typename F> using min_flat_t = typename min_flat<T, F>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<template<typename> typename Pred, product_type T> struct selector_t
    {
      KUMI_ABI constexpr auto operator()() const noexcept
      {
        struct
        {
          std::size_t count = {}, cut = {}, t[1 + size_v<T>];
        } that{};
        auto locate = [&]<std::size_t... I>(std::index_sequence<I...>) {
          ((Pred<raw_element_t<I, T>>::value ? (that.t[that.count++] = I) : I), ...);
          that.cut = that.count;
          ((!Pred<raw_element_t<I, T>>::value ? (that.t[that.count++] = I) : I), ...);
        };
        locate(std::make_index_sequence<size_v<T>>{});
        return that;
      }
    };
    template<template<typename> typename Pred, product_type T> inline constexpr selector_t<Pred, T> selector{};
  }
  template<template<typename> typename Pred, product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto partition(T&& t) noexcept
  {
    constexpr auto pos = _::selector<Pred, T>();
    auto select = [&]<typename O, std::size_t... I>(O, std::index_sequence<I...>) {
      using type = _::builder_make_t<T, element_t<pos.t[O::value + I], T>...>;
      return type{get<pos.t[O::value + I]>(KUMI_FWD(t))...};
    };
    return kumi::tuple{select(kumi::index<0>, std::make_index_sequence<pos.cut>{}),
                       select(kumi::index<pos.cut>, std::make_index_sequence<size_v<T> - pos.cut>{})};
  }
  template<template<typename> typename Pred, product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto filter(T&& t) noexcept
  {
    constexpr auto pos = _::selector<Pred, T>();
    if constexpr (sized_product_type<T, 0>) return _::builder<T>::make();
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = _::builder_make_t<T, element_t<pos.t[I], T>...>;
        return type{get<pos.t[I]>(KUMI_FWD(t))...};
      }(std::make_index_sequence<pos.cut>{});
  }
  template<template<typename> typename Pred, product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto filter_not(T&& t) noexcept
  {
    constexpr auto pos = _::selector<Pred, T>();
    if constexpr (sized_product_type<T, 0>) return _::builder<T>::make();
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = _::builder_make_t<T, element_t<pos.t[pos.cut + I], T>...>;
        return type{get<pos.t[pos.cut + I]>(KUMI_FWD(t))...};
      }(std::make_index_sequence<size_v<T> - pos.cut>{});
  }
  namespace result
  {
    template<template<typename> typename Pred, kumi::product_type T> struct partition
    {
      using type = decltype(kumi::partition<Pred>(std::declval<T>()));
    };
    template<template<typename> typename Pred, kumi::product_type T> struct filter
    {
      using type = decltype(kumi::filter<Pred>(std::declval<T>()));
    };
    template<template<typename> typename Pred, kumi::product_type T> struct filter_not
    {
      using type = decltype(kumi::filter_not<Pred>(std::declval<T>()));
    };
    template<template<typename> typename Pred, kumi::product_type T>
    using partition_t = typename partition<Pred, T>::type;
    template<template<typename> typename Pred, kumi::product_type T> using filter_t = typename filter<Pred, T>::type;
    template<template<typename> typename Pred, kumi::product_type T>
    using filter_not_t = typename filter_not<Pred, T>::type;
  }
}
namespace kumi
{
  template<typename Pred, product_type T> [[nodiscard]] KUMI_ABI constexpr auto all_of(T&& ts, Pred p) noexcept
  {
    if constexpr (record_type<T>) return all_of(values_of(KUMI_FWD(ts)), p);
    else if constexpr (sized_product_type<T, 0>) return true;
    else if constexpr (sized_product_type<T, 1>) return p(get<0>(KUMI_FWD(ts)));
    else return kumi::apply([&](auto&&... m) { return (p(m) && ...); }, KUMI_FWD(ts));
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto all_of(T&& ts) noexcept
  {
    if constexpr (record_type<T>) return all_of(values_of(KUMI_FWD(ts)));
    else if constexpr (sized_product_type<T, 0>) return true;
    else if constexpr (sized_product_type<T, 1>) return !!get<0>(KUMI_FWD(ts));
    else return kumi::apply([&](auto&&... m) { return (m && ...); }, KUMI_FWD(ts));
  }
  template<typename Pred, product_type T> [[nodiscard]] KUMI_ABI constexpr auto any_of(T&& ts, Pred p) noexcept
  {
    if constexpr (record_type<T>) return any_of(values_of(KUMI_FWD(ts)), p);
    else if constexpr (sized_product_type<T, 0>) return true;
    else if constexpr (sized_product_type<T, 1>) return p(get<0>(KUMI_FWD(ts)));
    else return kumi::apply([&](auto&&... m) { return (p(m) || ...); }, KUMI_FWD(ts));
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto any_of(T&& ts) noexcept
  {
    if constexpr (record_type<T>) return any_of(values_of(KUMI_FWD(ts)));
    else if constexpr (sized_product_type<T, 0>) return false;
    else if constexpr (sized_product_type<T, 1>) return !!get<0>(KUMI_FWD(ts));
    else return kumi::apply([&](auto&&... m) { return (m || ...); }, KUMI_FWD(ts));
  }
  template<typename Pred, product_type Tuple> [[nodiscard]] KUMI_ABI constexpr bool none_of(Tuple&& ts, Pred p) noexcept
  {
    return !any_of(KUMI_FWD(ts), p);
  }
  template<product_type Tuple> [[nodiscard]] KUMI_ABI constexpr bool none_of(Tuple&& ts) noexcept
  {
    return !any_of(KUMI_FWD(ts));
  }
  template<typename Pred, product_type T> [[nodiscard]] KUMI_ABI constexpr std::size_t count_if(T&& ts, Pred p) noexcept
  {
    constexpr std::size_t o = 1ULL;
    constexpr std::size_t z = 0ULL;
    if constexpr (sized_product_type<T, 0>) return z;
    else return kumi::apply([&](auto&&... m) { return ((p(m) ? o : z) + ... + z); }, KUMI_FWD(ts));
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr std::size_t count(T&& ts) noexcept
  {
    return count_if(KUMI_FWD(ts), [](auto const& m) { return static_cast<bool>(m); });
  }
}
namespace kumi
{
  namespace _
  {
    template<index_map auto idxs, product_type T> consteval auto in_bound_indexes()
    {
      using map_t = std::remove_cvref_t<decltype(idxs)>;
      if constexpr (sized_product_type<T, 0>) return false;
      else if constexpr (sized_product_type<map_t, 0>) return true;
      else
        return []<std::size_t... N>(std::index_sequence<N...>) {
          bool checks[] = {([]() {
            if constexpr (product_type<element_t<N, map_t>>) return in_bound_indexes<get<N>(idxs), T>();
            else if constexpr (get<N>(idxs) < size_v<T>) return true;
            else return false;
          }())...};
          for (std::size_t i = 0; i < idxs.size(); ++i)
            if (!checks[i]) return false;
          return true;
        }(std::make_index_sequence<idxs.size()>{});
    };
  }
  template<std::size_t... Idx, product_type T>
  requires((Idx < size_v<T>) && ...)
  [[nodiscard]] KUMI_ABI constexpr auto reorder(T&& t)
  {
    return _::builder<T>::make(get<Idx>(KUMI_FWD(t))...);
  }
  template<field_name... Name, product_type Tuple>
  requires(requires { get<Name>(std::declval<Tuple>()); } && ...)
  KUMI_ABI constexpr auto reorder_fields(Tuple&& t)
  {
    return _::builder<Tuple>::make(Name = get<Name>(KUMI_FWD(t))...);
  }
  template<index_map auto Indexes, product_type T>
  requires(_::in_bound_indexes<Indexes, T>())
  [[nodiscard]] KUMI_ABI constexpr auto reindex(T&& t)
  {
    using idx_t = std::remove_cvref_t<decltype(Indexes)>;
    auto mk = [&]<auto Idx>() -> decltype(auto) {
      if constexpr (product_type<decltype(Idx)>) return reindex<Idx>(KUMI_FWD(t));
      else return get<Idx>(KUMI_FWD(t));
    };
    if constexpr (sized_product_type<T, 0>) return _::builder<T>::make();
    else if constexpr (sized_product_type<idx_t, 0>) return _::builder<T>::make();
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return _::builder<T>::make(mk.template operator()<get<I>(Indexes)>()...);
      }(std::make_index_sequence<size_v<idx_t>>{});
  }
  namespace result
  {
    template<product_type T, std::size_t... Idx> struct reorder
    {
      using type = decltype(kumi::reorder<Idx...>(std::declval<T>()));
    };
    template<product_type Tuple, field_name... Name> struct reorder_fields
    {
      using type = decltype(kumi::reorder_fields<Name...>(std::declval<Tuple>()));
    };
    template<product_type T, index_map auto Indexes> struct reindex
    {
      using type = decltype(kumi::reindex<Indexes>(std::declval<T>()));
    };
    template<product_type T, std::size_t... Idx> using reorder_t = typename reorder<T, Idx...>::type;
    template<product_type Tuple, field_name... Name>
    using reorder_fields_t = typename reorder_fields<Tuple, Name...>::type;
    template<product_type T, index_map auto Indexes> using reindex_t = typename reindex<T, Indexes>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t N> struct reducer_t
    {
      constexpr auto operator()() const noexcept
      {
        constexpr std::size_t half = N / 2;
        struct
        {
          std::size_t count = {}, remainder = {}, idx1[half], idx2[half];
        } that{};
        that.remainder = N % 2;
        [&]<std::size_t... I>(std::index_sequence<I...>) {
          ((that.idx1[that.count] = 2 * I, that.idx2[that.count++] = 2 * I + 1), ...);
        }(std::make_index_sequence<half>{});
        return that;
      }
    };
    template<std::size_t N> inline constexpr reducer_t<N> reducer{};
  }
  template<monoid M, product_type T> [[nodiscard]] KUMI_ABI constexpr auto reduce(M&& m, T&& t)
  {
    if constexpr (record_type<T>) return reduce(KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (sized_product_type<T, 0>) return m.identity;
    else if constexpr (sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
    else
    {
      constexpr auto pos = _::reducer<size_v<T>>();
      auto process = [&]<std::size_t I>(index_t<I>) {
        if constexpr (I < pos.count) return KUMI_FWD(m)(get<pos.idx1[I]>(KUMI_FWD(t)), get<pos.idx2[I]>(KUMI_FWD(t)));
        else return get<size_v<T> - 1>(KUMI_FWD(t));
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return reduce(KUMI_FWD(m), tuple{process(index<I>)...});
      }(std::make_index_sequence<pos.count + pos.remainder>{});
    }
  }
  template<monoid M, product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto reduce(M&& m, T&& t, Value init)
  {
    if constexpr (sized_product_type<T, 0>) return init;
    else return KUMI_FWD(m)(init, reduce(KUMI_FWD(m), KUMI_FWD(t)));
  }
  template<product_type T, monoid M, typename Function>
  [[nodiscard]] KUMI_ABI constexpr auto map_reduce(Function&& f, M&& m, T&& t)
  {
    if constexpr (record_type<T>) return map_reduce(KUMI_FWD(f), KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (sized_product_type<T, 0>) return m.identity;
    else if constexpr (sized_product_type<T, 1>) return KUMI_FWD(f)(get<0>(KUMI_FWD(t)));
    else
    {
      constexpr auto pos = _::reducer<size_v<T>>();
      auto process = [&]<std::size_t I>(index_t<I>) {
        if constexpr (I < pos.count)
          return KUMI_FWD(m)(KUMI_FWD(f)(get<pos.idx1[I]>(KUMI_FWD(t))), KUMI_FWD(f)(get<pos.idx2[I]>(KUMI_FWD(t))));
        else return KUMI_FWD(f)(get<size_v<T> - 1>(KUMI_FWD(t)));
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return reduce(KUMI_FWD(m), tuple{process(index<I>)...});
      }(std::make_index_sequence<pos.count + pos.remainder>{});
    }
  }
  template<monoid M, product_type T, typename Function, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto map_reduce(Function&& f, M&& m, T&& t, Value init)
  {
    if constexpr (sized_product_type<T, 0>) return KUMI_FWD(f)(init);
    else return KUMI_FWD(m)(KUMI_FWD(f)(init), map_reduce(KUMI_FWD(f), KUMI_FWD(m), KUMI_FWD(t)));
  }
  template<product_type T, typename Value> [[nodiscard]] KUMI_ABI constexpr auto sum(T&& t, Value init)
  {
    return reduce(function::plus, KUMI_FWD(t), init);
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto sum(T&& t)
  {
    return reduce(function::plus, KUMI_FWD(t));
  }
  template<product_type T, typename Value> [[nodiscard]] KUMI_ABI constexpr auto prod(T&& t, Value init)
  {
    return reduce(function::multiplies, KUMI_FWD(t), init);
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto prod(T&& t)
  {
    return reduce(function::multiplies, KUMI_FWD(t));
  }
  template<product_type T, typename Value> [[nodiscard]] KUMI_ABI constexpr auto bit_and(T&& t, Value init)
  {
    return reduce(function::bit_and, KUMI_FWD(t), init);
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto bit_and(T&& t)
  {
    return reduce(function::bit_and, KUMI_FWD(t));
  }
  template<product_type T, typename Value> [[nodiscard]] KUMI_ABI constexpr auto bit_or(T&& t, Value init)
  {
    return reduce(function::bit_or, KUMI_FWD(t), init);
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto bit_or(T&& t)
  {
    return reduce(function::bit_or, KUMI_FWD(t));
  }
  template<product_type T, typename Value> [[nodiscard]] KUMI_ABI constexpr auto bit_xor(T&& t, Value init)
  {
    return reduce(function::bit_xor, KUMI_FWD(t), init);
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto bit_xor(T&& t)
  {
    return reduce(function::bit_xor, KUMI_FWD(t));
  }
  namespace result
  {
    template<monoid M, product_type T, typename Value = void> struct reduce
    {
      using type = decltype(kumi::reduce(std::declval<M>(), std::declval<T>(), std::declval<Value>()));
    };
    template<monoid M, product_type T> struct reduce<M, T>
    {
      using type = decltype(kumi::reduce(std::declval<M>(), std::declval<T>()));
    };
    template<typename F, monoid M, product_type T, typename Value = void> struct map_reduce
    {
      using type =
        decltype(kumi::map_reduce(std::declval<F>(), std::declval<M>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename F, monoid M, product_type T> struct map_reduce<F, M, T>
    {
      using type = decltype(kumi::map_reduce(std::declval<F>(), std::declval<M>(), std::declval<T>()));
    };
    template<product_type T, typename Value = void> struct sum
    {
      using type = decltype(kumi::sum(std::declval<T>(), std::declval<Value>()));
    };
    template<product_type T> struct sum<T>
    {
      using type = decltype(kumi::sum(std::declval<T>()));
    };
    template<product_type T, typename Value = void> struct prod
    {
      using type = decltype(kumi::prod(std::declval<T>(), std::declval<Value>()));
    };
    template<product_type T> struct prod<T>
    {
      using type = decltype(kumi::prod(std::declval<T>()));
    };
    template<product_type T, typename Value = void> struct bit_and
    {
      using type = decltype(kumi::bit_and(std::declval<T>(), std::declval<Value>()));
    };
    template<product_type T> struct bit_and<T>
    {
      using type = decltype(kumi::bit_and(std::declval<T>()));
    };
    template<product_type T, typename Value = void> struct bit_or
    {
      using type = decltype(kumi::bit_or(std::declval<T>(), std::declval<Value>()));
    };
    template<product_type T> struct bit_or<T>
    {
      using type = decltype(kumi::bit_or(std::declval<T>()));
    };
    template<product_type T, typename Value = void> struct bit_xor
    {
      using type = decltype(kumi::bit_xor(std::declval<T>(), std::declval<Value>()));
    };
    template<product_type T> struct bit_xor<T>
    {
      using type = decltype(kumi::bit_xor(std::declval<T>()));
    };
    template<monoid M, product_type T, typename Value = void> using reduce_t = typename reduce<M, T, Value>::type;
    template<typename F, monoid M, product_type T, typename Value = void>
    using map_reduce_t = typename map_reduce<F, M, T, Value>::type;
    template<product_type T, typename Value = void> using sum_t = typename sum<T, Value>::type;
    template<product_type T, typename Value = void> using prod_t = typename prod<T, Value>::type;
    template<product_type T, typename Value = void> using bit_and_t = typename bit_and<T, Value>::type;
    template<product_type T, typename Value = void> using bit_or_t = typename bit_or<T, Value>::type;
    template<product_type T, typename Value = void> using bit_xor_t = typename bit_xor<T, Value>::type;
  }
}
namespace kumi
{
  template<product_type Tuple> [[nodiscard]] KUMI_ABI constexpr auto reverse(Tuple&& t)
  {
    if constexpr (sized_product_type<Tuple, 0>) return _::builder<Tuple>::make();
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return _::builder<Tuple>::make(get<(size_v<Tuple> - 1 - I)>(KUMI_FWD(t))...);
      }(std::make_index_sequence<size<Tuple>::value>());
    }
  }
  namespace result
  {
    template<product_type Tuple> struct reverse
    {
      using type = decltype(kumi::reverse(std::declval<Tuple>()));
    };
    template<product_type Tuple> using reverse_t = typename reverse<Tuple>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t S, std::size_t R> struct rotate_t
    {
      KUMI_ABI constexpr auto operator()() const noexcept
      {
        struct
        {
          std::size_t t[1 + S];
        } that{};
        auto idxs = [&]<std::size_t... I>(std::index_sequence<I...>) { ((that.t[I] = (I + R) % S), ...); };
        idxs(std::make_index_sequence<S>{});
        return that;
      }
    };
    template<std::size_t S, std::size_t R> inline constexpr rotate_t<S, R> rotator{};
  }
  template<std::size_t R, product_type T> constexpr auto rotate_left(T&& t)
  {
    if constexpr (sized_product_type<T, 0>) return KUMI_FWD(t);
    else if constexpr ((R % size_v<T>) == 0) return KUMI_FWD(t);
    else
    {
      constexpr auto idxs = _::rotator<size_v<T>, R % size_v<T>>();
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = _::builder_make_t<T, element_t<idxs.t[I], T>...>;
        return type{get<idxs.t[I]>(KUMI_FWD(t))...};
      }(std::make_index_sequence<size_v<T>>{});
    }
  }
  template<std::size_t R, product_type T> constexpr auto rotate_right(T&& t)
  {
    if constexpr (sized_product_type<T, 0>) return KUMI_FWD(t);
    else if constexpr ((R % size_v<T>) == 0) return KUMI_FWD(t);
    else
    {
      constexpr auto F = R % size_v<T>;
      constexpr auto idxs = _::rotator<size_v<T>, size_v<T> - F>();
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = _::builder_make_t<T, element_t<idxs.t[I], T>...>;
        return type{get<idxs.t[I]>(KUMI_FWD(t))...};
      }(std::make_index_sequence<size_v<T>>{});
    }
  }
  namespace result
  {
    template<std::size_t R, product_type T> struct rotate_left
    {
      using type = decltype(kumi::rotate_left<R>(std::declval<T>()));
    };
    template<std::size_t R, product_type T> struct rotate_right
    {
      using type = decltype(kumi::rotate_right<R>(std::declval<T>()));
    };
    template<std::size_t R, product_type T> using rotate_left_t = typename rotate_left<R, T>::type;
    template<std::size_t R, product_type T> using rotate_right_t = typename rotate_right<R, T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename F, typename T> struct scannable
    {
      F func;
      T acc;
      template<typename W> KUMI_ABI friend constexpr decltype(auto) operator>>(scannable&& x, scannable<F, W>&& y)
      {
        constexpr auto size = kumi::size_v<T> - 1;
        return _::scannable{x.func, kumi::push_back(x.acc, x.func(kumi::get<size>(x.acc), y.acc))};
      }
      template<typename W> KUMI_ABI friend constexpr decltype(auto) operator<<(scannable&& x, scannable<F, W>&& y)
      {
        return _::scannable{x.func, kumi::push_front(x.acc, x.func(y.acc, kumi::get<0>(x.acc)))};
      }
    };
    template<class F, class T> scannable(F const&, T&&) -> scannable<F, T>;
  }
  template<typename Function, product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto inclusive_scan_left(Function&& f, T&& t, Value init)
  {
    if constexpr (record_type<T>) return inclusive_scan_left(KUMI_FWD(f), values_of(KUMI_FWD(t)), init);
    else if constexpr (sized_product_type<T, 0>) return tuple{};
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (_::scannable{f, tuple{f(init, get<0>(KUMI_FWD(t)))}} >> ... >> _::scannable{f, get<I + 1>(KUMI_FWD(t))})
          .acc;
      }(std::make_index_sequence<size_v<T> - 1>());
    }
  }
  template<monoid M, sized_product_type_or_more<1> T>
  [[nodiscard]] KUMI_ABI constexpr auto inclusive_scan_left(M&& m, T&& t)
  {
    if constexpr (record_type<T>) return inclusive_scan_left(KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (sized_product_type<T, 1>) return KUMI_FWD(t);
    else return inclusive_scan_left(KUMI_FWD(m), KUMI_FWD(t), m.identity);
  }
  template<typename Function, product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto exclusive_scan_left(Function&& f, T&& t, Value init)
  {
    if constexpr (record_type<T>) return exclusive_scan_left(KUMI_FWD(f), values_of(KUMI_FWD(t)), init);
    else if constexpr (sized_product_type<T, 0>) return tuple{init};
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (_::scannable{f, tuple{init}} >> ... >> _::scannable{f, get<I>(KUMI_FWD(t))}).acc;
      }(std::make_index_sequence<size_v<T> - 1>());
    }
  }
  template<monoid M, sized_product_type_or_more<1> T>
  [[nodiscard]] KUMI_ABI constexpr auto exclusive_scan_left(M&& m, T&& t)
  {
    if constexpr (record_type<T>) return exclusive_scan_left(KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (sized_product_type<T, 1>) return tuple(m.identity, get<0>(KUMI_FWD(t)));
    else return exclusive_scan_left(KUMI_FWD(m), KUMI_FWD(t), m.identity);
  }
  template<typename Function, product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto inclusive_scan_right(Function&& f, T&& t, Value init)
  {
    if constexpr (record_type<T>) return inclusive_scan_right(KUMI_FWD(f), values_of(KUMI_FWD(t)), init);
    else if constexpr (sized_product_type<T, 0>) return tuple{};
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (_::scannable{f, tuple{f(get<size_v<T> - 1>(KUMI_FWD(t)), init)}}
                << ... << _::scannable{f, get<size_v<T> - 2 - I>(KUMI_FWD(t))})
          .acc;
      }(std::make_index_sequence<size_v<T> - 1>());
    }
  }
  template<monoid M, sized_product_type_or_more<1> T>
  [[nodiscard]] KUMI_ABI constexpr auto inclusive_scan_right(M&& m, T&& t)
  {
    if constexpr (record_type<T>) return inclusive_scan_right(KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (sized_product_type<T, 1>) return KUMI_FWD(t);
    else return inclusive_scan_right(KUMI_FWD(m), KUMI_FWD(t), m.identity);
  }
  template<typename Function, product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto exclusive_scan_right(Function&& f, T&& t, Value init)
  {
    if constexpr (record_type<T>) return exclusive_scan_right(KUMI_FWD(f), values_of(KUMI_FWD(t)), init);
    else if constexpr (sized_product_type<T, 0>) return tuple{init};
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (_::scannable{f, tuple{init}} << ... << _::scannable{f, get<size_v<T> - 1 - I>(KUMI_FWD(t))}).acc;
      }(std::make_index_sequence<size_v<T> - 1>());
    }
  }
  template<monoid M, sized_product_type_or_more<1> T>
  [[nodiscard]] KUMI_ABI constexpr auto exclusive_scan_right(M&& m, T&& t)
  {
    if constexpr (record_type<T>) return exclusive_scan_right(KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (sized_product_type<T, 1>) return tuple{get<0>(KUMI_FWD(t)), m.identity};
    else return kumi::exclusive_scan_right(KUMI_FWD(m), KUMI_FWD(t), m.identity);
  }
  namespace result
  {
    template<typename Function, product_type T, typename Value = void> struct inclusive_scan_right
    {
      using type =
        decltype(kumi::inclusive_scan_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, product_type T> struct inclusive_scan_right<Function, T>
    {
      using type = decltype(kumi::inclusive_scan_right(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, product_type T, typename Value = void> struct exclusive_scan_right
    {
      using type =
        decltype(kumi::exclusive_scan_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, product_type T> struct exclusive_scan_right<Function, T>
    {
      using type = decltype(kumi::exclusive_scan_right(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, product_type T, typename Value = void> struct inclusive_scan_left
    {
      using type =
        decltype(kumi::inclusive_scan_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, product_type T> struct inclusive_scan_left<Function, T>
    {
      using type = decltype(kumi::inclusive_scan_left(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, product_type T, typename Value = void> struct exclusive_scan_left
    {
      using type =
        decltype(kumi::exclusive_scan_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, product_type T> struct exclusive_scan_left<Function, T>
    {
      using type = decltype(kumi::exclusive_scan_left(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, product_type T, typename Value = void>
    using inclusive_scan_right_t = typename inclusive_scan_right<Function, T, Value>::type;
    template<typename Function, product_type T, typename Value = void>
    using exclusive_scan_right_t = typename exclusive_scan_right<Function, T, Value>::type;
    template<typename Function, product_type T, typename Value = void>
    using inclusive_scan_left_t = typename inclusive_scan_left<Function, T, Value>::type;
    template<typename Function, product_type T, typename Value = void>
    using exclusive_scan_left_t = typename exclusive_scan_left<Function, T, Value>::type;
  }
}
namespace kumi
{
  template<std::size_t N, product_type T>
  requires(N > 0 && N <= size_v<T>)
  [[nodiscard]] KUMI_ABI constexpr auto windows(T&& t)
  {
    if constexpr (N == size_v<T>) return kumi::make_tuple(t);
    else
      return kumi::generate<size_v<T> - N + 1>(
        [&](auto idx) { return kumi::extract(KUMI_FWD(t), kumi::index<idx>, kumi::index<idx + N>); });
  }
  template<std::size_t N, product_type T>
  requires(N > 0 && N <= size_v<T>)
  [[nodiscard]] KUMI_ABI constexpr auto chunks(T&& t)
  {
    constexpr auto nb = (size_v<T> + N - 1) / N;
    constexpr auto sz = size_v<T>;
    if constexpr (N == size_v<T>) return kumi::make_tuple(t);
    else
      return kumi::generate<nb>([&](auto idx) {
        constexpr auto chk_sz = (idx + 1) * N > sz ? sz - idx * N : N;
        constexpr auto chk_id = idx * N;
        return kumi::extract(KUMI_FWD(t), kumi::index<chk_id>, kumi::index<chk_id + chk_sz>);
      });
  }
  namespace result
  {
    template<std::size_t N, kumi::product_type T> struct windows
    {
      using type = decltype(kumi::windows<N>(std::declval<T>()));
    };
    template<std::size_t N, kumi::product_type T> struct chunks
    {
      using type = decltype(kumi::chunks<N>(std::declval<T>()));
    };
    template<std::size_t N, kumi::product_type T> using windows_t = typename windows<N, T>::type;
    template<std::size_t N, kumi::product_type T> using chunks_t = typename chunks<N, T>::type;
  }
}
namespace kumi
{
  template<product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto transpose(T&& t)
  requires(_::supports_transpose<T>)
  {
    if constexpr (sized_product_type<T, 0>) return tuple{};
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        constexpr auto uz = []<typename N>(N const&, auto&& u) {
          return apply([](auto&&... m) { return _::builder<T>::make(get<N::value>(KUMI_FWD(m))...); }, KUMI_FWD(u));
        };
        return kumi::make_tuple(uz(index<I>, KUMI_FWD(t))...);
      }(std::make_index_sequence<size_v<raw_element_t<0, T>>>());
    }
  }
  namespace result
  {
    template<product_type T> struct transpose
    {
      using type = decltype(kumi::transpose(std::declval<T>()));
    };
    template<product_type T> using transpose_t = typename transpose<T>::type;
  }
}
namespace kumi
{
  template<template<typename...> typename Traits,
           product_type Tuple,
           typename Seq = std::make_index_sequence<size<Tuple>::value>>
  struct apply_traits;
  template<template<typename...> typename Traits, product_type Tuple, std::size_t... Is>
  requires(requires { typename Traits<element_t<Is, Tuple>...>::type; })
  struct apply_traits<Traits, Tuple, std::index_sequence<Is...>>
  {
    using type = typename Traits<element_t<Is, Tuple>...>::type;
  };
  template<template<typename...> typename Traits, product_type Tuple>
  using apply_traits_t = typename apply_traits<Traits, Tuple>::type;
  template<template<typename...> typename Traits,
           product_type Tuple,
           typename Seq = std::make_index_sequence<size<Tuple>::value>>
  struct map_traits;
  template<template<typename...> typename Traits, product_type Tuple, std::size_t... Is>
  requires(requires { typename Traits<element_t<Is, Tuple>>::type; } && ...)
  struct map_traits<Traits, Tuple, std::index_sequence<Is...>>
  {
    using type = tuple<typename Traits<element_t<Is, Tuple>>::type...>;
  };
  template<template<typename...> typename Traits, product_type Tuple>
  using map_traits_t = typename map_traits<Traits, Tuple>::type;
}
namespace kumi
{
  namespace _
  {
    template<typename T> struct make_unique
    {
      T acc;
      template<typename W> KUMI_ABI friend constexpr decltype(auto) operator|(make_unique&& x, make_unique<W>&& y)
      {
        constexpr auto value = []<std::size_t... I>(std::index_sequence<I...>) {
          return (all_uniques_v<W, raw_element_t<I, T>...>);
        }(std::make_index_sequence<size_v<T>>{});
        if constexpr (value)
          return [&]<std::size_t... I>(std::index_sequence<I...>) {
            using res_t = _::builder_make_t<T, element_t<I, T>..., W>;
            return _::make_unique{res_t{get<I>(KUMI_FWD(x.acc))..., KUMI_FWD(y.acc)}};
          }(std::make_index_sequence<size_v<T>>{});
        else return KUMI_FWD(x);
      }
    };
    template<typename W> make_unique(W&& w) -> make_unique<W>;
    struct uniquable
    {
      template<product_type T> [[nodiscard]] KUMI_ABI consteval auto operator()(as<T>) const noexcept
      {
        struct
        {
          std::size_t count{1}, t[size_v<T>];
        } that{};
        that.t[0] = 0;
        [&]<std::size_t... I>(std::index_sequence<I...>) {
          (
            [&] {
              constexpr auto L = I;
              constexpr auto R = I + 1;
              if constexpr (!std::is_same_v<raw_element_t<L, T>, raw_element_t<R, T>>) that.t[that.count++] = R;
            }(),
            ...);
        }(std::make_index_sequence<size_v<T> - 1>{});
        return that;
      }
    };
    inline constexpr uniquable uniqued{};
  }
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto unique(T&& t)
  {
    if constexpr (sized_product_type<T, 0>) return KUMI_FWD(t);
    else
    {
      constexpr auto pos = _::uniqued(as<T>{});
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using ret_t = _::builder_make_t<T, raw_element_t<pos.t[I], T>...>;
        return ret_t{get<pos.t[I]>(KUMI_FWD(t))...};
      }(std::make_index_sequence<pos.count>{});
    }
  };
  template<product_type T> [[nodiscard]] KUMI_ABI constexpr auto all_unique(T&& t)
  {
    if constexpr (sized_product_type<T, 0>) return t;
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (_::make_unique{_::builder_make_t<T, raw_element_t<0, T>>{get<0>(KUMI_FWD(t))}} | ... |
                _::make_unique<raw_element_t<I + 1, T>>{get<I + 1>(KUMI_FWD(t))})
          .acc;
      }(std::make_index_sequence<size_v<T> - 1>{});
    }
  }
  namespace result
  {
    template<product_type T> struct unique
    {
      using type = decltype(kumi::unique(std::declval<T>()));
    };
    template<product_type T> struct all_unique
    {
      using type = decltype(kumi::all_unique(std::declval<T>()));
    };
    template<product_type T> using unique_t = typename unique<T>::type;
    template<product_type T> using all_unique_t = typename all_unique<T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    struct zipper_t
    {
      template<std::size_t Size, product_type T>
      KUMI_ABI constexpr auto operator()(index_t<Size> const&, T&& t) const noexcept
      {
        if constexpr (sized_product_type<T, 0>) return t;
        else
        {
          constexpr auto uz = []<typename N>(N const&, auto&& u) {
            return apply(
              [](auto&&... m) {
                auto zip_ = [&]<product_type V>(V&& v) {
                  if constexpr (size_v<V> <= N::value) return none;
                  else return get<N::value>(KUMI_FWD(v));
                };
                return _::builder<element_t<0, T>>::make(zip_(KUMI_FWD(m))...);
              },
              KUMI_FWD(u));
          };
          return [&]<std::size_t... I>(std::index_sequence<I...>) {
            return kumi::make_tuple(uz(index_t<I>{}, KUMI_FWD(t))...);
          }(std::make_index_sequence<Size>());
        }
      }
    };
    inline constexpr zipper_t zipper{};
    template<typename T0, typename... Ts> consteval std::size_t min_size_v()
    {
      std::size_t result = size_v<T0>;
      if constexpr (sizeof...(Ts) == 0) return result;
      else return ((result = result < size_v<Ts> ? result : size_v<Ts>), ...);
    };
    template<typename T0, typename... Ts> consteval std::size_t max_size_v()
    {
      std::size_t result = size_v<T0>;
      if constexpr (sizeof...(Ts) == 0) return result;
      else return ((result = result > size_v<Ts> ? result : size_v<Ts>), ...);
    };
  }
  template<product_type T0, sized_product_type<size_v<T0>>... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto zip(T0&& t0, Ts&&... ts)
  requires(follows_same_semantic<T0, Ts...>)
  {
    return _::zipper(index<size_v<T0>>, kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...));
  }
  template<product_type T0, product_type... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto zip_min(T0&& t0, Ts&&... ts)
  requires(follows_same_semantic<T0, Ts...>)
  {
    constexpr std::size_t min = _::min_size_v<T0, Ts...>();
    return _::zipper(index<min>, kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...));
  }
  template<product_type T0, product_type... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto zip_max(T0&& t0, Ts&&... ts)
  requires(follows_same_semantic<T0, Ts...>)
  {
    constexpr std::size_t max = _::max_size_v<T0, Ts...>();
    return _::zipper(index<max>, kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...));
  }
  namespace result
  {
    template<product_type T0, sized_product_type<size_v<T0>>... Ts> struct zip
    {
      using type = decltype(kumi::zip(std::declval<T0>(), std::declval<Ts>()...));
    };
    template<product_type T0, product_type... Ts> struct zip_min
    {
      using type = decltype(kumi::zip_min(std::declval<T0>(), std::declval<Ts>()...));
    };
    template<product_type T0, product_type... Ts> struct zip_max
    {
      using type = decltype(kumi::zip_max(std::declval<T0>(), std::declval<Ts>()...));
    };
    template<product_type T0, product_type... Ts> using zip_t = typename zip<T0, Ts...>::type;
    template<product_type T0, product_type... Ts> using zip_min_t = typename zip_min<T0, Ts...>::type;
    template<product_type T0, product_type... Ts> using zip_max_t = typename zip_max<T0, Ts...>::type;
  }
}
