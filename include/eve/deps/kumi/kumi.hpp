//======================================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#ifndef KUMI_HPP_INCLUDED
#define KUMI_HPP_INCLUDED
namespace kumi
{
  template<decltype(sizeof(0)) N> struct str;
  template<typename... Ts> struct tuple;
  template<typename... Ts> struct record;
  template<auto... Vs> struct projection_map;
}
namespace kumi
{
}
namespace kumi
{
}
#if defined(_MSC_VER)
#if _MSVC_LANG < 202002L
#error "KUMI C++ version error"
#include "KUMI requires C++20 or higher. Use /std:c++20 or higher to enable C++20 features."
#endif
#else
#if __cplusplus < 202002L
#error "KUMI C++ version error"
#include "KUMI requires C++20 or higher. Use -std=c++20 or higher to enable C++20 features."
#endif
#endif
#define KUMI_FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#if defined(__CUDACC__) || defined(__NVCC__)
#define KUMI_CUDA __host__ __device__
#else
#define KUMI_CUDA
#endif
#if defined(KUMI_DEBUG)
#define KUMI_ABI KUMI_CUDA
#elif defined(__EDG__) || defined(__EDG_VERSION__) || defined(__CUDACC__) || defined(__NVCC__)
#define KUMI_ABI KUMI_CUDA inline
#elif defined(__GNUC__) || defined(__clang__)
#define KUMI_ABI [[using gnu: always_inline, flatten, artificial]] KUMI_CUDA inline
#elif defined(_MSC_VER)
#define KUMI_ABI [[using msvc: forceinline, flatten]] KUMI_CUDA inline
#else
#define KUMI_ABI KUMI_CUDA inline
#endif
#define KUMI_HIDDEN_ABI KUMI_CUDA inline
#if defined(__CUDA_ARCH__)
#define KUMI_VARIABLE_ABI __device__
#else
#define KUMI_VARIABLE_ABI inline
#endif
#if defined(__CUDA_ARCH__)
#define KUMI_ERROR(MESSAGE) __trap()
#else
#define KUMI_ERROR(MESSAGE) throw MESSAGE
#endif
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wmissing-braces"
#endif
namespace kumi::_
{
  inline namespace cxx20
  {
    struct adl_tag_t
    {
    } KUMI_VARIABLE_ABI constexpr adl_tag;
  }
}
#include <cstddef>
#include <concepts>
#include <iosfwd>
#include <type_traits>
#include <utility>
namespace kumi::_
{
  consteval std::size_t min(std::same_as<std::size_t> auto... sizes) noexcept
  {
    std::size_t result = std::size_t(-1);
    return ((result = (result < sizes ? result : sizes)), ...);
  }
  consteval std::size_t max(std::same_as<std::size_t> auto... sizes) noexcept
  {
    std::size_t result{};
    return ((result = (result > sizes ? result : sizes)), ...);
  }
  consteval std::size_t nth_pos(std::size_t I, std::same_as<bool> auto... b) noexcept
  {
    std::size_t seen{}, i{}, idx{};
    ((b ? (seen++ == I ? (i = idx, idx++) : idx++) : idx++), ...);
    return i;
  }
  template<std::size_t I, bool... Bs> inline constexpr std::size_t nth_pos_v = nth_pos(I, Bs...);
  template<std::size_t... I, std::size_t... J>
  consteval std::size_t stride_at(std::size_t Pos, std::index_sequence<I...>, std::index_sequence<J...>) noexcept
  {
    return ((J < Pos ? I : std::size_t{1}) * ...);
  }
}
#define FOR_LIST_OF_STRUCTS(DO)                                                                                        \
  DO(1)                                                                                                                \
  DO(2)                                                                                                                \
  DO(3)                                                                                                                \
  DO(4)                                                                                                                \
  DO(5)                                                                                                                \
  DO(6)                                                                                                                \
  DO(7)                                                                                                                \
  DO(8)                                                                                                                \
  DO(9)                                                                                                                \
  DO(10)
#define KUMI_REPEAT_0(m, d)
#define KUMI_REPEAT_1(m, d) m(0, d)
#define KUMI_REPEAT_2(m, d) KUMI_REPEAT_1(m, d) m(1, d)
#define KUMI_REPEAT_3(m, d) KUMI_REPEAT_2(m, d) m(2, d)
#define KUMI_REPEAT_4(m, d) KUMI_REPEAT_3(m, d) m(3, d)
#define KUMI_REPEAT_5(m, d) KUMI_REPEAT_4(m, d) m(4, d)
#define KUMI_REPEAT_6(m, d) KUMI_REPEAT_5(m, d) m(5, d)
#define KUMI_REPEAT_7(m, d) KUMI_REPEAT_6(m, d) m(6, d)
#define KUMI_REPEAT_8(m, d) KUMI_REPEAT_7(m, d) m(7, d)
#define KUMI_REPEAT_9(m, d) KUMI_REPEAT_8(m, d) m(8, d)
#define KUMI_REPEAT_10(m, d) KUMI_REPEAT_9(m, d) m(9, d)
#define KUMI_PP_REPEAT_(N, m, d) KUMI_REPEAT_##N(m, d)
#define KUMI_PP_REPEAT(N, m, d) KUMI_PP_REPEAT_(N, m, d)
#define KUMI_ENUM_0(m, d)
#define KUMI_ENUM_1(m, d) m(0, d)
#define KUMI_ENUM_2(m, d) KUMI_ENUM_1(m, d), m(1, d)
#define KUMI_ENUM_3(m, d) KUMI_ENUM_2(m, d), m(2, d)
#define KUMI_ENUM_4(m, d) KUMI_ENUM_3(m, d), m(3, d)
#define KUMI_ENUM_5(m, d) KUMI_ENUM_4(m, d), m(4, d)
#define KUMI_ENUM_6(m, d) KUMI_ENUM_5(m, d), m(5, d)
#define KUMI_ENUM_7(m, d) KUMI_ENUM_6(m, d), m(6, d)
#define KUMI_ENUM_8(m, d) KUMI_ENUM_7(m, d), m(7, d)
#define KUMI_ENUM_9(m, d) KUMI_ENUM_8(m, d), m(8, d)
#define KUMI_ENUM_10(m, d) KUMI_ENUM_9(m, d), m(9, d)
#define KUMI_PP_ENUM_(N, m, d) KUMI_ENUM_##N(m, d)
#define KUMI_PP_ENUM(N, m, d) KUMI_PP_ENUM_(N, m, d)
#define KUMI_PP_CAT_(P, S) P##S
#define KUMI_PP_CAT(P, S) KUMI_PP_CAT_(P, S)
#define KUMI_PP_TAC(P, S) KUMI_PP_CAT_(S, P)
#define KUMI_PP_IDENTITY(I, ...) I
#define KUMI_MEMBERS(N, _)                                                                                             \
  T##N member##N;                                                                                                      \
  using index##N = std::integral_constant<std::size_t, N>;                                                             \
  KUMI_HIDDEN_ABI constexpr auto& operator()(index##N) & noexcept                                                      \
  {                                                                                                                    \
    return member##N;                                                                                                  \
  }                                                                                                                    \
  KUMI_HIDDEN_ABI constexpr auto&& operator()(index##N) && noexcept                                                    \
  {                                                                                                                    \
    return static_cast<T##N&&>(member##N);                                                                             \
  }                                                                                                                    \
  KUMI_HIDDEN_ABI constexpr auto const&& operator()(index##N) const&& noexcept                                         \
  {                                                                                                                    \
    return static_cast<T##N const&&>(member##N);                                                                       \
  }                                                                                                                    \
  KUMI_HIDDEN_ABI constexpr auto const& operator()(index##N) const& noexcept                                           \
  {                                                                                                                    \
    return member##N;                                                                                                  \
  }
#define KUMI_GET_TYPE_LVALUE(N, T)                                                                                     \
  if constexpr (std::same_as<T, T##N>) return member##N;
#define KUMI_GET_TYPE_RVALUE(N, T)                                                                                     \
  if constexpr (std::same_as<T, T##N>) return static_cast<T##N&&>(member##N);
#define KUMI_GET_TYPE_CONST_RVALUE(N, T)                                                                               \
  if constexpr (std::same_as<T, T##N>) return static_cast<T##N const&&>(member##N);
#define KUMI_GET_NAME_LVALUE(N, I)                                                                                     \
  if constexpr (kumi::_::field<T##N> && requires { member##N(I{}); })                                                  \
    return member##N(kumi::_::identifier_of_t<T##N>{});
#define KUMI_GET_NAME_RVALUE(N, I)                                                                                     \
  if constexpr (kumi::_::field<T##N> && requires { member##N(I{}); })                                                  \
    return static_cast<T##N&&>(member##N)(kumi::_::identifier_of_t<T##N>{});
#define KUMI_GET_NAME_CONST_RVALUE(N, I)                                                                               \
  if constexpr (kumi::_::field<T##N> && requires { member##N(I{}); })                                                  \
    return static_cast<T##N const&&>(member##N)(kumi::_::identifier_of_t<T##N>{});
#define KUMI_BINDER(N)                                                                                                 \
  template<KUMI_PP_ENUM(N, KUMI_PP_TAC, typename T)>                                                                   \
  requires(kumi::_::no_empty<KUMI_PP_ENUM(N, KUMI_PP_TAC, T)> &&                                                       \
           kumi::_::no_references<KUMI_PP_ENUM(N, KUMI_PP_TAC, T)> &&                                                  \
           (N == 1 || !kumi::_::all_the_same<KUMI_PP_ENUM(N, KUMI_PP_TAC, T)>))                                        \
  struct binder<std::index_sequence<KUMI_PP_ENUM(N, KUMI_PP_IDENTITY, _)>, KUMI_PP_ENUM(N, KUMI_PP_TAC, T)>            \
  {                                                                                                                    \
    static constexpr bool is_homogeneous = (N == 1);                                                                   \
    KUMI_PP_REPEAT(N, KUMI_MEMBERS, _)                                                                                 \
                                                                                                                       \
    template<typename T> KUMI_HIDDEN_ABI constexpr auto& operator()(std::type_identity<T>) & noexcept                  \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_TYPE_LVALUE, T)                                                                       \
    }                                                                                                                  \
    template<typename T> KUMI_HIDDEN_ABI constexpr auto&& operator()(std::type_identity<T>) && noexcept                \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_TYPE_RVALUE, T)                                                                       \
    }                                                                                                                  \
    template<typename T> KUMI_HIDDEN_ABI constexpr auto const&& operator()(std::type_identity<T>) const&& noexcept     \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_TYPE_CONST_RVALUE, T)                                                                 \
    }                                                                                                                  \
    template<typename T> KUMI_HIDDEN_ABI constexpr auto const& operator()(std::type_identity<T>) const& noexcept       \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_TYPE_LVALUE, T)                                                                       \
    }                                                                                                                  \
                                                                                                                       \
    template<kumi::_::identifier I> KUMI_HIDDEN_ABI constexpr auto& operator()(I) & noexcept                           \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_LVALUE, I)                                                                       \
    }                                                                                                                  \
    template<kumi::_::identifier I> KUMI_HIDDEN_ABI constexpr auto&& operator()(I) && noexcept                         \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_RVALUE, I)                                                                       \
    }                                                                                                                  \
    template<kumi::_::identifier I> KUMI_HIDDEN_ABI constexpr auto const&& operator()(I) const&& noexcept              \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_CONST_RVALUE, I)                                                                 \
    }                                                                                                                  \
    template<kumi::_::identifier I> KUMI_HIDDEN_ABI constexpr auto const& operator()(I) const& noexcept                \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_LVALUE, I)                                                                       \
    }                                                                                                                  \
  };
