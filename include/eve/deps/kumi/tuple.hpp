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
  struct str;
  template<typename... Ts> struct tuple;
  template<typename... Ts> struct record;
  template<auto... Vs> struct projection_map;
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
#if defined(__EDG__) || defined(__EDG_VERSION__) || defined(__CUDACC__) || defined(__NVCC__)
#define KUMI_FWD(...) std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)
#else
#define KUMI_FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#endif
#if defined(__CUDACC__) || defined(__NVCC__)
#define KUMI_CUDA __host__ __device__
#else
#define KUMI_CUDA
#endif
#if defined(KUMI_DEBUG)
#define KUMI_ABI
#elif defined(__EDG__) || defined(__EDG_VERSION__) || defined(__CUDACC__) || defined(__NVCC__)
#define KUMI_ABI KUMI_CUDA inline
#elif defined(__GNUC__) || defined(__clang__)
#define KUMI_ABI [[using gnu: always_inline, flatten, artificial]] KUMI_CUDA inline
#elif defined(_MSC_VER)
#define KUMI_ABI [[using msvc: forceinline, flatten]] KUMI_CUDA inline
#endif
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wmissing-braces"
#endif
#include <cstddef>
#include <concepts>
#include <iosfwd>
#include <type_traits>
#include <utility>
namespace kumi::_
{
  KUMI_ABI consteval std::size_t min(std::same_as<std::size_t> auto... sizes)
  {
    std::size_t result = std::size_t(-1);
    return ((result = (result < sizes ? result : sizes)), ...);
  }
  KUMI_ABI consteval std::size_t max(std::same_as<std::size_t> auto... sizes)
  {
    std::size_t result{};
    return ((result = (result > sizes ? result : sizes)), ...);
  }
  struct container_of_index_t
  {
    KUMI_ABI consteval std::size_t operator()(std::size_t i, std::same_as<std::size_t> auto... sizes) const noexcept
    {
      std::size_t t{}, sum{};
      ((t += (i >= (sum += sizes))), ...);
      return t;
    }
  };
  struct element_of_index_t
  {
    KUMI_ABI consteval std::size_t operator()(std::size_t i, std::same_as<std::size_t> auto... sizes) const noexcept
    {
      std::size_t sum{}, offset{};
      ((offset = (i >= (sum += sizes) ? sum : offset)), ...);
      return i - offset;
    }
  };
  struct unflatten_index_t
  {
    KUMI_ABI consteval std::size_t operator()(std::size_t dim,
                                              std::size_t v,
                                              std::same_as<std::size_t> auto... sizes) const noexcept
    {
      std::size_t div = 1, curr_dim = 0, result = 0;
      (((curr_dim == dim ? (result = (v / div) % sizes) : 0), div *= sizes, curr_dim++), ...);
      return result;
    }
  };
  KUMI_ABI consteval std::size_t block_size(std::size_t I, std::size_t Stride, std::size_t Extent, std::size_t Size)
  {
    std::size_t s = I * Stride;
    return (s < Size) ? ((s + Extent > Size) ? (Size - s) : Extent) : 0;
  }
  struct digits_
  {
    template<typename F, std::size_t Base, std::size_t... Is>
    KUMI_ABI consteval auto operator()(F func,
                                       std::integral_constant<std::size_t, Base>,
                                       std::index_sequence<Is...>) const noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::index_sequence<func(I, Is...)...>{};
      }(std::make_index_sequence<Base>{});
    }
  };
  template<typename T, auto> struct repeat
  {
    using type = T;
  };
  template<typename T, auto I> using repeat_t = typename repeat<T, I>::type;
  template<typename T, auto N> struct as_homogeneous
  {
    template<std::size_t... I> static consteval auto homogeneify(std::index_sequence<I...>) -> tuple<repeat_t<T, I>...>;
    using type = std::remove_cvref_t<decltype(homogeneify(std::make_index_sequence<N>{}))>;
  };
  template<typename T, auto N> using as_homogeneous_t = typename as_homogeneous<T, N>::type;
  inline constexpr container_of_index_t container_of_index{};
  inline constexpr element_of_index_t element_of_index{};
  inline constexpr unflatten_index_t unflatten_index{};
  inline constexpr digits_ digits{};
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
#define KUMI_PP_REPEAT(N, m, d) KUMI_REPEAT_##N(m, d)
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
#define KUMI_PP_ENUM(N, m, d) KUMI_ENUM_##N(m, d)
#define KUMI_PP_CAT(P, S) P##S
#define KUMI_PP_TAC(P, S) S##P
#define KUMI_PP_IDENTITY(I, ...) I
#define KUMI_MEMBERS(N, _)                                                                                             \
  T##N member##N;                                                                                                      \
  using index##N = std::integral_constant<std::size_t, N>;                                                             \
  KUMI_ABI constexpr auto& operator()(index##N)& noexcept                                                              \
  {                                                                                                                    \
    return member##N;                                                                                                  \
  }                                                                                                                    \
  KUMI_ABI constexpr auto&& operator()(index##N)&& noexcept                                                            \
  {                                                                                                                    \
    return static_cast<T##N&&>(member##N);                                                                             \
  }                                                                                                                    \
  KUMI_ABI constexpr auto const&& operator()(index##N) const&& noexcept                                                \
  {                                                                                                                    \
    return static_cast<T##N const&&>(member##N);                                                                       \
  }                                                                                                                    \
  KUMI_ABI constexpr auto const& operator()(index##N) const& noexcept                                                  \
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
  if constexpr (field<T##N> && requires { member##N(I{}); }) return member##N(identifier_of_t<T##N>{});
#define KUMI_GET_NAME_RVALUE(N, I)                                                                                     \
  if constexpr (field<T##N> && requires { member##N(I{}); })                                                           \
    return static_cast<T##N&&>(member##N)(identifier_of_t<T##N>{});
#define KUMI_GET_NAME_CONST_RVALUE(N, I)                                                                               \
  if constexpr (field<T##N> && requires { member##N(I{}); })                                                           \
    return static_cast<T##N const&&>(member##N)(identifier_of_t<T##N>{});
#define KUMI_BINDER(N)                                                                                                 \
  template<KUMI_PP_ENUM(N, KUMI_PP_TAC, typename T)>                                                                   \
  requires(no_empty<KUMI_PP_ENUM(N, KUMI_PP_TAC, T)> && no_references<KUMI_PP_ENUM(N, KUMI_PP_TAC, T)>)                \
  struct binder<std::integer_sequence<int, KUMI_PP_ENUM(N, KUMI_PP_IDENTITY, _)>, KUMI_PP_ENUM(N, KUMI_PP_TAC, T)>     \
  {                                                                                                                    \
    static constexpr bool is_homogeneous = (N == 1);                                                                   \
    KUMI_PP_REPEAT(N, KUMI_MEMBERS, _)                                                                                 \
                                                                                                                       \
    template<typename T> KUMI_ABI constexpr auto& operator()(std::type_identity<T>) & noexcept                         \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_TYPE_LVALUE, T)                                                                       \
    }                                                                                                                  \
    template<typename T> KUMI_ABI constexpr auto&& operator()(std::type_identity<T>) && noexcept                       \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_TYPE_RVALUE, T)                                                                       \
    }                                                                                                                  \
    template<typename T> KUMI_ABI constexpr auto const&& operator()(std::type_identity<T>) const&& noexcept            \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_TYPE_CONST_RVALUE, T)                                                                 \
    }                                                                                                                  \
    template<typename T> KUMI_ABI constexpr auto const& operator()(std::type_identity<T>) const& noexcept              \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_TYPE_LVALUE, T)                                                                       \
    }                                                                                                                  \
                                                                                                                       \
    template<identifier I> KUMI_ABI constexpr auto& operator()(I) & noexcept                                           \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_LVALUE, I)                                                                       \
    }                                                                                                                  \
    template<identifier I> KUMI_ABI constexpr auto&& operator()(I) && noexcept                                         \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_RVALUE, I)                                                                       \
    }                                                                                                                  \
    template<identifier I> KUMI_ABI constexpr auto const&& operator()(I) const&& noexcept                              \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_CONST_RVALUE, I)                                                                 \
    }                                                                                                                  \
    template<identifier I> KUMI_ABI constexpr auto const& operator()(I) const& noexcept                                \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_LVALUE, I)                                                                       \
    }                                                                                                                  \
  };