namespace kumi::_
{
  using invalid = std::integral_constant<std::size_t, static_cast<std::size_t>(-1)>;
  template<typename From, typename To>
  concept ordered = requires(From const& a, To const& b) {
    { a < b };
  };
  template<typename T, typename U>
  concept comparable = requires(T t, U u) {
    { t == u };
  };
  template<typename T, typename... Args>
  concept implicit_constructible = requires(Args... args) { T{args...}; };
  template<auto N> void str_based(kumi::str<N> const&);
  template<typename T>
  concept str_like = requires(T const& t) { kumi::_::str_based(t); };
  template<typename T>
  concept valid_label =
    kumi::_::implicit_constructible<T> &&
    (!requires { to_str(T{}); } ||
    requires
    {
      { std::bool_constant<(to_str(T{}), true)>{} } -> std::same_as<std::true_type>;
      { to_str(T{}) } -> kumi::_::str_like;
    });
  template<typename T>
  concept label = requires(T&& t) {
    typename std::remove_cvref_t<T>::type;
    { std::remove_cvref_t<T>::value } -> kumi::_::str_like;
  };
  template<typename O>
  concept field = requires(O&& o) {
    typename std::remove_cvref_t<O>::type;
    typename std::remove_cvref_t<O>::identifier_type;
    typename std::remove_cvref_t<O>::label_type;
    { o(typename std::remove_cvref_t<O>::identifier_type{}) };
    { std::remove_cvref_t<O>::label() };
  };
  template<kumi::_::field T> using identifier_of_t = typename std::remove_cvref_t<T>::identifier_type;
  template<kumi::_::field T> struct identifier_of
  {
    using type = kumi::_::identifier_of_t<T>;
  };
  template<kumi::_::field T> using type_of_t = typename std::remove_cvref_t<T>::type;
  template<kumi::_::field T> struct type_of
  {
    using type = kumi::_::type_of_t<T>;
  };
  template<kumi::_::field T> using label_of_t = typename std::remove_cvref_t<T>::label_type;
  template<kumi::_::field T> struct label_of
  {
    using type = kumi::_::label_of_t<T>;
  };
  template<typename T>
  concept identifier = requires(T&& t) { typename std::remove_cvref_t<T>::type; };
  template<kumi::_::identifier T> using tag_of_t = typename std::remove_cvref_t<T>::type;
  template<kumi::_::identifier T> struct tag_of
  {
    using type = kumi::_::tag_of_t<T>;
  };
  template<typename T>
  concept non_empty_tuple = requires {
    typename std::tuple_element<0, std::remove_cvref_t<T>>::type;
    { std::tuple_size<T>::value };
  };
  template<typename T>
  concept empty_tuple = (std::tuple_size<std::remove_cvref_t<T>>::value == 0);
  template<typename T>
  concept std_tuple_compatible = kumi::_::empty_tuple<T> || kumi::_::non_empty_tuple<T>;
  template<typename T>
  concept container_like = requires(T const& t) {
    typename T::value_type;
    typename T::size_type;
    { t.size() } -> std::convertible_to<std::size_t>;
    { t.begin() };
    { t.end() };
  };
  template<typename T>
  concept contiguous_container_like = kumi::_::container_like<T> && requires(T const& t) {
    { t.data() };
  };
  template<typename, typename> inline constexpr bool is_piecewise_convertible_v = false;
  template<template<class...> class Box, typename... From, typename... To>
  requires(sizeof...(From) == sizeof...(To))
  inline constexpr bool is_piecewise_convertible_v<Box<From...>, Box<To...>> = (std::convertible_to<From, To> && ...);
  template<typename From, typename To>
  concept piecewise_convertible =
    kumi::_::is_piecewise_convertible_v<std::remove_cvref_t<From>, std::remove_cvref_t<To>>;
  template<typename, typename> inline constexpr bool is_piecewise_constructible_v = false;
  template<template<class...> class Box, typename... From, typename... To>
  requires(sizeof...(From) == sizeof...(To))
  inline constexpr bool is_piecewise_constructible_v<Box<From...>, Box<To...>> =
    (std::is_constructible_v<To, From> && ...);
  template<typename From, typename To>
  concept piecewise_constructible =
    kumi::_::is_piecewise_constructible_v<std::remove_cvref_t<From>, std::remove_cvref_t<To>>;
  template<typename, typename> inline constexpr bool is_piecewise_ordered_v = false;
  template<template<class...> class Box, typename... From, typename... To>
  requires(sizeof...(From) == sizeof...(To))
  inline constexpr bool is_piecewise_ordered_v<Box<From...>, Box<To...>> = (... && ordered<From, To>);
  template<typename From, typename To>
  concept piecewise_ordered = kumi::_::is_piecewise_ordered_v<std::remove_cvref_t<From>, std::remove_cvref_t<To>>;
  template<typename, typename> inline constexpr bool is_piecewise_comparable_v = false;
  template<template<class...> class Box, typename... From, typename... To>
  requires(sizeof...(From) == sizeof...(To))
  inline constexpr bool is_piecewise_comparable_v<Box<From...>, Box<To...>> = (... && comparable<From, To>);
  template<typename From, typename To>
  concept piecewise_comparable = kumi::_::is_piecewise_comparable_v<std::remove_cvref_t<From>, std::remove_cvref_t<To>>;
  template<typename... Ts> struct set : Ts...
  {
    using Ts::operator()...;
    consteval void operator()(...);
  };
  template<typename, typename> inline constexpr bool is_fieldwise_convertible_v = false;
  template<template<class...> class Box, typename... From, typename... To>
  requires(sizeof...(From) == sizeof...(To))
  inline constexpr bool is_fieldwise_convertible_v<Box<From...>, Box<To...>>{(
    std::is_convertible_v<decltype(std::declval<kumi::_::set<From...>>()(std::declval<kumi::_::identifier_of_t<To>>())),
                          kumi::_::type_of_t<To>> &&
    ...)};
  template<typename From, typename To>
  concept fieldwise_convertible =
    kumi::_::is_fieldwise_convertible_v<std::remove_cvref_t<From>, std::remove_cvref_t<To>>;
  template<typename From, typename To> inline constexpr bool is_fieldwise_constructible_v = false;
  template<template<class...> class Box, typename... From, typename... To>
  requires(sizeof...(From) == sizeof...(To))
  inline constexpr bool is_fieldwise_constructible_v<Box<From...>, Box<To...>>{
    (std::is_constructible_v<kumi::_::type_of_t<To>,
                             decltype(std::declval<kumi::_::set<From...>>()(
                               std::declval<kumi::_::identifier_of_t<To>>()))> &&
     ...)};
  template<typename From, typename To>
  concept fieldwise_constructible =
    kumi::_::is_fieldwise_constructible_v<std::remove_cvref_t<From>, std::remove_cvref_t<To>>;
  template<typename, typename> inline constexpr bool is_fieldwise_comparable_v = false;
  template<template<class...> class Box, typename... From, typename... To>
  requires(sizeof...(From) == sizeof...(To))
  inline constexpr bool is_fieldwise_comparable_v<Box<From...>, Box<To...>>{
    (kumi::_::comparable<decltype(std::declval<kumi::_::set<From...>>()(std::declval<kumi::_::identifier_of_t<To>>())),
                         kumi::_::type_of_t<To>> &&
     ...)};
  template<typename From, typename To>
  concept fieldwise_comparable = kumi::_::is_fieldwise_comparable_v<std::remove_cvref_t<From>, std::remove_cvref_t<To>>;
}
namespace kumi::_
{
  enum class case_
  {
    normal,
    indexed,
    field
  };
  template<typename...> struct undefined;
  template<std::size_t I, typename T> extern std::integral_constant<std::size_t, I> index_or_key;
  template<std::size_t I, kumi::_::field T> extern kumi::_::identifier_of_t<T> index_or_key<I, T>;
  template<std::size_t I, typename T> using index_or_key_t = decltype(index_or_key<I, T>);
  template<std::size_t I, typename T> struct unique
  {
    operator std::type_identity<T>();
    operator std::integral_constant<std::size_t, I>();
    template<typename U>
    requires(std::same_as<T, U>)
    std::integral_constant<std::size_t, I> operator()(U const&);
  };
  template<std::size_t I, kumi::_::field T> struct unique<I, T>
  {
    operator std::type_identity<T>();
    operator kumi::_::identifier_of_t<T>();
    template<typename U>
    requires(std::same_as<kumi::_::type_of_t<T>, U>)
    std::integral_constant<std::size_t, I> operator()(U const&);
    std::integral_constant<std::size_t, I> operator()(kumi::_::identifier_of_t<T> const&);
    template<kumi::_::label U>
    requires(U::value == std::remove_cvref_t<T>::label())
    std::integral_constant<std::size_t, I> operator()(U const&);
  };
  template<typename T, typename... Keys>
  concept is_set = requires { (void(static_cast<Keys&&>(std::declval<T>())), ...); };
  template<typename Seq, typename... Ts> struct family;
  template<std::size_t... I, typename... Ts> struct family<std::index_sequence<I...>, Ts...> : kumi::_::unique<I, Ts>...
  {
    using kumi::_::unique<I, Ts>::operator()...;
    kumi::_::invalid operator()(...);
    template<typename Ref> using type = decltype(std::declval<family>()(std::declval<Ref>()));
  };
  template<typename... Ts> using make_family = family<std::index_sequence_for<Ts...>, Ts...>;
  template<typename T> inline constexpr bool is_set_v = false;
  template<std::size_t... I, typename... Ts>
  inline constexpr bool is_set_v<kumi::_::family<std::index_sequence<I...>, Ts...>> =
    kumi::_::is_set<kumi::_::family<std::index_sequence<I...>, Ts...>, std::type_identity<Ts>...>;
  template<typename T> inline constexpr bool is_map_v = false;
  template<std::size_t... I, typename... Ts>
  inline constexpr bool is_map_v<kumi::_::family<std::index_sequence<I...>, Ts...>> =
    kumi::_::is_set<kumi::_::family<std::index_sequence<I...>, Ts...>, kumi::_::index_or_key_t<I, Ts>...>;
  template<typename T, typename... Ts> inline constexpr bool same_mapping_v = false;
  template<std::size_t... I, typename... Ts, typename... Us>
  inline constexpr bool same_mapping_v<kumi::_::family<std::index_sequence<I...>, Ts...>, Us...> =
    kumi::_::is_set<kumi::_::family<std::index_sequence<I...>, Ts...>, kumi::_::index_or_key_t<I, Ts>...>;
  template<typename Ref, typename... Fields>
  using index_of_type = typename kumi::_::make_family<Fields...>::template type<Ref>;
  template<typename Ref, typename... Fields>
  using index_of_tag = typename kumi::_::make_family<Fields...>::template type<kumi::_::tag_of_t<Ref>>;
  template<typename Ref, typename... Fields>
  using index_of_label = typename kumi::_::make_family<Fields...>::template type<Ref>;
  template<template<typename...> typename Meta, typename Target, typename PT, typename Seq>
  inline constexpr bool can_query = false;
  template<template<typename...> typename Meta, typename Target, typename PT, std::size_t... I>
  inline constexpr bool can_query<Meta, Target, PT, std::index_sequence<I...>> =
    Meta<Target, std::tuple_element_t<I, PT>...>::value != kumi::_::invalid{};
}
namespace kumi::_
{
  template<std::size_t N, typename T> struct leaf
  {
    T value;
    using index = std::integral_constant<std::size_t, N>;
    using inner_type = std::type_identity<T>;
    KUMI_HIDDEN_ABI constexpr T& operator()(index) & noexcept { return value; }
    KUMI_HIDDEN_ABI constexpr T&& operator()(index) && noexcept { return static_cast<T&&>(value); }
    KUMI_HIDDEN_ABI constexpr T const&& operator()(index) const&& noexcept { return static_cast<T const&&>(value); }
    KUMI_HIDDEN_ABI constexpr T const& operator()(index) const& noexcept { return value; }
    KUMI_HIDDEN_ABI constexpr T& operator()(inner_type) & noexcept { return value; }
    KUMI_HIDDEN_ABI constexpr T&& operator()(inner_type) && noexcept { return static_cast<T&&>(value); }
    KUMI_HIDDEN_ABI constexpr T const&& operator()(inner_type) const&& noexcept
    {
      return static_cast<T const&&>(value);
    }
    KUMI_HIDDEN_ABI constexpr T const& operator()(inner_type) const& noexcept { return value; }
  };
  template<std::size_t N, typename T>
  requires(std::is_empty_v<T> && (!std::is_final_v<T>) && (!kumi::_::field<T>))
  struct leaf<N, T> : std::remove_cvref_t<T>
  {
    using base = std::remove_cvref_t<T>;
    using index = std::integral_constant<std::size_t, N>;
    using inner_type = std::type_identity<base>;
    KUMI_HIDDEN_ABI constexpr base& operator()(index) & noexcept { return *this; }
    KUMI_HIDDEN_ABI constexpr base&& operator()(index) && noexcept { return static_cast<base&&>(*this); }
    KUMI_HIDDEN_ABI constexpr base const&& operator()(index) const&& noexcept
    {
      return static_cast<base const&&>(*this);
    }
    KUMI_HIDDEN_ABI constexpr base const& operator()(index) const& noexcept { return *this; }
    KUMI_HIDDEN_ABI constexpr base& operator()(inner_type) & noexcept { return *this; }
    KUMI_HIDDEN_ABI constexpr base&& operator()(inner_type) && noexcept { return static_cast<base&&>(*this); }
    KUMI_HIDDEN_ABI constexpr base const&& operator()(inner_type) const&& noexcept
    {
      return static_cast<base const&&>(*this);
    }
    KUMI_HIDDEN_ABI constexpr base const& operator()(inner_type) const& noexcept { return *this; }
  };
  template<std::size_t N, kumi::_::field T> struct leaf<N, T> : std::remove_cvref_t<T>
  {
    using base = std::remove_cvref_t<T>;
    using base::operator();
    using index = std::integral_constant<std::size_t, N>;
    KUMI_HIDDEN_ABI constexpr base& operator()(index) & noexcept { return *this; }
    KUMI_HIDDEN_ABI constexpr base&& operator()(index) && noexcept { return static_cast<base&&>(*this); }
    KUMI_HIDDEN_ABI constexpr base const&& operator()(index) const&& noexcept
    {
      return static_cast<base const&&>(*this);
    }
    KUMI_HIDDEN_ABI constexpr base const& operator()(index) const& noexcept { return *this; }
  };
  template<typename ISeq, typename... Ts> struct binder;
  template<std::size_t... Is, typename... Ts>
  struct binder<std::index_sequence<Is...>, Ts...> : kumi::_::leaf<Is, Ts>...
  {
    static constexpr bool is_homogeneous = false;
    using kumi::_::leaf<Is, Ts>::operator()...;
  };
  template<typename ISeq, typename... Ts> using make_binder_t = kumi::_::binder<ISeq, Ts...>;
  template<typename... Ts> using make_set_t = kumi::_::set<Ts...>;
}
namespace kumi::_
{
  template<typename... Ts> inline constexpr bool no_references = (true && ... && !std::is_reference_v<Ts>);
  template<typename... Ts> inline constexpr bool no_empty = (true && ... && !std::is_empty_v<Ts>);
  template<typename T0, typename... Ts> inline constexpr bool all_the_same = (true && ... && std::is_same_v<T0, Ts>);
  template<std::size_t... Is, typename T0, typename T1, typename... Ts>
  requires(kumi::_::all_the_same<T0, T1, Ts...> && kumi::_::no_references<T0, T1, Ts...> &&
           kumi::_::no_empty<T0, T1, Ts...>)
  struct binder<std::index_sequence<Is...>, T0, T1, Ts...>
  {
    using type = T0;
    static constexpr std::size_t N = 2 + sizeof...(Ts);
    static constexpr bool is_homogeneous = true;
    type members[N];
    template<std::size_t I>
    KUMI_HIDDEN_ABI constexpr auto& operator()(std::integral_constant<std::size_t, I>) & noexcept
    {
      return members[I];
    }
    template<std::size_t I>
    KUMI_HIDDEN_ABI constexpr auto const& operator()(std::integral_constant<std::size_t, I>) const& noexcept
    {
      return members[I];
    }
    template<std::size_t I>
    KUMI_HIDDEN_ABI constexpr auto&& operator()(std::integral_constant<std::size_t, I>) && noexcept
    {
      return static_cast<type&&>(members[I]);
    }
    template<std::size_t I>
    KUMI_HIDDEN_ABI constexpr auto const&& operator()(std::integral_constant<std::size_t, I>) const&& noexcept
    {
      return static_cast<type const&&>(members[I]);
    }
  };
  FOR_LIST_OF_STRUCTS(KUMI_BINDER)
}
namespace kumi
{
  template<typename T> struct as
  {
    using type = T;
    constexpr as() noexcept {}
    explicit constexpr as(T const&) noexcept {}
    constexpr inline operator std::type_identity<T>() const noexcept { return {}; }
  };
  template<> struct as<void>
  {
    using type = void;
    constexpr as() noexcept {}
  };
}
namespace kumi
{
  template<typename T> struct builder;
  template<typename T> using builder_t = typename builder<std::remove_cvref_t<T>>::type;
  template<typename T, typename... Args>
  using builder_make_t = typename builder<std::remove_cvref_t<T>>::template to<Args...>;
}
namespace kumi
{
  template<typename T> inline constexpr bool is_product_type_v = kumi::_::std_tuple_compatible<T>;
  template<typename T> struct is_product_type
  {
    static constexpr bool value = kumi::is_product_type_v<T>;
  };
  template<typename T>
  inline constexpr bool is_record_type_v = requires { typename T::is_record_type; } && kumi::_::std_tuple_compatible<T>;
  template<typename T> struct is_record_type
  {
    static constexpr bool value = kumi::is_record_type_v<T>;
  };
  template<typename T> inline constexpr std::size_t size_v = std::tuple_size<std::remove_cvref_t<T>>::value;
  template<typename T> struct size
  {
    static constexpr std::size_t value = kumi::size_v<T>;
  };
  template<std::size_t I, typename T> using element_t = std::tuple_element_t<I, std::remove_cvref_t<T>>;
  template<std::size_t I, typename T> struct element
  {
    using type = kumi::element_t<I, T>;
  };
  template<std::size_t I, typename T> using member_t = decltype(get<I>(std::declval<T&&>()));
  template<std::size_t I, typename T> struct member
  {
    using type = kumi::member_t<I, T>;
  };
}
namespace kumi
{
  template<typename T> inline constexpr bool is_container_v = kumi::_::container_like<T>;
  template<typename T, std::size_t N> inline constexpr bool is_container_v<T[N]> = true;
  template<typename T> struct is_container
  {
    static constexpr bool value = kumi::is_container_v<T>;
  };
  namespace _
  {
    template<typename T> inline constexpr std::size_t container_size_ = kumi::_::invalid{};
    template<template<class, std::size_t> typename Container, typename T, std::size_t N>
    requires kumi::_::container_like<Container<T, N>> && (N != static_cast<std::size_t>(-1))
    inline constexpr std::size_t container_size_<Container<T, N>> = N;
    template<typename T, std::size_t N> inline constexpr std::size_t container_size_<T[N]> = N;
  }
  template<typename T> inline constexpr std::size_t container_size_v = kumi::_::container_size_<std::remove_cvref_t<T>>;
  template<typename T> struct container_size
  {
    static constexpr std::size_t value = kumi::container_size_v<T>;
  };
  namespace _
  {
    template<typename T> extern kumi::_::undefined<T> container_type;
    template<typename T>
    requires(kumi::_::container_like<T>)
    extern typename T::value_type container_type<T>;
    template<typename T, std::size_t N> extern T container_type<T[N]>;
  }
  template<typename T> using container_type_t = decltype(kumi::_::container_type<std::remove_cvref_t<T>>);
  template<typename T> struct container_type
  {
    using type = kumi::container_type_t<T>;
  };
  template<typename T>
  inline constexpr bool has_static_size_v{
    (!std::same_as<std::integral_constant<std::size_t, kumi::container_size_v<T>>, kumi::_::invalid>)};
  template<typename T, std::size_t N> inline constexpr bool has_static_size_v<T[N]> = true;
  template<typename T> struct has_static_size
  {
    static constexpr bool value = kumi::has_static_size_v<T>;
  };
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename Seq> inline constexpr bool homogeneous_ = false;
    template<typename T> inline constexpr bool homogeneous_<T, std::index_sequence<>> = false;
    template<typename T, std::size_t... I>
    inline constexpr bool homogeneous_<T, std::index_sequence<I...>>{(sizeof...(I) == 1) ||
                                                                     kumi::_::all_the_same<kumi::element_t<I, T>...>};
  }
  template<typename T> inline constexpr bool is_homogeneous_v = false;
  template<typename T>
  requires(kumi::is_product_type_v<T> && !kumi::is_record_type_v<T>)
  inline constexpr bool is_homogeneous_v<T> = requires { requires T::is_homogeneous; } || kumi::is_container_v<T> ||
                                              kumi::_::homogeneous_<T, std::make_index_sequence<kumi::size_v<T>>>;
  template<typename T> struct is_homogeneous
  {
    static constexpr bool value = kumi::is_homogeneous_v<T>;
  };
  template<typename T> inline constexpr bool is_projection_map_v = requires { T::is_projection_map; };
  template<std::size_t... I> inline constexpr bool is_projection_map_v<std::index_sequence<I...>> = true;
  template<typename T> struct is_projection_map
  {
    static constexpr bool value = kumi::is_projection_map_v<T>;
  };
  namespace _
  {
    template<std::size_t I, typename T> extern kumi::member_t<I, T> stored_member;
    template<std::size_t I, typename T>
    requires(kumi::is_record_type_v<std::remove_cvref_t<T>>)
    extern decltype(get<kumi::_::identifier_of_t<kumi::element_t<I, T>>{}>(std::declval<T&&>())) stored_member<I, T>;
  }
  template<std::size_t I, typename T> using stored_member_t = decltype(kumi::_::stored_member<I, T>);
  template<std::size_t I, typename T> struct stored_member
  {
    using type = kumi::stored_member_t<I, T>;
  };
  namespace _
  {
    template<std::size_t I, typename T> extern kumi::element_t<I, T> stored_element;
    template<std::size_t I, typename T>
    requires(kumi::is_record_type_v<std::remove_cvref_t<T>>)
    extern typename kumi::element_t<I, T>::type stored_element<I, T>;
  }
  template<std::size_t I, typename T> using stored_element_t = decltype(kumi::_::stored_element<I, T>);
  template<std::size_t I, typename T> struct stored_element
  {
    using type = kumi::stored_element_t<I, T>;
  };
  template<typename T, typename U> inline constexpr bool is_instance_of_v = false;
  template<template<typename...> class T, typename... Args1, typename... Args2>
  inline constexpr bool is_instance_of_v<T<Args1...>, T<Args2...>> = true;
  template<template<auto...> class T, auto... Args1, auto... Args2>
  inline constexpr bool is_instance_of_v<T<Args1...>, T<Args2...>> = true;
  template<typename T, typename U> struct is_instance_of
  {
    static constexpr bool value = kumi::is_instance_of_v<T, U>;
  };
  template<typename... Ts> struct common_product_type;
  template<typename T, typename... Ts>
  requires((kumi::is_product_type_v<Ts> && ...) &&
           ((std::same_as<T, Ts> && ...) || (kumi::is_instance_of_v<T, Ts> && ...)))
  struct common_product_type<T, Ts...>
  {
    using type = std::remove_cvref_t<T>;
  };
  template<typename... Ts> using common_product_type_t = typename common_product_type<Ts...>::type;
  template<typename... Ts> inline constexpr bool all_uniques_v = kumi::_::is_set_v<kumi::_::make_family<Ts...>>;
  template<typename... Ts> struct all_uniques
  {
    static constexpr bool value = kumi::all_uniques_v<Ts...>;
  };
  template<typename... Ts> inline constexpr bool all_unique_names_v = kumi::_::is_map_v<kumi::_::make_family<Ts...>>;
  template<typename... Ts> struct all_unique_names
  {
    static constexpr bool value = kumi::all_unique_names_v<Ts...>;
  };
  namespace _
  {
    template<typename T, typename U, typename Seq> inline constexpr bool is_equivalent = false;
    template<typename T, typename U> inline constexpr bool is_equivalent<T, U, std::index_sequence<>> = true;
    template<typename T, typename U, std::size_t... Is>
    inline constexpr bool is_equivalent<T, U, std::index_sequence<Is...>>{
      kumi::_::same_mapping_v<kumi::_::family<std::index_sequence<Is...>, kumi::element_t<Is, T>...>,
                              kumi::element_t<Is, U>...>};
  }
  template<typename T, typename U> inline constexpr bool is_equivalent_v = false;
  template<typename T, typename U>
  requires((kumi::is_product_type_v<T> && kumi::is_product_type_v<U>) &&
           (!kumi::is_record_type_v<T> || !kumi::is_record_type_v<U>))
  inline constexpr bool is_equivalent_v<T, U> = kumi::size_v<T> == kumi::size_v<U>;
  template<typename T, typename U>
  requires(kumi::is_record_type_v<T> && kumi::is_record_type_v<U>)
  inline constexpr bool is_equivalent_v<T, U> =
    (kumi::size_v<T> == kumi::size_v<U>) && kumi::_::is_equivalent<T, U, std::make_index_sequence<kumi::size_v<T>>>;
  template<typename T, typename U> struct is_equivalent
  {
    static constexpr bool value = kumi::is_equivalent_v<T, U>;
  };
  namespace _
  {
    template<typename T, typename U, typename Seq> inline constexpr bool is_equality_comparable = false;
    template<typename T, typename U> inline constexpr bool is_equality_comparable<T, U, std::index_sequence<>> = true;
    template<typename T, typename U, std::size_t... I>
    requires(kumi::is_record_type_v<T> && kumi::is_record_type_v<U>)
    inline constexpr bool is_equality_comparable<T, U, std::index_sequence<I...>>{
      (kumi::_::comparable<decltype(std::declval<kumi::_::set<kumi::element_t<I, T>...>>()(
                             std::declval<kumi::_::identifier_of_t<kumi::element_t<I, U>>>())),
                           kumi::_::type_of_t<kumi::element_t<I, U>>> &&
       ...)};
    template<typename T, typename U, std::size_t... I>
    inline constexpr bool is_equality_comparable<T, U, std::index_sequence<I...>>{
      (kumi::_::comparable<kumi::element_t<I, T>, kumi::element_t<I, U>> && ...)};
  }
  template<typename T, typename U> inline constexpr bool is_equality_comparable_v = false;
  template<typename T, typename U>
  requires(kumi::is_product_type_v<T> && kumi::is_product_type_v<U>)
  inline constexpr bool is_equality_comparable_v<T, U>{
    (kumi::size_v<T> == kumi::size_v<U>) &&
    kumi::_::is_equality_comparable<T, U, std::make_index_sequence<kumi::size_v<T>>>};
  template<typename T, typename U> struct is_equality_comparable
  {
    static constexpr bool value = kumi::is_equality_comparable_v<T, U>;
  };
  template<template<typename...> typename Traits, typename T, typename Seq = std::make_index_sequence<kumi::size_v<T>>>
  requires is_product_type_v<std::remove_cvref_t<T>>
  struct apply_traits;
  template<template<typename...> typename Traits, typename T, std::size_t... Is>
  requires is_product_type_v<std::remove_cvref_t<T>> && (requires { typename Traits<kumi::element_t<Is, T>...>::type; })
  struct apply_traits<Traits, T, std::index_sequence<Is...>>
  {
    using type = typename Traits<kumi::element_t<Is, T>...>::type;
  };
  template<template<typename...> typename Traits, typename T>
  requires kumi::is_product_type_v<std::remove_cvref_t<T>>
  using apply_traits_t = typename kumi::apply_traits<Traits, T>::type;
  template<template<typename...> typename Traits, typename T, typename Seq = std::make_index_sequence<kumi::size_v<T>>>
  requires kumi::is_product_type_v<std::remove_cvref_t<T>>
  struct map_traits;
  template<template<typename...> typename Traits, typename T, std::size_t... Is>
  requires kumi::is_product_type_v<std::remove_cvref_t<T>> &&
           (requires { typename Traits<kumi::element_t<Is, T>>::type; } && ...)
  struct map_traits<Traits, T, std::index_sequence<Is...>>
  {
    using type = kumi::builder_make_t<T, typename Traits<kumi::element_t<Is, T>>::type...>;
  };
  template<template<typename...> typename Traits, typename T>
  requires kumi::is_product_type_v<std::remove_cvref_t<T>>
  using map_traits_t = typename kumi::map_traits<Traits, T>::type;
}
namespace kumi
{
#ifndef KUMI_DOXYGEN_INVOKED
  template<typename T> inline constexpr bool is_kumi_tuple_v = false;
  template<typename... Ts> inline constexpr bool is_kumi_tuple_v<kumi::tuple<Ts...>> = true;
  template<typename T> struct is_kumi_tuple
  {
    static constexpr bool value = kumi::is_kumi_tuple_v<T>;
  };
  template<typename T> inline constexpr bool is_kumi_record_v = false;
  template<typename... Ts> inline constexpr bool is_kumi_record_v<kumi::record<Ts...>> = true;
  template<typename T> struct is_kumi_record
  {
    static constexpr bool value = kumi::is_kumi_record_v<T>;
  };
#endif
}
namespace kumi
{
  namespace _
  {
    template<typename F, typename T, typename Seq> inline constexpr bool can_apply = false;
    template<typename F, typename T, std::size_t... N>
    inline constexpr bool can_apply<F, T, std::index_sequence<N...>> =
      std::invocable<F, kumi::stored_member_t<N, T>...>;
    template<typename F, typename T>
    concept supports_apply = can_apply<F, T, std::make_index_sequence<kumi::size_v<T>>>;
    template<typename F, typename T, typename Seq> inline constexpr bool can_nothrow_apply = false;
    template<typename F, typename T, std::size_t... N>
    inline constexpr bool can_nothrow_apply<F, T, std::index_sequence<N...>> =
      std::is_nothrow_invocable_v<F, kumi::stored_member_t<N, T>...>;
    template<typename F, typename T>
    concept supports_nothrow_apply = can_nothrow_apply<F, T, std::make_index_sequence<kumi::size_v<T>>>;
    template<std::size_t N, typename F, typename... Ts>
    inline constexpr bool can_call_ = std::invocable<F, kumi::stored_member_t<N, Ts>...>;
    template<typename F, typename Seq, typename... Ts> inline constexpr bool can_call = false;
    template<typename F, std::size_t... N, typename... Ts>
    inline constexpr bool can_call<F, std::index_sequence<N...>, Ts...> = (can_call_<N, F, Ts...> && ...);
    template<typename F, typename T, typename... Ts>
    concept supports_call = can_call<F, std::make_index_sequence<kumi::size_v<T>>, T, Ts...>;
    template<typename T, typename Seq> inline constexpr bool can_transpose = false;
    template<typename T, std::size_t... N>
    inline constexpr bool can_transpose<T, std::index_sequence<N...>> =
      ((kumi::size_v<kumi::stored_member_t<0, T>> == kumi::size_v<kumi::stored_member_t<N + 1, T>>) && ...);
    template<typename T>
    concept supports_transpose =
      (kumi::size_v<T> <= 1) || can_transpose<T, std::make_index_sequence<kumi::size_v<T> - 1>>;
  }
  namespace concepts
  {
    template<typename T>
    concept product_type = kumi::is_product_type_v<std::remove_cvref_t<T>>;
    template<typename T>
    concept record_type = kumi::concepts::product_type<T> && kumi::is_record_type_v<std::remove_cvref_t<T>>;
    template<typename T>
    concept container = kumi::is_container_v<std::remove_cvref_t<T>>;
    template<typename T>
    concept static_container = kumi::concepts::container<T> && kumi::has_static_size_v<std::remove_cvref_t<T>>;
    template<typename T>
    concept unit_type =
      (kumi::concepts::product_type<T> && (kumi::size_v<T> == 0)) || std::is_null_pointer_v<std::remove_cvref_t<T>>;
    template<typename T>
    concept index = requires(T const& t) {
      { T::value } -> std::convertible_to<std::size_t>;
    };
    template<typename T>
    concept field = kumi::_::field<T>;
    template<typename T>
    concept identifier = kumi::_::identifier<T>;
    template<typename T>
    concept projection_map = kumi::is_projection_map_v<std::remove_cvref_t<T>>;
    template<typename T>
    concept projection = kumi::concepts::projection_map<T> || kumi::concepts::identifier<T> || kumi::concepts::index<T>;
    template<typename T, std::size_t N>
    concept sized_product_type = kumi::concepts::product_type<T> && (kumi::size_v<T> == N);
    template<typename T, std::size_t N>
    concept sized_product_type_or_more = kumi::concepts::product_type<T> && (kumi::size_v<T> >= N);
    template<typename T>
    concept empty_product_type = kumi::concepts::product_type<T> && (kumi::size_v<T> == 0);
    template<typename T>
    concept non_empty_product_type = kumi::concepts::product_type<T> && (kumi::size_v<T> != 0);
    template<typename T>
    concept homogeneous_product_type =
      kumi::concepts::product_type<T> && kumi::is_homogeneous_v<std::remove_cvref_t<T>>;
    template<typename... Ts>
    concept has_named_fields = (... || kumi::concepts::field<Ts>);
    template<typename... Ts>
    concept fully_named = (... && kumi::concepts::field<Ts>);
    template<typename... Ts>
    concept uniquely_typed = (sizeof...(Ts) == 0) || (!kumi::concepts::has_named_fields<Ts...> &&
                                                      kumi::all_uniques_v<std::remove_cvref_t<Ts>...>);
    template<typename... Ts>
    concept uniquely_named = (sizeof...(Ts) == 0) || (kumi::concepts::has_named_fields<Ts...> &&
                                                      kumi::all_unique_names_v<std::remove_cvref_t<Ts>...>);
    template<typename... Ts>
    concept uniquely_labeled =
      (sizeof...(Ts) == 0) ||
      (kumi::concepts::fully_named<Ts...> &&
       (kumi::all_uniques_v<std::integral_constant<kumi::str<std::remove_cvref_t<Ts>::label().size()>,
                                                   std::remove_cvref_t<Ts>::label()>...>));
    template<typename T, typename... Ts>
    concept contains_type = kumi::_::index_of_type<T, Ts...>::value != kumi::_::invalid{};
    template<typename Name, typename... Ts>
    concept contains_identifier =
      kumi::concepts::identifier<Name> && kumi::_::index_of_tag<Name, Ts...>::value != kumi::_::invalid{};
    template<typename Label, typename... Ts>
    concept contains_label =
      kumi::_::label<Label> && kumi::_::index_of_label<std::remove_cvref_t<Label>, Ts...>::value != kumi::_::invalid{};
    template<typename T, typename U>
    concept equivalent = kumi::concepts::product_type<T> && kumi::concepts::product_type<U> &&
                         kumi::is_equivalent_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;
    template<typename T, typename U>
    concept equality_comparable = kumi::concepts::equivalent<T, U> &&
                                  kumi::is_equality_comparable_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;
    template<typename... Ts>
    concept follows_same_semantic = ((kumi::concepts::product_type<Ts> && !kumi::concepts::record_type<Ts>) && ...) ||
                                    ((kumi::concepts::record_type<Ts> && ...));
    template<typename T, typename... Us>
    concept compatible_product_types =
      (kumi::concepts::follows_same_semantic<T, Us...> && (kumi::concepts::equivalent<T, Us> && ...));
    template<typename M>
    concept monoid = requires {
      { std::remove_cvref_t<M>::identity };
      { std::remove_cvref_t<M>{}(std::remove_cvref_t<M>::identity, std::remove_cvref_t<M>::identity) };
    };
    template<typename Type, typename T>
    concept queryable_by_type =
      kumi::concepts::product_type<T> &&
      kumi::_::can_query<kumi::_::index_of_type, Type, T, std::make_index_sequence<kumi::size_v<T>>>;
    template<typename Id, typename T>
    concept queryable_by_identifier =
      kumi::concepts::identifier<Id> && kumi::concepts::product_type<T> &&
      kumi::_::can_query<kumi::_::index_of_tag, Id, T, std::make_index_sequence<kumi::size_v<T>>>;
    template<typename L, typename T>
    concept queryable_by_label =
      kumi::_::label<L> && kumi::concepts::product_type<T> &&
      kumi::_::can_query<kumi::_::index_of_label, L, T, std::make_index_sequence<kumi::size_v<T>>>;
  }
}
namespace kumi
{
  struct unit
  {
    KUMI_ABI friend constexpr auto operator<=>(unit, unit) noexcept = default;
    template<typename T>
    [[nodiscard]] KUMI_ABI constexpr operator T() const noexcept
    requires(kumi::concepts::unit_type<T>)
    {
      return {};
    }
    template<typename T>
    [[nodiscard]] KUMI_ABI constexpr operator T() noexcept
    requires(kumi::concepts::unit_type<T>)
    {
      return {};
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, unit) noexcept
    {
      return os << '\'' << "none" << '\'';
    }
  };
  inline constexpr kumi::unit none{};
}
namespace kumi
{
  inline constexpr auto npos = static_cast<std::size_t>(-1);
  template<std::size_t N> struct str
  {
    static constexpr char separator = '.';
    char data_[N + 1] = {0};
    constexpr str() = default;
    KUMI_ABI constexpr str(char const (&s)[N + 1])
    {
      for (std::size_t i = 0; i < N + 1; ++i) data_[i] = s[i];
    }
    KUMI_ABI constexpr std::size_t size() const noexcept { return N; }
    KUMI_ABI constexpr auto data() const noexcept { return data_; }
    template<typename T>
    requires requires { T{data_, std::size_t{N}}; }
    KUMI_ABI constexpr auto as() const
    {
      return T{data_, std::size_t{N}};
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, str const& s) noexcept
    {
      os << '\'';
      for (std::size_t i = 0; i < N; ++i) os << s.data_[i];
      return os << '\'';
    }
    template<kumi::concepts::index Pos, kumi::concepts::index Count>
    KUMI_ABI constexpr auto substr(Pos p, Count c) const
    {
      constexpr std::size_t pos = static_cast<std::size_t>(p);
      constexpr std::size_t count = static_cast<std::size_t>(c);
      static_assert(pos <= N, "Out of range");
      constexpr std::size_t len = (count == kumi::npos || pos + count > N) ? (N - pos) : count;
      str<len> res{};
      for (std::size_t i = 0; i < len; ++i) res.data_[i] = data_[pos + i];
      return res;
    }
    template<kumi::concepts::index Pos> KUMI_ABI constexpr auto substr(Pos p) const
    {
      return substr(p, std::integral_constant<std::size_t, kumi::npos>{});
    }
    KUMI_ABI constexpr auto substr() const { return substr(std::integral_constant<std::size_t, 0>{}); }
    template<kumi::concepts::index Size> KUMI_ABI constexpr auto remove_prefix(Size s) const
    {
      static_assert(static_cast<std::size_t>(s) <= N, "Out of range");
      return substr(std::integral_constant<std::size_t, static_cast<std::size_t>(s)>{},
                    std::integral_constant<std::size_t, N - static_cast<std::size_t>(s)>{});
    }
    template<kumi::concepts::index Size> KUMI_ABI constexpr auto remove_suffix(Size s) const
    {
      static_assert(static_cast<std::size_t>(s) <= N, "Out of range");
      return substr(std::integral_constant<std::size_t, 0>{},
                    std::integral_constant<std::size_t, N - static_cast<std::size_t>(s)>{});
    }
    template<std::size_t M> KUMI_ABI constexpr bool starts_with(char const (&s)[M]) const
    {
      constexpr std::size_t n = M - 1;
      if (n > N) return false;
      for (std::size_t i = 0; i < n; ++i)
        if (data_[i] != s[i]) return false;
      return true;
    }
    template<std::size_t M> KUMI_ABI constexpr bool ends_with(char const (&s)[M]) const
    {
      constexpr std::size_t n = M - 1;
      if (n > N) return false;
      for (std::size_t i = 0; i < n; ++i)
        if (data_[N - n + i] != s[i]) return false;
      return true;
    }
    template<std::size_t M> KUMI_ABI constexpr bool contains(char const (&s)[M]) const { return find(s) != kumi::npos; }
    template<std::size_t M> KUMI_ABI constexpr std::size_t find(char const (&s)[M], std::size_t pos = 0) const
    {
      constexpr std::size_t n = M - 1;
      if (n == 0) return pos <= N ? pos : kumi::npos;
      if (n > N) return kumi::npos;
      for (std::size_t i = pos; i <= N - n; ++i)
      {
        bool match = true;
        for (std::size_t j = 0; j < n; ++j)
          if (data_[i + j] != s[j])
          {
            match = false;
            break;
          }
        if (match) return i;
      }
      return kumi::npos;
    }
    template<std::size_t M> KUMI_ABI constexpr int compare(char const (&other)[M]) const noexcept
    {
      constexpr std::size_t n = M - 1;
      constexpr std::size_t min_size = (N < n) ? N : n;
      for (std::size_t i = 0; i < min_size; ++i)
      {
        if (data_[i] < other[i]) return -1;
        if (data_[i] > other[i]) return 1;
      }
      if (N < n) return -1;
      if (N > n) return 1;
      return 0;
    }
    template<std::size_t M> KUMI_ABI constexpr std::size_t rfind(char const (&s)[M], std::size_t pos = kumi::npos) const
    {
      constexpr std::size_t n = M - 1;
      if (n == 0) return (pos > N ? N : pos);
      if (n > N) return kumi::npos;
      std::size_t start = (pos > N - n) ? (N - n) : pos;
      for (std::size_t i = start; i > 0; --i)
      {
        bool match = true;
        for (std::size_t j = 0; j < n; ++j)
          if (data_[i + j] != s[j])
          {
            match = false;
            break;
          }
        if (match) return i;
      }
      return kumi::npos;
    }
    template<std::size_t M> KUMI_ABI constexpr std::size_t find_first_of(char const (&s)[M], std::size_t pos = 0) const
    {
      constexpr std::size_t n = M - 1;
      for (std::size_t i = pos; i < N; ++i)
        for (std::size_t j = 0; j < n; ++j)
          if (data_[i] == s[j]) return i;
      return kumi::npos;
    }
    template<std::size_t M>
    KUMI_ABI constexpr std::size_t find_last_of(char const (&s)[M], std::size_t pos = kumi::npos) const
    {
      constexpr std::size_t n = M - 1;
      if (N == 0) return kumi::npos;
      for (std::size_t i = (pos >= N ? N - 1 : pos);; --i)
      {
        for (std::size_t j = 0; j < n; ++j)
          if (data_[i] == s[j]) return i;
        if (i == 0) break;
      }
      return kumi::npos;
    }
    template<std::size_t M>
    KUMI_ABI constexpr std::size_t find_first_not_of(char const (&s)[M], std::size_t pos = 0) const
    {
      constexpr std::size_t n = M - 1;
      for (std::size_t i = pos; i < N; ++i)
      {
        bool found = false;
        for (std::size_t j = 0; j < n; ++j)
          if (data_[i] == s[j])
          {
            found = true;
            break;
          }
        if (!found) return i;
      }
      return kumi::npos;
    }
    template<std::size_t M>
    KUMI_ABI constexpr std::size_t find_last_not_of(char const (&s)[M], std::size_t pos = kumi::npos) const
    {
      constexpr std::size_t n = M - 1;
      if (N == 0) return kumi::npos;
      for (std::size_t i = (pos >= N ? N - 1 : pos);; --i)
      {
        bool found = false;
        for (std::size_t j = 0; j < n; ++j)
          if (data_[i] == s[j])
          {
            found = true;
            break;
          }
        if (!found) return i;
        if (i == 0) break;
      }
      return kumi::npos;
    }
    template<std::size_t M> KUMI_ABI constexpr str<N + M> operator+(char const (&other)[M]) const
    {
      str<N + M> res{};
      for (std::size_t i = 0; i < N; ++i) res.data_[i] = data_[i];
      res.data_[N] = separator;
      for (std::size_t i = 0; i < M - 1; ++i) res.data_[N + 1 + i] = other[i];
      return res;
    }
    template<std::size_t M> KUMI_ABI constexpr str<N + 1 + M> operator+(str<M> const& other) const
    {
      return *this + other.data_;
    }
  };
  template<std::size_t M> str(char const (&)[M]) -> str<M - 1>;
  template<std::size_t N, std::size_t M>
  KUMI_ABI constexpr bool operator==(str<N> const& lhs, str<M> const& rhs) noexcept
  {
    return lhs.compare(rhs.data_) == 0;
  }
  template<std::size_t N, std::size_t M>
  KUMI_ABI constexpr auto operator<=>(str<N> const& lhs, str<M> const& rhs) noexcept
  {
    return lhs.compare(rhs.data_) <=> 0;
  }
  template<std::size_t N, std::size_t M>
  KUMI_ABI constexpr bool operator==(str<N> const& lhs, char const (&rhs)[M]) noexcept
  {
    return lhs.compare(rhs) == 0;
  }
  template<std::size_t N, std::size_t M>
  KUMI_ABI constexpr auto operator<=>(str<N> const& lhs, char const (&rhs)[M]) noexcept
  {
    return lhs.compare(rhs) <=> 0;
  }
  inline namespace literals
  {
    template<kumi::str S> KUMI_ABI constexpr auto operator""_str()
    {
      return S;
    }
  }
  struct unknown
  {
    static constexpr auto value = kumi::str{"kumi::unknown"};
    using type = decltype(value);
    constexpr inline operator type() const noexcept { return value; }
    KUMI_ABI friend constexpr auto operator<=>(unknown const&, unknown const&) noexcept = default;
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, unknown const&) noexcept
    {
      return os << "kumi::unknown";
    }
  };
}
namespace kumi
{
  template<typename T> [[nodiscard]] consteval auto typer() noexcept
  {
#if defined(__clang__)
    constexpr auto pfx = kumi::str{"auto kumi::typer() [T = "}.size();
    constexpr auto sfx = kumi::str{"]"}.size();
    constexpr auto value = kumi::str{__PRETTY_FUNCTION__}
                             .remove_prefix(std::integral_constant<std::size_t, pfx>{})
                             .remove_suffix(std::integral_constant<std::size_t, sfx>{});
#elif defined(__GNUC__)
    constexpr auto pfx = kumi::str{"constexpr auto kumi::typer() [with T = "}.size();
    constexpr auto sfx = kumi::str{"]"}.size();
    constexpr auto value = kumi::str{__PRETTY_FUNCTION__}
                             .remove_prefix(std::integral_constant<std::size_t, pfx>{})
                             .remove_suffix(std::integral_constant<std::size_t, sfx>{});
#elif defined(_MSC_VER)
    constexpr auto pfx = kumi::str{"auto __cdecl kumi::typer<"}.size();
    constexpr auto sfx = kumi::str{">(void)"}.size();
    constexpr auto value = kumi::str{__FUNCSIG__}
                             .remove_prefix(std::integral_constant<std::size_t, pfx>{})
                             .remove_suffix(std::integral_constant<std::size_t, sfx>{});
#endif
    return value;
  }
}
#ifdef KUMI_DOXYGEN_INVOKED
auto as_streamable(auto e);
kumi::str constexpr to_str(auto e);
#endif
namespace kumi::_
{
  template<typename T> auto make_streamable(T const& e)
  {
    if constexpr (requires(std::ostream& os) { os << e; }) return e;
    else if constexpr (requires { as_streamable(e); }) return as_streamable(e);
    else return kumi::unknown{};
  }
  template<kumi::_::valid_label T> consteval kumi::_::str_like auto make_str(T const& t)
  {
    if constexpr (requires { to_str(t); }) return to_str(t);
    else return kumi::typer<std::remove_cvref_t<T>>();
  }
}
namespace kumi
{
  template<typename Id, typename T> struct field
  {
    static constexpr auto label() { return kumi::_::make_str(Id{}); }
    using type = T;
    using identifier_type = Id;
    using inner_type = std::type_identity<T>;
    using label_type = std::integral_constant<kumi::str<label().size()>, label()>;
    T value;
    KUMI_HIDDEN_ABI constexpr T& operator()(identifier_type) & noexcept { return value; }
    KUMI_HIDDEN_ABI constexpr T&& operator()(identifier_type) && noexcept { return static_cast<T&&>(value); }
    KUMI_HIDDEN_ABI constexpr T const& operator()(identifier_type) const& noexcept { return value; }
    KUMI_HIDDEN_ABI constexpr T const&& operator()(identifier_type) const&& noexcept
    {
      return static_cast<T const&&>(value);
    }
    KUMI_HIDDEN_ABI constexpr T& operator()(inner_type) & noexcept { return value; }
    KUMI_HIDDEN_ABI constexpr T&& operator()(inner_type) && noexcept { return static_cast<T&&>(value); }
    KUMI_HIDDEN_ABI constexpr T const& operator()(inner_type) const& noexcept { return value; }
    KUMI_HIDDEN_ABI constexpr T const&& operator()(inner_type) const&& noexcept
    {
      return static_cast<T const&&>(value);
    }
    KUMI_HIDDEN_ABI constexpr T& operator()(label_type) & noexcept { return value; }
    KUMI_HIDDEN_ABI constexpr T&& operator()(label_type) && noexcept { return static_cast<T&&>(value); }
    KUMI_HIDDEN_ABI constexpr T const& operator()(label_type) const& noexcept { return value; }
    KUMI_HIDDEN_ABI constexpr T const&& operator()(label_type) const&& noexcept
    {
      return static_cast<T const&&>(value);
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, field const& w) noexcept
    {
      return os << kumi::_::make_str(std::remove_cvref_t<Id>{}) << " : " << kumi::_::make_streamable(w.value);
    }
  };
  template<typename Id, typename T>
  requires(std::is_empty_v<T> && !std::is_final_v<T>)
  struct field<Id, T> : T
  {
    static constexpr auto label() { return kumi::_::make_str(Id{}); }
    using type = T;
    using identifier_type = Id;
    using inner_type = std::type_identity<T>;
    using label_type = std::integral_constant<kumi::str<label().size()>, label()>;
    KUMI_HIDDEN_ABI constexpr T& operator()(identifier_type) & noexcept { return *this; }
    KUMI_HIDDEN_ABI constexpr T&& operator()(identifier_type) && noexcept { return static_cast<T&&>(*this); }
    KUMI_HIDDEN_ABI constexpr T const& operator()(identifier_type) const& noexcept { return *this; }
    KUMI_HIDDEN_ABI constexpr T const&& operator()(identifier_type) const&& noexcept
    {
      return static_cast<T const&&>(*this);
    }
    KUMI_HIDDEN_ABI constexpr T& operator()(inner_type) & noexcept { return *this; }
    KUMI_HIDDEN_ABI constexpr T&& operator()(inner_type) && noexcept { return static_cast<T&&>(*this); }
    KUMI_HIDDEN_ABI constexpr T const& operator()(inner_type) const& noexcept { return *this; }
    KUMI_HIDDEN_ABI constexpr T const&& operator()(inner_type) const&& noexcept
    {
      return static_cast<T const&&>(*this);
    }
    KUMI_HIDDEN_ABI constexpr T& operator()(label_type) & noexcept { return *this; }
    KUMI_HIDDEN_ABI constexpr T&& operator()(label_type) && noexcept { return static_cast<T&&>(*this); }
    KUMI_HIDDEN_ABI constexpr T const& operator()(label_type) const& noexcept { return *this; }
    KUMI_HIDDEN_ABI constexpr T const&& operator()(label_type) const&& noexcept
    {
      return static_cast<T const&&>(*this);
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, field const& w) noexcept
    {
      return os << kumi::_::make_str(std::remove_cvref_t<Id>{}) << " : "
                << kumi::_::make_streamable(w(_::identifier_of_t<decltype(w)>{}));
    }
  };
  template<typename Id, typename T>
  requires(!kumi::_::valid_label<Id>)
  struct field<Id, T>
  {
    field(T&&) = delete;
    static_assert(kumi::_::valid_label<Id>, "User defined to_str(...) function is not constexpr");
  };
  template<typename T> [[nodiscard]] KUMI_ABI consteval auto identifier_of() noexcept
  {
    if constexpr (kumi::_::field<T>) return kumi::_::identifier_of_t<T>{};
    else return kumi::unknown{};
  }
  template<typename T> [[nodiscard]] KUMI_ABI consteval kumi::_::str_like auto label_of() noexcept
  {
    if constexpr (kumi::_::field<T>) return kumi::_::label_of_t<T>::value;
    else return kumi::unknown::value;
  }
  template<typename T> [[nodiscard]] KUMI_ABI constexpr decltype(auto) field_value_of(T&& t) noexcept
  {
    if constexpr (kumi::_::field<T>) return (KUMI_FWD(t)(kumi::_::identifier_of_t<T>{}));
    else return KUMI_FWD(t);
  }
  template<_::identifier auto Name, typename T>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) capture_field(T&& t) noexcept
  {
    return kumi::field<decltype(Name), T>{KUMI_FWD(t)};
  }
  template<typename U, typename T> [[nodiscard]] KUMI_ABI constexpr decltype(auto) field_cast(T&& t) noexcept
  {
    if constexpr (kumi::_::field<U>)
      return kumi::field<kumi::_::identifier_of_t<T>, kumi::_::type_of_t<U>>{
        static_cast<kumi::_::type_of_t<U>>(KUMI_FWD(t)(kumi::_::identifier_of_t<T>{}))};
    else if constexpr (!kumi::_::field<T>) return static_cast<kumi::_::type_of_t<U>>(KUMI_FWD(t));
    else return kumi::field<kumi::_::identifier_of_t<T>, U>{static_cast<U>(KUMI_FWD(t)(kumi::_::identifier_of_t<T>{}))};
  }
  namespace result
  {
    template<typename T> using identifier_of_t = decltype(kumi::identifier_of<T>());
    template<typename T> struct identifier_of
    {
      using type = kumi::result::identifier_of_t<T>;
    };
    template<typename T> using label_of_t = decltype(kumi::label_of<T>());
    template<typename T> struct label_of
    {
      using type = kumi::result::label_of_t<T>;
    };
    template<typename T> using field_value_of_t = decltype(kumi::field_value_of(std::declval<T>()));
    template<typename T> struct field_value_of
    {
      using type = kumi::result::field_value_of_t<T>;
    };
    template<_::identifier auto Name, typename T>
    using capture_field_t = decltype(kumi::capture_field<Name>(std::declval<T>()));
    template<kumi::_::identifier auto Name, typename T> struct capture_field
    {
      using type = kumi::result::capture_field_t<Name, T>;
    };
    template<typename U, typename T> using field_cast_t = decltype(kumi::field_cast<U, T>(std::declval<T>()));
    template<typename U, typename T> struct field_cast
    {
      using type = kumi::result::field_cast_t<U, T>;
    };
  }
}
namespace kumi
{
  template<typename T> struct only_t
  {
    template<typename U> static constexpr bool value = std::same_as<T, U>;
  };
  template<template<class> typename Traits> struct traits_check
  {
    template<typename U> static constexpr bool value = Traits<U>::value;
  };
  template<typename T> inline constexpr kumi::only_t<T> only = {};
  template<template<class> typename Traits> inline constexpr traits_check<Traits> if_ = {};
  template<typename ID, typename Check = void> struct identifier;
  template<typename ID> struct identifier<ID, void>
  {
    using type = std::remove_cvref_t<ID>;
    constexpr identifier() noexcept = default;
    constexpr identifier(ID const&) noexcept {}
    template<typename T> constexpr kumi::field<type, std::unwrap_ref_decay_t<T>> operator=(T&& v) const noexcept
    {
      return {KUMI_FWD(v)};
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         identifier const&) noexcept
    {
      return os << kumi::_::make_str(type{});
    }
  };
  template<typename ID, typename Checker> struct identifier
  {
    using type = identifier<ID, Checker>;
    friend constexpr kumi::_::str_like auto to_str(identifier const&) { return kumi::_::make_str(ID{}); }
    constexpr identifier() noexcept = default;
    constexpr identifier([[maybe_unused]] ID const& id, [[maybe_unused]] Checker const& check) noexcept {}
    template<typename T>
    requires(Checker::template value<T>)
    constexpr auto operator=(T&& v) const noexcept -> kumi::field<type, std::unwrap_ref_decay_t<T>>
    {
      return {KUMI_FWD(v)};
    }
    template<typename T>
    requires(!Checker::template value<T>)
    constexpr kumi::field<type, std::unwrap_ref_decay_t<T>> operator=(T&& v) const = delete;
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         identifier const&) noexcept
    {
      return os << kumi::_::make_str(identifier{});
    }
  };
  template<typename ID> identifier(ID const&) -> identifier<ID>;
  template<typename ID, typename Checker> identifier(ID const&, Checker const&) -> identifier<ID, Checker>;
  template<kumi::str ID> struct name
  {
    using type = name<ID>;
    friend constexpr kumi::_::str_like auto to_str(name const&) { return ID; }
    template<typename T> constexpr auto operator=(T&& v) const noexcept -> kumi::field<type, std::unwrap_ref_decay_t<T>>
    {
      return {KUMI_FWD(v)};
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, name const&) noexcept
    {
      return os << ID;
    }
  };
  template<kumi::concepts::identifier L, kumi::concepts::identifier R>
  KUMI_ABI constexpr bool operator==(L const&, R const&)
  {
    return std::same_as<std::remove_cvref_t<L>, std::remove_cvref_t<R>>;
  }
  namespace _
  {
    template<auto N, typename... Ts> consteval auto contains_identifier()
    {
      if constexpr (std::integral<std::remove_cvref_t<decltype(N)>>) return false;
      else if constexpr (kumi::concepts::index<decltype(N)>) return false;
      else if constexpr (kumi::concepts::identifier<std::remove_cvref_t<decltype(N)>>) return false;
      else return kumi::concepts::contains_identifier<kumi::name<N>, Ts...>;
    }
    template<auto N, typename... Ts> consteval auto contains_label()
    {
      if constexpr (std::integral<std::remove_cvref_t<decltype(N)>>) return false;
      else if constexpr (kumi::concepts::index<decltype(N)>) return false;
      else if constexpr (!kumi::_::str_like<decltype(N)>) return false;
      else return kumi::concepts::contains_label<std::integral_constant<kumi::str<N.size()>, N>, Ts...>;
    }
  }
}
namespace kumi
{
  namespace _
  {
    template<char... c> constexpr auto b10()
    {
      auto value = 0ULL;
      ((value = value * 10 + (c - '0')), ...);
      return value;
    }
  }
  template<std::size_t N> struct index_t
  {
    static constexpr auto value = N;
    constexpr inline operator std::size_t() const noexcept { return N; }
    constexpr inline operator std::integral_constant<std::size_t, N>() const noexcept { return {}; }
  };
  template<std::size_t N> inline constexpr kumi::index_t<N> index = {};
  template<kumi::str Label> struct label_t
  {
    using type = decltype(Label);
    static constexpr kumi::str value = Label;
    constexpr inline operator type() const noexcept { return Label; }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, label_t const&) noexcept
    {
      return os << value;
    }
  };
  template<str Label> inline constexpr kumi::label_t<Label> label = {};
  inline namespace literals
  {
    template<char... c> constexpr auto operator""_c() noexcept
    {
      return kumi::index<kumi::_::b10<c...>()>;
    }
    template<kumi::str ID> constexpr auto operator""_id() noexcept
    {
      return kumi::name<ID>{};
    }
    template<kumi::str ID> constexpr auto operator""_l() noexcept
    {
      return kumi::label<ID>;
    }
  }
  template<template<class> class Pred> [[nodiscard]] constexpr auto predicate() noexcept
  {
    return []<typename T>(T const&) constexpr { return Pred<T>::value; };
  }
  template<typename U, kumi::concepts::product_type T>
  KUMI_ABI consteval auto get_index_of_type()
  requires(kumi::concepts::queryable_by_type<U, T>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::_::index_of_type<U, kumi::stored_element_t<I, T>...>::value;
    }(std::make_index_sequence<kumi::size_v<T>>{});
  }
  template<kumi::concepts::identifier Id, kumi::concepts::product_type T>
  KUMI_ABI consteval auto get_index_of_field()
  requires(kumi::concepts::queryable_by_identifier<Id, T>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::_::index_of_tag<Id, kumi::element_t<I, T>...>::value;
    }(std::make_index_sequence<kumi::size_v<T>>{});
  }
  template<kumi::str L, kumi::concepts::product_type T>
  KUMI_ABI consteval auto get_index_of_label()
  requires(kumi::concepts::queryable_by_label<kumi::label_t<L>, T>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::_::index_of_label<kumi::label_t<L>, kumi::element_t<I, T>...>::value;
    }(std::make_index_sequence<kumi::size_v<T>>{});
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t I, typename T> extern std::size_t value_at;
    template<std::size_t I, auto Head, auto... Tail>
    inline constexpr auto value_at<I, kumi::projection_map<Head, Tail...>> =
      kumi::_::value_at<I - 1, kumi::projection_map<Tail...>>;
    template<std::size_t I, auto... Vs>
    inline constexpr auto value_at<I, kumi::projection_map<Vs...> const> =
      kumi::_::value_at<I, kumi::projection_map<Vs...>>;
    template<auto Head, auto... Tail> inline constexpr auto value_at<0, kumi::projection_map<Head, Tail...>> = Head;
  }
  template<auto... V> struct projection_map
  {
    static_assert((kumi::concepts::projection<decltype(V)> && ...), "Invalid projections in projection_map definition");
    static constexpr bool is_projection_map = true;
    consteval projection_map() noexcept = default;
    consteval explicit projection_map(auto...) noexcept {}
    [[nodiscard]] static consteval auto size() noexcept { return sizeof...(V); }
    [[nodiscard]] static consteval bool empty() noexcept { return sizeof...(V) == 0; }
    template<std::size_t I>
    requires(I < sizeof...(V))
    constexpr decltype(auto) operator[]([[maybe_unused]] kumi::index_t<I> i) const noexcept
    {
      return kumi::_::value_at<I, projection_map>;
    }
    template<std::size_t I>
    requires(I < sizeof...(V))
    [[nodiscard]] friend constexpr decltype(auto) get(projection_map const& pm) noexcept
    {
      return pm[kumi::index<I>];
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         projection_map const&) noexcept
    {
      std::size_t p = 0;
      os << '[';
      ((os << V << (++p < sizeof...(V) ? ", " : "")), ...);
      os << ']';
      return os;
    }
  };
  template<kumi::concepts::projection... Ts> projection_map(Ts...) -> projection_map<Ts{}...>;
  template<kumi::concepts::index... Ts> [[nodiscard]] consteval auto indexes(Ts...) noexcept
  {
    return kumi::projection_map<Ts{}...>{};
  }
  template<std::convertible_to<std::size_t> auto... vs> [[nodiscard]] consteval auto make_indexes() noexcept
  {
    return kumi::projection_map<kumi::index<vs>...>{};
  }
  template<kumi::concepts::identifier... Ts>
  requires(kumi::all_uniques_v<Ts...>)
  [[nodiscard]] consteval auto identifiers(Ts...) noexcept
  {
    return kumi::projection_map<Ts{}...>{};
  }
}
#if !defined(KUMI_DOXYGEN_INVOKED)
namespace kumi::_
{
  template<std::size_t I, typename T> extern kumi::_::undefined<T> tuple_element;
  template<template<class...> class Box, typename Head, typename... Tail>
  extern Head tuple_element<0, Box<Head, Tail...>>;
  template<std::size_t I, template<class...> typename Box, typename Head, typename... Tail>
  extern decltype(kumi::_::tuple_element<I - 1, Box<Tail...>>) tuple_element<I, Box<Head, Tail...>>;
  template<std::size_t I, template<class...> typename Box, typename... Ts>
  extern decltype(kumi::_::tuple_element<I, Box<Ts...>>) const tuple_element<I, Box<Ts...> const>;
}
template<std::size_t I, typename... Ts> struct std::tuple_element<I, kumi::tuple<Ts...>>
{
  static_assert(I < sizeof...(Ts), "[KUMI] - Tuple index must be in range");
  using type = decltype(kumi::_::tuple_element<I, kumi::tuple<Ts...>>);
};
template<typename... Ts> struct std::tuple_size<kumi::tuple<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>
{
};
template<std::size_t I, typename... Ts> struct std::tuple_element<I, kumi::record<Ts...>>
{
  static_assert(I < sizeof...(Ts), "[KUMI] - Record index must be in range");
  using type = decltype(kumi::_::tuple_element<I, kumi::record<Ts...>>);
};
template<typename... Ts>
struct std::tuple_size<kumi::record<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>
{
};
template<> struct std::tuple_size<kumi::unit> : std::integral_constant<std::size_t, 0>
{
};
template<std::size_t I> struct std::tuple_element<I, kumi::unit>
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
namespace kumi
{
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename U, std::size_t... I> constexpr T static_cast_(U&& u, std::index_sequence<I...>)
    {
      return {static_cast<kumi::element_t<I, T>>(get<I>(KUMI_FWD(u)))...};
    }
    template<typename T, typename U, std::size_t... I> constexpr void assign(T&& t, U&& u, std::index_sequence<I...>)
    {
      ((get<I>(KUMI_FWD(t)) = get<I>(KUMI_FWD(u))), ...);
    }
    template<typename T, typename U, std::size_t... I>
    constexpr auto compare(T&& t, U&& u, std::index_sequence<I...>) noexcept
    {
      return ((get<I>(KUMI_FWD(t)) == get<I>(KUMI_FWD(u))) && ...);
    }
    template<typename T, typename U, std::size_t... I>
    constexpr auto lexicographic_compare(T const& t, U const& u, std::index_sequence<I...>) noexcept
    {
      using result_t = decltype((... || (get<I>(t) < get<I>(u))));
      result_t less{false};
      result_t equal{true};
      ((less = less || (equal && (get<I>(t) < get<I>(u))), equal = equal && !less && !(get<I>(u) < get<I>(t))), ...);
      return less;
    }
    template<typename Os, typename T, std::size_t... I>
    constexpr Os& print(
      Os& os, T&& t, char start, [[maybe_unused]] char separator, char stop, std::index_sequence<I...>)
    {
      os << start << ' ';
      ((os << kumi::_::make_streamable(get<I>(KUMI_FWD(t))) << separator << ' '), ...);
      os << kumi::_::make_streamable(get<sizeof...(I)>(KUMI_FWD(t))) << ' ' << stop;
      return os;
    }
  }
}
namespace kumi
{
  template<typename... Ts> struct tuple
  {
    using binder_t = kumi::_::make_binder_t<std::index_sequence_for<Ts...>, Ts...>;
    static constexpr bool is_homogeneous = binder_t::is_homogeneous;
    binder_t impl;
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] kumi::index_t<I> i) & noexcept
    requires(I < sizeof...(Ts))
    {
      return impl(std::integral_constant<std::size_t, I>{});
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::index_t<I>) && noexcept
    requires(I < sizeof...(Ts))
    {
      return static_cast<binder_t&&>(impl)(std::integral_constant<std::size_t, I>{});
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::index_t<I>) const&& noexcept
    requires(I < sizeof...(Ts))
    {
      return static_cast<binder_t const&&>(impl)(std::integral_constant<std::size_t, I>{});
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::index_t<I>) const& noexcept
    requires(I < sizeof...(Ts))
    {
      return impl(std::integral_constant<std::size_t, I>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] kumi::as<T> type) & noexcept
    requires(kumi::concepts::uniquely_typed<Ts...> && kumi::concepts::contains_type<T, Ts...>)
    {
      return impl(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::as<T>) && noexcept
    requires(kumi::concepts::uniquely_typed<Ts...> && kumi::concepts::contains_type<T, Ts...>)
    {
      return static_cast<binder_t&&>(impl)(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::as<T>) const&& noexcept
    requires(kumi::concepts::uniquely_typed<Ts...> && kumi::concepts::contains_type<T, Ts...>)
    {
      return static_cast<binder_t const&&>(impl)(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::as<T>) const& noexcept
    requires(kumi::concepts::uniquely_typed<Ts...> && kumi::concepts::contains_type<T, Ts...>)
    {
      return impl(std::type_identity<T>{});
    }
    template<kumi::str L>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] kumi::label_t<L> s) & noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<L>, Ts...>)
    {
      return impl(std::integral_constant<kumi::str<L.size()>, L>{});
    }
    template<kumi::str L>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<L>) && noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<L>, Ts...>)
    {
      return static_cast<binder_t&&>(impl)(std::integral_constant<kumi::str<L.size()>, L>{});
    }
    template<kumi::str L>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<L>) const&& noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<L>, Ts...>)
    {
      return static_cast<binder_t const&&>(impl)(std::integral_constant<kumi::str<L.size()>, L>{});
    }
    template<kumi::str L>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<L>) const& noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<L>, Ts...>)
    {
      return impl(std::integral_constant<kumi::str<L.size()>, L>{});
    }
    template<kumi::concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) & noexcept
    requires(kumi::concepts::uniquely_named<Ts...> && kumi::concepts::contains_identifier<Id, Ts...>)
    {
      return impl(kumi::_::tag_of_t<Id>{});
    }
    template<kumi::concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) && noexcept
    requires(kumi::concepts::uniquely_named<Ts...> && kumi::concepts::contains_identifier<Id, Ts...>)
    {
      return static_cast<binder_t&&>(impl)(kumi::_::tag_of_t<Id>{});
    }
    template<kumi::concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) const&& noexcept
    requires(kumi::concepts::uniquely_named<Ts...> && kumi::concepts::contains_identifier<Id, Ts...>)
    {
      return static_cast<binder_t const&&>(impl)(kumi::_::tag_of_t<Id>{});
    }
    template<kumi::concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) const& noexcept
    requires(kumi::concepts::uniquely_named<Ts...> && kumi::concepts::contains_identifier<Id, Ts...>)
    {
      return impl(kumi::_::tag_of_t<Id>{});
    }
    [[nodiscard]] KUMI_ABI static constexpr auto size() noexcept { return sizeof...(Ts); }
    [[nodiscard]] KUMI_ABI static constexpr bool empty() noexcept { return sizeof...(Ts) == 0; }
    [[nodiscard]] KUMI_ABI static constexpr auto identifiers() noexcept
    {
      return kumi::tuple{kumi::identifier_of<Ts>()...};
    }
    [[nodiscard]] KUMI_ABI static constexpr auto labels() noexcept { return kumi::tuple{kumi::label_of<Ts>()...}; }
    template<typename... Us>
    KUMI_ABI
#ifndef KUMI_DOXYGEN_INVOKED
      explicit(!kumi::_::piecewise_convertible<tuple<Ts const&...>, tuple<Us...>>)
#endif
        constexpr operator tuple<Us...>() const
    requires(sizeof...(Us) == sizeof...(Ts)) && (!std::same_as<tuple<Ts...>, tuple<Us...>>)
#ifndef KUMI_DOXYGEN_INVOKED
            && (kumi::_::piecewise_constructible<tuple<Ts const&...>, tuple<Us...>>)
#endif
    {
      return kumi::_::static_cast_<tuple<Us...>>(*this, std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    KUMI_ABI
#ifndef KUMI_DOXYGEN_INVOKED
      explicit(!kumi::_::piecewise_convertible<tuple<Ts&...>, tuple<Us...>>)
#endif
        constexpr operator tuple<Us...>()
    requires(sizeof...(Us) == sizeof...(Ts)) && (!std::same_as<tuple<Ts...>, tuple<Us...>>)
#ifndef KUMI_DOXYGEN_INVOKED
            && (kumi::_::piecewise_constructible<tuple<Ts&...>, tuple<Us...>>)
#endif
    {
      return kumi::_::static_cast_<tuple<Us...>>(*this, std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    KUMI_ABI constexpr tuple& operator=(tuple<Us...> const& other)
#ifndef KUMI_DOXYGEN_INVOKED
    requires(kumi::_::piecewise_convertible<tuple, tuple<Us...>>)
#endif
    {
      kumi::_::assign(*this, other, std::make_index_sequence<sizeof...(Ts)>{});
      return *this;
    }
    template<typename... Us>
    KUMI_ABI constexpr tuple& operator=(tuple<Us...>&& other)
#ifndef KUMI_DOXYGEN_INVOKED
    requires(kumi::_::piecewise_convertible<tuple, tuple<Us...>>)
#endif
    {
      kumi::_::assign(*this, other, std::make_index_sequence<sizeof...(Ts)>{});
      return *this;
    }
  };
  template<typename... Ts, typename... Us>
  KUMI_ABI constexpr auto operator==(tuple<Ts...> const& self, tuple<Us...> const& other) noexcept
#ifndef KUMI_DOXYGEN_INVOKED
  requires(sizeof...(Ts) > 0) && (kumi::_::piecewise_comparable<tuple<Ts...>, tuple<Us...>>)
#endif
  {
    return kumi::_::compare(self, other, std::make_index_sequence<sizeof...(Ts)>{});
  }
  template<typename... Ts, typename... Us>
  KUMI_ABI constexpr auto operator!=(tuple<Ts...> const& self, tuple<Us...> const& other) noexcept
#ifndef KUMI_DOXYGEN_INVOKED
  requires(sizeof...(Ts) > 0) && (kumi::_::piecewise_comparable<tuple<Ts...>, tuple<Us...>>)
#endif
  {
    return !(self == other);
  }
  template<typename... Ts, typename... Us>
  KUMI_ABI constexpr auto operator<(tuple<Ts...> const& lhs, tuple<Us...> const& rhs) noexcept
  requires(sizeof...(Ts) > 0 && sizeof...(Ts) == sizeof...(Us))
#ifndef KUMI_DOXYGEN_INVOKED
          && (kumi::_::piecewise_ordered<tuple<Ts...>, tuple<Us...>>)
#endif
  {
    return kumi::_::lexicographic_compare(lhs, rhs, std::make_index_sequence<sizeof...(Ts)>{});
  }
  template<typename... Ts, typename... Us>
  KUMI_ABI constexpr auto operator<=(tuple<Ts...> const& lhs, tuple<Us...> const& rhs) noexcept
  requires requires { rhs < lhs; }
  {
    return !(rhs < lhs);
  }
  template<typename... Ts, typename... Us>
  KUMI_ABI constexpr auto operator>(tuple<Ts...> const& lhs, tuple<Us...> const& rhs) noexcept
  requires requires { rhs < lhs; }
  {
    return rhs < lhs;
  }
  template<typename... Ts, typename... Us>
  KUMI_ABI constexpr auto operator>=(tuple<Ts...> const& lhs, tuple<Us...> const& rhs) noexcept
  requires requires { lhs < rhs; }
  {
    return !(lhs < rhs);
  }
  template<typename CharT, typename Traits, typename... Ts>
  requires(sizeof...(Ts) > 0)
  std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, tuple<Ts...> const& t) noexcept
  {
    return kumi::_::print(os, t, '(', ',', ')', std::make_index_sequence<sizeof...(Ts) - 1>{});
  }
  template<> struct tuple<>
  {
    static constexpr bool is_homogeneous = false;
    [[nodiscard]] KUMI_ABI static constexpr auto size() noexcept { return std::size_t{0}; }
    [[nodiscard]] KUMI_ABI static constexpr auto empty() noexcept { return true; }
    [[nodiscard]] KUMI_ABI static constexpr auto names() noexcept { return kumi::tuple{}; }
    KUMI_ABI friend constexpr auto operator<=>(tuple<>, tuple<>) noexcept = default;
    template<typename T>
    [[nodiscard]] KUMI_ABI constexpr operator T() const noexcept
    requires(kumi::concepts::unit_type<T>)
    {
      return {};
    }
    template<typename T>
    [[nodiscard]] KUMI_ABI constexpr operator T() noexcept
    requires(kumi::concepts::unit_type<T>)
    {
      return {};
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, tuple<>) noexcept
    {
      return os << "()";
    }
  };
  template<typename... Ts> tuple(Ts&&...) -> tuple<std::unwrap_ref_decay_t<Ts>...>;
  struct tie_t
  {
    template<typename... Ts> [[nodiscard]] KUMI_ABI constexpr kumi::tuple<Ts&...> operator()(Ts&... ts) const
    {
      return {ts...};
    }
  };
  KUMI_VARIABLE_ABI constexpr tie_t tie{};
  struct forward_as_tuple_t
  {
    template<typename... Ts> [[nodiscard]] KUMI_ABI constexpr auto operator()(Ts&&... ts) const -> kumi::tuple<Ts&&...>
    {
      return {KUMI_FWD(ts)...};
    }
  };
  KUMI_VARIABLE_ABI constexpr forward_as_tuple_t forward_as_tuple{};
  struct make_tuple_t
  {
    template<typename... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Ts&&... ts) const -> kumi::tuple<std::unwrap_ref_decay_t<Ts>...>
    {
      return {KUMI_FWD(ts)...};
    }
  };
  KUMI_VARIABLE_ABI constexpr make_tuple_t make_tuple{};
  namespace _
  {
    template<kumi::concepts::product_type T, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto to_ref_(kumi::_::adl_tag_t, T&& t, std::index_sequence<I...>)
      -> kumi::tuple<kumi::member_t<I, T>&&...>
    {
      return {get<I>(KUMI_FWD(t))...};
    }
  }
  struct to_ref_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      return to_ref_(kumi::_::adl_tag, KUMI_FWD(t), std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr to_ref_t to_ref{};
  template<typename Type> struct from_tuple_t
  {
  private:
    template<typename T, std::size_t... I> KUMI_HIDDEN_ABI constexpr Type impl(T&& t, std::index_sequence<I...>) const
    {
      return {get<I>(KUMI_FWD(t))...};
    }
  public:
    template<typename... Ts>
    [[nodiscard]] KUMI_ABI constexpr Type operator()(tuple<Ts...> const& t) const
    requires(!kumi::concepts::product_type<Type> && kumi::_::implicit_constructible<Type, Ts...>)
    {
      return impl(t, std::make_index_sequence<sizeof...(Ts)>{});
    }
  };
  template<typename Type> KUMI_VARIABLE_ABI constexpr from_tuple_t<Type> from_tuple{};
  struct to_tuple_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return kumi::tuple{};
      else
        return [&]<std::size_t... I>(std::index_sequence<I...>) {
          return kumi::tuple{get<I>(KUMI_FWD(t))...};
        }(std::make_index_sequence<kumi::size_v<T>>{});
    }
    template<kumi::concepts::static_container S>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(S&& s) const
    requires(!kumi::concepts::product_type<S>)
    {
      constexpr std::size_t N = kumi::container_size_v<S>;
      if constexpr (N == 0) return kumi::tuple{};
      else
        return [&]<std::size_t... I>(std::index_sequence<I...>) {
          return kumi::tuple{KUMI_FWD(s)[I]...};
        }(std::make_index_sequence<N>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr to_tuple_t to_tuple{};
  namespace _
  {
    template<typename T, typename IndexSequence, template<typename...> class Meta = std::type_identity> struct as_tuple;
    template<typename T, std::size_t... I> struct as_tuple<T, std::index_sequence<I...>>
    {
      using type = kumi::tuple<kumi::element_t<I, T>...>;
    };
    template<typename T, std::size_t... I, template<typename...> class Meta>
    struct as_tuple<T, std::index_sequence<I...>, Meta>
    {
      using type = tuple<typename Meta<kumi::element_t<I, T>>::type...>;
    };
  }
  template<typename T, template<typename...> class Meta = std::type_identity> struct as_tuple;
  template<typename T, template<typename...> class Meta>
  requires(kumi::concepts::product_type<T>)
  struct as_tuple<T, Meta> : kumi::_::as_tuple<T, std::make_index_sequence<kumi::size_v<T>>, Meta>
  {
  };
  template<typename T, template<typename...> class Meta>
  requires(!kumi::concepts::product_type<T>)
  struct as_tuple<T, Meta>
  {
    using type = kumi::tuple<typename Meta<T>::type>;
  };
  template<typename T, template<typename...> class Meta = std::type_identity>
  using as_tuple_t = typename kumi::as_tuple<T, Meta>::type;
  struct members_of_t
  {
  private:
    template<typename T, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto impl(as<T>, std::index_sequence<I...>) const noexcept
    {
      if constexpr (sizeof...(I) == 0) return kumi::tuple{};
      else return kumi::tuple{kumi::identifier_of<kumi::element_t<I, T>>()...};
    }
  public:
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(as<T> type) const noexcept
    {
      return impl(type, std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr members_of_t members_of{};
  struct values_of_t
  {
    template<typename T, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto impl(T&& t, std::index_sequence<I...>) const noexcept
    {
      if constexpr (sizeof...(I) == 0) return kumi::tuple{};
      else
        return kumi::tuple<kumi::result::field_value_of_t<kumi::member_t<I, T>>...>{
          kumi::field_value_of(get<I>(KUMI_FWD(t)))...};
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      return impl(KUMI_FWD(t), std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr values_of_t values_of{};
  namespace result
  {
    template<kumi::concepts::product_type T> using members_of_t = decltype(kumi::members_of(as<T>{}));
    template<kumi::concepts::product_type T> struct members_of
    {
      using type = kumi::result::members_of_t<T>;
    };
    template<kumi::concepts::product_type T> using values_of_t = decltype(kumi::values_of(std::declval<T>()));
    template<kumi::concepts::product_type T> struct values_of
    {
      using type = kumi::result::values_of_t<T>;
    };
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  requires(I < sizeof...(Ts))
  {
    return t[kumi::index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& arg) noexcept
  requires(I < sizeof...(Ts))
  {
    return static_cast<tuple<Ts...>&&>(arg)[kumi::index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& arg) noexcept
  requires(I < sizeof...(Ts))
  {
    return arg[kumi::index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& arg) noexcept
  requires(I < sizeof...(Ts))
  {
    return static_cast<tuple<Ts...> const&&>(arg)[kumi::index<I>];
  }
  template<kumi::str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  requires(kumi::concepts::uniquely_named<Ts...> && kumi::_::contains_label<L, Ts...>())
  {
    return t[kumi::label<L>];
  }
  template<kumi::str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& t) noexcept
  requires(kumi::concepts::uniquely_named<Ts...> && kumi::_::contains_label<L, Ts...>())
  {
    return static_cast<tuple<Ts...>&&>(t)[kumi::label<L>];
  }
  template<kumi::str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& t) noexcept
  requires(kumi::concepts::uniquely_named<Ts...> && kumi::_::contains_label<L, Ts...>())
  {
    return t[kumi::label<L>];
  }
  template<kumi::str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& t) noexcept
  requires(kumi::concepts::uniquely_named<Ts...> && kumi::_::contains_label<L, Ts...>())
  {
    return static_cast<tuple<Ts...> const&&>(t)[kumi::label<L>];
  }
  template<kumi::concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  requires(kumi::concepts::uniquely_named<Ts...> && kumi::concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return t[Id];
  }
  template<kumi::concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& t) noexcept
  requires(kumi::concepts::uniquely_named<Ts...> && kumi::concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return static_cast<tuple<Ts...>&&>(t)[Id];
  }
  template<kumi::concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& t) noexcept
  requires(kumi::concepts::uniquely_named<Ts...> && kumi::concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return t[Id];
  }
  template<kumi::concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& t) noexcept
  requires(kumi::concepts::uniquely_named<Ts...> && kumi::concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return static_cast<tuple<Ts...> const&&>(t)[Id];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  requires(kumi::concepts::uniquely_typed<Ts...> && kumi::concepts::contains_type<T, Ts...>)
  {
    return t[kumi::as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& t) noexcept
  requires(kumi::concepts::uniquely_typed<Ts...> && kumi::concepts::contains_type<T, Ts...>)
  {
    return static_cast<tuple<Ts...>&&>(t)[kumi::as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& t) noexcept
  requires(kumi::concepts::uniquely_typed<Ts...> && kumi::concepts::contains_type<T, Ts...>)
  {
    return t[kumi::as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& t) noexcept
  requires(kumi::concepts::uniquely_typed<Ts...> && kumi::concepts::contains_type<T, Ts...>)
  {
    return static_cast<tuple<Ts...> const&&>(t)[kumi::as<T>{}];
  }
#ifndef KUMI_DOXYGEN_INVOKED
  template<std::size_t I, typename T>
  requires(kumi::is_kumi_tuple_v<std::remove_cvref_t<T>> && (I >= kumi::size_v<T>))
  constexpr auto get(T&& r) = delete;
  template<str S, typename T>
  requires(kumi::is_kumi_tuple_v<std::remove_cvref_t<T>> && !kumi::_::contains_identifier<S, T>())
  constexpr auto get(T&& t) = delete;
  template<kumi::concepts::identifier auto S, typename T>
  requires(kumi::is_kumi_tuple_v<std::remove_cvref_t<T>> && !kumi::concepts::contains_identifier<decltype(S), T>)
  constexpr auto get(T&& t) = delete;
  template<typename U, typename T>
  requires(kumi::is_kumi_tuple_v<std::remove_cvref_t<T>> && !kumi::concepts::contains_type<U, T>)
  constexpr auto get(T&& t) = delete;
#endif
  template<kumi::concepts::product_type T> struct builder<T>
  {
    using type = T;
    template<typename... Us> using to = kumi::tuple<Us...>;
    template<typename... Args> [[nodiscard]] KUMI_ABI static constexpr auto make(Args&&... args)
    {
      return kumi::make_tuple(KUMI_FWD(args)...);
    }
    template<typename... Args> [[nodiscard]] KUMI_ABI static constexpr auto build(Args&&... args)
    {
      return kumi::tuple{KUMI_FWD(args)...};
    }
  };
  template<kumi::concepts::product_type... Ts> struct common_product_type<Ts...>
  {
    using type = kumi::tuple<>;
  };
}
namespace kumi
{
  template<typename... Ts> struct record
  {
    using is_record_type = void;
    using set_t = kumi::_::make_set_t<Ts...>;
    static constexpr bool is_homogeneous = false;
    set_t impl;
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] kumi::index_t<I> i) & noexcept
    requires(I < sizeof...(Ts))
    {
      using T = kumi::element_t<I, tuple<Ts...>>;
      return static_cast<T&>(impl);
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::index_t<I>) && noexcept
    requires(I < sizeof...(Ts))
    {
      using T = kumi::element_t<I, tuple<Ts...>>;
      return static_cast<T&&>(static_cast<set_t&&>(impl));
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::index_t<I>) const&& noexcept
    requires(I < sizeof...(Ts))
    {
      using T = kumi::element_t<I, tuple<Ts...>>;
      return static_cast<T const&&>(static_cast<set_t const&&>(impl));
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::index_t<I>) const& noexcept
    requires(I < sizeof...(Ts))
    {
      using T = kumi::element_t<I, tuple<Ts...>>;
      return static_cast<T const&>(impl);
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] kumi::as<T> type) & noexcept
    requires(kumi::concepts::uniquely_typed<kumi::_::type_of_t<Ts>...> &&
             kumi::concepts::contains_type<T, kumi::_::type_of_t<Ts>...>)
    {
      return impl(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::as<T>) && noexcept
    requires(kumi::concepts::uniquely_typed<kumi::_::type_of_t<Ts>...> &&
             kumi::concepts::contains_type<T, kumi::_::type_of_t<Ts>...>)
    {
      return static_cast<set_t&&>(impl)(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::as<T>) const&& noexcept
    requires(kumi::concepts::uniquely_typed<kumi::_::type_of_t<Ts>...> &&
             kumi::concepts::contains_type<T, kumi::_::type_of_t<Ts>...>)
    {
      return static_cast<set_t const&&>(impl)(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::as<T>) const& noexcept
    requires(kumi::concepts::uniquely_typed<kumi::_::type_of_t<Ts>...> &&
             kumi::concepts::contains_type<T, kumi::_::type_of_t<Ts>...>)
    {
      return impl(std::type_identity<T>{});
    }
    template<kumi::str Name>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] kumi::label_t<Name> l) & noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<Name>, Ts...>)
    {
      return impl(std::integral_constant<kumi::str<Name.size()>, Name>{});
    }
    template<kumi::str Name>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<Name>) && noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<Name>, Ts...>)
    {
      return static_cast<set_t&&>(impl)(std::integral_constant<kumi::str<Name.size()>, Name>{});
    }
    template<kumi::str Name>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<Name>) const&& noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<Name>, Ts...>)
    {
      return static_cast<set_t const&&>(impl)(std::integral_constant<kumi::str<Name.size()>, Name>{});
    }
    template<kumi::str Name>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<Name>) const& noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<Name>, Ts...>)
    {
      return impl(std::integral_constant<kumi::str<Name.size()>, Name>{});
    }
    template<kumi::concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) & noexcept
    requires(kumi::concepts::contains_identifier<Id, Ts...>)
    {
      return impl(kumi::_::tag_of_t<Id>{});
    }
    template<kumi::concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) && noexcept
    requires(kumi::concepts::contains_identifier<Id, Ts...>)
    {
      return static_cast<set_t&&>(impl)(kumi::_::tag_of_t<Id>{});
    }
    template<kumi::concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) const&& noexcept
    requires(kumi::concepts::contains_identifier<Id, Ts...>)
    {
      return static_cast<set_t const&&>(impl)(kumi::_::tag_of_t<Id>{});
    }
    template<kumi::concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) const& noexcept
    requires(kumi::concepts::contains_identifier<Id, Ts...>)
    {
      return impl(kumi::_::tag_of_t<Id>{});
    }
    [[nodiscard]] KUMI_ABI static constexpr auto size() noexcept { return sizeof...(Ts); }
    [[nodiscard]] KUMI_ABI static constexpr bool empty() noexcept { return sizeof...(Ts) == 0; }
    [[nodiscard]] KUMI_ABI static constexpr auto identifiers() noexcept { return tuple{kumi::identifier_of<Ts>()...}; }
    [[nodiscard]] KUMI_ABI static constexpr auto labels() noexcept { return tuple{kumi::label_of<Ts>()...}; }
    [[nodiscard]] KUMI_ABI constexpr auto values() noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<stored_member_t<I, record&>...>{kumi::field_value_of(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    [[nodiscard]] KUMI_ABI constexpr auto values() const noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<stored_member_t<I, record const&>...>{kumi::field_value_of(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    KUMI_ABI constexpr record& operator=(record<Us...> const& other)
    requires(kumi::concepts::equivalent<record, record<Us...>>)
#ifndef KUMI_DOXYGEN_INVOKED
            && (kumi::_::fieldwise_convertible<record, record<Us...>>)
#endif
    {
      ((get<kumi::identifier_of<Ts>()>(*this) = get<kumi::identifier_of<Ts>()>(KUMI_FWD(other))), ...);
      return *this;
    }
    template<typename... Us>
    KUMI_ABI constexpr record& operator=(record<Us...>&& other)
    requires(kumi::concepts::equivalent<record, record<Us...>>)
#ifndef KUMI_DOXYGEN_INVOKED
            && (kumi::_::fieldwise_convertible<record, record<Us...>>)
#endif
    {
      ((get<kumi::identifier_of<Ts>()>(*this) = get<kumi::identifier_of<Ts>()>(KUMI_FWD(other))), ...);
      return *this;
    }
  };
  template<typename... Ts, typename... Us>
  KUMI_ABI constexpr auto operator==(record<Ts...> const& self, record<Us...> const& other) noexcept
#ifndef KUMI_DOXYGEN_INVOKED
  requires(kumi::_::fieldwise_comparable<record<Ts...>, record<Us...>>)
#endif
  {
    return ((get<kumi::identifier_of<Ts>()>(self) == get<kumi::identifier_of<Ts>()>(other)) && ...);
  }
  template<typename... Ts, typename... Us>
  KUMI_ABI constexpr auto operator!=(record<Ts...> const& self, record<Us...> const& other) noexcept
#ifndef KUMI_DOXYGEN_INVOKED
  requires(kumi::_::fieldwise_comparable<record<Ts...>, record<Us...>>)
#endif
  {
    return !(self == other);
  }
  template<typename CharT, typename Traits, typename... Ts>
  std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, record<Ts...> const& t) noexcept
  {
    return kumi::_::print(os, t, '{', ',', '}', std::make_index_sequence<sizeof...(Ts) - 1>{});
  }
  template<> struct record<>
  {
    using is_record_type = void;
    static constexpr bool is_homogeneous = false;
    [[nodiscard]] KUMI_ABI static constexpr auto size() noexcept { return std::size_t{0}; }
    [[nodiscard]] KUMI_ABI static constexpr auto empty() noexcept { return true; }
    [[nodiscard]] KUMI_ABI static constexpr auto names() noexcept { return kumi::tuple{}; }
    [[nodiscard]] KUMI_ABI static constexpr auto values() noexcept { return kumi::tuple{}; }
    KUMI_ABI friend constexpr auto operator<=>(record<>, record<>) noexcept = default;
    template<typename T>
    [[nodiscard]] KUMI_ABI constexpr operator T() const noexcept
    requires(kumi::concepts::unit_type<T>)
    {
      return {};
    }
    template<typename T>
    [[nodiscard]] KUMI_ABI constexpr operator T() noexcept
    requires(kumi::concepts::unit_type<T>)
    {
      return {};
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, record<>) noexcept
    {
      return os << "{}";
    }
  };
  template<typename... Ts>
  requires(!kumi::concepts::uniquely_named<Ts...> || !kumi::concepts::fully_named<Ts...> ||
           !kumi::concepts::uniquely_labeled<Ts...>)
  struct record<Ts...>
  {
    static_assert(kumi::concepts::uniquely_named<Ts...>, "Duplicate fields in record definition");
    static_assert(kumi::concepts::uniquely_labeled<Ts...>, "Duplicate identifier representation in record definition");
    static_assert(kumi::concepts::fully_named<Ts...>, "Anonymous field usage in record definition");
    record(Ts&&...) = delete;
  };
  template<typename... Ts> record(Ts&&...) -> record<std::unwrap_ref_decay_t<Ts>...>;
  template<kumi::concepts::identifier auto... Fields> struct tie_as_record_t
  {
    template<typename... Ts> [[nodiscard]] KUMI_ABI constexpr auto operator()(Ts&... ts) const
    {
      return kumi::record<kumi::field<decltype(Fields), Ts&>...>{ts...};
    }
  };
  template<kumi::concepts::identifier auto... Fields>
  KUMI_VARIABLE_ABI constexpr tie_as_record_t<Fields...> tie_as_record{};
  template<kumi::concepts::identifier auto... Fields> struct forward_as_record_t
  {
    template<typename... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Ts&&... ts) const
    requires(sizeof...(Fields) == sizeof...(Ts))
    {
      return kumi::record<kumi::field<decltype(Fields), Ts&&>...>{KUMI_FWD(ts)...};
    }
  };
  template<kumi::concepts::identifier auto... Fields>
  KUMI_VARIABLE_ABI constexpr forward_as_record_t<Fields...> forward_as_record{};
  struct make_record_t
  {
    template<typename... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Ts&&... ts) const -> kumi::record<std::unwrap_ref_decay_t<Ts>...>
    requires(kumi::concepts::uniquely_named<Ts...> && kumi::concepts::fully_named<Ts...>)
    {
      return {KUMI_FWD(ts)...};
    }
  };
  KUMI_VARIABLE_ABI constexpr make_record_t make_record{};
  namespace _
  {
    template<kumi::concepts::record_type T, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto to_ref_(kumi::_::adl_tag_t, T&& t, std::index_sequence<I...>) -> kumi::record<
      kumi::field<decltype(kumi::identifier_of<kumi::element_t<I, T>>()), kumi::stored_member_t<I, T>&&>...>
    {
      return {kumi::field_value_of(get<I>(KUMI_FWD(t)))...};
    }
  }
  template<kumi::concepts::record_type Type> struct from_record_t
  {
  private:
    template<typename... Ts, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr Type impl(record<Ts...> const& r, std::index_sequence<I...>) const
    {
      return Type{get<kumi::identifier_of<kumi::element_t<I, Type>>()>(r)...};
    }
  public:
    template<typename... Ts>
    [[nodiscard]] KUMI_ABI constexpr Type operator()(record<Ts...> const& r) const
    requires(
      kumi::concepts::equivalent<typename kumi::_::as_tuple<Type, std::make_index_sequence<kumi::size_v<Type>>>::type,
                                 kumi::tuple<Ts...>>)
    {
      return impl(r, std::make_index_sequence<sizeof...(Ts)>{});
    }
  };
  template<kumi::concepts::record_type Type> KUMI_VARIABLE_ABI constexpr from_record_t<Type> from_record{};
  struct to_record_t
  {
  private:
    template<typename R, std::size_t... I> KUMI_HIDDEN_ABI constexpr auto impl(R&& r, std::index_sequence<I...>) const
    {
      if constexpr (sizeof...(I) == 0) return kumi::record{};
      else
        return kumi::record{kumi::capture_field<kumi::identifier_of<kumi::element_t<I, R>>()>(
          get<kumi::identifier_of<kumi::element_t<I, R>>()>(KUMI_FWD(r)))...};
    }
  public:
    template<kumi::concepts::record_type Type> [[nodiscard]] KUMI_ABI constexpr auto operator()(Type&& r) const
    {
      return impl(KUMI_FWD(r), std::make_index_sequence<kumi::size_v<Type>>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr to_record_t to_record{};
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>& r) noexcept
  requires(I < sizeof...(Ts))
  {
    return r[kumi::index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>&& r) noexcept
  requires(I < sizeof...(Ts))
  {
    return static_cast<record<Ts...>&&>(r)[kumi::index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const& r) noexcept
  requires(I < sizeof...(Ts))
  {
    return r[kumi::index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const&& r) noexcept
  requires(I < sizeof...(Ts))
  {
    return static_cast<record<Ts...> const&&>(r)[kumi::index<I>];
  }
  template<kumi::str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>& r) noexcept
  requires(kumi::_::contains_label<L, Ts...>())
  {
    return r[kumi::label<L>];
  }
  template<kumi::str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>&& r) noexcept
  requires(kumi::_::contains_label<L, Ts...>())
  {
    return static_cast<record<Ts...>&&>(r)[kumi::label<L>];
  }
  template<kumi::str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const& r) noexcept
  requires(kumi::_::contains_label<L, Ts...>())
  {
    return r[kumi::label<L>];
  }
  template<kumi::str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const&& r) noexcept
  requires(kumi::_::contains_label<L, Ts...>())
  {
    return static_cast<record<Ts...> const&&>(r)[kumi::label<L>];
  }
  template<kumi::concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>& r) noexcept
  requires(kumi::concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return r[Id];
  }
  template<kumi::concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>&& r) noexcept
  requires(kumi::concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return static_cast<record<Ts...>&&>(r)[Id];
  }
  template<kumi::concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const& r) noexcept
  requires(kumi::concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return r[Id];
  }
  template<kumi::concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const&& r) noexcept
  requires(kumi::concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return static_cast<record<Ts...> const&&>(r)[Id];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>& r) noexcept
  requires(kumi::concepts::uniquely_typed<kumi::_::type_of_t<Ts>...> &&
           kumi::concepts::contains_type<T, kumi::_::type_of_t<Ts>...>)
  {
    return r[kumi::as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>&& r) noexcept
  requires(kumi::concepts::uniquely_typed<kumi::_::type_of_t<Ts>...> &&
           kumi::concepts::contains_type<T, kumi::_::type_of_t<Ts>...>)
  {
    return static_cast<record<Ts...>&&>(r)[kumi::as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const& r) noexcept
  requires(kumi::concepts::uniquely_typed<kumi::_::type_of_t<Ts>...> &&
           kumi::concepts::contains_type<T, kumi::_::type_of_t<Ts>...>)
  {
    return r[kumi::as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const&& r) noexcept
  requires(kumi::concepts::uniquely_typed<kumi::_::type_of_t<Ts>...> &&
           kumi::concepts::contains_type<T, kumi::_::type_of_t<Ts>...>)
  {
    return static_cast<record<Ts...> const&&>(r)[kumi::as<T>{}];
  }
#ifndef KUMI_DOXYGEN_INVOKED
  template<std::size_t I, typename R>
  requires(kumi::is_kumi_record_v<std::remove_cvref_t<R>> && ((I >= kumi::size_v<R>) || (I < 0)))
  constexpr auto get(R&& r) = delete;
  template<kumi::str S, typename R>
  requires(kumi::is_kumi_record_v<std::remove_cvref_t<R>> && !kumi::_::contains_identifier<S, R>())
  constexpr auto get(R&& r) = delete;
  template<kumi::concepts::identifier auto S, typename R>
  requires(kumi::is_kumi_record_v<std::remove_cvref_t<R>> && !kumi::concepts::contains_identifier<decltype(S), R>)
  constexpr auto get(R&& r) = delete;
  template<typename U, typename R>
  requires(kumi::is_kumi_record_v<std::remove_cvref_t<R>> && !kumi::concepts::contains_type<U, R>)
  constexpr auto get(R&& r) = delete;
#endif
  template<kumi::concepts::record_type R> struct builder<R>
  {
    using type = R;
    template<typename... Us> using to = kumi::record<Us...>;
    template<typename... Args> [[nodiscard]] KUMI_ABI static constexpr auto make(Args&&... args)
    {
      return kumi::make_record(KUMI_FWD(args)...);
    }
    template<typename... Args> [[nodiscard]] KUMI_ABI static constexpr auto build(Args&&... args)
    {
      return kumi::record{KUMI_FWD(args)...};
    }
  };
  template<kumi::concepts::record_type... Ts> struct common_product_type<Ts...>
  {
    using type = kumi::record<>;
  };
}
namespace kumi
{
}
namespace kumi
{
  namespace _
  {
    template<typename T>
    inline constexpr bool is_reference_wrapper_v =
      !std::is_same_v<std::decay_t<typename std::unwrap_reference<T&&>::type>,
                      typename std::unwrap_ref_decay<T&&>::type>;
    template<typename T> KUMI_HIDDEN_ABI constexpr decltype(auto) unwrap_memptr(T&& obj)
    {
      if constexpr (kumi::_::is_reference_wrapper_v<std::remove_cvref_t<T>>) return KUMI_FWD(obj).get();
      else if constexpr (std::is_pointer_v<std::remove_cvref_t<T>>) return *KUMI_FWD(obj);
      else return KUMI_FWD(obj);
    }
    template<typename C, typename P, typename O, typename... Ts>
    KUMI_HIDDEN_ABI constexpr decltype(auto) invoke_memptr(P C::* member, O&& o, Ts&&... ts)
    {
      using callable_t = P C::*;
      if constexpr (std::is_member_object_pointer_v<callable_t>) return unwrap_memptr(KUMI_FWD(o)).*member;
      else return (unwrap_memptr(KUMI_FWD(o)).*member)(KUMI_FWD(ts)...);
    }
  }
  template<typename C, typename... Ts> KUMI_ABI constexpr decltype(auto) invoke(C&& c, Ts&&... ts)
  {
    if constexpr (std::is_member_pointer_v<std::decay_t<C>>) return kumi::_::invoke_memptr(c, KUMI_FWD(ts)...);
    else return KUMI_FWD(c)(KUMI_FWD(ts)...);
  }
  template<typename R, typename C, typename... Ts>
  KUMI_ABI constexpr R invoke_r(C&& c, Ts&&... ts) noexcept(std::is_nothrow_invocable_r_v<R, C, Ts...>)
  requires(std::is_invocable_r_v<R, C, Ts...>)
  {
    if constexpr (std::is_void_v<R>) kumi::invoke(KUMI_FWD(c), KUMI_FWD(ts)...);
    else return kumi::invoke(KUMI_FWD(c), KUMI_FWD(ts)...);
  }
}
namespace kumi
{
  namespace _
  {
    enum class Binding
    {
      front,
      back
    };
    template<Binding D, typename F, typename... Bound>
    struct bind_t : leaf<static_cast<std::size_t>(-1), F>,
                    make_binder_t<std::make_index_sequence<sizeof...(Bound)>, Bound...>
    {
      static constexpr auto function_index = static_cast<std::size_t>(-1);
      static constexpr auto seq = std::make_index_sequence<sizeof...(Bound)>{};
      using binder_t = make_binder_t<std::make_index_sequence<sizeof...(Bound)>, Bound...>;
      using func_t = leaf<function_index, F>;
      template<typename... Args> KUMI_HIDDEN_ABI constexpr decltype(auto) operator()(Args&&... args) &
      {
        return impl(seq, *this, KUMI_FWD(args)...);
      }
      template<typename... Args> KUMI_HIDDEN_ABI constexpr decltype(auto) operator()(Args&&... args) const&
      {
        return impl(seq, *this, KUMI_FWD(args)...);
      }
      template<typename... Args> KUMI_HIDDEN_ABI constexpr decltype(auto) operator()(Args&&... args) &&
      {
        return impl(seq, std::move(*this), KUMI_FWD(args)...);
      }
      template<typename... Args> KUMI_HIDDEN_ABI constexpr decltype(auto) operator()(Args&&... args) const&&
      {
        return impl(seq, std::move(*this), KUMI_FWD(args)...);
      }
      template<std::size_t... Is, typename Self, typename... Args>
      KUMI_HIDDEN_ABI static constexpr decltype(auto) impl(std::index_sequence<Is...>, Self&& s, Args&&... args)
      {
        if constexpr (D == Binding::front)
        {
          return kumi::invoke(KUMI_FWD(s).func_t::operator()(std::integral_constant<size_t, function_index>{}),
                              KUMI_FWD(s).binder_t::operator()(std::integral_constant<std::size_t, Is>{})...,
                              KUMI_FWD(args)...);
        }
        else
        {
          return kumi::invoke(KUMI_FWD(s).func_t::operator()(std::integral_constant<size_t, function_index>{}),
                              KUMI_FWD(args)...,
                              KUMI_FWD(s).binder_t::operator()(std::integral_constant<std::size_t, Is>{})...);
        }
      }
    };
  }
  template<typename C, typename... Ts>
  KUMI_ABI constexpr auto bind_front(C&& c, Ts&&... ts)
    noexcept(std::is_nothrow_move_constructible_v<std::decay_t<C>> &&
             (std::is_nothrow_move_constructible_v<std::decay_t<Ts>> && ...))
  requires(std::is_move_constructible_v<std::decay_t<C>> && (std::is_move_constructible_v<std::decay_t<Ts>> && ...))
  {
    return kumi::_::bind_t<kumi::_::Binding::front, std::decay_t<C>, std::decay_t<Ts>...>{KUMI_FWD(c), KUMI_FWD(ts)...};
  }
  template<typename C, typename... Ts>
  KUMI_ABI constexpr auto bind_back(C&& c, Ts&&... ts)
    noexcept(std::is_nothrow_move_constructible_v<std::decay_t<C>> &&
             (std::is_nothrow_move_constructible_v<std::decay_t<Ts>> && ...))
  requires(std::is_move_constructible_v<std::decay_t<C>> && (std::is_move_constructible_v<std::decay_t<Ts>> && ...))
  {
    return kumi::_::bind_t<kumi::_::Binding::back, std::decay_t<C>, std::decay_t<Ts>...>{KUMI_FWD(c), KUMI_FWD(ts)...};
  }
  template<typename C, typename... Ts>
  KUMI_ABI constexpr auto bind(C&& c, Ts&&... ts)
    noexcept(std::is_nothrow_move_constructible_v<std::decay_t<C>> &&
             (std::is_nothrow_move_constructible_v<std::decay_t<Ts>> && ...))
  requires(std::is_move_constructible_v<std::decay_t<C>> && (std::is_move_constructible_v<std::decay_t<Ts>> && ...))
  {
    return kumi::_::bind_t<kumi::_::Binding::front, std::decay_t<C>, std::decay_t<Ts>...>{KUMI_FWD(c), KUMI_FWD(ts)...};
  }
}
namespace kumi::_
{
  template<typename T, typename...> extern T cat_index_sequence;
  template<std::size_t... I, std::size_t... J>
  extern std::index_sequence<I..., J...> cat_index_sequence<std::index_sequence<I...>, std::index_sequence<J...>>;
  template<typename T, typename... Ts> using cat_index_sequence_t = decltype(kumi::_::cat_index_sequence<T, Ts...>);
  template<std::size_t... I, std::size_t... J, typename... Ts>
  extern cat_index_sequence_t<std::index_sequence<I..., J...>, Ts...>
    cat_index_sequence<std::index_sequence<I...>, std::index_sequence<J...>, Ts...>;
  template<std::size_t, typename T> extern T fill_index_sequence;
  template<std::size_t E, std::size_t... I>
  extern std::index_sequence<((void)I, E)...> fill_index_sequence<E, std::index_sequence<I...>>;
  template<std::size_t B, std::size_t S, std::size_t n, typename T> extern T remove_index_sequence;
  template<std::size_t B, std::size_t S, std::size_t n, std::size_t... I>
  extern std::index_sequence<(I + (I < B ? 0 : (1 + (I - B) / (S - 1) < n ? 1 + (I - B) / (S - 1) : n)))...>
    remove_index_sequence<B, S, n, std::index_sequence<I...>>;
  template<std::size_t B, std::size_t n, std::size_t... I>
  extern std::index_sequence<(I < B ? I : I + n)...> remove_index_sequence<B, 1, n, std::index_sequence<I...>>;
  template<typename T> extern T reverse_index_sequence;
  template<std::size_t... I>
  extern std::index_sequence<(sizeof...(I) - 1 - I)...> reverse_index_sequence<std::index_sequence<I...>>;
  template<std::size_t, typename T> extern T rotate_index_sequence;
  template<std::size_t R, std::size_t... I>
  extern std::index_sequence<((I + R) % sizeof...(I))...> rotate_index_sequence<R, std::index_sequence<I...>>;
  template<std::size_t, typename T> extern T shift_index_sequence;
  template<std::size_t O, std::size_t... I>
  extern std::index_sequence<(I + O)...> shift_index_sequence<O, std::index_sequence<I...>>;
  template<std::size_t B, std::size_t S, typename T> extern T slice_index_sequence;
  template<std::size_t B, std::size_t S, std::size_t... I>
  extern std::index_sequence<(B + I * S)...> slice_index_sequence<B, S, std::index_sequence<I...>>;
  template<typename Sizes, typename Elts> extern Sizes strided_index_sequence;
  template<std::size_t... I, std::size_t... J>
  extern std::index_sequence<stride_at(J, std::index_sequence<I...>{}, std::index_sequence<J...>{})...>
    strided_index_sequence<std::index_sequence<I...>, std::index_sequence<J...>>;
}
namespace kumi::function
{
  template<typename Sizes, typename Elts>
  using cartesian_strides = decltype(kumi::_::strided_index_sequence<Sizes, Elts>);
  template<typename... Ts> using cat_index_sequence = decltype(kumi::_::cat_index_sequence<Ts...>);
  template<std::size_t E, std::size_t N>
  using fill_index_sequence = decltype(kumi::_::fill_index_sequence<E, std::make_index_sequence<N>>);
  template<typename T> using indexes_for = std::make_index_sequence<kumi::size_v<T>>;
  template<std::size_t N, std::size_t B, std::size_t E, std::size_t S = 1>
  using remove_index_sequence =
    decltype(kumi::_::remove_index_sequence<B,
                                            S,
                                            ((E > B) ? (E - B + S - 1) / S : 0),
                                            std::make_index_sequence<N - ((E > B) ? (E - B + S - 1) / S : 0)>>);
  template<std::size_t N>
  using reverse_index_sequence = decltype(kumi::_::reverse_index_sequence<std::make_index_sequence<N>>);
  template<std::size_t R, std::size_t N>
  using rotate_index_sequence = decltype(kumi::_::rotate_index_sequence<R, std::make_index_sequence<N>>);
  template<std::size_t O, std::size_t N>
  using shift_index_sequence = decltype(kumi::_::shift_index_sequence<O, std::make_index_sequence<N>>);
  template<std::size_t B, std::size_t E, std::size_t S = 1>
  using slice_index_sequence =
    decltype(kumi::_::slice_index_sequence<B, S, std::make_index_sequence<((E > B) ? ((E - B + S - 1) / S) : 0)>>);
}
namespace kumi
{
  namespace _
  {
    template<typename Seq, typename... Ts> struct multiset;
    template<std::size_t I, typename T> struct multiset<std::index_sequence<I>, T>
    {
      consteval auto operator()(std::type_identity<T>) const noexcept
      {
        return std::integral_constant<std::size_t, I>{};
      }
    };
    template<std::size_t I, std::size_t... Is, typename T, typename... Ts>
    struct multiset<std::index_sequence<I, Is...>, T, Ts...> : kumi::_::multiset<std::index_sequence<Is...>, Ts...>
    {
      consteval auto operator()(std::type_identity<T>) const noexcept
      {
        return std::integral_constant<std::size_t, I>{};
      }
      using kumi::_::multiset<std::index_sequence<Is...>, Ts...>::operator();
    };
    template<typename... Ts> using make_multiset_t = typename kumi::_::multiset<Ts...>;
    template<typename T, bool... Bs> extern T unique_index_sequence;
    template<std::size_t... I, bool... Bs>
    extern std::index_sequence<kumi::_::nth_pos_v<I, Bs...>...> unique_index_sequence<std::index_sequence<I...>, Bs...>;
    template<typename T, bool... Bs> extern T select_index_sequence;
    template<std::size_t... I, bool... Bs>
    extern std::index_sequence<kumi::_::nth_pos_v<I, Bs...>...> select_index_sequence<std::index_sequence<I...>, Bs...>;
    template<typename T, bool... Bs> extern T adjacent_index_sequence;
    template<std::size_t... I, bool... Bs>
    extern std::index_sequence<0, (kumi::_::nth_pos_v<I, Bs...> + 1)...>
      adjacent_index_sequence<std::index_sequence<I...>, Bs...>;
  }
  namespace function
  {
    template<bool... Bs>
    using unique_index_sequence =
      decltype(kumi::_::unique_index_sequence<std::make_index_sequence<(Bs + ... + 0)>, Bs...>);
    template<bool... Bs>
    using select_index_sequence =
      decltype(kumi::_::select_index_sequence<std::make_index_sequence<(Bs + ... + 0)>, Bs...>);
    template<bool... Bs>
    using adjacent_index_sequence =
      decltype(kumi::_::adjacent_index_sequence<std::make_index_sequence<(Bs + ... + 0)>, Bs...>);
  }
}
namespace kumi
{
  namespace function
  {
    struct identity_t
    {
      template<typename T> KUMI_ABI constexpr T&& operator()(T&& t) const noexcept { return KUMI_FWD(t); }
    } KUMI_VARIABLE_ABI constexpr identity;
    struct max_t
    {
      template<typename T, typename U>
      KUMI_ABI constexpr decltype(auto) operator()(T&& t, U&& u) const noexcept(noexcept(KUMI_FWD(t) > KUMI_FWD(u)))
      requires requires { KUMI_FWD(t) > KUMI_FWD(u); }
      {
        return KUMI_FWD(t) > KUMI_FWD(u) ? KUMI_FWD(t) : KUMI_FWD(u);
      }
    } KUMI_VARIABLE_ABI constexpr max;
    struct min_t
    {
      template<typename T, typename U>
      KUMI_ABI constexpr decltype(auto) operator()(T&& t, U&& u) const noexcept(noexcept(KUMI_FWD(t) < KUMI_FWD(u)))
      requires requires { KUMI_FWD(t) < KUMI_FWD(u); }
      {
        return KUMI_FWD(t) < KUMI_FWD(u) ? KUMI_FWD(t) : KUMI_FWD(u);
      }
    } KUMI_VARIABLE_ABI constexpr min;
    struct adressof_t
    {
      template<typename T>
      requires(std::is_object_v<T>)
      KUMI_ABI constexpr T* operator()(T& t) const noexcept(noexcept(&t))
      {
        return &t;
      }
      template<typename T> constexpr T const* operator()(T const&&) = delete;
    } KUMI_VARIABLE_ABI constexpr adressof;
  }
  namespace _
  {
    template<typename T, typename> extern T common_product_type;
    template<typename T, std::size_t... I>
    extern kumi::common_product_type_t<std::remove_cvref_t<kumi::element_t<I, T>>...>
      common_product_type<T, std::index_sequence<I...>>;
    template<typename T> using common_product_type_t = decltype(common_product_type<T, kumi::function::indexes_for<T>>);
    struct builder_t
    {
      template<kumi::concepts::product_type T, std::size_t... I>
      KUMI_HIDDEN_ABI constexpr auto operator()(T&& t, std::index_sequence<I...>) const
      {
        using res_t = kumi::builder_make_t<T, kumi::element_t<I, T>...>;
        return res_t{get<I>(KUMI_FWD(t))...};
      }
      template<typename T, std::size_t N, std::size_t... I>
      KUMI_HIDDEN_ABI constexpr auto operator()(T&& t,
                                                std::integral_constant<std::size_t, N>,
                                                std::index_sequence<I...>) const
      {
        using U = kumi::_::common_product_type_t<T>;
        using res_t = kumi::builder_make_t<U, kumi::element_t<N, kumi::element_t<I, T>>...>;
        return res_t{get<N>(get<I>(KUMI_FWD(t)))...};
      }
      template<typename T, std::size_t... E, std::size_t... I>
      KUMI_HIDDEN_ABI constexpr auto operator()(T&& t, std::index_sequence<E...>, std::index_sequence<I...>) const
      {
        using U = kumi::_::common_product_type_t<T>;
        using res_t = kumi::builder_make_t<U, kumi::element_t<E, kumi::element_t<I, T>>...>;
        return res_t{get<E>(get<I>(KUMI_FWD(t)))...};
      }
    };
    KUMI_VARIABLE_ABI constexpr builder_t builder{};
  }
}
namespace kumi::function
{
  struct numeric_add
  {
    static constexpr auto identity{0};
    template<typename T1, typename T2>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T1&& a, T2&& b) const noexcept(noexcept(KUMI_FWD(a) + KUMI_FWD(b)))
    requires requires { KUMI_FWD(a) + KUMI_FWD(b); }
    {
      return KUMI_FWD(a) + KUMI_FWD(b);
    }
  };
  struct numeric_prod
  {
    static constexpr auto identity{1};
    template<typename T1, typename T2>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T1&& a, T2&& b) const noexcept(noexcept(KUMI_FWD(a) * KUMI_FWD(b)))
    requires requires { KUMI_FWD(a) * KUMI_FWD(b); }
    {
      return KUMI_FWD(a) * KUMI_FWD(b);
    }
  };
  struct boolean_and
  {
    static constexpr bool identity{true};
    template<typename T1, typename T2>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T1&& a, T2&& b) const noexcept(noexcept(KUMI_FWD(a) & KUMI_FWD(b)))
    requires requires { KUMI_FWD(a) & KUMI_FWD(b); }
    {
      return KUMI_FWD(a) & KUMI_FWD(b);
    }
  };
  struct boolean_or
  {
    static constexpr bool identity{false};
    template<typename T1, typename T2>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T1&& a, T2&& b) const noexcept(noexcept(KUMI_FWD(a) | KUMI_FWD(b)))
    requires requires { KUMI_FWD(a) | KUMI_FWD(b); }
    {
      return KUMI_FWD(a) | KUMI_FWD(b);
    }
  };
  struct boolean_xor
  {
    static constexpr bool identity{false};
    template<typename T1, typename T2>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T1&& a, T2&& b) const noexcept(noexcept(KUMI_FWD(a) ^ KUMI_FWD(b)))
    requires requires { KUMI_FWD(a) ^ KUMI_FWD(b); }
    {
      return KUMI_FWD(a) ^ KUMI_FWD(b);
    }
  };
  inline constexpr kumi::function::numeric_add plus{};
  inline constexpr kumi::function::numeric_prod multiplies{};
  inline constexpr kumi::function::boolean_and bit_and{};
  inline constexpr kumi::function::boolean_or bit_or{};
  inline constexpr kumi::function::boolean_xor bit_xor{};
}
namespace kumi::function
{
  template<typename T, auto V> inline constexpr auto size_or_v = V;
  template<typename T, auto V>
  requires(kumi::concepts::product_type<T>)
  inline constexpr auto size_or_v<T, V> = kumi::size_v<T>;
  template<typename T, auto V> struct size_or
  {
    static constexpr auto value = kumi::function::size_or_v<T, V>;
  };
  template<std::size_t I, typename T, typename V> [[nodiscard]] KUMI_ABI constexpr decltype(auto) get_or(T&& t, V&& v)
  {
    if constexpr (kumi::concepts::product_type<T> && I < kumi::size_v<T>) return get<I>(KUMI_FWD(t));
    else return KUMI_FWD(v);
  }
  template<std::size_t I, typename T, typename U>
  using element_or_t = std::remove_cvref_t<decltype(kumi::function::get_or<I>(std::declval<T>(), std::declval<U>()))>;
  template<std::size_t I, typename T, typename U> struct element_or
  {
    using type = kumi::function::element_or_t<I, T, U>;
  };
  template<typename T> struct foldable
  {
    T value;
    template<typename C> KUMI_ABI friend constexpr decltype(auto) operator>>(foldable&& f, C&& c)
    {
      return kumi::function::foldable{kumi::invoke(c, f.value)};
    }
    template<typename C> KUMI_ABI friend constexpr decltype(auto) operator<<(C&& c, foldable&& f)
    {
      return kumi::function::foldable{kumi::invoke(c, f.value)};
    }
    KUMI_ABI constexpr auto operator()() const noexcept { return value; }
  };
  template<typename F, typename V> struct scannable
  {
    F func;
    V value;
    template<typename C> KUMI_ABI friend constexpr decltype(auto) operator>>(scannable&& s, C&& c)
    {
      auto res = kumi::invoke(c, s.value);
      return kumi::function::scannable{kumi::bind_front(std::move(s.func), std::move(s.value)), res};
    }
    template<typename C> KUMI_ABI friend constexpr decltype(auto) operator<<(C&& c, scannable&& s)
    {
      auto res = kumi::invoke(c, s.value);
      return kumi::function::scannable{kumi::bind_back(std::move(s.func), std::move(s.value)), res};
    }
    KUMI_ABI constexpr decltype(auto) operator()() const noexcept { return kumi::invoke(func, value); }
  };
  template<typename T> foldable(T&& t) -> foldable<std::unwrap_ref_decay_t<T>>;
  template<typename F, typename T> scannable(F&& f, T&& t) -> scannable<F, std::unwrap_ref_decay_t<T>>;
}
namespace kumi
{
}
namespace kumi
{
  namespace _
  {
    template<typename F, typename T, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr decltype(auto) apply_(kumi::_::adl_tag_t, F&& f, T&& t, std::index_sequence<I...>)
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return kumi::invoke(KUMI_FWD(f));
      else return kumi::invoke(KUMI_FWD(f), get<I>(KUMI_FWD(t))...);
    }
  }
  struct apply_t
  {
    template<typename Function, kumi::concepts::product_type T>
    KUMI_ABI constexpr decltype(auto) operator()(Function&& f, T&& t) const
      noexcept(kumi::_::supports_nothrow_apply<Function&&, T&&>)
    requires(kumi::_::supports_apply<Function, T>)
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(KUMI_FWD(f), kumi::values_of(KUMI_FWD(t)));
      else return apply_(kumi::_::adl_tag, KUMI_FWD(f), KUMI_FWD(t), kumi::function::indexes_for<T>{});
    }
  };
  struct apply_field_t
  {
    template<typename Function, kumi::concepts::record_type R>
    KUMI_ABI constexpr decltype(auto) operator()(Function&& f, R&& t) const
    {
      return apply_(kumi::_::adl_tag, KUMI_FWD(f), KUMI_FWD(t), kumi::function::indexes_for<R>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr apply_t apply{};
  KUMI_VARIABLE_ABI constexpr apply_field_t apply_field{};
  namespace result
  {
    template<typename Function, kumi::concepts::product_type T>
    using apply_t = decltype(kumi::apply(std::declval<Function>(), std::declval<T>()));
    template<typename Function, kumi::concepts::product_type T> struct apply
    {
      using type = kumi::result::apply_t<Function, T>;
    };
    template<typename Function, concepts::record_type R>
    using apply_field_t = decltype(kumi::apply_field(std::declval<Function>(), std::declval<R>()));
    template<typename Function, kumi::concepts::record_type R> struct apply_field
    {
      using type = kumi::result::apply_field_t<Function, R>;
    };
  }
}
namespace kumi
{
  struct front_t
  {
    template<kumi::concepts::non_empty_product_type T>
    [[nodiscard]] KUMI_ABI constexpr decltype(auto) operator()(T&& t) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)));
      else return get<0>(KUMI_FWD(t));
    }
  };
  struct back_t
  {
    template<kumi::concepts::non_empty_product_type T>
    [[nodiscard]] KUMI_ABI constexpr decltype(auto) operator()(T&& t) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)));
      else return get<kumi::size_v<T> - 1>(KUMI_FWD(t));
    }
  };
  KUMI_VARIABLE_ABI constexpr front_t front{};
  KUMI_VARIABLE_ABI constexpr back_t back{};
  namespace result
  {
    template<kumi::concepts::product_type T> using front_t = kumi::stored_member_t<0, T>;
    template<kumi::concepts::product_type T> struct front
    {
      using type = kumi::result::front_t<T>;
    };
    template<kumi::concepts::product_type T> using back_t = kumi::stored_member_t<kumi::size_v<T> - 1, T>;
    template<kumi::concepts::product_type T> struct back
    {
      using type = kumi::result::back_t<T>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t K, typename T, std::size_t... I, std::size_t... J, std::size_t... S>
    KUMI_HIDDEN_ABI constexpr auto cartesian_element_(
      kumi::_::adl_tag_t, T&& t, std::index_sequence<I...>, std::index_sequence<J...> j, std::index_sequence<S...>)
    {
      return kumi::_::builder(KUMI_FWD(t), std::index_sequence<((K / S) % I)...>{}, j);
    }
    template<typename T, typename Sizes, typename Elts, typename Strides, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto cartesian_product_(
      kumi::_::adl_tag_t, T&& t, Sizes s, Elts e, Strides st, std::index_sequence<I...>)
    {
      return kumi::make_tuple(cartesian_element_<I>(kumi::_::adl_tag, t, s, e, st)...);
    }
  }
  struct cartesian_product_t
  {
    template<kumi::concepts::product_type... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Ts&&... ts) const
    requires(kumi::concepts::follows_same_semantic<Ts...>)
    {
      if constexpr (sizeof...(Ts) == 0) return kumi::tuple{};
      else
      {
        using out = std::make_index_sequence<(kumi::size_v<Ts> * ...)>;
        using elts = std::index_sequence_for<Ts...>;
        using sizes = std::index_sequence<kumi::size_v<Ts>...>;
        using strides = kumi::function::cartesian_strides<sizes, elts>;
        return cartesian_product_(kumi::_::adl_tag, kumi::forward_as_tuple(KUMI_FWD(ts)...), sizes{}, elts{}, strides{},
                                  out{});
      }
    }
  };
  KUMI_VARIABLE_ABI constexpr cartesian_product_t cartesian_product{};
  namespace result
  {
    template<typename... Ts> using cartesian_product_t = decltype(kumi::cartesian_product(std::declval<Ts>()...));
    template<typename... Ts> struct cartesian_product
    {
      using type = kumi::result::cartesian_product_t<Ts...>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t, typename T> using always_t = T;
    template<typename Target, typename T, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr decltype(auto) member_cast_(kumi::_::adl_tag_t, T&& t, std::index_sequence<I...>)
    {
      if constexpr (kumi::concepts::record_type<T>)
        return kumi::builder<T>::make(kumi::field_cast<Target>(get<I>(KUMI_FWD(t)))...);
      else return kumi::builder_make_t<T, kumi::_::always_t<I, Target>...>{static_cast<Target>(get<I>(KUMI_FWD(t)))...};
    }
  }
  template<typename Target> struct member_cast_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else return member_cast_<Target>(kumi::_::adl_tag, KUMI_FWD(t), kumi::function::indexes_for<T>{});
    }
  };
  template<typename T> inline constexpr member_cast_t<T> member_cast{};
  namespace result
  {
    template<typename Target, kumi::concepts::product_type T>
    using member_cast_t = decltype(kumi::member_cast<Target>(std::declval<T>()));
    template<typename Target, kumi::concepts::product_type T> struct member_cast
    {
      using type = kumi::result::member_cast_t<Target, T>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename Seq, std::size_t... I>
    constexpr auto cat_(kumi::_::adl_tag_t, T&& t, Seq inner, std::index_sequence<I...>)
    {
      using outer = kumi::function::cat_index_sequence<
        kumi::function::fill_index_sequence<I, kumi::size_v<kumi::element_t<I, T>>>...>;
      return kumi::_::builder(KUMI_FWD(t), inner, outer{});
    }
  }
  struct cat_t
  {
    template<kumi::concepts::product_type... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Ts&&... ts) const
    requires(kumi::concepts::follows_same_semantic<Ts...>)
    {
      if constexpr (sizeof...(Ts) == 0) return kumi::tuple{};
      else
      {
        using inner = kumi::function::cat_index_sequence<kumi::function::indexes_for<Ts>...>;
        using outer = std::make_index_sequence<sizeof...(Ts)>;
        return cat_(kumi::_::adl_tag, kumi::forward_as_tuple(KUMI_FWD(ts)...), inner{}, outer{});
      }
    }
  };
  KUMI_VARIABLE_ABI constexpr cat_t cat{};
  namespace result
  {
    template<concepts::product_type... Ts> using cat_t = decltype(kumi::cat(std::declval<Ts>()...));
    template<kumi::concepts::product_type... Ts> struct cat
    {
      using type = kumi::result::cat_t<Ts...>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename... Ts>
    inline constexpr bool contains = ((kumi::concepts::field<T> && std::invocable<T, kumi::_::tag_of_t<Ts>>) || ...);
    template<typename T, typename ID, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto contains_(kumi::_::adl_tag_t, T&&, ID const&, std::index_sequence<I...>)
    {
      return std::bool_constant<
        kumi::concepts::contains_identifier<std::remove_cvref_t<ID>, kumi::element_t<I, T>...>>{};
    }
    template<typename T, std::size_t... I, typename... Is>
    KUMI_HIDDEN_ABI constexpr auto contains_only_(kumi::_::adl_tag_t, T&&, std::index_sequence<I...>, Is const&...)
    {
      return std::bool_constant<(kumi::_::contains<kumi::element_t<I, T>, Is...> && ...)>{};
    }
  }
  struct contains_t
  {
    template<kumi::concepts::product_type T, kumi::concepts::identifier ID>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, ID const& id) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return std::false_type{};
      else return contains_(kumi::_::adl_tag, KUMI_FWD(t), id, kumi::function::indexes_for<T>{});
    }
  };
  struct contains_any_t
  {
    template<kumi::concepts::product_type T, kumi::concepts::identifier... Is>
    [[nodiscard]] KUMI_ABI constexpr auto operator()([[maybe_unused]] T&& t, Is const&... ids) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return std::false_type{};
      else if constexpr (sizeof...(Is) == 0) return std::false_type{};
      else
        return std::bool_constant<(
          decltype(contains_(kumi::_::adl_tag, std::declval<T>(), ids, kumi::function::indexes_for<T>{})){} || ...)>{};
    }
  };
  struct contains_only_t
  {
    template<kumi::concepts::product_type T, kumi::concepts::identifier... Is>
    [[nodiscard]] KUMI_ABI constexpr auto operator()([[maybe_unused]] T&& t,
                                                     [[maybe_unused]] Is const&... ids) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return std::false_type{};
      else if constexpr (sizeof...(Is) == 0) return std::false_type{};
      else if constexpr (sizeof...(Is) < kumi::size_v<T>) return std::false_type{};
      else return contains_only_(kumi::_::adl_tag, KUMI_FWD(t), kumi::function::indexes_for<T>{}, ids...);
    }
  };
  struct contains_none_t : private contains_any_t
  {
    template<kumi::concepts::product_type T, kumi::concepts::identifier... Is>
    [[nodiscard]] KUMI_ABI constexpr auto operator()([[maybe_unused]] T&& t, Is const&... ids) const noexcept
    {
      using R = decltype(contains_any_t::operator()(std::declval<T>(), ids...));
      return std::bool_constant<!R{}>{};
    }
  };
  KUMI_VARIABLE_ABI constexpr contains_t contains{};
  KUMI_VARIABLE_ABI constexpr contains_any_t contains_any{};
  KUMI_VARIABLE_ABI constexpr contains_only_t contains_only{};
  KUMI_VARIABLE_ABI constexpr contains_none_t contains_none{};
  namespace result
  {
    template<kumi::concepts::product_type T, kumi::concepts::identifier ID>
    using contains_t = decltype(kumi::contains(std::declval<T>(), std::declval<ID>()));
    template<kumi::concepts::product_type T, kumi::concepts::identifier ID> struct contains
    {
      using type = kumi::result::contains_t<T, ID>;
    };
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs>
    using contains_any_t = decltype(kumi::contains_any(std::declval<T>(), std::declval<IDs>()...));
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs> struct contains_any
    {
      using type = kumi::result::contains_any_t<T, IDs...>;
    };
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs>
    using contains_only_t = decltype(kumi::contains_only(std::declval<T>(), std::declval<IDs>()...));
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs> struct contains_only
    {
      using type = kumi::result::contains_only_t<T, IDs...>;
    };
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs>
    using contains_none_t = decltype(kumi::contains_none(std::declval<T>(), std::declval<IDs>()...));
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs> struct contains_none
    {
      using type = kumi::result::contains_none_t<T, IDs...>;
    };
  }
}
namespace kumi
{
  struct extract_t
  {
    template<kumi::concepts::product_type T, std::size_t B, std::size_t E, std::size_t S>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t,
                                                     kumi::index_t<B>,
                                                     kumi::index_t<E>,
                                                     kumi::index_t<S>) const noexcept
    {
      static_assert((B <= kumi::size_v<T>) && (E <= kumi::size_v<T>), "[KUMI] - Invalid index");
      return kumi::_::builder(KUMI_FWD(t), kumi::function::slice_index_sequence<B, E, S>{});
    }
    template<kumi::concepts::product_type T, std::size_t B, std::size_t E>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, kumi::index_t<B>, kumi::index_t<E>) const noexcept
    {
      static_assert((B <= kumi::size_v<T>) && (E <= kumi::size_v<T>), "[KUMI] - Invalid index");
      return kumi::_::builder(KUMI_FWD(t), kumi::function::slice_index_sequence<B, E>{});
    }
    template<kumi::concepts::product_type T, std::size_t B>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, kumi::index_t<B> b) const noexcept
    {
      static_assert(B <= kumi::size_v<T>, "[KUMI] - Invalid index");
      return (*this)(KUMI_FWD(t), b, kumi::index<size_v<T>>);
    }
  };
  struct remove_t
  {
    template<kumi::concepts::product_type T, std::size_t B, std::size_t E, std::size_t S>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t,
                                                     kumi::index_t<B>,
                                                     kumi::index_t<E>,
                                                     kumi::index_t<S>) const noexcept
    {
      static_assert((B <= kumi::size_v<T>) && (E <= kumi::size_v<T>), "[KUMI] - Invalid index");
      using kept = kumi::function::remove_index_sequence<kumi::size_v<T>, B, E, S>;
      return kumi::_::builder(KUMI_FWD(t), kept{});
    }
    template<kumi::concepts::product_type T, std::size_t B, std::size_t E>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, kumi::index_t<B> b, kumi::index_t<E> e) const noexcept
    {
      static_assert((B <= kumi::size_v<T>) && (E <= kumi::size_v<T>), "[KUMI] - Invalid index");
      return (*this)(KUMI_FWD(t), b, e, kumi::index<1>);
    }
    template<kumi::concepts::product_type T, std::size_t B>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, kumi::index_t<B> b) const noexcept
    {
      static_assert(B <= kumi::size_v<T>, "[KUMI] - Invalid index");
      return (*this)(KUMI_FWD(t), b, kumi::index<kumi::size_v<T>>);
    }
  };
  struct split_t
  {
    template<kumi::concepts::product_type T, std::size_t I>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, kumi::index_t<I>) const noexcept
    {
      static_assert(I <= kumi::size_v<T>, "[KUMI] - Invalid index");
      using first = std::make_index_sequence<I>;
      using last = kumi::function::shift_index_sequence<I, kumi::size_v<T> - I>;
      return kumi::tuple{kumi::_::builder(KUMI_FWD(t), first{}), kumi::_::builder(KUMI_FWD(t), last{})};
    }
  };
  KUMI_VARIABLE_ABI constexpr extract_t extract{};
  KUMI_VARIABLE_ABI constexpr remove_t remove{};
  KUMI_VARIABLE_ABI constexpr split_t split{};
  namespace result
  {
    template<kumi::concepts::product_type T, std::size_t... I>
    requires((sizeof...(I) == 1) || (sizeof...(I) == 2))
    using extract_t = decltype(kumi::extract(std::declval<T>(), kumi::index_t<I>{}...));
    template<kumi::concepts::product_type T, std::size_t... I>
    requires((sizeof...(I) == 1) || (sizeof...(I) == 2))
    struct extract
    {
      using type = kumi::result::extract_t<T, I...>;
    };
    template<kumi::concepts::product_type T, std::size_t... I>
    requires((sizeof...(I) == 1) || (sizeof...(I) == 2))
    using remove_t = decltype(kumi::remove(std::declval<T>(), kumi::index_t<I>{}...));
    template<kumi::concepts::product_type T, std::size_t... I>
    requires((sizeof...(I) == 1) || (sizeof...(I) == 2))
    struct remove
    {
      using type = kumi::result::remove_t<T, I...>;
    };
    template<kumi::concepts::product_type T, std::size_t I>
    using split_t = decltype(kumi::split(std::declval<T>(), kumi::index_t<I>{}));
    template<kumi::concepts::product_type T, std::size_t I> struct split
    {
      using type = kumi::result::split_t<T, I>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<kumi::_::case_ Case, typename F, typename T, typename... Ts>
    KUMI_HIDDEN_ABI constexpr void for_each_switch(auto N, F f, T&& t, Ts&&... ts)
    {
      if constexpr (Case == kumi::_::case_::normal)
      {
        if constexpr (kumi::concepts::record_type<T>)
        {
          constexpr auto field = kumi::identifier_of<kumi::element_t<N, T>>();
          kumi::invoke(f, get<field>(KUMI_FWD(t)), get<field>(KUMI_FWD(ts))...);
        }
        else kumi::invoke(f, get<N>(KUMI_FWD(t)), get<N>(KUMI_FWD(ts))...);
      }
      else if constexpr (Case == kumi::_::case_::indexed)
      {
        kumi::invoke(f, N, get<N>(KUMI_FWD(t)), get<N>(KUMI_FWD(ts))...);
      }
      else if constexpr (Case == kumi::_::case_::field)
      {
        constexpr auto field = kumi::identifier_of<kumi::element_t<N, T>>();
        kumi::invoke(f, kumi::_::make_str(field), get<field>(KUMI_FWD(t)), get<field>(KUMI_FWD(ts))...);
      }
    }
    template<kumi::_::case_ Case, typename F, std::size_t... I, typename T, typename... Ts>
    KUMI_HIDDEN_ABI constexpr void for_each_(kumi::_::adl_tag_t, F&& f, std::index_sequence<I...>, T&& t, Ts&&... ts)
    {
      if constexpr (sizeof...(I) == 0) return;
      else ((for_each_switch<Case>(kumi::index<I>, KUMI_FWD(f), KUMI_FWD(t), KUMI_FWD(ts)...)), ...);
    }
  }
  struct for_each_t
  {
    template<typename Function, kumi::concepts::product_type T, kumi::concepts::product_type... Ts>
    KUMI_ABI constexpr void operator()(Function f, T&& t, Ts&&... ts) const
    requires(kumi::concepts::compatible_product_types<T, Ts...>) && (kumi::_::supports_call<Function&, T, Ts...>)
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return;
      else
        for_each_<kumi::_::case_::normal>(kumi::_::adl_tag, f, kumi::function::indexes_for<T>{}, KUMI_FWD(t),
                                          KUMI_FWD(ts)...);
    }
  };
  struct for_each_index_t
  {
    template<typename Function, kumi::concepts::product_type T, kumi::concepts::product_type... Ts>
    KUMI_ABI constexpr void operator()(Function f, T&& t, Ts&&... ts) const
    requires(!kumi::concepts::record_type<T> && (!kumi::concepts::record_type<Ts> && ...))
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return;
      else
        for_each_<kumi::_::case_::indexed>(kumi::_::adl_tag, f, kumi::function::indexes_for<T>{}, KUMI_FWD(t),
                                           KUMI_FWD(ts)...);
    }
  };
  struct for_each_field_t
  {
    template<typename Function, kumi::concepts::record_type R, kumi::concepts::record_type... Rs>
    KUMI_ABI constexpr void operator()(Function f, R&& r, Rs&&... rs) const
    requires(kumi::concepts::compatible_product_types<R, Rs...>)
    {
      if constexpr (kumi::concepts::empty_product_type<R>) return;
      else
        for_each_<kumi::_::case_::field>(kumi::_::adl_tag, f, kumi::function::indexes_for<R>{}, KUMI_FWD(r),
                                         KUMI_FWD(rs)...);
    }
  };
  KUMI_VARIABLE_ABI constexpr for_each_t for_each{};
  KUMI_VARIABLE_ABI constexpr for_each_index_t for_each_index{};
  KUMI_VARIABLE_ABI constexpr for_each_field_t for_each_field{};
}
namespace kumi
{
  namespace _
  {
    template<typename Pred, typename T, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr std::size_t locate_(kumi::_::adl_tag_t, Pred p, T&& t, std::index_sequence<I...>) noexcept
    {
      std::size_t index = kumi::size_v<T>;
      ((kumi::invoke(p, get<I>(KUMI_FWD(t))) && ((index = I), true)) || ...);
      return index;
    }
  }
  struct locate_t
  {
    template<typename Pred, kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr std::size_t operator()(T&& t, Pred p) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return 0;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)), p);
      else return locate_(kumi::_::adl_tag, p, KUMI_FWD(t), kumi::function::indexes_for<T>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr locate_t locate{};
}
namespace kumi
{
  namespace _
  {
    struct flatten_all_case_t
    {
      template<typename T, typename V, typename F, typename Self>
      KUMI_HIDDEN_ABI constexpr auto operator()(T&&, V&& v, F f, Self s) const
      {
        using FV = kumi::result::field_value_of_t<V>;
        if constexpr (kumi::concepts::record_type<FV> && kumi::concepts::record_type<T>)
          return kumi::capture_field<kumi::identifier_of<V>()>(s(kumi::field_value_of(KUMI_FWD(v)), f));
        else if constexpr (kumi::concepts::follows_same_semantic<T, V>) return s(KUMI_FWD(v), f);
        else if constexpr (kumi::concepts::record_type<T> && kumi::concepts::field<V>)
          return kumi::capture_field<kumi::identifier_of<V>()>(kumi::invoke(f, kumi::field_value_of(KUMI_FWD(v))));
        else return kumi::invoke(f, KUMI_FWD(v));
      }
    } KUMI_VARIABLE_ABI constexpr flatten_all_case{};
    struct flatten_case_t
    {
      template<typename T, typename V> KUMI_HIDDEN_ABI constexpr auto operator()(T&&, V&& v, auto J) const
      {
        using FV = kumi::result::field_value_of_t<V>;
        if constexpr (kumi::concepts::record_type<FV> && kumi::concepts::record_type<T>)
        {
          constexpr auto new_name = kumi::label_of<V>() + kumi::label_of<kumi::element_t<J, FV>>();
          return (
            kumi::capture_field<name<new_name>{}>(kumi::field_value_of(get<J>(kumi::field_value_of(KUMI_FWD(v))))));
        }
        else if constexpr (kumi::concepts::follows_same_semantic<T, V>) return get<J>(KUMI_FWD(v));
        else return KUMI_FWD(v);
      }
    } KUMI_VARIABLE_ABI constexpr flatten_case{};
    template<typename T, typename V, std::size_t... J, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto flatten_intern_(
      kumi::_::adl_tag_t, T&& t, V visitor, std::index_sequence<J...>, std::index_sequence<I...>)
    {
      if constexpr (sizeof...(I) == 0) return kumi::builder<T>::make();
      else return kumi::builder<T>::make(visitor(KUMI_FWD(t), get<I>(KUMI_FWD(t)), kumi::index<J>)...);
    }
    template<typename T, typename V, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto flatten_(kumi::_::adl_tag_t, T&& t, V visitor, std::index_sequence<I...>)
    {
      using inner = kumi::function::cat_index_sequence<
        std::make_index_sequence<kumi::function::size_or_v<kumi::stored_element_t<I, T>, 1>>...>;
      using outer = kumi::function::cat_index_sequence<
        kumi::function::fill_index_sequence<I, kumi::function::size_or_v<kumi::stored_element_t<I, T>, 1>>...>;
      return flatten_intern_(kumi::_::adl_tag, KUMI_FWD(t), visitor, inner{}, outer{});
    }
    template<typename T, typename V, typename F, typename S, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto flatten_all_(
      kumi::_::adl_tag_t, T&& t, V visitor, F f, S self, std::index_sequence<I...>)
    {
      return kumi::builder<T>::make(visitor(KUMI_FWD(t), get<I>(KUMI_FWD(t)), f, self)...);
    }
    template<typename E, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto compress_(kumi::_::adl_tag_t, E&& e, std::index_sequence<I...>)
    {
      using V = kumi::result::field_value_of_t<E>;
      if constexpr (sizeof...(I) == 0 || kumi::concepts::empty_product_type<V>) return kumi::builder<V>::make();
      else
      {
        constexpr auto outer = kumi::label_of<E>();
        return kumi::builder<V>::make(
          kumi::capture_field<kumi::name<outer + kumi::label_of<kumi::element_t<I, V>>()>{}>(
            kumi::field_value_of(get<I>(kumi::field_value_of(KUMI_FWD(e)))))...);
      }
    }
  }
  struct compress_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else
      {
        using V = kumi::result::field_value_of_t<kumi::element_t<0, T>>;
        if constexpr (kumi::concepts::sized_product_type<T, 1> && kumi::concepts::follows_same_semantic<T, V>)
        {
          if constexpr (kumi::concepts::record_type<T>)
            return (*this)(compress_(kumi::_::adl_tag, get<0>(KUMI_FWD(t)), kumi::function::indexes_for<V>{}));
          else return (*this)(get<0>(KUMI_FWD(t)));
        }
        else return KUMI_FWD(t);
      }
    }
  };
  struct flatten_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else return flatten_(kumi::_::adl_tag, KUMI_FWD(t), kumi::_::flatten_case, kumi::function::indexes_for<T>{});
    }
  };
  struct flatten_all_t : private kumi::flatten_t
  {
    template<kumi::concepts::product_type T, typename Func>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, Func f) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else
      {
        return this->flatten_t::operator()(flatten_all_(kumi::_::adl_tag, KUMI_FWD(t), kumi::_::flatten_all_case, f,
                                                        (*this), kumi::function::indexes_for<T>{}));
      }
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else return (*this)(KUMI_FWD(t), kumi::function::identity);
    }
  };
  struct as_flat_ptr_t : private kumi::flatten_all_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI auto operator()(T&& t) const noexcept
    {
      return this->flatten_all_t::operator()(KUMI_FWD(t), kumi::function::adressof);
    }
  };
  KUMI_VARIABLE_ABI constexpr compress_t compress{};
  KUMI_VARIABLE_ABI constexpr flatten_t flatten{};
  KUMI_VARIABLE_ABI constexpr flatten_all_t flatten_all{};
  KUMI_VARIABLE_ABI constexpr as_flat_ptr_t as_flat_ptr{};
  namespace result
  {
    template<kumi::concepts::product_type T> using compress_t = decltype(kumi::compress(std::declval<T>()));
    template<kumi::concepts::product_type T> struct compress
    {
      using type = kumi::result::compress_t<T>;
    };
    template<kumi::concepts::product_type T> using flatten_t = decltype(kumi::flatten(std::declval<T>()));
    template<kumi::concepts::product_type T> struct flatten
    {
      using type = kumi::result::flatten_t<T>;
    };
    template<kumi::concepts::product_type T, typename... Func>
    requires((sizeof...(Func) == 0) || (sizeof...(Func) == 1))
    using flatten_all_t = decltype(kumi::flatten_all(std::declval<T>(), std::declval<Func>()...));
    template<kumi::concepts::product_type T, typename... Func>
    requires((sizeof...(Func) == 0) || (sizeof...(Func) == 1))
    struct flatten_all
    {
      using type = kumi::result::flatten_all_t<T>;
    };
    template<kumi::concepts::product_type T> using as_flat_ptr_t = decltype(kumi::as_flat_ptr(std::declval<T>()));
    template<kumi::concepts::product_type T> struct as_flat_ptr
    {
      using type = kumi::result::as_flat_ptr_t<T>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename F, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr decltype(auto) generate_(kumi::_::adl_tag_t, F&& f, std::index_sequence<I...>) noexcept
    {
      return kumi::tuple{kumi::invoke(KUMI_FWD(f), kumi::index<I>)...};
    }
  }
  template<std::size_t N> struct generate_t
  {
    template<typename Function> [[nodiscard]] KUMI_ABI constexpr auto operator()(Function const& f) const noexcept
    {
      if constexpr (N == 0) return kumi::tuple{};
      else return generate_(kumi::_::adl_tag, f, std::make_index_sequence<N>{});
    }
  };
  template<std::size_t N> struct fill_t
  {
    template<typename T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T const& v) const noexcept
    {
      if constexpr (N == 0) return kumi::tuple{};
      else return generate_(kumi::_::adl_tag, [&](auto) { return v; }, std::make_index_sequence<N>{});
    }
  };
  template<std::size_t N> struct iota_t
  {
    template<typename T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T v) const noexcept
    {
      if constexpr (N == 0) return kumi::tuple{};
      else
        return generate_(
          kumi::_::adl_tag, [&](auto I) { return static_cast<T>(v + I); }, std::make_index_sequence<N>{});
    }
  };
  template<std::size_t N> inline constexpr generate_t<N> generate{};
  template<std::size_t N> inline constexpr fill_t<N> fill{};
  template<std::size_t N> inline constexpr iota_t<N> iota{};
  namespace result
  {
    template<std::size_t N, typename Function> using generate_t = decltype(kumi::generate<N>(std::declval<Function>()));
    template<std::size_t N, typename Function> struct generate
    {
      using type = kumi::result::generate_t<N, Function>;
    };
    template<std::size_t N, typename T> using fill_t = decltype(kumi::fill<N>(std::declval<T>()));
    template<std::size_t N, typename T> struct fill
    {
      using type = kumi::result::fill_t<N, T>;
    };
    template<std::size_t N, typename T> using iota_t = decltype(kumi::iota<N>(std::declval<T>()));
    template<std::size_t N, typename T> struct iota
    {
      using type = kumi::result::iota_t<N, T>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename U, typename V, typename Sum, typename Prod, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto inner_product_(
      kumi::_::adl_tag_t, T&& t, U&& u, V init, Sum sum, Prod prod, std::index_sequence<I...>) noexcept
    {
      if constexpr (kumi::concepts::record_type<T>)
        return (kumi::function::foldable{init} >> ... >>
                kumi::bind_back(sum, kumi::invoke(prod, get<kumi::identifier_of<kumi::element_t<I, T>>()>(KUMI_FWD(t)),
                                                  get<kumi::identifier_of<kumi::element_t<I, U>>()>(KUMI_FWD(u)))))();
      else
        return (kumi::function::foldable{init} >> ... >>
                kumi::bind_back(sum, kumi::invoke(prod, get<I>(KUMI_FWD(t)), get<I>(KUMI_FWD(u)))))();
    }
    template<typename T, typename U, typename V, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto inner_product_fast_(
      kumi::_::adl_tag_t, T&& t, U&& u, V init, std::index_sequence<I...>) noexcept
    {
      if constexpr (kumi::concepts::record_type<T>)
        return (init + ... +
                (get<kumi::identifier_of<kumi::element_t<I, T>>()>(KUMI_FWD(t)) *
                 get<kumi::identifier_of<kumi::element_t<I, U>>()>(KUMI_FWD(u))));
      else return (init + ... + (get<I>(KUMI_FWD(t)) * get<I>(KUMI_FWD(u))));
    }
  }
  struct inner_product_t
  {
    template<kumi::concepts::product_type S1,
             kumi::concepts::sized_product_type<kumi::size_v<S1>> S2,
             typename T,
             typename Sum,
             typename Prod>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(S1&& s1, S2&& s2, T init, Sum sum, Prod prod) const noexcept
    requires(kumi::concepts::compatible_product_types<S1, S2>)
    {
      if constexpr (kumi::concepts::empty_product_type<S1>) return init;
      else
        return inner_product_(kumi::_::adl_tag, KUMI_FWD(s1), KUMI_FWD(s2), init, sum, prod,
                              kumi::function::indexes_for<S1>{});
    }
    template<kumi::concepts::product_type S1, kumi::concepts::sized_product_type<kumi::size_v<S1>> S2, typename T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(S1&& s1, S2&& s2, T init) const noexcept
    requires(kumi::concepts::compatible_product_types<S1, S2>)
    {
      if constexpr (kumi::concepts::empty_product_type<S1>) return init;
      else
        return inner_product_fast_(kumi::_::adl_tag, KUMI_FWD(s1), KUMI_FWD(s2), init,
                                   kumi::function::indexes_for<S1>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr inner_product_t inner_product{};
  namespace result
  {
    template<kumi::concepts::product_type S1,
             kumi::concepts::sized_product_type<kumi::size_v<S1>> S2,
             typename T,
             typename... Operators>
    requires((sizeof...(Operators) == 0) || (sizeof...(Operators) == 2))
    using inner_product_t = decltype(kumi::inner_product(
      std::declval<S1>(), std::declval<S2>(), std::declval<T>(), std::declval<Operators>()...));
    template<kumi::concepts::product_type S1,
             kumi::concepts::sized_product_type<kumi::size_v<S1>> S2,
             typename T,
             typename... Operators>
    requires((sizeof...(Operators) == 0) || (sizeof...(Operators) == 2))
    struct inner_product
    {
      using type = kumi::result::inner_product_t<S1, S2, T, Operators...>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<kumi::_::case_ Case, typename F, typename T, typename... Ts>
    KUMI_HIDDEN_ABI constexpr decltype(auto) map_switch(auto N, F f, T&& t, Ts&&... ts)
    {
      if constexpr (Case == kumi::_::case_::normal)
      {
        if constexpr (kumi::concepts::record_type<T>)
        {
          constexpr auto field = kumi::identifier_of<kumi::element_t<N, T>>();
          return kumi::capture_field<field>(kumi::invoke(f, get<field>(KUMI_FWD(t)), get<field>(KUMI_FWD(ts))...));
        }
        else return kumi::invoke(f, get<N>(KUMI_FWD(t)), get<N>(KUMI_FWD(ts))...);
      }
      else if constexpr (Case == kumi::_::case_::indexed)
      {
        return kumi::invoke(f, N, get<N>(KUMI_FWD(t)), get<N>(KUMI_FWD(ts))...);
      }
      else if constexpr (Case == kumi::_::case_::field)
      {
        constexpr auto field = kumi::identifier_of<kumi::element_t<N, T>>();
        return kumi::capture_field<field>(
          kumi::invoke(f, kumi::_::make_str(field), get<field>(KUMI_FWD(t)), get<field>(KUMI_FWD(ts))...));
      }
    }
    template<kumi::_::case_ Case, typename F, std::size_t... I, typename T, typename... Ts>
    KUMI_HIDDEN_ABI constexpr decltype(auto) map_(
      kumi::_::adl_tag_t, F&& f, std::index_sequence<I...>, T&& t, Ts&&... ts)
    {
      if constexpr (sizeof...(I) == 0) return kumi::builder<T>::make();
      else
        return kumi::builder<T>::make(map_switch<Case>(kumi::index<I>, KUMI_FWD(f), KUMI_FWD(t), KUMI_FWD(ts)...)...);
    }
  }
  struct map_t
  {
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t, Ts&&... ts) const
    requires(kumi::concepts::compatible_product_types<T, Ts...>) && (kumi::_::supports_call<Function, T&&, Ts&&...>)
    {
      return map_<kumi::_::case_::normal>(kumi::_::adl_tag, f, kumi::function::indexes_for<T>{}, KUMI_FWD(t),
                                          KUMI_FWD(ts)...);
    }
  };
  struct map_index_t
  {
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t, Ts&&... ts) const
    requires(!kumi::concepts::record_type<T> && (!kumi::concepts::record_type<Ts> && ...))
    {
      return map_<kumi::_::case_::indexed>(kumi::_::adl_tag, f, kumi::function::indexes_for<T>{}, KUMI_FWD(t),
                                           KUMI_FWD(ts)...);
    }
  };
  struct map_field_t
  {
    template<typename Function,
             kumi::concepts::record_type R,
             kumi::concepts::sized_product_type<kumi::size_v<R>>... Rs>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, R&& r, Rs&&... rs) const
    requires(kumi::concepts::compatible_product_types<R, Rs...>)
    {
      return map_<kumi::_::case_::field>(kumi::_::adl_tag, f, kumi::function::indexes_for<R>{}, KUMI_FWD(r),
                                         KUMI_FWD(rs)...);
    }
  };
  KUMI_VARIABLE_ABI constexpr map_t map{};
  KUMI_VARIABLE_ABI constexpr map_index_t map_index{};
  KUMI_VARIABLE_ABI constexpr map_field_t map_field{};
  namespace result
  {
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    using map_t = decltype(kumi::map(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    struct map
    {
      using type = kumi::result::map_t<Function, T, Ts...>;
    };
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    using map_index_t = decltype(kumi::map_index(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    struct map_index
    {
      using type = kumi::result::map_index_t<Function, T, Ts...>;
    };
    template<typename Function,
             kumi::concepts::record_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    using map_field_t = decltype(kumi::map_field(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    template<typename Function,
             kumi::concepts::record_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    struct map_field
    {
      using type = kumi::result::map_field_t<Function, T, Ts...>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename V, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto push_front_(kumi::_::adl_tag_t, T&& t, V&& v, std::index_sequence<I...>)
    {
      return kumi::builder<T>::make(KUMI_FWD(v), get<I>(KUMI_FWD(t))...);
    }
    template<typename T, typename V, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto push_back_(kumi::_::adl_tag_t, T&& t, V&& v, std::index_sequence<I...>)
    {
      return kumi::builder<T>::make(get<I>(KUMI_FWD(t))..., KUMI_FWD(v));
    }
  }
  struct push_front_t
  {
    template<kumi::concepts::product_type T, typename V>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, V&& v) const
    {
      return push_front_(kumi::_::adl_tag, KUMI_FWD(t), KUMI_FWD(v), kumi::function::indexes_for<T>{});
    }
  };
  struct pop_front_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return kumi::builder<T>::make();
      else return kumi::_::builder(KUMI_FWD(t), kumi::function::shift_index_sequence<1, kumi::size_v<T> - 1>{});
    }
  };
  struct push_back_t
  {
    template<kumi::concepts::product_type T, typename V>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, V&& v) const
    {
      return push_back_(kumi::_::adl_tag, KUMI_FWD(t), KUMI_FWD(v), kumi::function::indexes_for<T>{});
    }
  };
  struct pop_back_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return kumi::builder<T>::make();
      else return kumi::_::builder(KUMI_FWD(t), std::make_index_sequence<kumi::size_v<T> - 1>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr push_front_t push_front{};
  KUMI_VARIABLE_ABI constexpr pop_front_t pop_front{};
  KUMI_VARIABLE_ABI constexpr push_back_t push_back{};
  KUMI_VARIABLE_ABI constexpr pop_back_t pop_back{};
  namespace result
  {
    template<kumi::concepts::product_type T, typename V>
    using push_front_t = decltype(kumi::push_front(std::declval<T>(), std::declval<V>()));
    template<kumi::concepts::product_type T, typename V> struct push_front
    {
      using type = kumi::result::push_front_t<T, V>;
    };
    template<kumi::concepts::product_type T> using pop_front_t = decltype(kumi::pop_front(std::declval<T>()));
    template<kumi::concepts::product_type T> struct pop_front
    {
      using type = kumi::result::pop_front_t<T>;
    };
    template<kumi::concepts::product_type T, typename V>
    using push_back_t = decltype(kumi::push_back(std::declval<T>(), std::declval<V>()));
    template<kumi::concepts::product_type T, typename V> struct push_back
    {
      using type = kumi::result::push_back_t<T, V>;
    };
    template<kumi::concepts::product_type T> using pop_back_t = decltype(kumi::pop_back(std::declval<T>()));
    template<kumi::concepts::product_type T> struct pop_back
    {
      using type = kumi::result::pop_back_t<T>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename F, typename T, typename V, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto fold_left_(kumi::_::adl_tag_t, F f, T&& t, V v, std::index_sequence<I...>)
    {
      return (kumi::function::foldable{v} >> ... >> kumi::bind_back(f, get<I>(KUMI_FWD(t))))();
    }
    template<typename F, typename T, typename V, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto fold_right_(kumi::_::adl_tag_t, F f, T&& t, V v, std::index_sequence<I...>)
    {
      return (kumi::bind_front(f, get<I>(KUMI_FWD(t))) << ... << kumi::function::foldable{v})();
    }
  }
  struct fold_left_t
  {
    template<typename Function, kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t, Value init) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(f, kumi::values_of(KUMI_FWD(t)), init);
      else if constexpr (kumi::concepts::empty_product_type<T>) return init;
      else return fold_left_(kumi::_::adl_tag, f, KUMI_FWD(t), init, kumi::function::indexes_for<T>{});
    }
    template<typename Function, kumi::concepts::non_empty_product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(f, kumi::values_of(KUMI_FWD(t)));
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
      else
        return fold_left_(kumi::_::adl_tag, f, KUMI_FWD(t), get<0>(KUMI_FWD(t)),
                          kumi::function::shift_index_sequence<1, kumi::size_v<T> - 1>{});
    }
  };
  struct fold_right_t
  {
    template<typename Function, kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t, Value init) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(f, kumi::values_of(KUMI_FWD(t)), init);
      else if constexpr (kumi::concepts::empty_product_type<T>) return init;
      else return fold_right_(kumi::_::adl_tag, f, KUMI_FWD(t), init, kumi::function::indexes_for<T>{});
    }
    template<typename Function, kumi::concepts::non_empty_product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(f, kumi::values_of(KUMI_FWD(t)));
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
      else
        return fold_right_(kumi::_::adl_tag, f, KUMI_FWD(t), get<0>(KUMI_FWD(t)),
                           kumi::function::shift_index_sequence<1, kumi::size_v<T> - 1>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr fold_left_t fold_left{};
  KUMI_VARIABLE_ABI constexpr fold_right_t fold_right{};
  namespace result
  {
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using fold_left_t =
      decltype(kumi::fold_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()...));
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct fold_left
    {
      using type = kumi::result::fold_left_t<Function, T, Value...>;
    };
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using fold_right_t =
      decltype(kumi::fold_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()...));
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct fold_right
    {
      using type = kumi::result::fold_right_t<Function, T, Value...>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    struct minmax_case_t
    {
      template<typename V, typename F, typename C> KUMI_HIDDEN_ABI constexpr auto operator()(V&& v, F f, C c) const
      {
        if constexpr (kumi::concepts::product_type<V>) return c(KUMI_FWD(v), f);
        else return kumi::invoke(f, KUMI_FWD(v));
      }
    };
    KUMI_VARIABLE_ABI constexpr minmax_case_t minmax_case{};
    template<typename F, typename T, typename V, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto minmax_(kumi::_::adl_tag_t, F f, T&& t, V v, std::index_sequence<I...>)
    {
      return (kumi::function::foldable{v} >> ... >> kumi::bind_back(f, get<I + 1>(KUMI_FWD(t))))();
    }
    template<typename M, typename F, typename T, typename V, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto map_minmax_(kumi::_::adl_tag_t, M m, F f, T&& t, V v, std::index_sequence<I...>)
    {
      return (kumi::function::foldable{kumi::invoke(m, v)} >> ... >>
              kumi::bind_back(f, kumi::invoke(m, get<I + 1>(KUMI_FWD(t)))))();
    }
    template<typename T, typename V, typename F, typename S, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto minmax_flat_(
      kumi::_::adl_tag_t, T&& t, V visitor, F f, S self, std::index_sequence<I...>) noexcept
    {
      return kumi::make_tuple(visitor(get<I>(KUMI_FWD(t)), f, self)...);
    }
  }
  struct max_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)));
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
      else
      {
        return minmax_(kumi::_::adl_tag, kumi::function::max, KUMI_FWD(t), get<0>(KUMI_FWD(t)),
                       std::make_index_sequence<kumi::size_v<T> - 1>{});
      }
    }
    template<kumi::concepts::product_type T, typename F>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, F f) const noexcept
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)), f);
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return invoke(f, get<0>(KUMI_FWD(t)));
      else
      {
        return map_minmax_(kumi::_::adl_tag, f, kumi::function::max, KUMI_FWD(t), get<0>(KUMI_FWD(t)),
                           std::make_index_sequence<kumi::size_v<T> - 1>{});
      }
    }
  };
  struct max_flat_t : private kumi::max_t
  {
    template<kumi::concepts::product_type T, typename F>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, F f) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return 0;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)), f);
      else
        return this->max_t::operator()(minmax_flat_(kumi::_::adl_tag, KUMI_FWD(t), kumi::_::minmax_case, f, (*this),
                                                    kumi::function::indexes_for<T>{}));
    }
  };
  struct min_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)));
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
      else
      {
        return minmax_(kumi::_::adl_tag, kumi::function::min, KUMI_FWD(t), get<0>(KUMI_FWD(t)),
                       std::make_index_sequence<kumi::size_v<T> - 1>{});
      }
    }
    template<kumi::concepts::product_type T, typename F>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, F f) const noexcept
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)), f);
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return kumi::invoke(f, get<0>(KUMI_FWD(t)));
      else
      {
        return map_minmax_(kumi::_::adl_tag, f, kumi::function::min, KUMI_FWD(t), get<0>(KUMI_FWD(t)),
                           std::make_index_sequence<kumi::size_v<T> - 1>{});
      }
    }
  };
  struct min_flat_t : private kumi::min_t
  {
    template<kumi::concepts::product_type T, typename F>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, F f) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return 0;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)), f);
      else
        return this->min_t::operator()(minmax_flat_(kumi::_::adl_tag, KUMI_FWD(t), kumi::_::minmax_case, f, (*this),
                                                    kumi::function::indexes_for<T>{}));
    }
  };
  KUMI_VARIABLE_ABI constexpr max_t max{};
  KUMI_VARIABLE_ABI constexpr max_flat_t max_flat{};
  KUMI_VARIABLE_ABI constexpr min_t min{};
  KUMI_VARIABLE_ABI constexpr min_flat_t min_flat{};
  namespace result
  {
    template<typename T, typename... F>
    requires((sizeof...(F) == 0) || (sizeof...(F) == 1))
    using max_t = decltype(kumi::max(std::declval<T>(), std::declval<F>()...));
    template<typename T, typename... F>
    requires((sizeof...(F) == 0) || (sizeof...(F) == 1))
    struct max
    {
      using type = kumi::result::max_t<T, F...>;
    };
    template<typename T, typename F> using max_flat_t = decltype(kumi::max_flat(std::declval<T>(), std::declval<F>()));
    template<typename T, typename F> struct max_flat
    {
      using type = kumi::result::max_flat_t<T, F>;
    };
    template<typename T, typename... F>
    requires((sizeof...(F) == 0) || (sizeof...(F) == 1))
    using min_t = decltype(kumi::min(std::declval<T>(), std::declval<F>()...));
    template<typename T, typename... F>
    requires((sizeof...(F) == 0) || (sizeof...(F) == 1))
    struct min
    {
      using type = kumi::result::min_t<T, F...>;
    };
    template<typename T, typename F> using min_flat_t = decltype(kumi::min_flat(std::declval<T>(), std::declval<F>()));
    template<typename T, typename F> struct min_flat
    {
      using type = kumi::result::min_flat_t<T, F>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, template<typename> typename Pred, std::size_t... I>
    KUMI_HIDDEN_ABI consteval auto select_in_(kumi::_::adl_tag_t, std::index_sequence<I...>) noexcept
    {
      return kumi::function::select_index_sequence<(Pred<kumi::stored_element_t<I, T>>::value)...>{};
    }
    template<typename T, template<typename> typename Pred, std::size_t... I>
    KUMI_HIDDEN_ABI consteval auto select_out_(kumi::_::adl_tag_t, std::index_sequence<I...>) noexcept
    {
      return kumi::function::select_index_sequence<(!Pred<kumi::stored_element_t<I, T>>::value)...>{};
    }
  }
  template<template<typename> typename Pred> struct partition_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return kumi::tuple{builder<T>::make(), builder<T>::make()};
      else
      {
        constexpr auto in = select_in_<T, Pred>(kumi::_::adl_tag, kumi::function::indexes_for<T>{});
        constexpr auto out = select_out_<T, Pred>(kumi::_::adl_tag, kumi::function::indexes_for<T>{});
        return kumi::tuple{kumi::_::builder(KUMI_FWD(t), in), kumi::_::builder(KUMI_FWD(t), out)};
      }
    }
  };
  template<template<typename> typename Pred> struct filter_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return builder<T>::make();
      else
      {
        constexpr auto pos = select_in_<T, Pred>(kumi::_::adl_tag, kumi::function::indexes_for<T>{});
        return kumi::_::builder(KUMI_FWD(t), pos);
      }
    }
  };
  template<template<typename> typename Pred> struct filter_not_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return builder<T>::make();
      else
      {
        constexpr auto pos = select_out_<T, Pred>(kumi::_::adl_tag, kumi::function::indexes_for<T>{});
        return kumi::_::builder(KUMI_FWD(t), pos);
      }
    }
  };
  template<template<typename> typename Pred> inline constexpr partition_t<Pred> partition{};
  template<template<typename> typename Pred> inline constexpr filter_t<Pred> filter{};
  template<template<typename> typename Pred> inline constexpr filter_not_t<Pred> filter_not{};
  namespace result
  {
    template<template<typename> typename Pred, kumi::concepts::product_type T>
    using partition_t = decltype(kumi::partition<Pred>(std::declval<T>()));
    template<template<typename> typename Pred, kumi::concepts::product_type T> struct partition
    {
      using type = kumi::result::partition_t<Pred, T>;
    };
    template<template<typename> typename Pred, kumi::concepts::product_type T>
    using filter_t = decltype(kumi::filter<Pred>(std::declval<T>()));
    template<template<typename> typename Pred, kumi::concepts::product_type T> struct filter
    {
      using type = kumi::result::filter_t<Pred, T>;
    };
    template<template<typename> typename Pred, kumi::concepts::product_type T>
    using filter_not_t = decltype(kumi::filter_not<Pred>(std::declval<T>()));
    template<template<typename> typename Pred, kumi::concepts::product_type T> struct filter_not
    {
      using type = kumi::result::filter_not_t<Pred, T>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename Pred, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto all_of_(kumi::_::adl_tag_t, T&& t, Pred p, std::index_sequence<I...>)
    {
      return (kumi::invoke(p, get<I>(KUMI_FWD(t))) && ...);
    }
    template<typename T, typename Pred, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto any_of_(kumi::_::adl_tag_t, T&& t, Pred p, std::index_sequence<I...>)
    {
      return (kumi::invoke(p, get<I>(KUMI_FWD(t))) || ...);
    }
    template<typename T, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr std::size_t count_(kumi::_::adl_tag_t, T&& t, std::index_sequence<I...>)
    {
      return ((static_cast<bool>(get<I>(KUMI_FWD(t)))) + ... + 0ULL);
    }
    template<typename Pred, typename T, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr std::size_t count_if_(kumi::_::adl_tag_t, T&& t, Pred p, std::index_sequence<I...>)
    {
      [[maybe_unused]] constexpr std::size_t o = 1ULL;
      [[maybe_unused]] constexpr std::size_t z = 0ULL;
      return ((kumi::invoke(p, get<I>(KUMI_FWD(t))) ? o : z) + ... + z);
    }
  }
  struct all_of_t
  {
    template<typename Pred, kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, Pred p) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return true;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)), p);
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return kumi::invoke(p, get<0>(KUMI_FWD(t)));
      else return all_of_(kumi::_::adl_tag, KUMI_FWD(t), p, kumi::function::indexes_for<T>{});
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return true;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)));
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return !!get<0>(KUMI_FWD(t));
      else return (*this)(KUMI_FWD(t), kumi::function::identity);
    }
  };
  struct any_of_t
  {
    template<typename Pred, kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, Pred p) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return true;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)), p);
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return kumi::invoke(p, get<0>(KUMI_FWD(t)));
      else return any_of_(kumi::_::adl_tag, KUMI_FWD(t), p, kumi::function::indexes_for<T>{});
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return false;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)));
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return !!get<0>(KUMI_FWD(t));
      else return (*this)(KUMI_FWD(t), kumi::function::identity);
    }
  };
  struct none_of_t : private kumi::any_of_t
  {
    template<typename Pred, kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, Pred p) const noexcept
    {
      return !kumi::any_of_t::operator()(KUMI_FWD(t), p);
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      return !kumi::any_of_t::operator()(KUMI_FWD(t));
    }
  };
  struct count_if_t
  {
    template<typename Pred, kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr std::size_t operator()(T&& t, Pred p) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return 0ULL;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(values_of(KUMI_FWD(t)), p);
      else return count_if_(kumi::_::adl_tag, KUMI_FWD(t), p, kumi::function::indexes_for<T>{});
    }
  };
  struct count_t
  {
    template<kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr std::size_t operator()(T&& t) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return 0ULL;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(values_of(KUMI_FWD(t)));
      else return count_(kumi::_::adl_tag, KUMI_FWD(t), kumi::function::indexes_for<T>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr all_of_t all_of{};
  KUMI_VARIABLE_ABI constexpr any_of_t any_of{};
  KUMI_VARIABLE_ABI constexpr none_of_t none_of{};
  KUMI_VARIABLE_ABI constexpr count_if_t count_if{};
  KUMI_VARIABLE_ABI constexpr count_t count{};
}
namespace kumi
{
  namespace _
  {
    struct reindex_case_t
    {
      template<typename T, template<auto> class C, auto Old, auto P>
      KUMI_HIDDEN_ABI constexpr auto operator()(T&& t, C<Old>, kumi::projection_map<P>) const
      {
        if constexpr (kumi::concepts::projection_map<decltype(P)>) return C<P>{}(KUMI_FWD(t));
        else
        {
          static_assert(requires { get<P>(std::declval<T>()); }, "[KUMI] - Invalid projection for input type");
          return get<P>(KUMI_FWD(t));
        }
      }
    };
    KUMI_VARIABLE_ABI constexpr reindex_case_t reindex_case{};
    template<typename T, typename S, auto... E>
    KUMI_HIDDEN_ABI constexpr auto reindex_(kumi::_::adl_tag_t, T&& t, S self, kumi::projection_map<E...>)
    {
      return kumi::builder<T>::make(kumi::_::reindex_case(KUMI_FWD(t), self, kumi::projection_map<E>{})...);
    }
  }
  template<std::size_t... Idx> struct reorder_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      static_assert(((Idx < kumi::size_v<T>) && ...), "[KUMI] - Index out of bounds");
      return builder<T>::make(get<Idx>(KUMI_FWD(t))...);
    }
  };
  template<kumi::concepts::identifier auto... Name> struct reorder_fields_t
  {
    template<kumi::concepts::product_type Tuple> [[nodiscard]] KUMI_ABI constexpr auto operator()(Tuple&& t) const
    {
      static_assert((requires { get<Name>(std::declval<Tuple>()); } && ...),
                    "[KUMI] - Identifier not present in input type");
      return builder<Tuple>::make(Name = get<Name>(KUMI_FWD(t))...);
    }
  };
  template<kumi::concepts::projection_map auto Projections> struct reindex_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      using proj_t = std::remove_cvref_t<decltype(Projections)>;
      if constexpr (kumi::concepts::empty_product_type<T>) return builder<T>::make();
      else if constexpr (proj_t::size() == 0) return builder<T>::make();
      else return reindex_(kumi::_::adl_tag, KUMI_FWD(t), (*this), Projections);
    }
  };
  template<std::size_t... I> inline constexpr reorder_t<I...> reorder{};
  template<kumi::concepts::identifier auto... Name> inline constexpr reorder_fields_t<Name...> reorder_fields{};
  template<kumi::concepts::projection_map auto Projections> inline constexpr reindex_t<Projections> reindex{};
  namespace result
  {
    template<kumi::concepts::product_type T, std::size_t... Idx>
    using reorder_t = decltype(kumi::reorder<Idx...>(std::declval<T>()));
    template<kumi::concepts::product_type T, std::size_t... Idx> struct reorder
    {
      using type = kumi::result::reorder_t<T, Idx...>;
    };
    template<kumi::concepts::product_type Tuple, kumi::concepts::identifier auto... Name>
    using reorder_fields_t = decltype(kumi::reorder_fields<Name...>(std::declval<Tuple>()));
    template<kumi::concepts::product_type Tuple, kumi::concepts::identifier auto... Name> struct reorder_fields
    {
      using type = kumi::result::reorder_fields_t<Tuple, Name...>;
    };
    template<kumi::concepts::product_type T, kumi::concepts::projection_map auto Indexes>
    using reindex_t = decltype(kumi::reindex<Indexes>(std::declval<T>()));
    template<kumi::concepts::product_type T, kumi::concepts::projection_map auto Indexes> struct reindex
    {
      using type = kumi::result::reindex_t<T, Indexes>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t L, std::size_t R, typename M, typename T>
    KUMI_HIDDEN_ABI constexpr auto reduce_(kumi::_::adl_tag_t, M&& m, T&& t)
    {
      constexpr auto N = R - L;
      if constexpr (N == 1) return get<L>(KUMI_FWD(t));
      else
        return kumi::invoke(KUMI_FWD(m), reduce_<L, L + (N / 2)>(kumi::_::adl_tag, KUMI_FWD(m), KUMI_FWD(t)),
                            reduce_<L + (N / 2), R>(kumi::_::adl_tag, KUMI_FWD(m), KUMI_FWD(t)));
    }
    template<std::size_t L, std::size_t R, typename M, typename T, typename F>
    KUMI_HIDDEN_ABI constexpr auto map_reduce_(kumi::_::adl_tag_t, M&& m, T&& t, F f)
    {
      constexpr auto N = R - L;
      if constexpr (N == 1) return kumi::invoke(f, get<L>(KUMI_FWD(t)));
      else
        return kumi::invoke(KUMI_FWD(m), map_reduce_<L, L + (N / 2)>(kumi::_::adl_tag, KUMI_FWD(m), KUMI_FWD(t), f),
                            map_reduce_<L + (N / 2), R>(kumi::_::adl_tag, KUMI_FWD(m), KUMI_FWD(t), f));
    }
  }
  struct reduce_t
  {
    template<kumi::concepts::monoid M, kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(M&& m, T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return m.identity;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(KUMI_FWD(m), kumi::values_of(KUMI_FWD(t)));
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
      else return reduce_<0, kumi::size_v<T>>(kumi::_::adl_tag, KUMI_FWD(m), KUMI_FWD(t));
    }
    template<kumi::concepts::monoid M, kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(M&& m, T&& t, Value init) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return init;
      else return KUMI_FWD(m)(init, (*this)(KUMI_FWD(m), KUMI_FWD(t)));
    }
  };
  struct map_reduce_t
  {
    template<kumi::concepts::product_type T, kumi::concepts::monoid M, typename Function>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, M&& m, T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return m.identity;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(f, KUMI_FWD(m), kumi::values_of(KUMI_FWD(t)));
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return kumi::invoke(f, get<0>(KUMI_FWD(t)));
      else return map_reduce_<0, kumi::size_v<T>>(kumi::_::adl_tag, KUMI_FWD(m), KUMI_FWD(t), f);
    }
    template<kumi::concepts::monoid M, kumi::concepts::product_type T, typename Function, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, M&& m, T&& t, Value init) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return kumi::invoke(f, init);
      else return KUMI_FWD(m)(kumi::invoke(f, init), (*this)(f, KUMI_FWD(m), KUMI_FWD(t)));
    }
  };
  struct sum_t : private kumi::reduce_t
  {
    template<kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, Value init) const
    {
      return this->reduce_t::operator()(kumi::function::plus, KUMI_FWD(t), init);
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      return this->reduce_t::operator()(kumi::function::plus, KUMI_FWD(t));
    }
  };
  struct prod_t : private kumi::reduce_t
  {
    template<kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, Value init) const
    {
      return this->reduce_t::operator()(kumi::function::multiplies, KUMI_FWD(t), init);
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      return this->reduce_t::operator()(kumi::function::multiplies, KUMI_FWD(t));
    }
  };
  struct bit_and_t : private kumi::reduce_t
  {
    template<kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, Value init) const
    {
      return this->reduce_t::operator()(kumi::function::bit_and, KUMI_FWD(t), init);
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      return this->reduce_t::operator()(kumi::function::bit_and, KUMI_FWD(t));
    }
  };
  struct bit_or_t : private kumi::reduce_t
  {
    template<kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, Value init) const
    {
      return this->reduce_t::operator()(kumi::function::bit_or, KUMI_FWD(t), init);
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      return this->reduce_t::operator()(kumi::function::bit_or, KUMI_FWD(t));
    }
  };
  struct bit_xor_t : private kumi::reduce_t
  {
    template<kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, Value init) const
    {
      return this->reduce_t::operator()(kumi::function::bit_xor, KUMI_FWD(t), init);
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      return this->reduce_t::operator()(kumi::function::bit_xor, KUMI_FWD(t));
    }
  };
  KUMI_VARIABLE_ABI constexpr reduce_t reduce{};
  KUMI_VARIABLE_ABI constexpr map_reduce_t map_reduce{};
  KUMI_VARIABLE_ABI constexpr sum_t sum{};
  KUMI_VARIABLE_ABI constexpr prod_t prod{};
  KUMI_VARIABLE_ABI constexpr bit_and_t bit_and{};
  KUMI_VARIABLE_ABI constexpr bit_or_t bit_or{};
  KUMI_VARIABLE_ABI constexpr bit_xor_t bit_xor{};
  namespace result
  {
    template<kumi::concepts::monoid M, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using reduce_t = decltype(kumi::reduce(std::declval<M>(), std::declval<T>(), std::declval<Value>()...));
    template<kumi::concepts::monoid M, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct reduce
    {
      using type = kumi::result::reduce_t<M, T, Value...>;
    };
    template<typename F, kumi::concepts::monoid M, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using map_reduce_t =
      decltype(kumi::map_reduce(std::declval<F>(), std::declval<M>(), std::declval<T>(), std::declval<Value>()...));
    template<typename F, kumi::concepts::monoid M, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct map_reduce
    {
      using type = kumi::result::map_reduce_t<F, M, T, Value...>;
    };
    template<kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using sum_t = decltype(kumi::sum(std::declval<T>(), std::declval<Value>()...));
    template<kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct sum
    {
      using type = kumi::result::sum_t<T, Value...>;
    };
    template<kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using prod_t = decltype(kumi::prod(std::declval<T>(), std::declval<Value>()...));
    template<kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct prod
    {
      using type = kumi::result::prod_t<T, Value...>;
    };
    template<kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using bit_and_t = decltype(kumi::bit_and(std::declval<T>(), std::declval<Value>()...));
    template<kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct bit_and
    {
      using type = kumi::result::bit_and_t<T, Value...>;
    };
    template<kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using bit_or_t = decltype(kumi::bit_or(std::declval<T>(), std::declval<Value>()...));
    template<kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct bit_or
    {
      using type = kumi::result::bit_or_t<T, Value...>;
    };
    template<kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using bit_xor_t = decltype(kumi::bit_xor(std::declval<T>(), std::declval<Value>()...));
    template<kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct bit_xor
    {
      using type = kumi::result::bit_xor_t<T, Value...>;
    };
  }
}
namespace kumi
{
  struct reverse_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return builder<T>::make();
      else return kumi::_::builder(KUMI_FWD(t), kumi::function::reverse_index_sequence<kumi::size_v<T>>{});
    }
  };
  KUMI_VARIABLE_ABI constexpr reverse_t reverse{};
  namespace result
  {
    template<kumi::concepts::product_type T> using reverse_t = decltype(kumi::reverse(std::declval<T>()));
    template<kumi::concepts::product_type T> struct reverse
    {
      using type = kumi::result::reverse_t<T>;
    };
  }
}
namespace kumi
{
  template<std::size_t R> struct rotate_left_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else if constexpr ((R % kumi::size_v<T>) == 0) return KUMI_FWD(t);
      else
        return kumi::_::builder(KUMI_FWD(t),
                                kumi::function::rotate_index_sequence<R % kumi::size_v<T>, kumi::size_v<T>>{});
    }
  };
  template<std::size_t R> struct rotate_right_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else if constexpr ((R % kumi::size_v<T>) == 0) return KUMI_FWD(t);
      else
        return kumi::_::builder(
          KUMI_FWD(t),
          kumi::function::rotate_index_sequence<(kumi::size_v<T> - (R % kumi::size_v<T>)), kumi::size_v<T>>{});
    }
  };
  template<std::size_t R> inline constexpr rotate_left_t<R> rotate_left{};
  template<std::size_t R> inline constexpr rotate_right_t<R> rotate_right{};
  namespace result
  {
    template<std::size_t R, kumi::concepts::product_type T>
    using rotate_left_t = decltype(kumi::rotate_left<R>(std::declval<T>()));
    template<std::size_t R, kumi::concepts::product_type T> struct rotate_left
    {
      using type = kumi::result::rotate_left_t<R, T>;
    };
    template<std::size_t R, kumi::concepts::product_type T>
    using rotate_right_t = decltype(kumi::rotate_right<R>(std::declval<T>()));
    template<std::size_t R, kumi::concepts::product_type T> struct rotate_right
    {
      using type = kumi::result::rotate_right_t<R, T>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename V, typename F, typename O, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto inclusive_scan_left_(
      kumi::_::adl_tag_t, T&& t, V v, F f, O o, std::index_sequence<I...>)
    {
      return (kumi::function::scannable{o, kumi::invoke(f, v, get<0>(KUMI_FWD(t)))} >> ... >>
              kumi::bind_back(f, get<I + 1>(KUMI_FWD(t))))();
    }
    template<typename T, typename V, typename F, typename O, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto exclusive_scan_left_(
      kumi::_::adl_tag_t, T&& t, V v, F f, O o, std::index_sequence<I...>)
    {
      return (kumi::function::scannable{o, v} >> ... >> kumi::bind_back(f, get<I>(KUMI_FWD(t))))();
    }
    template<typename T, typename V, typename F, typename O, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto inclusive_scan_right_(
      kumi::_::adl_tag_t, T&& t, V v, F f, O o, std::index_sequence<I...>)
    {
      return (kumi::bind_front(f, get<I>(KUMI_FWD(t)))
              << ... << kumi::function::scannable{o, kumi::invoke(f, get<kumi::size_v<T> - 1>(KUMI_FWD(t)), v)})();
    }
    template<typename T, typename V, typename F, typename O, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto exclusive_scan_right_(
      kumi::_::adl_tag_t, T&& t, V v, F f, O o, std::index_sequence<I...>)
    {
      return (kumi::bind_front(f, get<I + 1>(KUMI_FWD(t))) << ... << kumi::function::scannable{o, v})();
    }
  }
  struct inclusive_scan_left_t
  {
    template<typename Function, kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t, Value init) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(f, kumi::values_of(KUMI_FWD(t)), init);
      else if constexpr (kumi::concepts::empty_product_type<T>) return kumi::tuple{};
      else if constexpr (kumi::concepts::sized_product_type<T, 1>)
        return kumi::tuple{kumi::invoke(f, init, get<0>(KUMI_FWD(t)))};
      else
      {
        return inclusive_scan_left_(kumi::_::adl_tag, KUMI_FWD(t), init, f, kumi::make_tuple,
                                    std::make_index_sequence<kumi::size_v<T> - 1>{});
      }
    }
    template<kumi::concepts::monoid M, kumi::concepts::sized_product_type_or_more<1> T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(M&& m, T&& t) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(KUMI_FWD(m), kumi::values_of(KUMI_FWD(t)));
      else return (*this)(KUMI_FWD(m), KUMI_FWD(t), m.identity);
    }
  };
  struct exclusive_scan_left_t
  {
    template<typename Function, kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t, Value init) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(f, kumi::values_of(KUMI_FWD(t)), init);
      else if constexpr (kumi::concepts::empty_product_type<T>) return kumi::tuple{};
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return kumi::tuple{init};
      else
      {
        return exclusive_scan_left_(kumi::_::adl_tag, KUMI_FWD(t), init, f, kumi::make_tuple,
                                    std::make_index_sequence<kumi::size_v<T> - 1>{});
      }
    }
    template<kumi::concepts::monoid M, kumi::concepts::sized_product_type_or_more<1> T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(M&& m, T&& t) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(KUMI_FWD(m), kumi::values_of(KUMI_FWD(t)));
      else return (*this)(KUMI_FWD(m), KUMI_FWD(t), m.identity);
    }
  };
  struct inclusive_scan_right_t
  {
    template<typename Function, kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t, Value init) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(KUMI_FWD(f), kumi::values_of(KUMI_FWD(t)), init);
      else if constexpr (kumi::concepts::empty_product_type<T>) return kumi::tuple{};
      else if constexpr (kumi::concepts::sized_product_type<T, 1>)
        return kumi::tuple{kumi::invoke(f, get<0>(KUMI_FWD(t)), init)};
      else
      {
        return inclusive_scan_right_(kumi::_::adl_tag, KUMI_FWD(t), init, f, kumi::make_tuple,
                                     std::make_index_sequence<kumi::size_v<T> - 1>{});
      }
    }
    template<kumi::concepts::monoid M, kumi::concepts::sized_product_type_or_more<1> T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(M&& m, T&& t) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(KUMI_FWD(m), kumi::values_of(KUMI_FWD(t)));
      else return (*this)(KUMI_FWD(m), KUMI_FWD(t), m.identity);
    }
  };
  struct exclusive_scan_right_t
  {
    template<typename Function, kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t, Value init) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(KUMI_FWD(f), kumi::values_of(KUMI_FWD(t)), init);
      else if constexpr (kumi::concepts::empty_product_type<T>) return kumi::tuple{};
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return kumi::tuple{init};
      else
      {
        return exclusive_scan_right_(kumi::_::adl_tag, KUMI_FWD(t), init, f, kumi::make_tuple,
                                     std::make_index_sequence<kumi::size_v<T> - 1>{});
      }
    }
    template<kumi::concepts::monoid M, kumi::concepts::sized_product_type_or_more<1> T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(M&& m, T&& t) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(KUMI_FWD(m), kumi::values_of(KUMI_FWD(t)));
      else return (*this)(KUMI_FWD(m), KUMI_FWD(t), m.identity);
    }
  };
  KUMI_VARIABLE_ABI constexpr inclusive_scan_left_t inclusive_scan_left{};
  KUMI_VARIABLE_ABI constexpr exclusive_scan_left_t exclusive_scan_left{};
  KUMI_VARIABLE_ABI constexpr inclusive_scan_right_t inclusive_scan_right{};
  KUMI_VARIABLE_ABI constexpr exclusive_scan_right_t exclusive_scan_right{};
  namespace result
  {
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using inclusive_scan_right_t =
      decltype(kumi::inclusive_scan_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()...));
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct inclusive_scan_right
    {
      using type = kumi::result::inclusive_scan_right_t<Function, T, Value...>;
    };
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using exclusive_scan_right_t =
      decltype(kumi::exclusive_scan_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()...));
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct exclusive_scan_right
    {
      using type = kumi::result::exclusive_scan_right_t<Function, T, Value...>;
    };
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using inclusive_scan_left_t =
      decltype(kumi::inclusive_scan_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()...));
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct inclusive_scan_left
    {
      using type = kumi::result::inclusive_scan_left_t<Function, T, Value...>;
    };
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    using exclusive_scan_left_t =
      decltype(kumi::exclusive_scan_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()...));
    template<typename Function, kumi::concepts::product_type T, typename... Value>
    requires((sizeof...(Value) == 0) || (sizeof...(Value) == 1))
    struct exclusive_scan_left
    {
      using type = kumi::result::exclusive_scan_left_t<Function, T, Value...>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t N, std::size_t O, std::size_t Sz, typename T, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto tiles_(kumi::_::adl_tag_t, T&& t, std::index_sequence<I...>)
    {
      return kumi::tuple{kumi::_::builder(
        KUMI_FWD(t), kumi::function::slice_index_sequence<I * O, (I * O + N < Sz) ? (I * O + N) : Sz>{})...};
    }
  }
  template<std::size_t N, std::size_t O> struct tiles_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      static_assert(N > 0 && N <= kumi::size_v<T>, "[KUMI] - Invalid tile size");
      if constexpr (N == kumi::size_v<T>) return kumi::make_tuple(t);
      else
      {
        constexpr auto range = std::make_index_sequence<1 + (kumi::size_v<T> - N + O - 1) / O>{};
        return kumi::_::tiles_<N, O, kumi::size_v<T>>(kumi::_::adl_tag, KUMI_FWD(t), range);
      }
    }
  };
  template<std::size_t N, std::size_t O> inline constexpr tiles_t<N, O> tiles{};
  template<std::size_t N> inline constexpr tiles_t<N, 1> windows{};
  template<std::size_t N> inline constexpr tiles_t<N, N> chunks{};
  namespace result
  {
    template<std::size_t N, std::size_t O, kumi::concepts::product_type T>
    using tiles_t = decltype(kumi::tiles<N, O>(std::declval<T>()));
    template<std::size_t N, std::size_t O, kumi::concepts::product_type T> struct tiles
    {
      using type = kumi::result::tiles_t<N, O, T>;
    };
    template<std::size_t N, kumi::concepts::product_type T>
    using windows_t = decltype(kumi::windows<N>(std::declval<T>()));
    template<std::size_t N, kumi::concepts::product_type T> struct windows
    {
      using type = kumi::result::windows_t<N, T>;
    };
    template<std::size_t N, kumi::concepts::product_type T>
    using chunks_t = decltype(kumi::chunks<N>(std::declval<T>()));
    template<std::size_t N, kumi::concepts::product_type T> struct chunks
    {
      using type = kumi::result::chunks_t<N, T>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, std::size_t... I, std::size_t... J>
    KUMI_HIDDEN_ABI constexpr decltype(auto) transpose_(kumi::_::adl_tag_t,
                                                        T&& t,
                                                        std::index_sequence<I...>,
                                                        std::index_sequence<J...> is)
    {
      return kumi::make_tuple(kumi::_::builder(KUMI_FWD(t), std::integral_constant<std::size_t, I>{}, is)...);
    }
  }
  struct transpose_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      static_assert(kumi::_::supports_transpose<T>, "[KUMI] - Cannot transpose given product type");
      if constexpr (kumi::concepts::empty_product_type<T>) return kumi::tuple{};
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)));
      else
      {
        constexpr std::size_t c = kumi::size_v<T>;
        constexpr std::size_t s = kumi::size_v<kumi::element_t<0, T>>;
        using outer = std::make_index_sequence<c>;
        using inner = std::make_index_sequence<s>;
        return transpose_(kumi::_::adl_tag, KUMI_FWD(t), inner{}, outer{});
      }
    }
  };
  KUMI_VARIABLE_ABI constexpr transpose_t transpose{};
  namespace result
  {
    template<kumi::concepts::product_type T> using transpose_t = decltype(kumi::transpose(std::declval<T>()));
    template<kumi::concepts::product_type T> struct transpose
    {
      using type = kumi::result::transpose_t<T>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, std::size_t... I>
    KUMI_HIDDEN_ABI consteval auto all_unique_(kumi::_::adl_tag_t, std::index_sequence<I...>) noexcept
    {
      using set = kumi::_::make_multiset_t<std::index_sequence<I...>, kumi::stored_element_t<I, T>...>;
      return kumi::function::unique_index_sequence<(set{}(std::type_identity<kumi::stored_element_t<I, T>>{}) ==
                                                    I)...>{};
    }
    template<typename T, std::size_t... I>
    KUMI_HIDDEN_ABI consteval auto unique_(kumi::_::adl_tag_t, std::index_sequence<I...>) noexcept
    {
      return kumi::function::adjacent_index_sequence<
        !std::is_same_v<kumi::stored_element_t<I, T>, kumi::stored_element_t<I + 1, T>>...>{};
    }
  }
  struct unique_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return KUMI_FWD(t);
      else
      {
        constexpr auto proj = unique_<T>(kumi::_::adl_tag, std::make_index_sequence<kumi::size_v<T> - 1>{});
        return kumi::_::builder(KUMI_FWD(t), proj);
      }
    }
  };
  struct all_unique_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return t;
      else
      {
        constexpr auto proj = all_unique_<T>(kumi::_::adl_tag, kumi::function::indexes_for<T>{});
        return kumi::_::builder(KUMI_FWD(t), proj);
      }
    }
  };
  KUMI_VARIABLE_ABI constexpr unique_t unique{};
  KUMI_VARIABLE_ABI constexpr all_unique_t all_unique{};
  namespace result
  {
    template<kumi::concepts::product_type T> using unique_t = decltype(kumi::unique(std::declval<T>()));
    template<kumi::concepts::product_type T> struct unique
    {
      using type = kumi::result::unique_t<T>;
    };
    template<kumi::concepts::product_type T> using all_unique_t = decltype(kumi::all_unique(std::declval<T>()));
    template<kumi::concepts::product_type T> struct all_unique
    {
      using type = kumi::result::all_unique_t<T>;
    };
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, std::size_t... I, std::size_t... J>
    KUMI_HIDDEN_ABI constexpr auto zip_(kumi::_::adl_tag_t,
                                        T&& t,
                                        std::index_sequence<I...>,
                                        std::index_sequence<J...> is)
    {
      return kumi::make_tuple(kumi::_::builder(KUMI_FWD(t), std::integral_constant<std::size_t, I>{}, is)...);
    }
    template<typename T, std::size_t N, std::size_t... I>
    KUMI_HIDDEN_ABI constexpr auto zip_intern_(T&& t, kumi::index_t<N>, std::index_sequence<I...>)
    {
      using U = kumi::common_product_type_t<std::remove_cvref_t<kumi::function::element_or_t<I, T, kumi::unit>>...>;
      return kumi::builder<U>::make(kumi::function::get_or<N>(get<I>(KUMI_FWD(t)), kumi::none)...);
    }
    template<typename T, std::size_t... I, std::size_t... J>
    KUMI_HIDDEN_ABI constexpr auto zip_max_(kumi::_::adl_tag_t,
                                            T&& t,
                                            std::index_sequence<I...>,
                                            std::index_sequence<J...> is)
    {
      return kumi::make_tuple(kumi::_::zip_intern_(KUMI_FWD(t), kumi::index<I>, is)...);
    }
  }
  struct zip_t
  {
    template<kumi::concepts::product_type T0, kumi::concepts::sized_product_type<kumi::size_v<T0>>... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T0&& t0, Ts&&... ts) const
    requires(kumi::concepts::follows_same_semantic<T0, Ts...>)
    {
      if constexpr (kumi::concepts::sized_product_type<T0, 0>) return kumi::tuple{};
      else
      {
        constexpr auto c = 1 + sizeof...(Ts);
        constexpr auto outer = std::make_index_sequence<c>{};
        constexpr auto inner = kumi::function::indexes_for<T0>{};
        return zip_(kumi::_::adl_tag, kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...), inner, outer);
      }
    }
  };
  struct zip_min_t
  {
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T0&& t0, Ts&&... ts) const
    requires(kumi::concepts::follows_same_semantic<T0, Ts...>)
    {
      constexpr std::size_t m = kumi::_::min(kumi::size_v<T0>, kumi::size_v<Ts>...);
      if constexpr (m == 0) return kumi::tuple{};
      else
      {
        constexpr std::size_t c = 1 + sizeof...(Ts);
        constexpr auto outer = std::make_index_sequence<c>{};
        constexpr auto inner = std::make_index_sequence<m>{};
        return zip_(kumi::_::adl_tag, kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...), inner, outer);
      }
    }
  };
  struct zip_max_t
  {
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T0&& t0, Ts&&... ts) const
    requires(kumi::concepts::follows_same_semantic<T0, Ts...>)
    {
      constexpr std::size_t m = kumi::_::max(kumi::size_v<T0>, kumi::size_v<Ts>...);
      if constexpr (m == 0) return kumi::tuple{};
      else
      {
        constexpr std::size_t c = 1 + sizeof...(Ts);
        constexpr auto outer = std::make_index_sequence<c>{};
        constexpr auto inner = std::make_index_sequence<m>{};
        return zip_max_(kumi::_::adl_tag, kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...), inner, outer);
      }
    }
  };
  KUMI_VARIABLE_ABI constexpr zip_t zip{};
  KUMI_VARIABLE_ABI constexpr zip_min_t zip_min{};
  KUMI_VARIABLE_ABI constexpr zip_max_t zip_max{};
  namespace result
  {
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts>
    using zip_t = decltype(kumi::zip(std::declval<T0>(), std::declval<Ts>()...));
    template<kumi::concepts::product_type T0, kumi::concepts::sized_product_type<kumi::size_v<T0>>... Ts> struct zip
    {
      using type = kumi::result::zip_t<T0, Ts...>;
    };
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts>
    using zip_min_t = decltype(kumi::zip_min(std::declval<T0>(), std::declval<Ts>()...));
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts> struct zip_min
    {
      using type = kumi::result::zip_min_t<T0, Ts...>;
    };
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts>
    using zip_max_t = decltype(kumi::zip_max(std::declval<T0>(), std::declval<Ts>()...));
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts> struct zip_max
    {
      using type = kumi::result::zip_max_t<T0, Ts...>;
    };
  }
}
#endif