namespace kumi::_
{
  template<auto ID> struct value
  {
    using type = decltype(ID);
  };
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
  template<typename T>
  concept valid_label = implicit_constructible<T> &&
                        (!requires { to_str(T{}); } || std::same_as<typename value<to_str(T{})>::type, kumi::str>);
  template<typename T>
  concept label = requires(T&& t) {
    typename std::remove_cvref_t<T>::type;
    { T::value } -> std::convertible_to<kumi::str>;
  };
  template<typename O>
  concept field = requires(O const& o) {
    typename std::remove_cvref_t<O>::type;
    typename std::remove_cvref_t<O>::identifier_type;
    typename std::remove_cvref_t<O>::label_type;
    { o(typename std::remove_cvref_t<O>::identifier_type{}) };
    { std::remove_cvref_t<O>::label() };
  };
  template<field T> struct identifier_of
  {
    using type = typename std::remove_cvref_t<T>::identifier_type;
  };
  template<field T> struct type_of
  {
    using type = typename std::remove_cvref_t<T>::type;
  };
  template<field T> struct label_of
  {
    using type = typename std::remove_cvref_t<T>::label_type;
  };
  template<field T> using identifier_of_t = typename identifier_of<std::remove_cvref_t<T>>::type;
  template<field T> using type_of_t = typename type_of<std::remove_cvref_t<T>>::type;
  template<field T> using label_of_t = typename label_of<std::remove_cvref_t<T>>::type;
  template<typename T>
  concept identifier = requires(T const& t) { typename std::remove_cvref_t<T>::type; };
  template<identifier T> struct tag_of
  {
    using type = typename std::remove_cvref_t<T>::type;
  };
  template<identifier T> using tag_of_t = typename tag_of<std::remove_cvref_t<T>>::type;
  template<typename From, typename To> struct is_piecewise_constructible : std::false_type
  {
  };
  template<typename From, typename To> struct is_piecewise_convertible : std::false_type
  {
  };
  template<typename From, typename To> struct is_piecewise_ordered : std::false_type
  {
  };
  template<typename From, typename To> struct is_piecewise_comparable : std::false_type
  {
  };
  template<template<class...> class Box, typename... From, typename... To>
  requires(sizeof...(From) == sizeof...(To))
  struct is_piecewise_convertible<Box<From...>, Box<To...>>
  {
    static constexpr bool value = (... && std::convertible_to<From, To>);
  };
  template<template<class...> class Box, typename... From, typename... To>
  requires(sizeof...(From) == sizeof...(To))
  struct is_piecewise_constructible<Box<From...>, Box<To...>>
  {
    static constexpr bool value = (... && std::is_constructible_v<To, From>);
  };
  template<template<class...> class Box, typename... From, typename... To>
  requires(sizeof...(From) == sizeof...(To))
  struct is_piecewise_ordered<Box<From...>, Box<To...>>
  {
    static constexpr bool value = (... && ordered<From, To>);
  };
  template<template<class...> class Box, typename... Ts, typename... Us>
  requires(sizeof...(Ts) == sizeof...(Us))
  struct is_piecewise_comparable<Box<Ts...>, Box<Us...>>
  {
    static constexpr bool value = (... && _::comparable<Ts, Us>);
  };
  template<typename From, typename To>
  concept piecewise_convertible = is_piecewise_convertible<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename From, typename To>
  concept piecewise_constructible =
    is_piecewise_constructible<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename From, typename To>
  concept piecewise_ordered = is_piecewise_ordered<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename From, typename To>
  concept piecewise_comparable = is_piecewise_comparable<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename Field> struct check_value
  {
    static consteval std::false_type get(...);
  };
  template<field F> struct check_value<F>
  {
    template<field T>
    requires(std::is_same_v<identifier_of_t<F>, identifier_of_t<T>>)
    static consteval type_of_t<F> get(T);
  };
  template<typename... Ts> struct sort : std::true_type
  {
  };
  template<template<class...> class Box, typename... Ts, typename... Us>
  requires(sizeof...(Ts) == sizeof...(Us))
  struct sort<Box<Ts...>, Box<Us...>> : check_value<Ts>...
  {
    using check_value<Ts>::get...;
    using t_list = Box<decltype(get(std::declval<Us>()))...>;
    using u_list = Box<decltype(get(std::declval<Us>()))...>;
    using is_fieldwise_constructible = is_piecewise_constructible<t_list, u_list>;
    using is_fieldwise_convertible = is_piecewise_convertible<t_list, u_list>;
    using is_fieldwise_comparable = is_piecewise_comparable<t_list, u_list>;
  };
  template<typename From, typename To>
  concept fieldwise_convertible =
    sort<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::is_fieldwise_convertible::value;
  template<typename From, typename To>
  concept fieldwise_constructible =
    sort<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::is_fieldwise_constructible::value;
  template<typename From, typename To>
  concept fieldwise_comparable =
    sort<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::is_fieldwise_comparable::value;
  struct find_failed
  {
    static consteval std::false_type get(...);
    static consteval invalid get_index(...);
  };
  template<template<class, class> class Matcher, std::size_t I, typename Ref, typename Field> struct match_node
  {
    static consteval std::false_type get();
    static consteval invalid get_index();
  };
  template<template<class, class> class Matcher, std::size_t I, typename Ref, typename Field>
  requires(Matcher<Ref, Field>::value)
  struct match_node<Matcher, I, Ref, Field>
  {
    using index = std::integral_constant<std::size_t, I>;
    static consteval Field get(Ref);
    static consteval index get_index(Ref);
  };
  template<template<class, class> class Matcher, typename Ref, typename Seq, typename... Fields> struct find_engine;
  template<template<class, class> class Matcher, typename Ref, std::size_t... I, typename... Fields>
  struct find_engine<Matcher, Ref, std::index_sequence<I...>, Fields...> : find_failed,
                                                                           match_node<Matcher, I, Ref, Fields>...
  {
    using find_failed::get;
    using find_failed::get_index;
    using match_node<Matcher, I, Ref, Fields>::get...;
    using match_node<Matcher, I, Ref, Fields>::get_index...;
    using type = decltype(get(std::declval<Ref>()));
    static constexpr auto value = decltype(get_index(std::declval<Ref>()))::value;
  };
  template<typename Ref, typename Field> struct match_by_type : std::is_same<Ref, Field>
  {
  };
  template<typename Ref, typename... Fields>
  using find_by_type_t = find_engine<match_by_type, Ref, std::index_sequence_for<Fields...>, Fields...>;
  template<typename Ref, typename... Fields> using get_field_by_type_t = typename find_by_type_t<Ref, Fields...>::type;
  template<typename Ref, typename... Fields>
  inline constexpr auto get_index_by_type_v = find_by_type_t<Ref, Fields...>::value;
  template<typename Ref, typename... Fields>
  concept can_get_field_by_type = !std::is_same_v<get_field_by_type_t<Ref, Fields...>, std::false_type>;
  template<typename Ref, typename Field> struct match_by_tag : std::false_type
  {
  };
  template<identifier Ref, field Field>
  struct match_by_tag<Ref, Field> : std::is_same<tag_of_t<Ref>, identifier_of_t<Field>>
  {
  };
  template<typename Ref, typename... Fields>
  using find_by_tag_t = find_engine<match_by_tag, Ref, std::index_sequence_for<Fields...>, Fields...>;
  template<typename Ref, typename... Fields> using get_field_by_value_t = typename find_by_tag_t<Ref, Fields...>::type;
  template<typename Ref, typename... Fields>
  inline constexpr auto get_index_by_value_v = find_by_tag_t<Ref, Fields...>::value;
  template<typename Ref, typename... Fields>
  concept can_get_field_by_value = !std::is_same_v<get_field_by_value_t<Ref, Fields...>, std::false_type>;
  template<typename Ref, typename Field> struct match_by_label : std::false_type
  {
  };
  template<label Ref, field Field> struct match_by_label<Ref, Field> : std::bool_constant<Ref::value == Field::label()>
  {
  };
  template<typename Ref, typename... Fields>
  using find_by_label_t = find_engine<match_by_label, Ref, std::index_sequence_for<Fields...>, Fields...>;
  template<typename Ref, typename... Fields>
  using get_field_by_label_t = typename find_by_label_t<Ref, Fields...>::type;
  template<typename Ref, typename... Fields>
  inline constexpr auto get_index_by_label_v = find_by_label_t<Ref, Fields...>::value;
  template<typename Ref, typename... Fields>
  concept can_get_field_by_label = !std::is_same_v<get_field_by_label_t<Ref, Fields...>, std::false_type>;
}
namespace kumi::_
{
  template<std::size_t I, typename T> consteval auto get_key()
  {
    using type = std::remove_cvref_t<T>;
    if constexpr (_::field<T>) return typename type::identifier_type{};
    else return std::integral_constant<std::size_t, I>{};
  }
  template<std::size_t, typename T> struct unique
  {
    operator std::type_identity<T>();
  };
  template<std::size_t I, typename T> struct unique_name
  {
    operator std::integral_constant<std::size_t, I>();
  };
  template<std::size_t I, _::field T> struct unique_name<I, T>
  {
    operator typename std::remove_cvref_t<T>::identifier_type();
  };
  inline consteval std::true_type true_fn(...);
}
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
    template<std::size_t N, std::size_t O, std::size_t... Is>
    requires(sizeof...(Is) <= max_size)
    constexpr str(char const (&s)[N], std::integral_constant<std::size_t, O>, std::index_sequence<Is...>)
      : data_{s[Is + O]...}, size_(sizeof...(Is))
    {
    }
    template<std::size_t N>
    requires(N <= max_size)
    constexpr str(char const (&s)[N]) : str{s, std::make_index_sequence<N>{}}
    {
    }
    template<std::size_t N, std::size_t P, std::size_t S>
    requires((N >= P + S) && ((N - P - S) <= max_size))
    constexpr str(char const (&s)[N],
                  std::integral_constant<std::size_t, P> prefix,
                  std::integral_constant<std::size_t, S>)
      : str{s, prefix, std::make_index_sequence<(N - 1) - P - S>{}}
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
  struct unknown
  {
    constexpr inline operator str() const noexcept { return str{"kumi::unknown"}; }
    KUMI_ABI friend constexpr auto operator<=>(unknown const&, unknown const&) noexcept = default;
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, unknown const&) noexcept
    {
      return os << "kumi::unknown";
    }
  };
  template<str... Strs>
  requires((Strs.size() + ... + sizeof...(Strs)) < str::max_size)
  [[nodiscard]] KUMI_ABI constexpr auto concatenate_str() noexcept
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
  }
}
namespace kumi::_
{
  template<typename T> constexpr auto typer() noexcept
  {
#if defined(__clang__)
    constexpr auto pfx = kumi::str{"auto kumi::_::typer() [T = "}.size();
    constexpr auto sfx = kumi::str{"]"}.size();
    constexpr auto value = kumi::str{__PRETTY_FUNCTION__, std::integral_constant<std::size_t, pfx>{},
                                     std::integral_constant<std::size_t, sfx>{}};
#elif defined(__GNUC__)
    constexpr auto pfx = kumi::str{"constexpr auto kumi::_::typer() [with T = "}.size();
    constexpr auto sfx = kumi::str{"]"}.size();
    constexpr auto value = kumi::str{__PRETTY_FUNCTION__, std::integral_constant<std::size_t, pfx>{},
                                     std::integral_constant<std::size_t, sfx>{}};
#elif defined(_MSC_VER)
    constexpr auto pfx = kumi::str{"auto __cdecl kumi::_::typer<"}.size();
    constexpr auto sfx = kumi::str{">(void)"}.size();
    constexpr auto value =
      kumi::str{__FUNCSIG__, std::integral_constant<std::size_t, pfx>{}, std::integral_constant<std::size_t, sfx>{}};
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
  template<valid_label T> consteval str make_str(T const& t)
  {
    if constexpr (requires { to_str(t); }) return to_str(t);
    else return typer<std::remove_cvref_t<T>>();
  }
}
namespace kumi
{
  template<typename Id, typename T> struct field
  {
    static constexpr auto label() { return _::make_str(Id{}); }
    using type = T;
    using identifier_type = Id;
    using inner_type = std::type_identity<T>;
    using label_type = std::integral_constant<kumi::str, label()>;
    T value;
    KUMI_ABI constexpr T& operator()(identifier_type) & noexcept { return value; }
    KUMI_ABI constexpr T&& operator()(identifier_type) && noexcept { return static_cast<T&&>(value); }
    KUMI_ABI constexpr T const& operator()(identifier_type) const& noexcept { return value; }
    KUMI_ABI constexpr T const&& operator()(identifier_type) const&& noexcept { return static_cast<T const&&>(value); }
    KUMI_ABI constexpr T& operator()(inner_type) & noexcept { return value; }
    KUMI_ABI constexpr T&& operator()(inner_type) && noexcept { return static_cast<T&&>(value); }
    KUMI_ABI constexpr T const& operator()(inner_type) const& noexcept { return value; }
    KUMI_ABI constexpr T const&& operator()(inner_type) const&& noexcept { return static_cast<T const&&>(value); }
    KUMI_ABI constexpr T& operator()(label_type) & noexcept { return value; }
    KUMI_ABI constexpr T&& operator()(label_type) && noexcept { return static_cast<T&&>(value); }
    KUMI_ABI constexpr T const& operator()(label_type) const& noexcept { return value; }
    KUMI_ABI constexpr T const&& operator()(label_type) const&& noexcept { return static_cast<T const&&>(value); }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, field const& w) noexcept
    {
      return os << _::make_str(std::remove_cvref_t<Id>{}) << " : " << _::make_streamable(w.value);
    }
  };
  template<typename Id, typename T>
  requires(std::is_empty_v<T>)
  struct field<Id, T> : T
  {
    static constexpr auto label() { return _::make_str(Id{}); }
    using type = T;
    using identifier_type = Id;
    using inner_type = std::type_identity<T>;
    using label_type = std::integral_constant<kumi::str, label()>;
    KUMI_ABI constexpr T& operator()(identifier_type) & noexcept { return *this; }
    KUMI_ABI constexpr T&& operator()(identifier_type) && noexcept { return static_cast<T&&>(*this); }
    KUMI_ABI constexpr T const& operator()(identifier_type) const& noexcept { return *this; }
    KUMI_ABI constexpr T const&& operator()(identifier_type) const&& noexcept { return static_cast<T const&&>(*this); }
    KUMI_ABI constexpr T& operator()(inner_type) & noexcept { return *this; }
    KUMI_ABI constexpr T&& operator()(inner_type) && noexcept { return static_cast<T&&>(*this); }
    KUMI_ABI constexpr T const& operator()(inner_type) const& noexcept { return *this; }
    KUMI_ABI constexpr T const&& operator()(inner_type) const&& noexcept { return static_cast<T const&&>(*this); }
    KUMI_ABI constexpr T& operator()(label_type) & noexcept { return *this; }
    KUMI_ABI constexpr T&& operator()(label_type) && noexcept { return static_cast<T&&>(*this); }
    KUMI_ABI constexpr T const& operator()(label_type) const& noexcept { return *this; }
    KUMI_ABI constexpr T const&& operator()(label_type) const&& noexcept { return static_cast<T const&&>(*this); }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, field const& w) noexcept
    {
      return os << _::make_str(std::remove_cvref_t<Id>{}) << " : "
                << _::make_streamable(w(_::identifier_of_t<decltype(w)>{}));
    }
  };
  template<typename Id, typename T>
  requires(!_::valid_label<Id>)
  struct field<Id, T>
  {
    field(T&&) = delete;
    static_assert(_::valid_label<Id>, "User defined to_str(...) function is not constexpr");
  };
  template<typename T> [[nodiscard]] KUMI_ABI consteval auto identifier_of() noexcept
  {
    if constexpr (_::field<T>) return _::identifier_of_t<T>{};
    else return kumi::unknown{};
  }
  template<typename T> [[nodiscard]] KUMI_ABI consteval str label_of() noexcept
  {
    if constexpr (_::field<T>) return _::label_of_t<T>{};
    else return kumi::unknown{};
  }
  template<typename T> [[nodiscard]] KUMI_ABI constexpr decltype(auto) field_value_of(T&& t) noexcept
  {
    if constexpr (_::field<T>) return (KUMI_FWD(t)(_::identifier_of_t<T>{}));
    else return KUMI_FWD(t);
  }
  template<_::identifier auto Name, typename T>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) capture_field(T&& t) noexcept
  {
    return field<decltype(Name), T>{KUMI_FWD(t)};
  }
  template<typename U, typename T> [[nodiscard]] KUMI_ABI constexpr decltype(auto) field_cast(T&& t) noexcept
  {
    if constexpr (_::field<U>)
      return field<_::identifier_of_t<T>, _::type_of_t<U>>{
        static_cast<_::type_of_t<U>>(KUMI_FWD(t)(_::identifier_of_t<T>{}))};
    else if constexpr (!_::field<T>) return static_cast<_::type_of_t<U>>(KUMI_FWD(t));
    else return field<_::identifier_of_t<T>, U>{static_cast<U>(KUMI_FWD(t)(_::identifier_of_t<T>{}))};
  }
  namespace result
  {
    template<typename T> struct identifier_of
    {
      using type = decltype(kumi::identifier_of<T>());
    };
    template<typename T> struct label_of
    {
      using type = decltype(kumi::label_of<T>());
    };
    template<typename T> struct field_value_of
    {
      using type = decltype(kumi::field_value_of(std::declval<T>()));
    };
    template<_::identifier auto Name, typename T> struct capture_field
    {
      using type = decltype(kumi::capture_field<Name>(std::declval<T>()));
    };
    template<typename U, typename T> struct field_cast
    {
      using type = decltype(kumi::field_cast<U, T>(std::declval<T>()));
    };
    template<typename T> using identifier_of_t = typename identifier_of<T>::type;
    template<typename T> using label_of_t = typename label_of<T>::type;
    template<typename T> using field_value_of_t = typename field_value_of<T>::type;
    template<_::identifier auto Name, typename T> using capture_field_t = typename capture_field<Name, T>::type;
    template<typename U, typename T> using field_cast_t = typename field_cast<U, T>::type;
  }
}
namespace kumi::_
{
  template<int N, typename T> struct leaf
  {
    T value;
    using index = std::integral_constant<std::size_t, N>;
    using inner_type = std::type_identity<T>;
    KUMI_ABI constexpr T& operator()(index) & noexcept { return value; }
    KUMI_ABI constexpr T&& operator()(index) && noexcept { return static_cast<T&&>(value); }
    KUMI_ABI constexpr T const&& operator()(index) const&& noexcept { return static_cast<T const&&>(value); }
    KUMI_ABI constexpr T const& operator()(index) const& noexcept { return value; }
    KUMI_ABI constexpr T& operator()(inner_type) & noexcept { return value; }
    KUMI_ABI constexpr T&& operator()(inner_type) && noexcept { return static_cast<T&&>(value); }
    KUMI_ABI constexpr T const&& operator()(inner_type) const&& noexcept { return static_cast<T const&&>(value); }
    KUMI_ABI constexpr T const& operator()(inner_type) const& noexcept { return value; }
  };
  template<int N, typename T>
  requires(std::is_empty_v<T> && (!field<T>))
  struct leaf<N, T> : T
  {
    using index = std::integral_constant<std::size_t, N>;
    using inner_type = std::type_identity<T>;
    KUMI_ABI constexpr T& operator()(index) & noexcept { return *this; }
    KUMI_ABI constexpr T&& operator()(index) && noexcept { return static_cast<T&&>(*this); }
    KUMI_ABI constexpr T const&& operator()(index) const&& noexcept { return static_cast<T const&&>(*this); }
    KUMI_ABI constexpr T const& operator()(index) const& noexcept { return *this; }
    KUMI_ABI constexpr T& operator()(inner_type) & noexcept { return *this; }
    KUMI_ABI constexpr T&& operator()(inner_type) && noexcept { return static_cast<T&&>(*this); }
    KUMI_ABI constexpr T const&& operator()(inner_type) const&& noexcept { return static_cast<T const&&>(*this); }
    KUMI_ABI constexpr T const& operator()(inner_type) const& noexcept { return *this; }
  };
  template<int N, field T> struct leaf<N, T> : T
  {
    using T::operator();
    using index = std::integral_constant<std::size_t, N>;
    using key = identifier_of_t<T>;
    using inner_type = type_of_t<T>;
    KUMI_ABI constexpr T& operator()(index) & noexcept { return *this; }
    KUMI_ABI constexpr T&& operator()(index) && noexcept { return static_cast<T&&>(*this); }
    KUMI_ABI constexpr T const&& operator()(index) const&& noexcept { return static_cast<T const&&>(*this); }
    KUMI_ABI constexpr T const& operator()(index) const& noexcept { return *this; }
  };
  template<typename ISeq, typename... Ts> struct binder;
  template<int... Is, typename... Ts> struct binder<std::integer_sequence<int, Is...>, Ts...> : leaf<Is, Ts>...
  {
    static constexpr bool is_homogeneous = false;
    using leaf<Is, Ts>::operator()...;
  };
  template<typename ISeq, typename... Ts> struct make_binder
  {
    using type = binder<ISeq, Ts...>;
  };
  template<typename ISeq, typename... Ts> using make_binder_t = typename make_binder<ISeq, Ts...>::type;
  template<typename... Ts> struct set : Ts...
  {
    using Ts::operator()...;
  };
  template<typename... Ts> struct make_set
  {
    using type = set<Ts...>;
  };
  template<typename... Ts> using make_set_t = typename make_set<Ts...>::type;
}
namespace kumi::_
{
  template<typename... Ts> inline constexpr bool no_references = (true && ... && !std::is_reference_v<Ts>);
  template<typename... Ts> inline constexpr bool no_empty = (true && ... && !std::is_empty_v<Ts>);
  template<typename T0, typename... Ts> inline constexpr bool all_the_same = (true && ... && std::is_same_v<T0, Ts>);
  template<typename T0, int N> struct binder_n
  {
    static constexpr bool is_homogeneous = true;
    T0 members[N];
    template<std::size_t I> KUMI_ABI constexpr auto& operator()(std::integral_constant<std::size_t, I>) & noexcept
    {
      return members[I];
    }
    template<std::size_t I>
    KUMI_ABI constexpr auto const& operator()(std::integral_constant<std::size_t, I>) const& noexcept
    {
      return members[I];
    }
    template<std::size_t I> KUMI_ABI constexpr auto&& operator()(std::integral_constant<std::size_t, I>) && noexcept
    {
      return static_cast<T0&&>(members[I]);
    }
    template<std::size_t I>
    KUMI_ABI constexpr auto const&& operator()(std::integral_constant<std::size_t, I>) const&& noexcept
    {
      return static_cast<T0 const&&>(members[I]);
    }
  };
  template<int... Is, typename T0, typename T1, typename... Ts>
  requires(all_the_same<T0, T1, Ts...> && no_references<T0, T1, Ts...> && no_empty<T0, T1, Ts...>)
  struct make_binder<std::integer_sequence<int, Is...>, T0, T1, Ts...>
  {
    using type = binder_n<T0, 2 + sizeof...(Ts)>;
  };
  FOR_LIST_OF_STRUCTS(KUMI_BINDER)
}
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
      { t.size() } -> std::convertible_to<std::size_t>;
      { t.begin() };
      { t.end() };
    };
    template<typename T>
    concept contiguous_container_like = container_like<T> && requires(T const& t) {
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
  template<typename T> struct size : std::tuple_size<std::remove_cvref_t<T>>
  {
  };
  template<typename T> inline constexpr auto size_v = size<T>::value;
  template<std::size_t I, typename T> struct element : std::tuple_element<I, std::remove_cvref_t<T>>
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
  template<typename T> struct is_container : std::false_type
  {
    using value_type = T;
    using size = _::invalid;
  };
  template<typename T>
  requires _::container_like<T>
  struct is_container<T> : std::true_type
  {
    using value_type = typename T::value_type;
    using size = _::invalid;
  };
  template<template<class, std::size_t> typename Container, typename T, std::size_t N>
  requires _::container_like<Container<T, N>> && (N != static_cast<std::size_t>(-1))
  struct is_container<Container<T, N>> : std::true_type
  {
    using value_type = T;
    using size = std::integral_constant<std::size_t, N>;
  };
  template<typename T, std::size_t N> struct is_container<T[N]> : std::true_type
  {
    using value_type = T;
    using size = std::integral_constant<std::size_t, N>;
  };
  template<typename T> inline constexpr auto is_container_v = is_container<T>::value;
  template<typename T> struct container_size : is_container<std::remove_cvref_t<T>>::size
  {
  };
  template<typename T> inline constexpr auto container_size_v = container_size<T>::value;
  template<typename T> struct container_type : is_container<std::remove_cvref_t<T>>
  {
    using type = typename is_container<std::remove_cvref_t<T>>::value_type;
  };
  template<typename T> using container_type_t = typename container_type<T>::type;
}
namespace kumi
{
  template<typename T> struct is_homogeneous : std::false_type
  {
  };
  template<typename T>
  requires(is_product_type_v<T>)
  struct is_homogeneous<T>
  {
    static consteval bool check()
    {
      if constexpr (requires { T::is_homogeneous; }) return T::is_homogeneous;
      else if constexpr (is_record_type_v<T>) return false;
      else if constexpr (is_container_v<T>) return true;
      else if constexpr (size_v<T> == 0) return false;
      else if constexpr (size_v<T> == 1) return true;
      else
        return []<std::size_t... I>(std::index_sequence<I...>) {
          return _::all_the_same<element_t<I, T>...>;
        }(std::make_index_sequence<size_v<T>>{});
    }
    static constexpr bool value = check();
  };
  template<typename T> inline constexpr auto is_homogeneous_v = is_homogeneous<T>::value;
  template<typename T> struct has_static_size : std::false_type
  {
  };
  template<typename T>
  requires(_::contiguous_container_like<T>)
  struct has_static_size<T>
  {
    static constexpr bool value = !std::same_as<typename is_container<T>::size, _::invalid>;
  };
  template<typename T, std::size_t N> struct has_static_size<T[N]> : std::true_type
  {
  };
  template<typename T> inline constexpr auto has_static_size_v = has_static_size<T>::value;
  template<typename T> struct is_projection_map : std::false_type
  {
  };
  template<typename T>
  requires(T::is_projection_map)
  struct is_projection_map<T> : std::true_type
  {
  };
  template<typename T> inline constexpr auto is_projection_map_v = is_projection_map<T>::value;
  template<std::size_t I, typename T> struct stored_member
  {
    using type = member_t<I, T>;
  };
  template<std::size_t I, typename T>
  requires(is_record_type<std::remove_cvref_t<T>>::value)
  struct stored_member<I, T>
  {
    using field_type = decltype(get<I>(std::declval<T&&>()));
    using type = decltype(std::declval<field_type&&>()(typename std::remove_cvref_t<field_type>::identifier_type{}));
  };
  template<std::size_t I, typename T> using stored_member_t = typename stored_member<I, T>::type;
  template<std::size_t I, typename T> struct stored_element
  {
    using type = element_t<I, T>;
  };
  template<std::size_t I, typename T>
  requires(is_record_type<std::remove_cvref_t<T>>::value)
  struct stored_element<I, T>
  {
    using type = typename element_t<I, T>::type;
  };
  template<std::size_t I, typename T> using stored_element_t = typename stored_element<I, T>::type;
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
    using type = decltype(is_set(std::type_identity<Ts>{}...));
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
    using type = decltype(is_set(_::get_key<Ints, Ts>()...));
  };
  template<typename... Ts>
  using all_unique_names_t = typename all_unique_names<std::index_sequence_for<Ts...>, Ts...>::type;
  template<typename... Ts> inline constexpr auto all_unique_names_v = all_unique_names_t<Ts...>::value;
  template<template<typename...> typename Traits,
           typename Tuple,
           typename Seq = std::make_index_sequence<size_v<Tuple>>>
  requires is_product_type_v<std::remove_cvref_t<Tuple>>
  struct apply_traits;
  template<template<typename...> typename Traits, typename Tuple, std::size_t... Is>
  requires is_product_type_v<std::remove_cvref_t<Tuple>> &&
           (requires { typename Traits<element_t<Is, Tuple>...>::type; })
  struct apply_traits<Traits, Tuple, std::index_sequence<Is...>>
  {
    using type = typename Traits<element_t<Is, Tuple>...>::type;
  };
  template<template<typename...> typename Traits, typename Tuple>
  requires is_product_type_v<std::remove_cvref_t<Tuple>>
  using apply_traits_t = typename apply_traits<Traits, Tuple>::type;
  template<template<typename...> typename Traits,
           typename Tuple,
           typename Seq = std::make_index_sequence<size_v<Tuple>>>
  requires is_product_type_v<std::remove_cvref_t<Tuple>>
  struct map_traits;
  template<template<typename...> typename Traits, typename Tuple, std::size_t... Is>
  requires is_product_type_v<std::remove_cvref_t<Tuple>> &&
           (requires { typename Traits<element_t<Is, Tuple>>::type; } && ...)
  struct map_traits<Traits, Tuple, std::index_sequence<Is...>>
  {
    using type = tuple<typename Traits<element_t<Is, Tuple>>::type...>;
  };
  template<template<typename...> typename Traits, typename Tuple>
  requires is_product_type_v<std::remove_cvref_t<Tuple>>
  using map_traits_t = typename map_traits<Traits, Tuple>::type;
}
namespace kumi
{
#ifndef KUMI_DOXYGEN_INVOKED
  template<typename T>
  requires(_::std_tuple_compatible<T>)
  struct is_product_type<T> : std::true_type
  {
  };
  template<typename T>
  requires(is_container_v<T> && has_static_size_v<T> && _::std_tuple_compatible<T>)
  struct is_product_type<T> : std::true_type
  {
  };
  template<std::size_t... I> struct is_projection_map<std::index_sequence<I...>> : std::true_type
  {
  };
  template<typename T> struct is_kumi_tuple : std::false_type
  {
  };
  template<typename... Ts> struct is_kumi_tuple<kumi::tuple<Ts...>> : std::true_type
  {
  };
  template<typename T> inline constexpr bool is_kumi_tuple_v = is_kumi_tuple<T>::value;
  template<typename T> struct is_kumi_record : std::false_type
  {
  };
  template<typename... Ts> struct is_kumi_record<kumi::record<Ts...>> : std::true_type
  {
  };
  template<typename T> inline constexpr bool is_kumi_record_v = is_kumi_record<T>::value;
#endif
}
namespace kumi
{
  template<typename... Ts> struct common_product_type
  {
  };
  template<typename... Ts> using common_product_type_t = typename common_product_type<Ts...>::type;
  template<typename T> struct builder;
  template<typename T> struct builder<T&> : builder<T>
  {
  };
  template<typename T> struct builder<T&&> : builder<T>
  {
  };
  template<typename T> struct builder<T const&> : builder<T>
  {
  };
  template<typename T> struct builder<T const&&> : builder<T>
  {
  };
  template<typename T> using builder_t = typename builder<T>::type;
  template<typename T, typename... Args> using builder_make_t = typename builder<T>::template to<Args...>;
}
namespace kumi
{
  namespace _
  {
    template<typename F, typename T>
    concept supports_apply = []<std::size_t... N>(std::index_sequence<N...>) {
      return std::invocable<F, stored_member_t<N, T>...>;
    }(std::make_index_sequence<size_v<T>>{});
    template<typename F, typename T>
    concept supports_nothrow_apply = []<std::size_t... N>(std::index_sequence<N...>) {
      return std::is_nothrow_invocable_v<F, stored_member_t<N, T>...>;
    }(std::make_index_sequence<size_v<T>>{});
    template<typename F, typename... Ts>
    concept supports_call = []<std::size_t... I>(std::index_sequence<I...>) {
      return ([]<std::size_t J>(std::integral_constant<std::size_t, J>) {
        return std::invocable<F, stored_member_t<J, Ts>...>;
      }(std::integral_constant<std::size_t, I>{}) &&
              ...);
    }(std::make_index_sequence<(size_v<Ts>, ...)>{});
    template<typename T>
    concept supports_transpose = (size_v<T> <= 1) || ([]<std::size_t... N>(std::index_sequence<N...>) {
                                   return ((size_v<stored_member_t<0, T>> == size_v<stored_member_t<N + 1, T>>) && ...);
                                 }(std::make_index_sequence<size_v<T> - 1>{}));
    template<typename Ints, typename... Ts> struct matches;
    template<> struct matches<std::index_sequence<>>
    {
      using type = std::true_type;
    };
    template<std::size_t... Is, template<class...> class Box, typename... Ts, typename... Us>
    struct matches<std::index_sequence<Is...>, Box<Ts...>, Box<Us...>>
    {
      struct match : _::unique_name<Is, Us>...
      {
      };
      template<typename... Key>
      static consteval auto is_present(Key...) -> decltype(_::true_fn(static_cast<Key>(match())...));
      static consteval std::false_type is_present(...);
      using type = decltype(is_present(_::get_key<Is, Ts>()...));
    };
    template<std::size_t S, typename T, typename U>
    using matches_t = typename matches<std::make_index_sequence<S>, T, U>::type;
    template<typename T, typename U> inline constexpr auto matches_v = matches_t<size_v<T>, T, U>::value;
  }
  namespace concepts
  {
    template<typename T>
    concept product_type = is_product_type<std::remove_cvref_t<T>>::value;
    template<typename T>
    concept record_type = product_type<T> && is_record_type<std::remove_cvref_t<T>>::value;
    template<typename T>
    concept container = is_container_v<std::remove_cvref_t<T>>;
    template<typename T>
    concept static_container = container<T> && has_static_size_v<std::remove_cvref_t<T>>;
    template<typename T>
    concept unit_type = (product_type<T> && (size_v<T> == 0)) || std::is_null_pointer_v<std::remove_cvref_t<T>>;
    template<typename T>
    concept index = requires(T const& t) {
      { T::value } -> std::convertible_to<std::size_t>;
    };
    template<typename T>
    concept field = kumi::_::field<T>;
    template<typename T>
    concept identifier = kumi::_::identifier<T>;
    template<typename T>
    concept projection_map = is_projection_map_v<std::remove_cvref_t<T>>;
    template<typename T>
    concept projection = projection_map<T> || identifier<T> || index<T>;
    template<typename T, std::size_t N>
    concept sized_product_type = product_type<T> && (size_v<T> == N);
    template<typename T, std::size_t N>
    concept sized_product_type_or_more = product_type<T> && (size_v<T> >= N);
    template<typename T>
    concept empty_product_type = product_type<T> && (size_v<T> == 0);
    template<typename T>
    concept non_empty_product_type = product_type<T> && (size_v<T> != 0);
    template<typename T>
    concept homogeneous_product_type = product_type<T> && is_homogeneous_v<std::remove_cvref_t<T>>;
    template<typename... Ts>
    concept has_named_fields = (... || field<Ts>);
    template<typename... Ts>
    concept fully_named = (... && field<Ts>);
    template<typename... Ts>
    concept uniquely_typed =
      (sizeof...(Ts) == 0) || (!has_named_fields<Ts...> && all_uniques_v<std::remove_cvref_t<Ts>...>);
    template<typename... Ts>
    concept uniquely_named =
      (sizeof...(Ts) == 0) || (has_named_fields<Ts...> && all_unique_names_v<std::remove_cvref_t<Ts>...>);
    template<typename... Ts>
    concept uniquely_labeled =
      (sizeof...(Ts) == 0) || (fully_named<Ts...> && (all_uniques_v<_::value<std::remove_cvref_t<Ts>::label()>...>));
    template<typename T, typename... Ts>
    concept contains_type = kumi::_::can_get_field_by_type<T, Ts...>;
    template<typename Name, typename... Ts>
    concept contains_identifier = identifier<Name> && kumi::_::can_get_field_by_value<Name, Ts...>;
    template<typename Label, typename... Ts>
    concept contains_label = std::is_same_v<std::remove_cvref_t<decltype(std::remove_cvref_t<Label>::value)>, str> &&
                             kumi::_::can_get_field_by_label<std::remove_cvref_t<Label>, Ts...>;
    template<typename T, typename U>
    concept equivalent = (size_v<T> == size_v<U>) && _::matches_v<std::remove_cvref_t<T>, std::remove_cvref_t<U>>;
    template<typename T, typename U>
    concept equality_comparable =
      equivalent<T, U> && ((product_type<T> && product_type<U> && _::piecewise_comparable<T, U>) ||
                           (record_type<T> && record_type<U> && _::fieldwise_comparable<T, U>));
    template<typename... Ts>
    concept follows_same_semantic = ((product_type<Ts> && !record_type<Ts>) && ...) || ((record_type<Ts> && ...));
    template<typename T, typename... Us>
    concept compatible_product_types =
      (follows_same_semantic<T, Us...> && ((!record_type<T>) || (equivalent<T, Us> && ...)));
    template<typename M>
    concept monoid = requires {
      { std::remove_cvref_t<M>::identity };
      { std::remove_cvref_t<M>{}(std::remove_cvref_t<M>::identity, std::remove_cvref_t<M>::identity) };
    };
    template<typename Type, typename T>
    concept queryable_by_type = product_type<T> && []<std::size_t... I>(std::index_sequence<I...>) {
      return _::can_get_field_by_type<Type, stored_element_t<I, T>...>;
    }(std::make_index_sequence<size_v<T>>{});
    template<typename Id, typename T>
    concept queryable_by_identifier =
      identifier<Id> && product_type<T> && []<std::size_t... I>(std::index_sequence<I...>) {
        return _::can_get_field_by_value<Id, element_t<I, T>...>;
      }(std::make_index_sequence<size_v<T>>{});
    template<typename L, typename T>
    concept queryable_by_label = _::label<L> && product_type<T> && []<std::size_t... I>(std::index_sequence<I...>) {
      return _::can_get_field_by_label<L, element_t<I, T>...>;
    }(std::make_index_sequence<size_v<T>>{});
  }
}
namespace kumi
{
  struct unit
  {
    KUMI_ABI friend constexpr auto operator<=>(unit, unit) noexcept = default;
    template<typename T>
    [[nodiscard]] KUMI_ABI constexpr operator T() const noexcept
    requires(concepts::unit_type<T>)
    {
      return {};
    }
    template<typename T>
    [[nodiscard]] KUMI_ABI constexpr operator T() noexcept
    requires(concepts::unit_type<T>)
    {
      return {};
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, unit) noexcept
    {
      return os << '\'' << "none" << '\'';
    }
  };
  inline constexpr unit none = {};
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
  template<typename T> inline constexpr only_t<T> only = {};
  template<template<class> typename Traits> inline constexpr traits_check<Traits> if_ = {};
  template<typename ID, typename Check = void> struct identifier;
  template<typename ID> struct identifier<ID, void>
  {
    using type = std::remove_cvref_t<ID>;
    constexpr identifier() noexcept {}
    constexpr identifier(ID const&) noexcept {}
    template<typename T> constexpr field<type, std::unwrap_ref_decay_t<T>> operator=(T&& v) const noexcept
    {
      return {KUMI_FWD(v)};
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         identifier const&) noexcept
    {
      return os << _::make_str(type{});
    }
  };
  template<typename ID, typename Checker> struct identifier
  {
    using type = identifier<ID, Checker>;
    friend constexpr str to_str(identifier<ID, Checker> const&) { return _::make_str(ID{}); }
    constexpr identifier() noexcept {}
    constexpr identifier([[maybe_unused]] ID const& id, [[maybe_unused]] Checker const& check) noexcept {}
    template<typename T>
    requires(Checker::template value<T>)
    constexpr auto operator=(T&& v) const noexcept -> field<type, std::unwrap_ref_decay_t<T>>
    {
      return {KUMI_FWD(v)};
    }
    template<typename T>
    requires(!Checker::template value<T>)
    constexpr field<type, std::unwrap_ref_decay_t<T>> operator=(T&& v) const = delete;
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         identifier const& id) noexcept
    {
      return os << _::make_str(id);
    }
  };
  template<typename ID> identifier(ID const&) -> identifier<ID, void>;
  template<typename ID, typename Checker> identifier(ID const&, Checker const&) -> identifier<ID, Checker>;
  template<str ID> struct name
  {
    using type = name<ID>;
    friend constexpr str to_str(name<ID> const&) { return ID; }
    template<typename T> constexpr auto operator=(T&& v) const noexcept -> field<type, std::unwrap_ref_decay_t<T>>
    {
      return {KUMI_FWD(v)};
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, name const&) noexcept
    {
      return os << ID;
    }
  };
  template<concepts::identifier L, kumi::concepts::identifier R> KUMI_ABI constexpr bool operator==(L const&, R const&)
  {
    return std::same_as<std::remove_cvref_t<L>, std::remove_cvref_t<R>>;
  }
  namespace _
  {
    template<auto N, typename... Ts> KUMI_ABI constexpr auto contains_identifier()
    {
      if constexpr (std::integral<std::remove_cvref_t<decltype(N)>>) return false;
      else if constexpr (concepts::index<decltype(N)>) return false;
      else if constexpr (concepts::identifier<std::remove_cvref_t<decltype(N)>>) return false;
      else return can_get_field_by_value<name<N>, Ts...>;
    }
    template<auto N, typename... Ts> KUMI_ABI constexpr auto contains_label()
    {
      if constexpr (std::integral<std::remove_cvref_t<decltype(N)>>) return false;
      else if constexpr (concepts::index<decltype(N)>) return false;
      else if constexpr (!std::is_same_v<std::remove_cvref_t<decltype(N)>, str>) return false;
      else return can_get_field_by_label<std::integral_constant<kumi::str, N>, Ts...>;
    }
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
  template<str Label> struct label_t
  {
    using type = str;
    static constexpr str value = Label;
    constexpr inline operator str() const noexcept { return Label; }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, label_t const&) noexcept
    {
      return os << value;
    }
  };
  template<str Label> inline constexpr label_t<Label> label = {};
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
    template<kumi::str ID> constexpr auto operator""_id() noexcept
    {
      return name<ID>{};
    }
    template<kumi::str ID> constexpr auto operator""_l() noexcept
    {
      return label<ID>;
    }
  }
  template<template<class> class Pred> [[nodiscard]] constexpr auto predicate() noexcept
  {
    return []<typename T>(T const&) constexpr { return Pred<T>::value; };
  }
  template<typename U, concepts::product_type T>
  KUMI_ABI consteval auto get_index_of_type()
  requires(concepts::queryable_by_type<U, T>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return _::get_index_by_type_v<U, stored_element_t<I, T>...>;
    }(std::make_index_sequence<size_v<T>>{});
  }
  template<concepts::identifier Id, concepts::product_type T>
  KUMI_ABI consteval auto get_index_of_field()
  requires(concepts::queryable_by_identifier<Id, T>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return _::get_index_by_value_v<Id, element_t<I, T>...>;
    }(std::make_index_sequence<size_v<T>>{});
  }
  template<str L, concepts::product_type T>
  KUMI_ABI consteval auto get_index_of_label()
  requires(concepts::queryable_by_label<label_t<L>, T>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return _::get_index_by_label_v<label_t<L>, element_t<I, T>...>;
    }(std::make_index_sequence<size_v<T>>{});
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t I, typename T> struct value_at
    {
    };
    template<std::size_t I, auto Head, auto... Tail>
    struct value_at<I, kumi::projection_map<Head, Tail...>> : value_at<I - 1, kumi::projection_map<Tail...>>
    {
    };
    template<std::size_t I, auto... Vs> struct value_at<I, kumi::projection_map<Vs...> const>
    {
      static constexpr auto value = value_at<I, kumi::projection_map<Vs...>>::value;
    };
    template<auto Head, auto... Tail> struct value_at<0, kumi::projection_map<Head, Tail...>>
    {
      static constexpr auto value = Head;
    };
  }
  template<auto... V> struct projection_map
  {
    static constexpr bool is_projection_map = true;
    consteval projection_map() noexcept = default;
    consteval explicit projection_map(auto...) noexcept {}
    [[nodiscard]] KUMI_ABI static constexpr auto size() noexcept { return sizeof...(V); }
    [[nodiscard]] KUMI_ABI static constexpr auto empty() noexcept { return sizeof...(V) == 0; }
    template<std::size_t I>
    requires(I < sizeof...(V))
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] index_t<I> i) const noexcept
    {
      return _::value_at<I, projection_map>::value;
    }
    template<std::size_t I>
    requires(I < sizeof...(V))
    [[nodiscard]] KUMI_ABI friend constexpr decltype(auto) get(projection_map const& pm) noexcept
    {
      return pm[index<I>];
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
  template<concepts::projection... Ts> KUMI_CUDA projection_map(Ts...) -> projection_map<Ts{}...>;
  template<concepts::index... Ts> [[nodiscard]] KUMI_ABI consteval auto indexes(Ts...) noexcept
  {
    return projection_map<Ts{}...>{};
  }
  template<std::convertible_to<std::size_t> auto... vs> [[nodiscard]] KUMI_ABI consteval auto make_indexes() noexcept
  {
    return projection_map<index<vs>...>{};
  }
  template<concepts::identifier... Ts>
  requires(all_uniques_v<Ts...>)
  [[nodiscard]] KUMI_ABI consteval auto identifiers(Ts...) noexcept
  {
    return projection_map<Ts{}...>{};
  }
  template<auto... Vs>
  requires(!concepts::projection<decltype(Vs)> && ...)
  struct projection_map<Vs...>
  {
    static_assert((concepts::projection<decltype(Vs)> && ...), "Invalid projections in projection_map definition");
    projection_map(decltype(Vs)...) = delete;
  };
}
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
  template<typename... Ts> struct tuple
  {
    using binder_t = _::make_binder_t<std::make_integer_sequence<int, sizeof...(Ts)>, Ts...>;
    static constexpr bool is_homogeneous = binder_t::is_homogeneous;
    binder_t impl;
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] index_t<I> i) & noexcept
    requires(I < sizeof...(Ts))
    {
      return impl(std::integral_constant<std::size_t, I>{});
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) && noexcept
    requires(I < sizeof...(Ts))
    {
      return static_cast<decltype(impl)&&>(impl)(std::integral_constant<std::size_t, I>{});
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) const&& noexcept
    requires(I < sizeof...(Ts))
    {
      return static_cast<decltype(impl) const&&>(impl)(std::integral_constant<std::size_t, I>{});
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) const& noexcept
    requires(I < sizeof...(Ts))
    {
      return impl(std::integral_constant<std::size_t, I>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] as<T> type) & noexcept
    requires(concepts::uniquely_typed<Ts...> && concepts::contains_type<T, Ts...>)
    {
      return impl(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](as<T>) && noexcept
    requires(concepts::uniquely_typed<Ts...> && concepts::contains_type<T, Ts...>)
    {
      return static_cast<decltype(impl)&&>(impl)(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](as<T>) const&& noexcept
    requires(concepts::uniquely_typed<Ts...> && concepts::contains_type<T, Ts...>)
    {
      return static_cast<decltype(impl) const&&>(impl)(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](as<T>) const& noexcept
    requires(concepts::uniquely_typed<Ts...> && concepts::contains_type<T, Ts...>)
    {
      return impl(std::type_identity<T>{});
    }
    template<str L>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] label_t<L> s) & noexcept
    requires(concepts::contains_label<label_t<L>, Ts...>)
    {
      return impl(std::integral_constant<str, L>{});
    }
    template<str L>
    KUMI_ABI constexpr decltype(auto) operator[](label_t<L>) && noexcept
    requires(concepts::contains_label<label_t<L>, Ts...>)
    {
      return static_cast<decltype(impl)&&>(impl)(std::integral_constant<str, L>{});
    }
    template<str L>
    KUMI_ABI constexpr decltype(auto) operator[](label_t<L>) const&& noexcept
    requires(concepts::contains_label<label_t<L>, Ts...>)
    {
      return static_cast<decltype(impl) const&&>(impl)(std::integral_constant<str, L>{});
    }
    template<str L>
    KUMI_ABI constexpr decltype(auto) operator[](label_t<L>) const& noexcept
    requires(concepts::contains_label<label_t<L>, Ts...>)
    {
      return impl(std::integral_constant<str, L>{});
    }
    template<concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) & noexcept
    requires(concepts::uniquely_named<Ts...> && concepts::contains_identifier<Id, Ts...>)
    {
      return impl(_::tag_of_t<Id>{});
    }
    template<concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) && noexcept
    requires(concepts::uniquely_named<Ts...> && concepts::contains_identifier<Id, Ts...>)
    {
      return static_cast<decltype(impl)&&>(impl)(_::tag_of_t<Id>{});
    }
    template<concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) const&& noexcept
    requires(concepts::uniquely_named<Ts...> && concepts::contains_identifier<Id, Ts...>)
    {
      return static_cast<decltype(impl) const&&>(impl)(_::tag_of_t<Id>{});
    }
    template<concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) const& noexcept
    requires(concepts::uniquely_named<Ts...> && concepts::contains_identifier<Id, Ts...>)
    {
      return impl(_::tag_of_t<Id>{});
    }
    [[nodiscard]] KUMI_ABI static constexpr auto size() noexcept { return sizeof...(Ts); }
    [[nodiscard]] KUMI_ABI static constexpr bool empty() noexcept { return sizeof...(Ts) == 0; }
    [[nodiscard]] KUMI_ABI static constexpr auto identifiers() noexcept { return kumi::tuple{identifier_of<Ts>()...}; }
    [[nodiscard]] KUMI_ABI static constexpr auto labels() noexcept { return kumi::tuple{label_of<Ts>()...}; }
    template<typename... Us>
    [[nodiscard]] KUMI_ABI explicit(!_::piecewise_convertible<tuple<Ts const&...>, tuple<Us...>>) constexpr
    operator tuple<Us...>() const
    requires(sizeof...(Us) == sizeof...(Ts)) && (!std::same_as<tuple<Ts...>, tuple<Us...>>)
#ifndef KUMI_DOXYGEN_INVOKED
            && (_::piecewise_constructible<tuple<Ts const&...>, tuple<Us...>>)
#endif
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<Us...>{static_cast<Us>(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    [[nodiscard]] KUMI_ABI explicit(!_::piecewise_convertible<tuple<Ts&...>, tuple<Us...>>) constexpr operator tuple<
      Us...>()
    requires(sizeof...(Us) == sizeof...(Ts)) && (!std::same_as<tuple<Ts...>, tuple<Us...>>)
#ifndef KUMI_DOXYGEN_INVOKED
            && (_::piecewise_constructible<tuple<Ts&...>, tuple<Us...>>)
#endif
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<Us...>{static_cast<Us>(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    KUMI_ABI constexpr tuple& operator=(tuple<Us...> const& other)
#ifndef KUMI_DOXYGEN_INVOKED
    requires(_::piecewise_convertible<tuple, tuple<Us...>>)
#endif
    {
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((get<I>(*this) = get<I>(other)), ...);
      }(std::make_index_sequence<sizeof...(Ts)>{});
      return *this;
    }
    template<typename... Us>
    KUMI_ABI constexpr tuple& operator=(tuple<Us...>&& other)
#ifndef KUMI_DOXYGEN_INVOKED
    requires(_::piecewise_convertible<tuple, tuple<Us...>>)
#endif
    {
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((get<I>(*this) = get<I>(KUMI_FWD(other))), ...);
      }(std::make_index_sequence<sizeof...(Ts)>{});
      return *this;
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator==(tuple const& self, tuple<Us...> const& other) noexcept
    requires(concepts::equality_comparable<tuple, tuple<Us...>>)
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return ((get<I>(self) == get<I>(other)) && ...);
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator!=(tuple const& self, tuple<Us...> const& other) noexcept
    requires(concepts::equality_comparable<tuple, tuple<Us...>>)
    {
      return !(self == other);
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator<(tuple const& lhs, tuple<Us...> const& rhs) noexcept
    requires(sizeof...(Ts) == sizeof...(Us))
#ifndef KUMI_DOXYGEN_INVOKED
            && (_::piecewise_ordered<tuple, tuple<Us...>>)
#endif
    {
      auto res = get<0>(lhs) < get<0>(rhs);
      auto const order = [&]<typename Index>(Index i) {
        auto y_less_x_prev = rhs[i] < lhs[i];
        auto x_less_y = lhs[index_t<Index::value + 1>{}] < rhs[index_t<Index::value + 1>{}];
        return x_less_y && !y_less_x_prev;
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (res || ... || order(index_t<I>{}));
      }(std::make_index_sequence<sizeof...(Ts) - 1>{});
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
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, tuple const& t) noexcept
    {
      os << "( ";
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((os << _::make_streamable(t[index<I>]) << ", "), ...);
      }(std::make_index_sequence<size_v<tuple> - 1>{});
      os << _::make_streamable(t[index<size_v<tuple> - 1>]) << " )";
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
    [[nodiscard]] KUMI_ABI constexpr operator T() const noexcept
    requires(concepts::unit_type<T>)
    {
      return {};
    }
    template<typename T>
    [[nodiscard]] KUMI_ABI constexpr operator T() noexcept
    requires(concepts::unit_type<T>)
    {
      return {};
    }
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
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto to_ref(T&& t)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::forward_as_tuple(get<I>(KUMI_FWD(t))...);
    }(std::make_index_sequence<size_v<T>>{});
  }
  template<typename Type, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto from_tuple(tuple<Ts...> const& t)
  requires(!concepts::product_type<Type> && _::implicit_constructible<Type, Ts...>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return Type{get<I>(t)...};
    }(std::make_index_sequence<sizeof...(Ts)>{});
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto to_tuple(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple{get<I>(KUMI_FWD(t))...};
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<concepts::static_container S>
  [[nodiscard]] KUMI_ABI constexpr auto to_tuple(S&& s)
  requires(!concepts::product_type<S>)
  {
    constexpr auto N = container_size_v<S>;
    if constexpr (N == 0) return tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple{KUMI_FWD(s)[I]...};
      }(std::make_index_sequence<N>{});
  }
  namespace _
  {
    template<concepts::product_type T, typename IndexSequence, template<typename...> class Meta = std::type_identity>
    struct as_tuple;
    template<concepts::product_type T, std::size_t... I> struct as_tuple<T, std::index_sequence<I...>>
    {
      using type = tuple<element_t<I, T>...>;
    };
    template<concepts::product_type T, std::size_t... I, template<typename...> class Meta>
    struct as_tuple<T, std::index_sequence<I...>, Meta>
    {
      using type = tuple<typename Meta<element_t<I, T>>::type...>;
    };
  }
  template<typename T, template<typename...> class Meta = std::type_identity> struct as_tuple;
  template<typename T, template<typename...> class Meta>
  requires(concepts::product_type<T>)
  struct as_tuple<T, Meta> : _::as_tuple<T, std::make_index_sequence<size_v<T>>, Meta>
  {
  };
  template<typename T, template<typename...> class Meta>
  requires(!concepts::product_type<T>)
  struct as_tuple<T, Meta>
  {
    using type = tuple<typename Meta<T>::type>;
  };
  template<typename T, template<typename...> class Meta = std::type_identity>
  using as_tuple_t = typename as_tuple<T, Meta>::type;
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto members_of(as<T>) noexcept
  {
    if constexpr (concepts::sized_product_type<T, 0>) return tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple{identifier_of<element_t<I, T>>()...};
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto values_of(T&& t) noexcept
  {
    if constexpr (concepts::sized_product_type<T, 0>) return tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<result::field_value_of_t<member_t<I, T>>...>{field_value_of(get<I>(KUMI_FWD(t)))...};
      }(std::make_index_sequence<size_v<T>>{});
  }
  namespace result
  {
    template<concepts::product_type T> struct members_of
    {
      using type = decltype(kumi::members_of(as<T>{}));
    };
    template<concepts::product_type T> struct values_of
    {
      using type = decltype(kumi::values_of(std::declval<T>()));
    };
    template<concepts::product_type T> using members_of_t = typename members_of<T>::type;
    template<concepts::product_type T> using values_of_t = typename values_of<T>::type;
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  requires(I < sizeof...(Ts))
  {
    return t[index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& arg) noexcept
  requires(I < sizeof...(Ts))
  {
    return static_cast<tuple<Ts...>&&>(arg)[index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& arg) noexcept
  requires(I < sizeof...(Ts))
  {
    return arg[index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& arg) noexcept
  requires(I < sizeof...(Ts))
  {
    return static_cast<tuple<Ts...> const&&>(arg)[index<I>];
  }
  template<str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  requires(concepts::uniquely_named<Ts...> && _::contains_label<L, Ts...>())
  {
    return t[label<L>];
  }
  template<str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& t) noexcept
  requires(concepts::uniquely_named<Ts...> && _::contains_label<L, Ts...>())
  {
    return static_cast<tuple<Ts...>&&>(t)[label<L>];
  }
  template<str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& t) noexcept
  requires(concepts::uniquely_named<Ts...> && _::contains_label<L, Ts...>())
  {
    return t[label<L>];
  }
  template<str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& t) noexcept
  requires(concepts::uniquely_named<Ts...> && _::contains_label<L, Ts...>())
  {
    return static_cast<tuple<Ts...> const&&>(t)[label<L>];
  }
  template<concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  requires(concepts::uniquely_named<Ts...> && concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return t[Id];
  }
  template<concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& t) noexcept
  requires(concepts::uniquely_named<Ts...> && concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return static_cast<tuple<Ts...>&&>(t)[Id];
  }
  template<concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& t) noexcept
  requires(concepts::uniquely_named<Ts...> && concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return t[Id];
  }
  template<concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& t) noexcept
  requires(concepts::uniquely_named<Ts...> && concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return static_cast<tuple<Ts...> const&&>(t)[Id];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>& t) noexcept
  requires(concepts::uniquely_typed<Ts...> && concepts::contains_type<T, Ts...>)
  {
    return t[as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...>&& t) noexcept
  requires(concepts::uniquely_typed<Ts...> && concepts::contains_type<T, Ts...>)
  {
    return static_cast<tuple<Ts...>&&>(t)[as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const& t) noexcept
  requires(concepts::uniquely_typed<Ts...> && concepts::contains_type<T, Ts...>)
  {
    return t[as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(tuple<Ts...> const&& t) noexcept
  requires(concepts::uniquely_typed<Ts...> && concepts::contains_type<T, Ts...>)
  {
    return static_cast<tuple<Ts...> const&&>(t)[as<T>{}];
  }
#ifndef KUMI_DOXYGEN_INVOKED
  template<std::size_t I, typename T>
  requires(is_kumi_tuple_v<std::remove_cvref_t<T>> && (I >= size_v<T>))
  constexpr auto get(T&& r) = delete;
  template<str S, typename T>
  requires(is_kumi_tuple_v<std::remove_cvref_t<T>> && !_::contains_identifier<S, T>())
  constexpr auto get(T&& t) = delete;
  template<concepts::identifier auto S, typename T>
  requires(is_kumi_tuple_v<std::remove_cvref_t<T>> && !concepts::contains_identifier<decltype(S), T>)
  constexpr auto get(T&& t) = delete;
  template<typename U, typename T>
  requires(is_kumi_tuple_v<std::remove_cvref_t<T>> && !concepts::contains_type<U, T>)
  constexpr auto get(T&& t) = delete;
#endif
  template<concepts::product_type T>
  requires(!concepts::record_type<T>)
  struct builder<T>
  {
    using type = T;
    template<typename... Us> using to = kumi::tuple<Us...>;
    template<typename... Args> static constexpr auto make(Args&&... args)
    {
      return kumi::make_tuple(KUMI_FWD(args)...);
    }
    template<typename... Args> static constexpr auto build(Args&&... args) { return kumi::tuple{KUMI_FWD(args)...}; }
  };
  template<concepts::product_type... Ts>
  requires(!concepts::record_type<Ts> && ...)
  struct common_product_type<Ts...>
  {
    using type = kumi::tuple<>;
  };
}
namespace kumi
{
  template<typename... Ts> struct record
  {
    using is_record_type = void;
    using set_t = _::make_set_t<Ts...>;
    static constexpr bool is_homogeneous = false;
    set_t impl;
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] index_t<I> i) & noexcept
    requires(I < sizeof...(Ts))
    {
      using T = element_t<I, tuple<Ts...>>;
      return static_cast<T&>(impl);
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) && noexcept
    requires(I < sizeof...(Ts))
    {
      using T = element_t<I, tuple<Ts...>>;
      return static_cast<T&&>(static_cast<decltype(impl)&&>(impl));
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) const&& noexcept
    requires(I < sizeof...(Ts))
    {
      using T = element_t<I, tuple<Ts...>>;
      return static_cast<T const&&>(static_cast<decltype(impl) const&&>(impl));
    }
    template<std::size_t I>
    KUMI_ABI constexpr decltype(auto) operator[](index_t<I>) const& noexcept
    requires(I < sizeof...(Ts))
    {
      using T = element_t<I, tuple<Ts...>>;
      return static_cast<T const&>(impl);
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] as<T> type) & noexcept
    requires(concepts::uniquely_typed<_::type_of_t<Ts>...> && concepts::contains_type<T, _::type_of_t<Ts>...>)
    {
      return impl(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](as<T>) && noexcept
    requires(concepts::uniquely_typed<_::type_of_t<Ts>...> && concepts::contains_type<T, _::type_of_t<Ts>...>)
    {
      return static_cast<decltype(impl)&&>(impl)(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](as<T>) const&& noexcept
    requires(concepts::uniquely_typed<_::type_of_t<Ts>...> && concepts::contains_type<T, _::type_of_t<Ts>...>)
    {
      return static_cast<decltype(impl) const&&>(impl)(std::type_identity<T>{});
    }
    template<typename T>
    KUMI_ABI constexpr decltype(auto) operator[](as<T>) const& noexcept
    requires(concepts::uniquely_typed<_::type_of_t<Ts>...> && concepts::contains_type<T, _::type_of_t<Ts>...>)
    {
      return impl(std::type_identity<T>{});
    }
    template<str Name>
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] label_t<Name> l) & noexcept
    requires(concepts::contains_label<label_t<Name>, Ts...>)
    {
      return impl(std::integral_constant<str, Name>{});
    }
    template<str Name>
    KUMI_ABI constexpr decltype(auto) operator[](label_t<Name>) && noexcept
    requires(concepts::contains_label<label_t<Name>, Ts...>)
    {
      return static_cast<decltype(impl)&&>(impl)(std::integral_constant<str, Name>{});
    }
    template<str Name>
    KUMI_ABI constexpr decltype(auto) operator[](label_t<Name>) const&& noexcept
    requires(concepts::contains_label<label_t<Name>, Ts...>)
    {
      return static_cast<decltype(impl) const&&>(impl)(std::integral_constant<str, Name>{});
    }
    template<str Name>
    KUMI_ABI constexpr decltype(auto) operator[](label_t<Name>) const& noexcept
    requires(concepts::contains_label<label_t<Name>, Ts...>)
    {
      return impl(std::integral_constant<str, Name>{});
    }
    template<concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) & noexcept
    requires(concepts::contains_identifier<Id, Ts...>)
    {
      return impl(_::tag_of_t<Id>{});
    }
    template<concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) && noexcept
    requires(concepts::contains_identifier<Id, Ts...>)
    {
      return static_cast<decltype(impl)&&>(impl)(_::tag_of_t<Id>{});
    }
    template<concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) const&& noexcept
    requires(concepts::contains_identifier<Id, Ts...>)
    {
      return static_cast<decltype(impl) const&&>(impl)(_::tag_of_t<Id>{});
    }
    template<concepts::identifier Id>
    KUMI_ABI constexpr decltype(auto) operator[](Id const&) const& noexcept
    requires(concepts::contains_identifier<Id, Ts...>)
    {
      return impl(_::tag_of_t<Id>{});
    }
    [[nodiscard]] KUMI_ABI static constexpr auto size() noexcept { return sizeof...(Ts); }
    [[nodiscard]] KUMI_ABI static constexpr bool empty() noexcept { return sizeof...(Ts) == 0; }
    [[nodiscard]] KUMI_ABI static constexpr auto identifiers() noexcept { return tuple{identifier_of<Ts>()...}; }
    [[nodiscard]] KUMI_ABI static constexpr auto labels() noexcept { return tuple{label_of<Ts>()...}; }
    [[nodiscard]] KUMI_ABI constexpr auto values() noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<stored_member_t<I, decltype(*this)>...>{field_value_of(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    [[nodiscard]] KUMI_ABI constexpr auto values() const noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<stored_member_t<I, decltype(*this)>...>{field_value_of(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    KUMI_ABI constexpr record& operator=(record<Us...> const& other)
    requires(concepts::equivalent<record, record<Us...>>)
#ifndef KUMI_DOXYGEN_INVOKED
            && (_::fieldwise_convertible<record, record<Us...>>)
#endif
    {
      ((get<identifier_of<Ts>()>(*this) = get<identifier_of<Ts>()>(KUMI_FWD(other))), ...);
      return *this;
    }
    template<typename... Us>
    KUMI_ABI constexpr record& operator=(record<Us...>&& other)
    requires(concepts::equivalent<record, record<Us...>>)
#ifndef KUMI_DOXYGEN_INVOKED
            && (_::fieldwise_convertible<record, record<Us...>>)
#endif
    {
      ((get<identifier_of<Ts>()>(*this) = get<identifier_of<Ts>()>(KUMI_FWD(other))), ...);
      return *this;
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator==(record const& self, record<Us...> const& other) noexcept
    requires(concepts::equality_comparable<record, record<Us...>>)
    {
      return ((get<identifier_of<Ts>()>(self) == get<identifier_of<Ts>()>(other)) && ...);
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator!=(record const& self, record<Us...> const& other) noexcept
    requires(concepts::equality_comparable<record, record<Us...>>)
    {
      return !(self == other);
    }
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         record const& t) noexcept
    {
      os << "{ ";
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((os << t[index<I>] << ", "), ...);
      }(std::make_index_sequence<size_v<record> - 1>{});
      os << t[index<size_v<record> - 1>] << " }";
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
    [[nodiscard]] KUMI_ABI constexpr operator T() const noexcept
    requires(concepts::unit_type<T>)
    {
      return {};
    }
    template<typename T>
    [[nodiscard]] KUMI_ABI constexpr operator T() noexcept
    requires(concepts::unit_type<T>)
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
  requires(!concepts::uniquely_named<Ts...> || !concepts::fully_named<Ts...> || !concepts::uniquely_labeled<Ts...>)
  struct record<Ts...>
  {
    static_assert(concepts::uniquely_named<Ts...>, "Duplicate fields in record definition");
    static_assert(concepts::uniquely_labeled<Ts...>, "Duplicate identifier representation in record definition");
    static_assert(concepts::fully_named<Ts...>, "Anonymous field usage in record definition");
    record(Ts&&...) = delete;
  };
  template<typename... Ts> KUMI_CUDA record(Ts&&...) -> record<std::unwrap_ref_decay_t<Ts>...>;
  template<concepts::identifier auto... Fields, typename... Ts>
  KUMI_ABI constexpr auto tie(Ts&... ts) -> record<field<decltype(Fields), Ts&>...>
  requires(sizeof...(Fields) == sizeof...(Ts))
  {
    return {ts...};
  }
  template<concepts::identifier auto... Fields, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto forward_as_record(Ts&&... ts) -> record<field<decltype(Fields), Ts&&>...>
  requires(sizeof...(Fields) == sizeof...(Ts))
  {
    return {KUMI_FWD(ts)...};
  }
  template<typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto make_record(Ts&&... ts) -> record<std::unwrap_ref_decay_t<Ts>...>
  requires(concepts::uniquely_named<Ts...> && concepts::fully_named<Ts...>)
  {
    return {KUMI_FWD(ts)...};
  }
  template<concepts::record_type R> [[nodiscard]] KUMI_ABI constexpr auto to_ref(R&& r)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::forward_as_record<identifier_of<element_t<I, R>>()...>(field_value_of(get<I>(KUMI_FWD(r)))...);
    }(std::make_index_sequence<size_v<R>>{});
  }
  template<concepts::record_type Type, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto from_record(record<Ts...> const& r)
  requires(concepts::equivalent<typename _::as_tuple<Type, std::make_index_sequence<size_v<Type>>>::type, tuple<Ts...>>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return Type{get<identifier_of<element_t<I, Type>>()>(r)...};
    }(std::make_index_sequence<size_v<Type>>());
  }
  template<concepts::record_type Type> [[nodiscard]] KUMI_ABI constexpr auto to_record(Type&& r)
  {
    if constexpr (concepts::empty_product_type<Type>) return kumi::record{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return record{
          capture_field<identifier_of<element_t<I, Type>>()>(get<identifier_of<element_t<I, Type>>()>(KUMI_FWD(r)))...};
      }(std::make_index_sequence<size_v<Type>>{});
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>& r) noexcept
  requires(I < sizeof...(Ts))
  {
    return r[index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>&& r) noexcept
  requires(I < sizeof...(Ts))
  {
    return static_cast<record<Ts...>&&>(r)[index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const& r) noexcept
  requires(I < sizeof...(Ts))
  {
    return r[index<I>];
  }
  template<std::size_t I, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const&& r) noexcept
  requires(I < sizeof...(Ts))
  {
    return static_cast<record<Ts...> const&&>(r)[index<I>];
  }
  template<str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>& r) noexcept
  requires(_::contains_label<L, Ts...>())
  {
    return r[label<L>];
  }
  template<str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>&& r) noexcept
  requires(_::contains_label<L, Ts...>())
  {
    return static_cast<record<Ts...>&&>(r)[label<L>];
  }
  template<str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const& r) noexcept
  requires(_::contains_label<L, Ts...>())
  {
    return r[label<L>];
  }
  template<str L, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const&& r) noexcept
  requires(_::contains_label<L, Ts...>())
  {
    return static_cast<record<Ts...> const&&>(r)[label<L>];
  }
  template<concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>& r) noexcept
  requires(concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return r[Id];
  }
  template<concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>&& r) noexcept
  requires(concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return static_cast<record<Ts...>&&>(r)[Id];
  }
  template<concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const& r) noexcept
  requires(concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return r[Id];
  }
  template<concepts::identifier auto Id, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const&& r) noexcept
  requires(concepts::contains_identifier<decltype(Id), Ts...>)
  {
    return static_cast<record<Ts...> const&&>(r)[Id];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>& r) noexcept
  requires(concepts::uniquely_typed<_::type_of_t<Ts>...> && concepts::contains_type<T, _::type_of_t<Ts>...>)
  {
    return r[as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...>&& r) noexcept
  requires(concepts::uniquely_typed<_::type_of_t<Ts>...> && concepts::contains_type<T, _::type_of_t<Ts>...>)
  {
    return static_cast<record<Ts...>&&>(r)[as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const& r) noexcept
  requires(concepts::uniquely_typed<_::type_of_t<Ts>...> && concepts::contains_type<T, _::type_of_t<Ts>...>)
  {
    return r[as<T>{}];
  }
  template<typename T, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr decltype(auto) get(record<Ts...> const&& r) noexcept
  requires(concepts::uniquely_typed<_::type_of_t<Ts>...> && concepts::contains_type<T, _::type_of_t<Ts>...>)
  {
    return static_cast<record<Ts...> const&&>(r)[as<T>{}];
  }
#ifndef KUMI_DOXYGEN_INVOKED
  template<std::size_t I, typename R>
  requires(is_kumi_record_v<std::remove_cvref_t<R>> && ((I >= size_v<R>) || (I < 0)))
  constexpr auto get(R&& r) = delete;
  template<str S, typename R>
  requires(is_kumi_record_v<std::remove_cvref_t<R>> && !_::contains_identifier<S, R>())
  constexpr auto get(R&& r) = delete;
  template<concepts::identifier auto S, typename R>
  requires(is_kumi_record_v<std::remove_cvref_t<R>> && !concepts::contains_identifier<decltype(S), R>)
  constexpr auto get(R&& r) = delete;
  template<typename U, typename R>
  requires(is_kumi_record_v<std::remove_cvref_t<R>> && !concepts::contains_type<U, R>)
  constexpr auto get(R&& r) = delete;
#endif
  template<concepts::record_type R> struct builder<R>
  {
    using type = R;
    template<typename... Us> using to = kumi::record<Us...>;
    template<typename... Args> static constexpr auto make(Args&&... args)
    {
      return kumi::make_record(KUMI_FWD(args)...);
    }
    template<typename... Args> static constexpr auto build(Args&&... args) { return kumi::record{KUMI_FWD(args)...}; }
  };
  template<concepts::record_type... Ts> struct common_product_type<Ts...>
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
    template<typename C, typename P, typename O, typename... Ts>
    KUMI_ABI constexpr decltype(auto) invoke_memptr(P C::* member, O&& o, Ts&&... ts)
    {
      using callable_t = P C::*;
      auto&& ptr = []<typename T>(T&& obj) -> decltype(auto) {
        if constexpr (_::is_reference_wrapper_v<std::remove_cvref_t<T>>) return obj.get();
        else if constexpr (std::is_pointer_v<std::remove_cvref_t<T>>) return *KUMI_FWD(obj);
        else return KUMI_FWD(obj);
      }(KUMI_FWD(o));
      if constexpr (std::is_member_object_pointer_v<callable_t>) return KUMI_FWD(ptr).*member;
      else return (KUMI_FWD(ptr).*member)(KUMI_FWD(ts)...);
    }
  }
  template<typename C, typename... Ts>
  KUMI_ABI constexpr decltype(auto) invoke(C&& c, Ts&&... ts) noexcept(std::is_nothrow_invocable_v<C, Ts...>)
  requires(std::is_invocable_v<C, Ts...>)
  {
    if constexpr (std::is_member_pointer_v<std::decay_t<C>>) return _::invoke_memptr(c, KUMI_FWD(ts)...);
    else return KUMI_FWD(c)(KUMI_FWD(ts)...);
  }
  template<typename R, typename C, typename... Ts>
  KUMI_ABI constexpr R invoke_r(C&& c, Ts&&... ts) noexcept(std::is_nothrow_invocable_r_v<R, C, Ts...>)
  requires(std::is_invocable_r_v<R, C, Ts...>)
  {
    if constexpr (std::is_void_v<R>) invoke(KUMI_FWD(c), KUMI_FWD(ts)...);
    else return invoke(KUMI_FWD(c), KUMI_FWD(ts)...);
  }
}
namespace kumi
{
  template<typename C, typename... Ts>
  KUMI_ABI constexpr auto bind_front(C&& c, Ts&&... ts)
    noexcept(std::is_nothrow_move_constructible_v<std::decay_t<C>> &&
             (std::is_nothrow_move_constructible_v<std::decay_t<Ts>> && ...))
  requires(std::is_move_constructible_v<std::decay_t<C>> && (std::is_move_constructible_v<std::decay_t<Ts>> && ...))
  {
    return [&]<typename... Args>(Args&&... call_args) -> decltype(auto) {
      return invoke(KUMI_FWD(c), KUMI_FWD(ts)..., KUMI_FWD(call_args)...);
    };
  }
  template<typename C, typename... Ts>
  KUMI_ABI constexpr auto bind_back(C&& c, Ts&&... ts)
    noexcept(std::is_nothrow_move_constructible_v<std::decay_t<C>> &&
             (std::is_nothrow_move_constructible_v<std::decay_t<Ts>> && ...))
  requires(std::is_move_constructible_v<std::decay_t<C>> && (std::is_move_constructible_v<std::decay_t<Ts>> && ...))
  {
    return [&]<typename... Args>(Args&&... call_args) -> decltype(auto) {
      return invoke(KUMI_FWD(c), KUMI_FWD(call_args)..., KUMI_FWD(ts)...);
    };
  }
  template<typename C, typename... Ts>
  KUMI_ABI constexpr auto bind(C&& c, Ts&&... ts)
    noexcept(std::is_nothrow_move_constructible_v<std::decay_t<C>> &&
             (std::is_nothrow_move_constructible_v<std::decay_t<Ts>> && ...))
  requires(std::is_move_constructible_v<std::decay_t<C>> && (std::is_move_constructible_v<std::decay_t<Ts>> && ...))
  {
    return [&]() -> decltype(auto) { return invoke(KUMI_FWD(c), KUMI_FWD(ts)...); };
  }
}
namespace kumi::function
{
  struct cartesian_product_t
  {
    template<std::size_t H, std::size_t... S>
    KUMI_ABI consteval auto operator()(index_t<H>, index_t<S>...) const noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return projection_map{_::digits(_::unflatten_index, std::integral_constant<std::size_t, sizeof...(S)>{},
                                        std::index_sequence<I, S...>{})...};
      }(std::make_index_sequence<H>{});
    }
  };
  struct cat_t
  {
    template<std::size_t... Sizes> KUMI_ABI consteval auto operator()(std::index_sequence<Sizes...>) const noexcept
    {
      constexpr auto N = std::integral_constant<std::size_t, (Sizes + ... + 0ULL)>{};
      constexpr auto Ids = std::index_sequence<Sizes...>{};
      return projection_map{_::digits(_::container_of_index, N, Ids), _::digits(_::element_of_index, N, Ids)};
    }
  };
  struct rotate_t
  {
    template<std::size_t S, std::size_t R> KUMI_ABI consteval auto operator()(index_t<S>, index_t<R>) const noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::index_sequence<(I + R) % S...>{};
      }(std::make_index_sequence<S>{});
    }
  };
  struct reduce_t
  {
    template<std::size_t N> KUMI_ABI consteval auto operator()(index_t<N>) const noexcept
    {
      constexpr std::size_t half = N / 2;
      constexpr std::size_t remainder = N % 2;
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return projection_map{std::index_sequence<(2 * I)...>{}, std::index_sequence<(2 * I + 1)...>{},
                              index<remainder>};
      }(std::make_index_sequence<half>{});
    }
  };
  struct split_t
  {
    template<std::size_t N, std::size_t Sz> KUMI_ABI consteval auto operator()(index_t<N>, index_t<Sz>) const noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return projection_map{std::make_index_sequence<N>{}, std::index_sequence<(I + N)...>{}};
      }(std::make_index_sequence<Sz - N>{});
    }
  };
  struct tile_t
  {
    template<std::size_t Sz, std::size_t Extent, std::size_t Stride>
    KUMI_ABI consteval auto operator()(index_t<Sz>, index_t<Extent>, index_t<Stride>) const noexcept
    {
      constexpr std::size_t nb_blocks = (Sz <= Extent) ? 1 : (Sz - Extent + Stride - 1) / Stride + 1;
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using blocks = std::index_sequence<_::block_size(I, Stride, Extent, Sz)...>;
        using offsets = std::index_sequence<(I * Stride)...>;
        return projection_map{blocks{}, offsets{}};
      }(std::make_index_sequence<nb_blocks>{});
    }
  };
  struct zip_t
  {
    template<std::size_t Count, std::size_t Size>
    KUMI_ABI consteval auto operator()(index_t<Count>, index_t<Size>) const noexcept
    {
      using tuples = std::make_index_sequence<Count>;
      using elements = std::make_index_sequence<Size>;
      return projection_map{tuples{}, elements{}};
    }
  };
  inline constexpr cartesian_product_t cartesian_producer{};
  inline constexpr cat_t concatenater{};
  inline constexpr rotate_t rotater{};
  inline constexpr reduce_t reducer{};
  inline constexpr split_t splitter{};
  inline constexpr tile_t tiler{};
  inline constexpr zip_t zipper{};
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
    struct multiset<std::index_sequence<I, Is...>, T, Ts...> : multiset<std::index_sequence<Is...>, Ts...>
    {
      consteval auto operator()(std::type_identity<T>) const noexcept
      {
        return std::integral_constant<std::size_t, I>{};
      }
      using multiset<std::index_sequence<Is...>, Ts...>::operator();
    };
    template<typename... Ts> struct make_multiset
    {
      using type = multiset<Ts...>;
    };
    template<typename... Ts> using make_multiset_t = typename make_multiset<Ts...>::type;
  }
  namespace function
  {
    struct unique_t
    {
      template<typename... Ts> KUMI_ABI consteval auto operator()(std::type_identity<Ts>...) const noexcept
      {
        using type = _::make_multiset_t<std::make_index_sequence<sizeof...(Ts)>, Ts...>;
        constexpr type impl{};
        struct
        {
          std::size_t e[sizeof...(Ts)], count = {};
        } that{};
        [&]<std::size_t... I>(std::index_sequence<I...>) {
          ((void)(impl(std::type_identity<Ts>{}) == I ? (that.e[that.count++] = I) : 0), ...);
        }(std::make_index_sequence<sizeof...(Ts)>{});
        return that;
      }
    };
    struct select_t
    {
      template<bool... Bs> KUMI_ABI consteval auto operator()(std::bool_constant<Bs>...) const noexcept
      {
        struct
        {
          std::size_t count = {}, cut = {}, t[sizeof...(Bs)];
        } that{};
        auto locate = [&]<std::size_t... I>(std::index_sequence<I...>) {
          ((void)(Bs ? (that.t[that.count++] = I) : 0), ...);
          that.cut = that.count;
          ((void)(!Bs ? (that.t[that.count++] = I) : 0), ...);
        };
        locate(std::make_index_sequence<sizeof...(Bs)>{});
        return that;
      }
    };
    struct adjacent_unicity_t
    {
      template<concepts::product_type T> [[nodiscard]] KUMI_ABI consteval auto operator()(as<T>) const noexcept
      {
        struct
        {
          std::size_t count{1}, t[size_v<T>];
        } that{};
        that.t[0] = 0;
        [&]<std::size_t... I>(std::index_sequence<I...>) {
          ((void)((std::is_same_v<stored_element_t<I, T>, stored_element_t<I + 1, T>>)
                    ? I
                    : (that.t[that.count++] = I + 1)),
           ...);
        }(std::make_index_sequence<size_v<T> - 1>{});
        return that;
      }
    };
    inline constexpr adjacent_unicity_t uniqued{};
    inline constexpr unique_t uniquer{};
    inline constexpr select_t selector{};
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
  inline constexpr numeric_add plus{};
  inline constexpr numeric_prod multiplies{};
  inline constexpr boolean_and bit_and{};
  inline constexpr boolean_or bit_or{};
  inline constexpr boolean_xor bit_xor{};
}
namespace kumi::function
{
  template<typename T, auto V> struct size_or
  {
    static constexpr auto value = [] {
      if constexpr (concepts::product_type<T>) return size_v<T>;
      else return V;
    }();
  };
  template<typename T, auto V> inline constexpr auto size_or_v = size_or<T, V>::value;
  template<std::size_t I, typename T, typename U> struct element_or
  {
    using type = typename decltype([] {
      if constexpr (concepts::product_type<T> && I < size_v<T>) return element<I, T>{};
      else return std::type_identity<U>{};
    }())::type;
  };
  template<std::size_t I, typename T, typename U> using element_or_t = typename element_or<I, T, U>::type;
  template<std::size_t I, typename T, typename V> [[nodiscard]] KUMI_ABI constexpr decltype(auto) get_or(T&& t, V&& v)
  {
    if constexpr (concepts::product_type<T> && I < size_v<T>) return get<I>(KUMI_FWD(t));
    else return KUMI_FWD(v);
  }
  template<typename T> struct foldable
  {
    T value;
    template<typename C> KUMI_ABI friend constexpr decltype(auto) operator>>(foldable&& f, C&& c)
    {
      return function::foldable{invoke(c, f.value)};
    }
    template<typename C> KUMI_ABI friend constexpr decltype(auto) operator<<(C&& c, foldable&& f)
    {
      return function::foldable{invoke(c, f.value)};
    }
    KUMI_ABI constexpr decltype(auto) operator()() const noexcept { return value; }
  };
  template<typename F, typename V> struct scannable
  {
    F func;
    V value;
    template<typename C> KUMI_ABI friend constexpr decltype(auto) operator>>(scannable&& s, C&& c)
    {
      auto res = invoke(c, s.value);
      return function::scannable{bind_front(std::move(s.func), std::move(s.value)), res};
    }
    template<typename C> KUMI_ABI friend constexpr decltype(auto) operator<<(C&& c, scannable&& s)
    {
      auto res = invoke(c, s.value);
      return function::scannable{bind_back(std::move(s.func), std::move(s.value)), res};
    }
    KUMI_ABI constexpr decltype(auto) operator()() const noexcept { return invoke(func, value); }
  };
  template<typename T> foldable(T&& t) -> foldable<std::unwrap_ref_decay_t<T>>;
  template<typename F, typename T> scannable(F&& f, T&& t) -> scannable<F, std::unwrap_ref_decay_t<T>>;
}
namespace kumi
{
}
namespace kumi
{
  template<typename Function, concepts::product_type T>
  KUMI_ABI constexpr decltype(auto) apply(Function&& f, T&& t) noexcept(_::supports_nothrow_apply<Function&&, T&&>)
#ifndef KUMI_DOXYGEN_INVOKED
  requires(_::supports_apply<Function, T>)
#endif
  {
    if constexpr (concepts::empty_product_type<T>) return invoke(KUMI_FWD(f));
    else if constexpr (concepts::record_type<T>) return apply(KUMI_FWD(f), values_of(KUMI_FWD(t)));
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto) {
        return invoke(KUMI_FWD(f), get<I>(KUMI_FWD(t))...);
      }(std::make_index_sequence<size_v<T>>{});
  }
  namespace result
  {
    template<typename Function, concepts::product_type T> struct apply
    {
      using type = decltype(kumi::apply(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, concepts::product_type T> using apply_t = typename apply<Function, T>::type;
  }
  namespace _
  {
    template<typename Function, concepts::record_type R>
    KUMI_ABI constexpr decltype(auto) apply_field(Function&& f, R&& t)
    {
      if constexpr (concepts::empty_product_type<R>) return invoke(KUMI_FWD(f));
      else
        return [&]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto) {
          return invoke(KUMI_FWD(f), get<I>(KUMI_FWD(t))...);
        }(std::make_index_sequence<size_v<R>>{});
      ;
    }
    namespace result
    {
      template<typename Function, concepts::record_type R> struct apply_field
      {
        using type = decltype(kumi::_::apply_field(std::declval<Function>(), std::declval<R>()));
      };
      template<typename Function, concepts::record_type R>
      using apply_field_t = typename apply_field<Function, R>::type;
    }
  }
}
namespace kumi
{
  template<concepts::non_empty_product_type T> [[nodiscard]] KUMI_ABI constexpr decltype(auto) front(T&& t)
  {
    if constexpr (concepts::record_type<T>) return front(values_of(KUMI_FWD(t)));
    else return get<0>(KUMI_FWD(t));
  }
  template<concepts::non_empty_product_type T> [[nodiscard]] KUMI_ABI constexpr decltype(auto) back(T&& t)
  {
    if constexpr (concepts::record_type<T>) return back(values_of(KUMI_FWD(t)));
    else return get<size_v<T> - 1>(KUMI_FWD(t));
  }
  namespace result
  {
    template<concepts::product_type T> struct front : stored_member<0, T>
    {
    };
    template<concepts::product_type T> struct back : stored_member<size_v<T> - 1, T>
    {
    };
    template<concepts::product_type T> using front_t = typename front<T>::type;
    template<concepts::product_type T> using back_t = typename back<T>::type;
  }
}
namespace kumi
{
  template<concepts::product_type... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto cartesian_product(Ts&&... ts)
  requires(concepts::follows_same_semantic<Ts...>)
  {
    if constexpr (sizeof...(Ts) == 0) return tuple{};
    else
    {
      using res_type = common_product_type_t<std::remove_cvref_t<Ts>...>;
      constexpr auto idx = function::cartesian_producer(index<(size_v<Ts> * ...)>, index<size_v<Ts>>...);
      auto maps = [&]<std::size_t... E, std::size_t... I>(std::index_sequence<E...>, std::index_sequence<I...>) {
        auto tps = kumi::forward_as_tuple(KUMI_FWD(ts)...);
        using res_t = builder_make_t<res_type, element_t<E, element_t<I, decltype(tps)>>...>;
        return res_t{get<E>(get<I>(tps))...};
      };
      return [&]<std::size_t... N>(std::index_sequence<N...>) {
        std::make_index_sequence<sizeof...(Ts)> ids;
        return kumi::make_tuple(maps(get<N>(idx), ids)...);
      }(std::make_index_sequence<(size_v<Ts> * ...)>{});
    }
  }
  namespace result
  {
    template<typename... Ts> struct cartesian_product
    {
      using type = decltype(kumi::cartesian_product(std::declval<Ts>()...));
    };
    template<typename... Ts> using cartesian_product_t = typename cartesian_product<Ts...>::type;
  }
}
namespace kumi
{
  template<typename Target, concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto member_cast(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return t;
    else if constexpr (concepts::record_type<T>)
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = builder_make_t<T, result::field_cast_t<Target, element_t<I, T>>...>;
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
    template<typename Target, concepts::product_type T> struct member_cast
    {
      using type = decltype(kumi::member_cast<Target, T>(std::declval<T>()));
    };
    template<typename Target, concepts::product_type T> using member_cast_t = typename member_cast<Target, T>::type;
  }
}
namespace kumi
{
  template<concepts::product_type... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto cat(Ts&&... ts)
  requires(concepts::follows_same_semantic<Ts...>)
  {
    if constexpr (sizeof...(Ts) == 0) return tuple{};
    else
    {
      constexpr auto pos = function::concatenater(std::index_sequence<size_v<Ts>...>{});
      using res_type = common_product_type_t<std::remove_cvref_t<Ts>...>;
      return [&]<typename T, std::size_t... E, std::size_t... N>(T&& t, std::index_sequence<E...>,
                                                                 std::index_sequence<N...>) {
        using type = builder_make_t<res_type, element_t<E, element_t<N, T>>...>;
        return type{get<E>(get<N>(KUMI_FWD(t)))...};
      }(kumi::forward_as_tuple(KUMI_FWD(ts)...), get<1>(pos), get<0>(pos));
    }
  }
  namespace result
  {
    template<concepts::product_type... Ts> struct cat
    {
      using type = decltype(kumi::cat(std::declval<Ts>()...));
    };
    template<concepts::product_type... Ts> using cat_t = typename cat<Ts...>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename... Ts>
    constexpr bool contains = ((concepts::field<T> && std::invocable<T, tag_of_t<Ts>>) || ...);
  }
  template<concepts::product_type T, concepts::identifier ID>
  KUMI_ABI constexpr auto contains([[maybe_unused]] T&& t, [[maybe_unused]] ID const& id) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return std::false_type{};
    else if constexpr (concepts::record_type<T>)
      return []<std::size_t... I>(std::index_sequence<I...>) {
        return std::bool_constant<_::can_get_field_by_value<std::remove_cvref_t<ID>, element_t<I, T>...>>{};
      }(std::make_index_sequence<size_v<T>>{});
    else
      return []<std::size_t... I>(std::index_sequence<I...>) {
        if constexpr (((concepts::field<element_t<I, T>> && std::invocable<element_t<I, T>, _::tag_of_t<ID>>) || ...))
          return std::true_type{};
        else return std::false_type{};
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<concepts::product_type T, concepts::identifier... Is>
  KUMI_ABI constexpr auto contains_any([[maybe_unused]] T&& t, Is const&... ids) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return std::false_type{};
    else if constexpr (sizeof...(Is) == 0) return std::false_type{};
    else return std::bool_constant<(decltype(contains(std::declval<T>(), ids)){} || ...)>{};
  }
  template<concepts::product_type T, concepts::identifier... Is>
  KUMI_ABI constexpr auto contains_only([[maybe_unused]] T&& t, [[maybe_unused]] Is const&... ids) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return std::false_type{};
    else if constexpr (sizeof...(Is) == 0) return std::false_type{};
    else if constexpr (sizeof...(Is) < size_v<T>) return std::false_type{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::bool_constant<(_::contains<element_t<I, T>, Is...> && ...)>{};
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<concepts::product_type T, concepts::identifier... Is>
  KUMI_ABI constexpr auto contains_none([[maybe_unused]] T&& t, Is const&... ids) noexcept
  {
    return std::bool_constant<!decltype(contains_any(std::declval<T>(), ids...)){}>{};
  }
  namespace result
  {
    template<concepts::product_type T, concepts::identifier ID> struct contains
    {
      using type = decltype(kumi::contains(std::declval<T>(), std::declval<ID>()));
    };
    template<concepts::product_type T, concepts::identifier... IDs> struct contains_any
    {
      using type = decltype(kumi::contains_any(std::declval<T>(), std::declval<IDs>()...));
    };
    template<concepts::product_type T, concepts::identifier... IDs> struct contains_only
    {
      using type = decltype(kumi::contains_only(std::declval<T>(), std::declval<IDs>()...));
    };
    template<concepts::product_type T, concepts::identifier... IDs> struct contains_none
    {
      using type = decltype(kumi::contains_none(std::declval<T>(), std::declval<IDs>()...));
    };
    template<concepts::product_type T, concepts::identifier ID> using contains_t = typename contains<T, ID>::type;
    template<concepts::product_type T, concepts::identifier... IDs>
    using contains_any_t = typename contains_any<T, IDs...>::type;
    template<concepts::product_type T, concepts::identifier... IDs>
    using contains_only_t = typename contains_only<T, IDs...>::type;
    template<concepts::product_type T, concepts::identifier... IDs>
    using contains_none_t = typename contains_none<T, IDs...>::type;
  }
}
namespace kumi
{
  template<std::size_t I0, std::size_t I1, concepts::product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto extract(T&& t,
                                                [[maybe_unused]] index_t<I0> i0,
                                                [[maybe_unused]] index_t<I1> i1) noexcept
  {
    static_assert((I0 <= size_v<T>) && (I1 <= size_v<T>), "[KUMI] - Invalid index");
    return [&]<std::size_t... N>(std::index_sequence<N...>) {
      using final_t = builder_make_t<T, element_t<N + I0, T>...>;
      return final_t{get<N + I0>(KUMI_FWD(t))...};
    }(std::make_index_sequence<I1 - I0>{});
  }
  template<std::size_t I0, concepts::product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto extract(T&& t, index_t<I0> i0) noexcept
  {
    static_assert(I0 <= size_v<T>, "[KUMI] - Invalid index");
    return extract(KUMI_FWD(t), i0, index<size_v<T>>);
  }
  template<std::size_t I0, concepts::product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto split(T&& t, [[maybe_unused]] index_t<I0> i0) noexcept
  {
    static_assert(I0 <= size_v<T>, "[KUMI] - Invalid index");
    constexpr auto proj = function::splitter(index<I0>, index<size_v<T>>);
    auto select = [&]<std::size_t... I>(std::index_sequence<I...>) {
      using type = builder_make_t<T, element_t<I, T>...>;
      return type{get<I>(KUMI_FWD(t))...};
    };
    return kumi::tuple{select(get<0>(proj)), select(get<1>(proj))};
  }
  namespace result
  {
    template<concepts::product_type T, std::size_t I0, std::size_t I1 = std::size_t(-1)> struct extract
    {
      using type = decltype(kumi::extract(std::declval<T>(), kumi::index_t<I0>{}, kumi::index_t<I1>{}));
    };
    template<concepts::product_type T, std::size_t I0> struct extract<T, I0>
    {
      using type = decltype(kumi::extract(std::declval<T>(), kumi::index_t<I0>{}));
    };
    template<concepts::product_type T, std::size_t I0> struct split
    {
      using type = decltype(kumi::split(std::declval<T>(), kumi::index_t<I0>{}));
    };
    template<concepts::product_type T, std::size_t I0, std::size_t I1 = std::size_t(-1)>
    using extract_t = typename extract<T, I0, I1>::type;
    template<concepts::product_type T, std::size_t I0> using split_t = typename split<T, I0>::type;
  }
}
namespace kumi
{
  template<typename Function, concepts::product_type T, concepts::product_type... Ts>
  KUMI_ABI constexpr void for_each(Function f, T&& t, Ts&&... ts)
  requires(concepts::compatible_product_types<T, Ts...>)
#ifndef KUMI_DOXYGEN_INVOKED
          && (_::supports_call<Function&, T, Ts...>)
#endif
  {
    if constexpr (concepts::empty_product_type<T>) return;
    else
    {
      auto const invoker{[&](auto const I) {
        if constexpr (concepts::record_type<T>)
        {
          constexpr auto field = identifier_of<element_t<I, T>>();
          invoke(f, get<field>(KUMI_FWD(t)), get<field>(KUMI_FWD(ts))...);
        }
        else invoke(f, get<I>(KUMI_FWD(t)), get<I>(KUMI_FWD(ts))...);
      }};
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        (invoker(index<I>), ...);
      }(std::make_index_sequence<size_v<T>>{});
    }
  }
  template<typename Function, concepts::product_type T, concepts::product_type... Ts>
  KUMI_ABI constexpr void for_each_index(Function f, T&& t, Ts&&... ts)
  requires(!concepts::record_type<T> && (!concepts::record_type<Ts> && ...))
  {
    if constexpr (concepts::empty_product_type<T>) return;
    else
    {
      auto const invoker{[&](auto const I) { invoke(f, I, get<I>(KUMI_FWD(t)), get<I>(KUMI_FWD(ts))...); }};
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        (invoker(index<I>), ...);
      }(std::make_index_sequence<size_v<T>>{});
    }
  }
  template<typename Function, concepts::record_type R, concepts::record_type... Rs>
  KUMI_ABI constexpr void for_each_field(Function f, R&& r, Rs&&... rs)
  requires(concepts::compatible_product_types<R, Rs...>)
  {
    if constexpr (concepts::empty_product_type<R>) return;
    else
    {
      constexpr auto fields = members_of(as<R>{});
      auto const invoker = [&](auto const I) {
        constexpr auto field = get<I>(fields);
        invoke(f, _::make_str(field), get<field>(KUMI_FWD(r)), get<field>(KUMI_FWD(rs))...);
      };
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        (invoker(index<I>), ...);
      }(std::make_index_sequence<size_v<R>>{});
    }
  }
}
namespace kumi
{
  template<typename Pred, concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto locate(T&& t, Pred p) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return 0;
    else if constexpr (concepts::record_type<T>) return locate(values_of(KUMI_FWD(t)), p);
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        bool checks[] = {invoke(p, get<I>(KUMI_FWD(t)))...};
        for (std::size_t i = 0; i < size_v<T>; ++i)
          if (checks[i]) return i;
        return size_v<T>;
      }(std::make_index_sequence<size_v<T>>{});
  }
}
namespace kumi
{
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto flatten(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return t;
    else
    {
      constexpr auto proj = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return function::concatenater(std::index_sequence<function::size_or_v<stored_element_t<I, T>, 1>...>{});
      }(std::make_index_sequence<size_v<T>>{});
      auto process = [&]<typename V>(auto J, V&& v) {
        using FV = result::field_value_of_t<V>;
        if constexpr (concepts::record_type<FV> && concepts::record_type<T>)
        {
          constexpr auto curr_name = label_of<V>();
          constexpr auto new_name = concatenate_str<curr_name, label_of<element_t<J, FV>>()>();
          return (capture_field<name<new_name>{}>(field_value_of(get<J>(field_value_of(KUMI_FWD(v))))));
        }
        else if constexpr (concepts::follows_same_semantic<T, V>) return get<J>(KUMI_FWD(v));
        else return KUMI_FWD(v);
      };
      return [&]<std::size_t... J, std::size_t... I>(std::index_sequence<J...>, std::index_sequence<I...>) {
        return builder<T>::make(process(index<J>, get<I>(KUMI_FWD(t)))...);
      }(get<1>(proj), get<0>(proj));
    }
  }
  template<concepts::product_type T, typename Func> [[nodiscard]] KUMI_ABI constexpr auto flatten_all(T&& t, Func f)
  {
    if constexpr (concepts::empty_product_type<T>) return t;
    else
    {
      auto process = [&]<typename V>(V&& v) {
        using FV = result::field_value_of_t<V>;
        if constexpr (concepts::record_type<FV> && concepts::record_type<T>)
          return capture_field<identifier_of<V>()>(flatten_all(field_value_of(KUMI_FWD(v)), f));
        else if constexpr (concepts::follows_same_semantic<T, V>) return flatten_all(KUMI_FWD(v), f);
        else if constexpr (concepts::record_type<T> && concepts::field<V>)
          return capture_field<identifier_of<V>()>(invoke(f, field_value_of(v)));
        else return invoke(f, v);
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return flatten(builder<T>::make(process(get<I>(KUMI_FWD(t)))...));
      }(std::make_index_sequence<size_v<T>>{});
    }
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto flatten_all(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return KUMI_FWD(t);
    else
    {
      auto process = [&]<typename V>(V&& v) {
        using FV = result::field_value_of_t<V>;
        if constexpr (concepts::record_type<FV> && concepts::record_type<T>)
          return capture_field<identifier_of<V>()>(flatten_all(field_value_of(KUMI_FWD(v))));
        else if constexpr (concepts::follows_same_semantic<T, V>) return flatten_all(KUMI_FWD(v));
        else return KUMI_FWD(v);
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return flatten(builder<T>::make(process(get<I>(KUMI_FWD(t)))...));
      }(std::make_index_sequence<size_v<T>>{});
    }
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI auto as_flat_ptr(T&& t) noexcept
  {
    return kumi::flatten_all(KUMI_FWD(t), [](auto& m) { return &m; });
  }
  namespace result
  {
    template<concepts::product_type T> struct flatten
    {
      using type = decltype(kumi::flatten(std::declval<T>()));
    };
    template<concepts::product_type T, typename Func = void> struct flatten_all
    {
      using type = decltype(kumi::flatten_all(std::declval<T>(), std::declval<Func>()));
    };
    template<concepts::product_type T> struct flatten_all<T>
    {
      using type = decltype(kumi::flatten_all(std::declval<T>()));
    };
    template<concepts::product_type T> struct as_flat_ptr
    {
      using type = decltype(kumi::as_flat_ptr(std::declval<T>()));
    };
    template<concepts::product_type T> using flatten_t = typename flatten<T>::type;
    template<concepts::product_type T, typename Func = void> using flatten_all_t = typename flatten_all<T, Func>::type;
    template<concepts::product_type T> using as_flat_ptr_t = typename as_flat_ptr<T>::type;
  }
}
namespace kumi
{
  template<std::size_t N, typename T> [[nodiscard]] KUMI_ABI constexpr auto fill(T const& v) noexcept
  {
    if constexpr (N == 0) return kumi::tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        auto eval = [](auto, auto const& vv) { return vv; };
        return kumi::tuple{eval(index<I>, v)...};
      }(std::make_index_sequence<N>{});
  }
  template<std::size_t N, typename Function> [[nodiscard]] KUMI_ABI constexpr auto generate(Function const& f) noexcept
  {
    if constexpr (N == 0) return kumi::tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return kumi::tuple{invoke(f, index<I>)...};
      }(std::make_index_sequence<N>{});
  }
  template<std::size_t N, typename T> [[nodiscard]] KUMI_ABI constexpr auto iota(T v) noexcept
  {
    if constexpr (N == 0) return kumi::tuple{};
    else
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
  template<concepts::product_type S1,
           concepts::sized_product_type<size_v<S1>> S2,
           typename T,
           typename Sum,
           typename Prod>
  [[nodiscard]] KUMI_ABI constexpr auto inner_product(S1&& s1, S2&& s2, T init, Sum sum, Prod prod) noexcept
  requires(concepts::compatible_product_types<S1, S2>)
  {
    if constexpr (concepts::empty_product_type<S1>) return init;
    else if constexpr (concepts::record_type<S1>)
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (function::foldable{init} >> ... >>
                bind_back(sum, invoke(prod, get<identifier_of<element_t<I, S1>>()>(KUMI_FWD(s1)),
                                      get<identifier_of<element_t<I, S1>>()>(KUMI_FWD(s2)))))();
      }(std::make_index_sequence<size_v<S1>>());
    }
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (function::foldable{init} >> ... >>
                bind_back(sum, invoke(prod, get<I>(KUMI_FWD(s1)), get<I>(KUMI_FWD(s2)))))();
      }(std::make_index_sequence<size_v<S1>>{});
    }
  }
  template<concepts::product_type S1, concepts::sized_product_type<size_v<S1>> S2, typename T>
  [[nodiscard]] KUMI_ABI constexpr auto inner_product(S1&& s1, S2&& s2, T init) noexcept
  requires(concepts::compatible_product_types<S1, S2>)
  {
    if constexpr (concepts::empty_product_type<S1>) return init;
    else if constexpr (concepts::record_type<S1>)
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (init + ... +
                (get<identifier_of<element_t<I, S1>>()>(KUMI_FWD(s1)) *
                 get<identifier_of<element_t<I, S1>>()>(KUMI_FWD(s2))));
      }(std::make_index_sequence<size<S1>::value>());
    }
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (init + ... + (get<I>(KUMI_FWD(s1)) * get<I>(KUMI_FWD(s2))));
      }(std::make_index_sequence<size_v<S1>>{});
    }
  }
  namespace result
  {
    template<concepts::product_type S1,
             concepts::sized_product_type<size_v<S1>> S2,
             typename T,
             typename Sum,
             typename Prod>
    struct inner_product
    {
      using type = decltype(kumi::inner_product(
        std::declval<S1>(), std::declval<S2>(), std::declval<T>(), std::declval<Sum>(), std::declval<Prod>()));
    };
    template<concepts::product_type S1, concepts::sized_product_type<size_v<S1>> S2, typename T>
    struct inner_product<S1, S2, T, void, void>
    {
      using type = decltype(kumi::inner_product(std::declval<S1>(), std::declval<S2>(), std::declval<T>()));
    };
    template<concepts::product_type S1,
             concepts::sized_product_type<size_v<S1>> S2,
             typename T,
             typename Sum = void,
             typename Prod = void>
    using inner_product_t = typename inner_product<S1, S2, T, Sum, Prod>::type;
  }
}
namespace kumi
{
  template<concepts::product_type T, typename Function, concepts::sized_product_type<size_v<T>>... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto map(Function f, T&& t0, Ts&&... others)
  requires(concepts::compatible_product_types<T, Ts...>)
#ifndef KUMI_DOXYGEN_INVOKED
          && (_::supports_call<Function, T &&, Ts && ...>)
#endif
  {
    if constexpr (concepts::empty_product_type<T>) return builder<T>::make();
    else
    {
      auto const call{[&](auto const N, auto&&... args) {
        if constexpr (concepts::record_type<T>)
        {
          constexpr auto field = identifier_of<element_t<N, T>>();
          return capture_field<field>(invoke(f, get<field>(args)...));
        }
        else return invoke(f, get<N>(KUMI_FWD(args))...);
      }};
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return builder<T>::make(call(index<I>, KUMI_FWD(t0), KUMI_FWD(others)...)...);
      }(std::make_index_sequence<size_v<T>>{});
    }
  }
  template<concepts::product_type T, typename Function, concepts::sized_product_type<size_v<T>>... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto map_index(Function f, T&& t0, Ts&&... others)
  requires(!concepts::record_type<T> && (!concepts::record_type<Ts> && ...))
  {
    if constexpr (concepts::empty_product_type<T>) return builder<T>::make();
    else
    {
      auto const call{[&](auto const N, auto&&... args) { return invoke(f, N, get<N>(KUMI_FWD(args))...); }};
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return builder<T>::make(call(index<I>, KUMI_FWD(t0), KUMI_FWD(others)...)...);
      }(std::make_index_sequence<size_v<T>>{});
    }
  }
  template<concepts::record_type T, typename Function, concepts::sized_product_type<size_v<T>>... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto map_field(Function f, T&& t0, Ts&&... others)
  requires(concepts::compatible_product_types<T, Ts...>)
  {
    if constexpr (concepts::empty_product_type<T>) return builder<T>::make();
    else
    {
      auto const call{[&](auto const N, auto&&... args) {
        constexpr auto field = identifier_of<element_t<N, T>>();
        return capture_field<field>(invoke(f, _::make_str(field), (get<field>(args))...));
      }};
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return builder<T>::make(call(index<I>, KUMI_FWD(t0), KUMI_FWD(others)...)...);
      }(std::make_index_sequence<size_v<T>>{});
    }
  }
  namespace result
  {
    template<typename Function, concepts::product_type T, concepts::sized_product_type<size<T>::value>... Ts> struct map
    {
      using type = decltype(kumi::map(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    };
    template<typename Function, concepts::product_type T, concepts::sized_product_type<size<T>::value>... Ts>
    struct map_index
    {
      using type = decltype(kumi::map_index(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    };
    template<typename Function, concepts::record_type T, concepts::sized_product_type<size<T>::value>... Ts>
    struct map_field
    {
      using type = decltype(kumi::map_field(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    };
    template<typename Function, concepts::product_type T, concepts::sized_product_type<size<T>::value>... Ts>
    using map_t = typename map<Function, T, Ts...>::type;
    template<typename Function, concepts::product_type T, concepts::sized_product_type<size<T>::value>... Ts>
    using map_index_t = typename map_index<Function, T, Ts...>::type;
    template<typename Function, concepts::record_type T, concepts::sized_product_type<size<T>::value>... Ts>
    using map_field_t = typename map_field<Function, T, Ts...>::type;
  }
}
namespace kumi
{
  template<concepts::product_type T, typename V> [[nodiscard]] KUMI_ABI constexpr auto push_front(T&& t, V&& v)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return builder<T>::make(KUMI_FWD(v), get<I>(KUMI_FWD(t))...);
    }(std::make_index_sequence<size_v<T>>{});
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto pop_front(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return builder<T>::make();
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return builder<T>::make(get<I + 1>(KUMI_FWD(t))...);
      }(std::make_index_sequence<size_v<T> - 1>{});
  }
  template<concepts::product_type T, typename V> [[nodiscard]] KUMI_ABI constexpr auto push_back(T&& t, V&& v)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return builder<T>::make(get<I>(KUMI_FWD(t))..., KUMI_FWD(v));
    }(std::make_index_sequence<size_v<T>>());
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto pop_back(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return builder<T>::make();
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return builder<T>::make(get<I>(KUMI_FWD(t))...);
      }(std::make_index_sequence<size_v<T> - 1>{});
  }
  namespace result
  {
    template<concepts::product_type T, typename V> struct push_front
    {
      using type = decltype(kumi::push_front(std::declval<T>(), std::declval<V>()));
    };
    template<concepts::product_type T> struct pop_front
    {
      using type = decltype(kumi::pop_front(std::declval<T>()));
    };
    template<concepts::product_type T, typename V> struct push_back
    {
      using type = decltype(kumi::push_back(std::declval<T>(), std::declval<V>()));
    };
    template<concepts::product_type T> struct pop_back
    {
      using type = decltype(kumi::pop_back(std::declval<T>()));
    };
    template<concepts::product_type T, typename V> using push_front_t = typename push_front<T, V>::type;
    template<concepts::product_type T> using pop_front_t = typename pop_front<T>::type;
    template<concepts::product_type T, typename V> using push_back_t = typename push_back<T, V>::type;
    template<concepts::product_type T> using pop_back_t = typename pop_back<T>::type;
  }
}
namespace kumi
{
  template<typename Function, concepts::product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto fold_left(Function f, T&& t, Value init)
  {
    if constexpr (concepts::record_type<T>) return fold_left(f, values_of(KUMI_FWD(t)), init);
    else if constexpr (concepts::empty_product_type<T>) return init;
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (function::foldable{init} >> ... >> bind_back(f, get<I>(KUMI_FWD(t))))();
      }(std::make_index_sequence<size_v<T>>());
  }
  template<typename Function, concepts::non_empty_product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto fold_left(Function f, T&& t)
  {
    if constexpr (concepts::record_type<T>) return fold_left(f, values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (function::foldable{get<0>(KUMI_FWD(t))} >> ... >> bind_back(f, get<I + 1>(KUMI_FWD(t))))();
      }(std::make_index_sequence<size_v<T> - 1>{});
  }
  template<typename Function, concepts::product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto fold_right(Function f, T&& t, Value init)
  {
    if constexpr (concepts::record_type<T>) return fold_right(f, values_of(KUMI_FWD(t)), init);
    else if constexpr (concepts::empty_product_type<T>) return init;
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (bind_front(f, get<I>(KUMI_FWD(t))) << ... << function::foldable{init})();
      }(std::make_index_sequence<size_v<T>>());
  }
  template<typename Function, concepts::non_empty_product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto fold_right(Function f, T&& t)
  {
    if constexpr (concepts::record_type<T>) return fold_right(f, values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (bind_front(f, get<I + 1>(KUMI_FWD(t))) << ... << function::foldable{get<0>(KUMI_FWD(t))})();
      }(std::make_index_sequence<size_v<T> - 1>());
  }
  namespace result
  {
    template<typename Function, concepts::product_type T, typename Value = void> struct fold_right
    {
      using type = decltype(kumi::fold_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, concepts::product_type T> struct fold_right<Function, T>
    {
      using type = decltype(kumi::fold_right(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, concepts::product_type T, typename Value = void> struct fold_left
    {
      using type = decltype(kumi::fold_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, concepts::product_type T> struct fold_left<Function, T>
    {
      using type = decltype(kumi::fold_left(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, concepts::product_type T, typename Value = void>
    using fold_right_t = typename fold_right<Function, T, Value>::type;
    template<typename Function, concepts::product_type T, typename Value = void>
    using fold_left_t = typename fold_left<Function, T, Value>::type;
  }
}
namespace kumi
{
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto max(T&& t) noexcept
  {
    if constexpr (concepts::record_type<T>) return max(values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
    else
    {
      auto const f = [](auto cur, auto u) { return cur > u ? cur : u; };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (function::foldable{get<0>(KUMI_FWD(t))} >> ... >> bind_back(f, get<I + 1>(KUMI_FWD(t))))();
      }(std::make_index_sequence<size_v<T> - 1>{});
    }
  }
  template<concepts::product_type T, typename F> [[nodiscard]] KUMI_ABI constexpr auto max(T&& t, F f) noexcept
  {
    if constexpr (concepts::record_type<T>) return max(values_of(KUMI_FWD(t)), f);
    else if constexpr (concepts::sized_product_type<T, 1>) return invoke(f, get<0>(KUMI_FWD(t)));
    else
    {
      auto const c = [f](auto cur, auto const& u) { return cur > invoke(f, u) ? cur : invoke(f, u); };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (function::foldable{invoke(f, get<0>(KUMI_FWD(t)))} >> ... >> bind_back(c, get<I + 1>(KUMI_FWD(t))))();
      }(std::make_index_sequence<size_v<T> - 1>{});
    }
  }
  template<concepts::product_type T, typename F> [[nodiscard]] KUMI_ABI constexpr auto max_flat(T&& t, F f) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return 0;
    else if constexpr (concepts::record_type<T>) return max_flat(values_of(KUMI_FWD(t)), f);
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return max(make_tuple([&]<typename V>(V&& v) {
          if constexpr (concepts::product_type<V>) return max_flat(KUMI_FWD(v), f);
          else return invoke(f, v);
        }(get<I>(KUMI_FWD(t)))...));
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto min(T&& t) noexcept
  {
    if constexpr (concepts::record_type<T>) return min(values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
    else
    {
      auto const f = [](auto cur, auto u) { return cur < u ? cur : u; };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (function::foldable{get<0>(KUMI_FWD(t))} >> ... >> bind_back(f, get<I + 1>(KUMI_FWD(t))))();
      }(std::make_index_sequence<size_v<T> - 1>{});
    }
  }
  template<concepts::product_type T, typename F> [[nodiscard]] KUMI_ABI constexpr auto min(T&& t, F f) noexcept
  {
    if constexpr (concepts::record_type<T>) return min(values_of(KUMI_FWD(t)), f);
    else if constexpr (concepts::sized_product_type<T, 1>) return invoke(f, get<0>(KUMI_FWD(t)));
    else
    {
      auto const c = [f](auto cur, auto const& u) { return cur < invoke(f, u) ? cur : invoke(f, u); };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (function::foldable{invoke(f, get<0>(KUMI_FWD(t)))} >> ... >> bind_back(c, get<I + 1>(KUMI_FWD(t))))();
      }(std::make_index_sequence<size_v<T> - 1>{});
    }
  }
  template<concepts::product_type T, typename F> [[nodiscard]] KUMI_ABI constexpr auto min_flat(T&& t, F f) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return 0;
    else if constexpr (concepts::record_type<T>) return min_flat(values_of(KUMI_FWD(t)), f);
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return min(make_tuple([&]<typename V>(V&& v) {
          if constexpr (concepts::product_type<V>) return min_flat(KUMI_FWD(v), f);
          else return invoke(f, v);
        }(get<I>(KUMI_FWD(t)))...));
      }(std::make_index_sequence<size_v<T>>{});
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
    template<typename T, typename F = void> using max_t = typename max<T, F>::type;
    template<typename T, typename F> using max_flat_t = typename max_flat<T, F>::type;
    template<typename T, typename F = void> using min_t = typename min<T, F>::type;
    template<typename T, typename F> using min_flat_t = typename min_flat<T, F>::type;
  }
}
namespace kumi
{
  template<template<typename> typename Pred, concepts::product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto partition(T&& t) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return tuple{builder<T>::make(), builder<T>::make()};
    else
    {
      constexpr auto pos = []<std::size_t... I>(std::index_sequence<I...>) {
        return function::selector(std::bool_constant<Pred<stored_element_t<I, T>>::value>{}...);
      }(std::make_index_sequence<size_v<T>>{});
      auto select = [&]<typename O, std::size_t... I>(O, std::index_sequence<I...>) {
        using type = builder_make_t<T, element_t<pos.t[O::value + I], T>...>;
        return type{get<pos.t[O::value + I]>(KUMI_FWD(t))...};
      };
      return kumi::tuple{select(kumi::index<0>, std::make_index_sequence<pos.cut>{}),
                         select(kumi::index<pos.cut>, std::make_index_sequence<size_v<T> - pos.cut>{})};
    }
  }
  template<template<typename> typename Pred, concepts::product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto filter(T&& t) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return builder<T>::make();
    else
    {
      constexpr auto pos = []<std::size_t... I>(std::index_sequence<I...>) {
        return function::selector(std::bool_constant<Pred<stored_element_t<I, T>>::value>{}...);
      }(std::make_index_sequence<size_v<T>>{});
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = builder_make_t<T, element_t<pos.t[I], T>...>;
        return type{get<pos.t[I]>(KUMI_FWD(t))...};
      }(std::make_index_sequence<pos.cut>{});
    }
  }
  template<template<typename> typename Pred, concepts::product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto filter_not(T&& t) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return builder<T>::make();
    else
    {
      constexpr auto pos = []<std::size_t... I>(std::index_sequence<I...>) {
        return function::selector(std::bool_constant<Pred<stored_element_t<I, T>>::value>{}...);
      }(std::make_index_sequence<size_v<T>>{});
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = builder_make_t<T, element_t<pos.t[pos.cut + I], T>...>;
        return type{get<pos.t[pos.cut + I]>(KUMI_FWD(t))...};
      }(std::make_index_sequence<size_v<T> - pos.cut>{});
    }
  }
  namespace result
  {
    template<template<typename> typename Pred, kumi::concepts::product_type T> struct partition
    {
      using type = decltype(kumi::partition<Pred>(std::declval<T>()));
    };
    template<template<typename> typename Pred, kumi::concepts::product_type T> struct filter
    {
      using type = decltype(kumi::filter<Pred>(std::declval<T>()));
    };
    template<template<typename> typename Pred, kumi::concepts::product_type T> struct filter_not
    {
      using type = decltype(kumi::filter_not<Pred>(std::declval<T>()));
    };
    template<template<typename> typename Pred, kumi::concepts::product_type T>
    using partition_t = typename partition<Pred, T>::type;
    template<template<typename> typename Pred, kumi::concepts::product_type T>
    using filter_t = typename filter<Pred, T>::type;
    template<template<typename> typename Pred, kumi::concepts::product_type T>
    using filter_not_t = typename filter_not<Pred, T>::type;
  }
}
namespace kumi
{
  template<typename Pred, concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto all_of(T&& t, Pred p) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return true;
    else if constexpr (concepts::record_type<T>) return all_of(values_of(KUMI_FWD(t)), p);
    else if constexpr (concepts::sized_product_type<T, 1>) return invoke(p, get<0>(KUMI_FWD(t)));
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (invoke(p, get<I>(KUMI_FWD(t))) && ...);
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto all_of(T&& t) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return true;
    else if constexpr (concepts::record_type<T>) return all_of(values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return !!get<0>(KUMI_FWD(t));
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (get<I>(KUMI_FWD(t)) && ...);
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<typename Pred, concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto any_of(T&& t, Pred p) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return true;
    else if constexpr (concepts::record_type<T>) return any_of(values_of(KUMI_FWD(t)), p);
    else if constexpr (concepts::sized_product_type<T, 1>) return invoke(p, get<0>(KUMI_FWD(t)));
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (invoke(p, get<I>(KUMI_FWD(t))) || ...);
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto any_of(T&& t) noexcept
  {
    if constexpr (concepts::empty_product_type<T>) return false;
    else if constexpr (concepts::record_type<T>) return any_of(values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return !!get<0>(KUMI_FWD(t));
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (get<I>(KUMI_FWD(t)) || ...);
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<typename Pred, concepts::product_type T>
  [[nodiscard]] KUMI_ABI constexpr bool none_of(T&& t, Pred p) noexcept
  {
    return !any_of(KUMI_FWD(t), p);
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr bool none_of(T&& t) noexcept
  {
    return !any_of(KUMI_FWD(t));
  }
  template<typename Pred, concepts::product_type T>
  [[nodiscard]] KUMI_ABI constexpr std::size_t count_if(T&& t, Pred p) noexcept
  {
    constexpr std::size_t o = 1ULL;
    constexpr std::size_t z = 0ULL;
    if constexpr (concepts::empty_product_type<T>) return z;
    else if constexpr (concepts::record_type<T>) return count_if(values_of(KUMI_FWD(t)), p);
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return ((invoke(p, get<I>(KUMI_FWD(t))) ? o : z) + ... + z);
      }(std::make_index_sequence<size_v<T>>{});
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr std::size_t count(T&& t) noexcept
  {
    return count_if(KUMI_FWD(t), [](auto const& m) { return static_cast<bool>(m); });
  }
}
namespace kumi
{
  template<std::size_t... Idx, concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto reorder(T&& t)
  {
    static_assert(((Idx < size_v<T>) && ...), "[KUMI] - Index out of bounds");
    return builder<T>::make(get<Idx>(KUMI_FWD(t))...);
  }
  template<concepts::identifier auto... Name, concepts::product_type Tuple>
  KUMI_ABI constexpr auto reorder_fields(Tuple&& t)
  {
    static_assert((requires { get<Name>(std::declval<Tuple>()); } && ...),
                  "[KUMI] - Identifier not present in input type");
    return builder<Tuple>::make(Name = get<Name>(KUMI_FWD(t))...);
  }
  template<concepts::projection_map auto Projections, concepts::product_type T>
  [[nodiscard]] KUMI_ABI constexpr auto reindex(T&& t)
  {
    using proj_t = std::remove_cvref_t<decltype(Projections)>;
    auto mk = [&]<concepts::projection auto proj>() -> decltype(auto) {
      if constexpr (concepts::projection_map<decltype(proj)>) return reindex<proj>(KUMI_FWD(t));
      else
      {
        static_assert(requires { get<proj>(std::declval<T>()); }, "[KUMI] - Invalid projection for input type");
        return get<proj>(KUMI_FWD(t));
      }
    };
    if constexpr (concepts::empty_product_type<T>) return builder<T>::make();
    else if constexpr (proj_t::size() == 0) return builder<T>::make();
    else
      return [&]<auto... E>(kumi::projection_map<E...>) {
        return builder<T>::make(mk.template operator()<E>()...);
      }(Projections);
  }
  namespace result
  {
    template<concepts::product_type T, std::size_t... Idx> struct reorder
    {
      using type = decltype(kumi::reorder<Idx...>(std::declval<T>()));
    };
    template<concepts::product_type Tuple, concepts::identifier auto... Name> struct reorder_fields
    {
      using type = decltype(kumi::reorder_fields<Name...>(std::declval<Tuple>()));
    };
    template<concepts::product_type T, concepts::projection_map auto Indexes> struct reindex
    {
      using type = decltype(kumi::reindex<Indexes>(std::declval<T>()));
    };
    template<concepts::product_type T, std::size_t... Idx> using reorder_t = typename reorder<T, Idx...>::type;
    template<concepts::product_type Tuple, concepts::identifier auto... Name>
    using reorder_fields_t = typename reorder_fields<Tuple, Name...>::type;
    template<concepts::product_type T, concepts::projection_map auto Indexes>
    using reindex_t = typename reindex<T, Indexes>::type;
  }
}
namespace kumi
{
  template<concepts::monoid M, concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto reduce(M&& m, T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return m.identity;
    else if constexpr (concepts::record_type<T>) return reduce(KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
    else
    {
      constexpr auto pos = function::reducer(index<size_v<T>>);
      return [&]<std::size_t... F, std::size_t... S>(std::index_sequence<F...>, std::index_sequence<S...>) {
        if constexpr (get<2>(pos) == 1)
          return reduce(KUMI_FWD(m), tuple{invoke(KUMI_FWD(m), get<F>(KUMI_FWD(t)), get<S>(KUMI_FWD(t)))...,
                                           get<size_v<T> - 1>(KUMI_FWD(t))});
        else return reduce(KUMI_FWD(m), tuple{invoke(KUMI_FWD(m), get<F>(KUMI_FWD(t)), get<S>(KUMI_FWD(t)))...});
      }(get<0>(pos), get<1>(pos));
    }
  }
  template<concepts::monoid M, concepts::product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto reduce(M&& m, T&& t, Value init)
  {
    if constexpr (concepts::empty_product_type<T>) return init;
    else return KUMI_FWD(m)(init, reduce(KUMI_FWD(m), KUMI_FWD(t)));
  }
  template<concepts::product_type T, concepts::monoid M, typename Function>
  [[nodiscard]] KUMI_ABI constexpr auto map_reduce(Function f, M&& m, T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return m.identity;
    else if constexpr (concepts::record_type<T>) return map_reduce(f, KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return invoke(f, get<0>(KUMI_FWD(t)));
    else
    {
      constexpr auto pos = function::reducer(index<size_v<T>>);
      return [&]<std::size_t... F, std::size_t... S>(std::index_sequence<F...>, std::index_sequence<S...>) {
        if constexpr (get<2>(pos) == 1)
          return reduce(KUMI_FWD(m),
                        tuple{invoke(KUMI_FWD(m), invoke(f, get<F>(KUMI_FWD(t))), invoke(f, get<S>(KUMI_FWD(t))))...,
                              invoke(f, get<size_v<T> - 1>(KUMI_FWD(t)))});
        else
          return reduce(KUMI_FWD(m),
                        tuple{invoke(KUMI_FWD(m), invoke(f, get<F>(KUMI_FWD(t))), invoke(f, get<S>(KUMI_FWD(t))))...});
      }(get<0>(pos), get<1>(pos));
    }
  }
  template<concepts::monoid M, concepts::product_type T, typename Function, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto map_reduce(Function f, M&& m, T&& t, Value init)
  {
    if constexpr (concepts::empty_product_type<T>) return invoke(f, init);
    else return KUMI_FWD(m)(invoke(f, init), map_reduce(f, KUMI_FWD(m), KUMI_FWD(t)));
  }
  template<concepts::product_type T, typename Value> [[nodiscard]] KUMI_ABI constexpr auto sum(T&& t, Value init)
  {
    return reduce(function::plus, KUMI_FWD(t), init);
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto sum(T&& t)
  {
    return reduce(function::plus, KUMI_FWD(t));
  }
  template<concepts::product_type T, typename Value> [[nodiscard]] KUMI_ABI constexpr auto prod(T&& t, Value init)
  {
    return reduce(function::multiplies, KUMI_FWD(t), init);
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto prod(T&& t)
  {
    return reduce(function::multiplies, KUMI_FWD(t));
  }
  template<concepts::product_type T, typename Value> [[nodiscard]] KUMI_ABI constexpr auto bit_and(T&& t, Value init)
  {
    return reduce(function::bit_and, KUMI_FWD(t), init);
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto bit_and(T&& t)
  {
    return reduce(function::bit_and, KUMI_FWD(t));
  }
  template<concepts::product_type T, typename Value> [[nodiscard]] KUMI_ABI constexpr auto bit_or(T&& t, Value init)
  {
    return reduce(function::bit_or, KUMI_FWD(t), init);
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto bit_or(T&& t)
  {
    return reduce(function::bit_or, KUMI_FWD(t));
  }
  template<concepts::product_type T, typename Value> [[nodiscard]] KUMI_ABI constexpr auto bit_xor(T&& t, Value init)
  {
    return reduce(function::bit_xor, KUMI_FWD(t), init);
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto bit_xor(T&& t)
  {
    return reduce(function::bit_xor, KUMI_FWD(t));
  }
  namespace result
  {
    template<concepts::monoid M, concepts::product_type T, typename Value = void> struct reduce
    {
      using type = decltype(kumi::reduce(std::declval<M>(), std::declval<T>(), std::declval<Value>()));
    };
    template<concepts::monoid M, concepts::product_type T> struct reduce<M, T>
    {
      using type = decltype(kumi::reduce(std::declval<M>(), std::declval<T>()));
    };
    template<typename F, concepts::monoid M, concepts::product_type T, typename Value = void> struct map_reduce
    {
      using type =
        decltype(kumi::map_reduce(std::declval<F>(), std::declval<M>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename F, concepts::monoid M, concepts::product_type T> struct map_reduce<F, M, T>
    {
      using type = decltype(kumi::map_reduce(std::declval<F>(), std::declval<M>(), std::declval<T>()));
    };
    template<concepts::product_type T, typename Value = void> struct sum
    {
      using type = decltype(kumi::sum(std::declval<T>(), std::declval<Value>()));
    };
    template<concepts::product_type T> struct sum<T>
    {
      using type = decltype(kumi::sum(std::declval<T>()));
    };
    template<concepts::product_type T, typename Value = void> struct prod
    {
      using type = decltype(kumi::prod(std::declval<T>(), std::declval<Value>()));
    };
    template<concepts::product_type T> struct prod<T>
    {
      using type = decltype(kumi::prod(std::declval<T>()));
    };
    template<concepts::product_type T, typename Value = void> struct bit_and
    {
      using type = decltype(kumi::bit_and(std::declval<T>(), std::declval<Value>()));
    };
    template<concepts::product_type T> struct bit_and<T>
    {
      using type = decltype(kumi::bit_and(std::declval<T>()));
    };
    template<concepts::product_type T, typename Value = void> struct bit_or
    {
      using type = decltype(kumi::bit_or(std::declval<T>(), std::declval<Value>()));
    };
    template<concepts::product_type T> struct bit_or<T>
    {
      using type = decltype(kumi::bit_or(std::declval<T>()));
    };
    template<concepts::product_type T, typename Value = void> struct bit_xor
    {
      using type = decltype(kumi::bit_xor(std::declval<T>(), std::declval<Value>()));
    };
    template<concepts::product_type T> struct bit_xor<T>
    {
      using type = decltype(kumi::bit_xor(std::declval<T>()));
    };
    template<concepts::monoid M, concepts::product_type T, typename Value = void>
    using reduce_t = typename reduce<M, T, Value>::type;
    template<typename F, concepts::monoid M, concepts::product_type T, typename Value = void>
    using map_reduce_t = typename map_reduce<F, M, T, Value>::type;
    template<concepts::product_type T, typename Value = void> using sum_t = typename sum<T, Value>::type;
    template<concepts::product_type T, typename Value = void> using prod_t = typename prod<T, Value>::type;
    template<concepts::product_type T, typename Value = void> using bit_and_t = typename bit_and<T, Value>::type;
    template<concepts::product_type T, typename Value = void> using bit_or_t = typename bit_or<T, Value>::type;
    template<concepts::product_type T, typename Value = void> using bit_xor_t = typename bit_xor<T, Value>::type;
  }
}
namespace kumi
{
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto reverse(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return builder<T>::make();
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return builder<T>::make(get<(size_v<T> - 1 - I)>(KUMI_FWD(t))...);
      }(std::make_index_sequence<size<T>::value>());
    }
  }
  namespace result
  {
    template<concepts::product_type T> struct reverse
    {
      using type = decltype(kumi::reverse(std::declval<T>()));
    };
    template<concepts::product_type T> using reverse_t = typename reverse<T>::type;
  }
}
namespace kumi
{
  template<std::size_t R, concepts::product_type T> constexpr auto rotate_left(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return KUMI_FWD(t);
    else if constexpr ((R % size_v<T>) == 0) return KUMI_FWD(t);
    else
    {
      constexpr auto idxs = function::rotater(index<size_v<T>>, index<(R % size_v<T>)>);
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = builder_make_t<T, element_t<I, T>...>;
        return type{get<I>(KUMI_FWD(t))...};
      }(idxs);
    }
  }
  template<std::size_t R, concepts::product_type T> constexpr auto rotate_right(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return KUMI_FWD(t);
    else if constexpr ((R % size_v<T>) == 0) return KUMI_FWD(t);
    else
    {
      constexpr auto F = R % size_v<T>;
      constexpr auto idxs = function::rotater(index<size_v<T>>, index<(size_v<T> - F)>);
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = builder_make_t<T, element_t<I, T>...>;
        return type{get<I>(KUMI_FWD(t))...};
      }(idxs);
    }
  }
  namespace result
  {
    template<std::size_t R, concepts::product_type T> struct rotate_left
    {
      using type = decltype(kumi::rotate_left<R>(std::declval<T>()));
    };
    template<std::size_t R, concepts::product_type T> struct rotate_right
    {
      using type = decltype(kumi::rotate_right<R>(std::declval<T>()));
    };
    template<std::size_t R, concepts::product_type T> using rotate_left_t = typename rotate_left<R, T>::type;
    template<std::size_t R, concepts::product_type T> using rotate_right_t = typename rotate_right<R, T>::type;
  }
}
namespace kumi
{
  template<typename Function, concepts::product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto inclusive_scan_left(Function f, T&& t, Value init)
  {
    if constexpr (concepts::record_type<T>) return inclusive_scan_left(f, values_of(KUMI_FWD(t)), init);
    else if constexpr (concepts::empty_product_type<T>) return tuple{};
    else
    {
      auto op = [](auto&&... xs) { return kumi::make_tuple(KUMI_FWD(xs)...); };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (function::scannable{op, invoke(f, init, get<0>(KUMI_FWD(t)))} >> ... >>
                bind_back(f, get<I + 1>(KUMI_FWD(t))))();
      }(std::make_index_sequence<size_v<T> - 1>{});
    }
  }
  template<concepts::monoid M, concepts::sized_product_type_or_more<1> T>
  [[nodiscard]] KUMI_ABI constexpr auto inclusive_scan_left(M&& m, T&& t)
  {
    if constexpr (concepts::record_type<T>) return inclusive_scan_left(KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return KUMI_FWD(t);
    else return inclusive_scan_left(KUMI_FWD(m), KUMI_FWD(t), m.identity);
  }
  template<typename Function, concepts::product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto exclusive_scan_left(Function f, T&& t, Value init)
  {
    if constexpr (concepts::record_type<T>) return exclusive_scan_left(f, values_of(KUMI_FWD(t)), init);
    else if constexpr (concepts::empty_product_type<T>) return tuple{init};
    else
    {
      auto op = [](auto&&... xs) { return kumi::make_tuple(KUMI_FWD(xs)...); };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (function::scannable{op, init} >> ... >> bind_back(f, get<I>(KUMI_FWD(t))))();
      }(std::make_index_sequence<size_v<T> - 1>{});
    }
  }
  template<concepts::monoid M, concepts::sized_product_type_or_more<1> T>
  [[nodiscard]] KUMI_ABI constexpr auto exclusive_scan_left(M&& m, T&& t)
  {
    if constexpr (concepts::record_type<T>) return exclusive_scan_left(KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return tuple(m.identity, get<0>(KUMI_FWD(t)));
    else return exclusive_scan_left(KUMI_FWD(m), KUMI_FWD(t), m.identity);
  }
  template<typename Function, concepts::product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto inclusive_scan_right(Function f, T&& t, Value init)
  {
    if constexpr (concepts::record_type<T>) return inclusive_scan_right(KUMI_FWD(f), values_of(KUMI_FWD(t)), init);
    else if constexpr (concepts::empty_product_type<T>) return tuple{};
    else
    {
      auto op = [](auto&&... xs) { return kumi::make_tuple(KUMI_FWD(xs)...); };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (bind_front(f, get<I>(KUMI_FWD(t)))
                << ... << function::scannable{op, invoke(f, get<size_v<T> - 1>(KUMI_FWD(t)), init)})();
      }(std::make_index_sequence<size_v<T> - 1>{});
    }
  }
  template<concepts::monoid M, concepts::sized_product_type_or_more<1> T>
  [[nodiscard]] KUMI_ABI constexpr auto inclusive_scan_right(M&& m, T&& t)
  {
    if constexpr (concepts::record_type<T>) return inclusive_scan_right(KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return KUMI_FWD(t);
    else return inclusive_scan_right(KUMI_FWD(m), KUMI_FWD(t), m.identity);
  }
  template<typename Function, concepts::product_type T, typename Value>
  [[nodiscard]] KUMI_ABI constexpr auto exclusive_scan_right(Function f, T&& t, Value init)
  {
    if constexpr (concepts::record_type<T>) return exclusive_scan_right(KUMI_FWD(f), values_of(KUMI_FWD(t)), init);
    else if constexpr (concepts::empty_product_type<T>) return tuple{init};
    else
    {
      auto op = [](auto&&... xs) { return kumi::make_tuple(KUMI_FWD(xs)...); };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (bind_front(f, get<I + 1>(KUMI_FWD(t))) << ... << function::scannable{op, init})();
      }(std::make_index_sequence<size_v<T> - 1>{});
    }
  }
  template<concepts::monoid M, concepts::sized_product_type_or_more<1> T>
  [[nodiscard]] KUMI_ABI constexpr auto exclusive_scan_right(M&& m, T&& t)
  {
    if constexpr (concepts::record_type<T>) return exclusive_scan_right(KUMI_FWD(m), values_of(KUMI_FWD(t)));
    else if constexpr (concepts::sized_product_type<T, 1>) return tuple{get<0>(KUMI_FWD(t)), m.identity};
    else return kumi::exclusive_scan_right(KUMI_FWD(m), KUMI_FWD(t), m.identity);
  }
  namespace result
  {
    template<typename Function, concepts::product_type T, typename Value = void> struct inclusive_scan_right
    {
      using type =
        decltype(kumi::inclusive_scan_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, concepts::product_type T> struct inclusive_scan_right<Function, T>
    {
      using type = decltype(kumi::inclusive_scan_right(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, concepts::product_type T, typename Value = void> struct exclusive_scan_right
    {
      using type =
        decltype(kumi::exclusive_scan_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, concepts::product_type T> struct exclusive_scan_right<Function, T>
    {
      using type = decltype(kumi::exclusive_scan_right(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, concepts::product_type T, typename Value = void> struct inclusive_scan_left
    {
      using type =
        decltype(kumi::inclusive_scan_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, concepts::product_type T> struct inclusive_scan_left<Function, T>
    {
      using type = decltype(kumi::inclusive_scan_left(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, concepts::product_type T, typename Value = void> struct exclusive_scan_left
    {
      using type =
        decltype(kumi::exclusive_scan_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, concepts::product_type T> struct exclusive_scan_left<Function, T>
    {
      using type = decltype(kumi::exclusive_scan_left(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, concepts::product_type T, typename Value = void>
    using inclusive_scan_right_t = typename inclusive_scan_right<Function, T, Value>::type;
    template<typename Function, concepts::product_type T, typename Value = void>
    using exclusive_scan_right_t = typename exclusive_scan_right<Function, T, Value>::type;
    template<typename Function, concepts::product_type T, typename Value = void>
    using inclusive_scan_left_t = typename inclusive_scan_left<Function, T, Value>::type;
    template<typename Function, concepts::product_type T, typename Value = void>
    using exclusive_scan_left_t = typename exclusive_scan_left<Function, T, Value>::type;
  }
}
namespace kumi
{
  template<std::size_t N, std::size_t O, concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto tiles(T&& t)
  {
    static_assert(N > 0 && N <= size_v<T>, "[KUMI] - Invalid tile size");
    if constexpr (N == size_v<T>) return kumi::make_tuple(t);
    else
    {
      constexpr auto proj = function::tiler(index<size_v<T>>, index<N>, index<O>);
      auto const build = [&]<std::size_t... J>(auto Off, std::index_sequence<J...>) {
        using type = builder_make_t<T, element_t<Off + J, T>...>;
        return type{get<Off + J>(KUMI_FWD(t))...};
      };
      return [&]<std::size_t... B, std::size_t... E>(std::index_sequence<B...>, std::index_sequence<E...>) {
        return tuple{build(index<E>, std::make_index_sequence<B>{})...};
      }(get<0>(proj), get<1>(proj));
    }
  }
  template<std::size_t N, concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto windows(T&& t)
  {
    static_assert(N > 0 && N <= size_v<T>, "[KUMI] - Invalid tile size");
    if constexpr (N == size_v<T>) return kumi::make_tuple(t);
    else
    {
      constexpr auto proj = function::tiler(index<size_v<T>>, index<N>, index<1>);
      auto const build = [&]<std::size_t... J>(auto O, std::index_sequence<J...>) {
        using type = builder_make_t<T, element_t<O + J, T>...>;
        return type{get<O + J>(KUMI_FWD(t))...};
      };
      return [&]<std::size_t... B, std::size_t... E>(std::index_sequence<B...>, std::index_sequence<E...>) {
        return tuple{build(index<E>, std::make_index_sequence<B>{})...};
      }(get<0>(proj), get<1>(proj));
    }
  }
  template<std::size_t N, concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto chunks(T&& t)
  {
    static_assert(N > 0 && N <= size_v<T>, "[KUMI] - Invalid tile size");
    if constexpr (N == size_v<T>) return kumi::make_tuple(t);
    else
    {
      constexpr auto proj = function::tiler(index<size_v<T>>, index<N>, index<N>);
      auto const build = [&]<std::size_t... J>(auto O, std::index_sequence<J...>) {
        using type = builder_make_t<T, element_t<O + J, T>...>;
        return type{get<O + J>(KUMI_FWD(t))...};
      };
      return [&]<std::size_t... B, std::size_t... E>(std::index_sequence<B...>, std::index_sequence<E...>) {
        return tuple{build(index<E>, std::make_index_sequence<B>{})...};
      }(get<0>(proj), get<1>(proj));
    }
  }
  namespace result
  {
    template<std::size_t N, std::size_t O, kumi::concepts::product_type T> struct tiles
    {
      using type = decltype(kumi::tiles<N, O>(std::declval<T>()));
    };
    template<std::size_t N, kumi::concepts::product_type T> struct windows
    {
      using type = decltype(kumi::windows<N>(std::declval<T>()));
    };
    template<std::size_t N, kumi::concepts::product_type T> struct chunks
    {
      using type = decltype(kumi::chunks<N>(std::declval<T>()));
    };
    template<std::size_t N, std::size_t O, kumi::concepts::product_type T>
    using tiles_t = typename tiles<N, O, T>::type;
    template<std::size_t N, kumi::concepts::product_type T> using windows_t = typename windows<N, T>::type;
    template<std::size_t N, kumi::concepts::product_type T> using chunks_t = typename chunks<N, T>::type;
  }
}
namespace kumi
{
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto transpose(T&& t)
  {
    static_assert(_::supports_transpose<T>, "[KUMI] - Cannot transpose given product type");
    if constexpr (concepts::empty_product_type<T>) return tuple{};
    else if constexpr (concepts::record_type<T>) return transpose(values_of(KUMI_FWD(t)));
    else
    {
      constexpr std::size_t count = size_v<T>;
      constexpr std::size_t size = size_v<element_t<0, T>>;
      constexpr auto pos = function::zipper(index<count>, index<size>);
      auto maps = [&]<std::size_t... I>(auto k, std::index_sequence<I...>) {
        using type = builder_make_t<element_t<0, T>, element_t<k, std::remove_cvref_t<element_t<I, T>>>...>;
        return type{get<k>(get<I>(KUMI_FWD(t)))...};
      };
      return [&]<std::size_t... N>(std::index_sequence<N...>) {
        return kumi::make_tuple(maps(index<N>, get<0>(pos))...);
      }(get<1>(pos));
    }
  }
  namespace result
  {
    template<concepts::product_type T> struct transpose
    {
      using type = decltype(kumi::transpose(std::declval<T>()));
    };
    template<concepts::product_type T> using transpose_t = typename transpose<T>::type;
  }
}
namespace kumi
{
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto unique(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return KUMI_FWD(t);
    else
    {
      constexpr auto pos = function::uniqued(as<T>{});
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using ret_t = builder_make_t<T, element_t<pos.t[I], T>...>;
        return ret_t{get<pos.t[I]>(KUMI_FWD(t))...};
      }(std::make_index_sequence<pos.count>{});
    }
  }
  template<concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto all_unique(T&& t)
  {
    if constexpr (concepts::empty_product_type<T>) return t;
    else
    {
      constexpr auto proj = [&]<std::size_t... I>(std::index_sequence<I...>) {
        return function::uniquer(std::type_identity<stored_element_t<I, T>>{}...);
      }(std::make_index_sequence<size_v<T>>{});
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        using type = builder_make_t<T, element_t<proj.e[I], T>...>;
        return type{get<proj.e[I]>(KUMI_FWD(t))...};
      }(std::make_index_sequence<proj.count>{});
    }
  }
  namespace result
  {
    template<concepts::product_type T> struct unique
    {
      using type = decltype(kumi::unique(std::declval<T>()));
    };
    template<concepts::product_type T> struct all_unique
    {
      using type = decltype(kumi::all_unique(std::declval<T>()));
    };
    template<concepts::product_type T> using unique_t = typename unique<T>::type;
    template<concepts::product_type T> using all_unique_t = typename all_unique<T>::type;
  }
}
namespace kumi
{
  template<concepts::product_type T0, concepts::sized_product_type<size_v<T0>>... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto zip(T0&& t0, Ts&&... ts)
  requires(concepts::follows_same_semantic<T0, Ts...>)
  {
    if constexpr (concepts::sized_product_type<T0, 0>) return tuple{};
    else
    {
      constexpr auto count = 1 + sizeof...(Ts);
      constexpr auto pos = function::zipper(index<count>, index<size_v<T0>>);
      using res_type = common_product_type_t<std::remove_cvref_t<T0>, std::remove_cvref_t<Ts>...>;
      auto maps = [&]<std::size_t... I>(auto k, std::index_sequence<I...>) {
        auto tps = kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...);
        using type = builder_make_t<res_type, element_t<k, element_t<I, decltype(tps)>>...>;
        return type{get<k>(get<I>(KUMI_FWD(tps)))...};
      };
      return [&]<std::size_t... N>(std::index_sequence<N...>) {
        return kumi::make_tuple(maps(index<N>, get<0>(pos))...);
      }(get<1>(pos));
    }
  }
  template<concepts::product_type T0, concepts::product_type... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto zip_min(T0&& t0, Ts&&... ts)
  requires(concepts::follows_same_semantic<T0, Ts...>)
  {
    constexpr std::size_t min = _::min(size_v<T0>, size_v<Ts>...);
    if constexpr (min == 0) return tuple{};
    else
    {
      constexpr std::size_t count = 1 + sizeof...(Ts);
      constexpr auto pos = function::zipper(index<count>, index<min>);
      using res_type = common_product_type_t<std::remove_cvref_t<T0>, std::remove_cvref_t<Ts>...>;
      auto maps = [&]<std::size_t... I>(auto E, std::index_sequence<I...>) {
        auto tps = kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...);
        using type = builder_make_t<res_type, element_t<E, element_t<I, decltype(tps)>>...>;
        return type{get<E>(get<I>(KUMI_FWD(tps)))...};
      };
      return [&]<std::size_t... N>(std::index_sequence<N...>) {
        return kumi::make_tuple(maps(index<N>, get<0>(pos))...);
      }(get<1>(pos));
    }
  }
  template<concepts::product_type T0, concepts::product_type... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto zip_max(T0&& t0, Ts&&... ts)
  requires(concepts::follows_same_semantic<T0, Ts...>)
  {
    constexpr std::size_t max = _::max(size_v<T0>, size_v<Ts>...);
    if constexpr (max == 0) return tuple{};
    else
    {
      constexpr std::size_t count = 1 + sizeof...(Ts);
      constexpr auto pos = function::zipper(index<count>, index<max>);
      using res_type = common_product_type_t<std::remove_cvref_t<T0>, std::remove_cvref_t<Ts>...>;
      auto maps = [&]<std::size_t... I>(auto k, std::index_sequence<I...>) {
        auto tps = kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...);
        using type = builder_make_t<res_type, function::element_or_t<k, element_t<I, decltype(tps)>, kumi::unit>...>;
        return type{function::get_or<k>(get<I>(KUMI_FWD(tps)), kumi::none)...};
      };
      return [&]<std::size_t... N>(std::index_sequence<N...>) {
        return kumi::make_tuple(maps(index<N>, get<0>(pos))...);
      }(get<1>(pos));
    }
  }
  namespace result
  {
    template<concepts::product_type T0, concepts::sized_product_type<size_v<T0>>... Ts> struct zip
    {
      using type = decltype(kumi::zip(std::declval<T0>(), std::declval<Ts>()...));
    };
    template<concepts::product_type T0, concepts::product_type... Ts> struct zip_min
    {
      using type = decltype(kumi::zip_min(std::declval<T0>(), std::declval<Ts>()...));
    };
    template<concepts::product_type T0, concepts::product_type... Ts> struct zip_max
    {
      using type = decltype(kumi::zip_max(std::declval<T0>(), std::declval<Ts>()...));
    };
    template<concepts::product_type T0, concepts::product_type... Ts> using zip_t = typename zip<T0, Ts...>::type;
    template<concepts::product_type T0, concepts::product_type... Ts>
    using zip_min_t = typename zip_min<T0, Ts...>::type;
    template<concepts::product_type T0, concepts::product_type... Ts>
    using zip_max_t = typename zip_max<T0, Ts...>::type;
  }
}
#endif
