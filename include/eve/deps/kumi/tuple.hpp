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
#define KUMI_FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
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
namespace kumi::_
{
  inline namespace cxx20
  {
    struct adl_tag_t
    {
    } inline constexpr adl_tag;
  }
}
#include <cstddef>
#include <concepts>
#include <iosfwd>
#include <type_traits>
#include <utility>
namespace kumi::_
{
  KUMI_ABI consteval std::size_t min(std::same_as<std::size_t> auto... sizes) noexcept
  {
    std::size_t result = std::size_t(-1);
    return ((result = (result < sizes ? result : sizes)), ...);
  }
  KUMI_ABI consteval std::size_t max(std::same_as<std::size_t> auto... sizes) noexcept
  {
    std::size_t result{};
    return ((result = (result > sizes ? result : sizes)), ...);
  }
  KUMI_ABI consteval std::size_t nth_pos(std::size_t I, std::same_as<bool> auto... b) noexcept
  {
    std::size_t seen{}, i{}, idx{};
    ((b ? (seen++ == I ? (i = idx, idx++) : idx++) : idx++), ...);
    return i;
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
  KUMI_ABI consteval std::size_t nb_blocks(std::size_t Sz, std::size_t Stride, std::size_t Extent) noexcept
  {
    return (Sz <= Extent) ? 1 : (Sz - Extent + Stride - 1) / Stride + 1;
  }
  KUMI_ABI consteval std::size_t block_size(std::size_t I,
                                            std::size_t Stride,
                                            std::size_t Extent,
                                            std::size_t Size) noexcept
  {
    std::size_t s = I * Stride;
    return (s < Size) ? ((s + Extent > Size) ? (Size - s) : Extent) : 0;
  }
  struct digits_
  {
    template<typename F, std::size_t... Base, std::size_t... Is>
    KUMI_ABI consteval auto operator()(F func, std::index_sequence<Base...>, std::index_sequence<Is...>) const noexcept
    {
      if constexpr (sizeof...(Base) == 0) return std::make_index_sequence<0>{};
      else return std::index_sequence<func(Base, Is...)...>{};
    }
  };
  template<typename T, auto> struct repeat
  {
    using type = T;
  };
  template<typename T, auto I> using repeat_t = typename kumi::_::repeat<T, I>::type;
  template<typename T, auto N> struct as_homogeneous
  {
    template<std::size_t... I>
    static consteval auto homogeneify(std::index_sequence<I...>) -> tuple<kumi::_::repeat_t<T, I>...>;
    using type = std::remove_cvref_t<decltype(homogeneify(std::make_index_sequence<N>{}))>;
  };
  template<typename T, auto N> using as_homogeneous_t = typename kumi::_::as_homogeneous<T, N>::type;
  inline constexpr kumi::_::container_of_index_t container_of_index{};
  inline constexpr kumi::_::element_of_index_t element_of_index{};
  inline constexpr kumi::_::unflatten_index_t unflatten_index{};
  inline constexpr kumi::_::digits_ digits{};
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
           kumi::_::no_references<KUMI_PP_ENUM(N, KUMI_PP_TAC, T)>)                                                    \
  struct binder<std::index_sequence<KUMI_PP_ENUM(N, KUMI_PP_IDENTITY, _)>, KUMI_PP_ENUM(N, KUMI_PP_TAC, T)>            \
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
    template<kumi::_::identifier I> KUMI_ABI constexpr auto& operator()(I) & noexcept                                  \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_LVALUE, I)                                                                       \
    }                                                                                                                  \
    template<kumi::_::identifier I> KUMI_ABI constexpr auto&& operator()(I) && noexcept                                \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_RVALUE, I)                                                                       \
    }                                                                                                                  \
    template<kumi::_::identifier I> KUMI_ABI constexpr auto const&& operator()(I) const&& noexcept                     \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_CONST_RVALUE, I)                                                                 \
    }                                                                                                                  \
    template<kumi::_::identifier I> KUMI_ABI constexpr auto const& operator()(I) const& noexcept                       \
    {                                                                                                                  \
      KUMI_PP_REPEAT(N, KUMI_GET_NAME_LVALUE, I)                                                                       \
    }                                                                                                                  \
  };
namespace kumi::_
{
  template<auto V> struct value
  {
    using type = decltype(V);
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
  concept valid_label =
    kumi::_::implicit_constructible<T> &&
    (!requires { to_str(T{}); } ||
    requires
    {
      { std::bool_constant<(to_str(T{}), true)>{} } -> std::same_as<std::true_type>;
      { to_str(T{}) } -> std::same_as<kumi::str>;
    });
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
  template<kumi::_::field T> struct identifier_of
  {
    using type = typename std::remove_cvref_t<T>::identifier_type;
  };
  template<kumi::_::field T> struct type_of
  {
    using type = typename std::remove_cvref_t<T>::type;
  };
  template<kumi::_::field T> struct label_of
  {
    using type = typename std::remove_cvref_t<T>::label_type;
  };
  template<kumi::_::field T> using identifier_of_t = typename kumi::_::identifier_of<std::remove_cvref_t<T>>::type;
  template<kumi::_::field T> using type_of_t = typename kumi::_::type_of<std::remove_cvref_t<T>>::type;
  template<kumi::_::field T> using label_of_t = typename kumi::_::label_of<std::remove_cvref_t<T>>::type;
  template<typename T>
  concept identifier = requires(T const& t) { typename std::remove_cvref_t<T>::type; };
  template<kumi::_::identifier T> struct tag_of
  {
    using type = typename std::remove_cvref_t<T>::type;
  };
  template<kumi::_::identifier T> using tag_of_t = typename kumi::_::tag_of<std::remove_cvref_t<T>>::type;
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
  concept piecewise_convertible =
    kumi::_::is_piecewise_convertible<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename From, typename To>
  concept piecewise_constructible =
    kumi::_::is_piecewise_constructible<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename From, typename To>
  concept piecewise_ordered = kumi::_::is_piecewise_ordered<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename From, typename To>
  concept piecewise_comparable =
    kumi::_::is_piecewise_comparable<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::value;
  template<typename Field> struct check_value
  {
    static consteval void get(...);
  };
  template<kumi::_::field F> struct check_value<F>
  {
    template<kumi::_::field T>
    requires(std::is_same_v<kumi::_::identifier_of_t<F>, kumi::_::identifier_of_t<T>>)
    static consteval kumi::_::type_of_t<F> get(T);
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
    using u_list = Box<kumi::_::type_of_t<Us>...>;
    using is_fieldwise_constructible = kumi::_::is_piecewise_constructible<t_list, u_list>;
    using is_fieldwise_convertible = kumi::_::is_piecewise_convertible<t_list, u_list>;
    using is_fieldwise_comparable = kumi::_::is_piecewise_comparable<t_list, u_list>;
  };
  template<typename From, typename To>
  concept fieldwise_convertible =
    kumi::_::sort<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::is_fieldwise_convertible::value;
  template<typename From, typename To>
  concept fieldwise_constructible =
    kumi::_::sort<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::is_fieldwise_constructible::value;
  template<typename From, typename To>
  concept fieldwise_comparable =
    kumi::_::sort<std::remove_cvref_t<From>, std::remove_cvref_t<To>>::is_fieldwise_comparable::value;
  struct find_failed
  {
    static consteval std::false_type get(...);
    static consteval kumi::_::invalid get_index(...);
  };
  template<template<class, class> class Matcher, std::size_t I, typename Ref, typename Field> struct match_node
  {
    static consteval std::false_type get();
    static consteval kumi::_::invalid get_index();
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
  struct find_engine<Matcher, Ref, std::index_sequence<I...>, Fields...>
    : find_failed, kumi::_::match_node<Matcher, I, Ref, Fields>...
  {
    using kumi::_::find_failed::get;
    using kumi::_::find_failed::get_index;
    using kumi::_::match_node<Matcher, I, Ref, Fields>::get...;
    using kumi::_::match_node<Matcher, I, Ref, Fields>::get_index...;
    using type = decltype(get(std::declval<Ref>()));
    static constexpr auto value = decltype(get_index(std::declval<Ref>()))::value;
  };
  template<typename Ref, typename Field> struct match_by_type : std::is_same<Ref, Field>
  {
  };
  template<typename Ref, typename... Fields>
  using find_by_type_t =
    kumi::_::find_engine<kumi::_::match_by_type, Ref, std::index_sequence_for<Fields...>, Fields...>;
  template<typename Ref, typename... Fields>
  using get_field_by_type_t = typename kumi::_::find_by_type_t<Ref, Fields...>::type;
  template<typename Ref, typename... Fields>
  inline constexpr auto get_index_by_type_v = kumi::_::find_by_type_t<Ref, Fields...>::value;
  template<typename Ref, typename... Fields>
  concept can_get_field_by_type = !std::is_same_v<kumi::_::get_field_by_type_t<Ref, Fields...>, std::false_type>;
  template<typename Ref, typename Field> struct match_by_tag : std::false_type
  {
  };
  template<kumi::_::identifier Ref, kumi::_::field Field>
  struct match_by_tag<Ref, Field> : std::is_same<kumi::_::tag_of_t<Ref>, kumi::_::identifier_of_t<Field>>
  {
  };
  template<typename Ref, typename... Fields>
  using find_by_tag_t = kumi::_::find_engine<kumi::_::match_by_tag, Ref, std::index_sequence_for<Fields...>, Fields...>;
  template<typename Ref, typename... Fields>
  using get_field_by_value_t = typename kumi::_::find_by_tag_t<Ref, Fields...>::type;
  template<typename Ref, typename... Fields>
  inline constexpr auto get_index_by_value_v = kumi::_::find_by_tag_t<Ref, Fields...>::value;
  template<typename Ref, typename... Fields>
  concept can_get_field_by_value = !std::is_same_v<kumi::_::get_field_by_value_t<Ref, Fields...>, std::false_type>;
  template<typename Ref, typename Field> struct match_by_label : std::false_type
  {
  };
  template<kumi::_::label Ref, kumi::_::field Field>
  struct match_by_label<Ref, Field> : std::bool_constant<Ref::value == Field::label()>
  {
  };
  template<typename Ref, typename... Fields>
  using find_by_label_t =
    kumi::_::find_engine<kumi::_::match_by_label, Ref, std::index_sequence_for<Fields...>, Fields...>;
  template<typename Ref, typename... Fields>
  using get_field_by_label_t = typename kumi::_::find_by_label_t<Ref, Fields...>::type;
  template<typename Ref, typename... Fields>
  inline constexpr auto get_index_by_label_v = kumi::_::find_by_label_t<Ref, Fields...>::value;
  template<typename Ref, typename... Fields>
  concept can_get_field_by_label = !std::is_same_v<kumi::_::get_field_by_label_t<Ref, Fields...>, std::false_type>;
}
namespace kumi::_
{
  template<std::size_t I, typename T> consteval auto get_key()
  {
    using type = std::remove_cvref_t<T>;
    if constexpr (kumi::_::field<T>) return typename type::identifier_type{};
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
  template<std::size_t I, kumi::_::field T> struct unique_name<I, T>
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
    static constexpr std::size_t npos = static_cast<std::size_t>(-1);
    static constexpr char separator = '.';
    char data_[max_size + 1] = {0};
    unsigned int size_;
    constexpr str() = default;
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
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, str const& s) noexcept
    {
      os << '\'';
      for (std::size_t i = 0; i < s.size(); ++i) os << s.data_[i];
      return os << '\'';
    }
    KUMI_ABI constexpr str remove_prefix(std::size_t n) const
    {
      if (n > size_) throw "Out of range";
      return substr(n, size_ - n);
    }
    KUMI_ABI constexpr str remove_suffix(std::size_t n) const
    {
      if (n > size_) throw "Out of range";
      return substr(0, size_ - n);
    }
    KUMI_ABI constexpr str substr(std::size_t pos = 0, std::size_t count = npos) const
    {
      std::size_t len = (count == npos || pos + count > size_) ? (size_ - pos) : count;
      str res{};
      res.size_ = static_cast<unsigned int>(len);
      for (std::size_t i = 0; i < len; ++i) res.data_[i] = data_[pos + i];
      return res;
    }
    KUMI_ABI constexpr bool starts_with(str const& s) const
    {
      if (s.size_ > size_) return false;
      for (std::size_t i = 0; i < s.size_; ++i)
        if (data_[i] != s.data_[i]) return false;
      return true;
    }
    KUMI_ABI constexpr bool ends_with(str const& s) const
    {
      if (s.size_ > size_) return false;
      for (std::size_t i = 0; i < s.size_; ++i)
        if (data_[size_ - s.size_ + i] != s.data_[i]) return false;
      return true;
    }
    KUMI_ABI constexpr bool contains(str const& s) const { return find(s) != npos; }
    constexpr std::size_t find(str const& s, std::size_t pos = 0) const
    {
      if (s.size_ == 0) return pos <= size_ ? pos : npos;
      if (s.size_ > size_) return npos;
      for (std::size_t i = pos; i <= size_ - s.size_; ++i)
      {
        bool match = true;
        for (std::size_t j = 0; j < s.size_; ++j)
          if (data_[i + j] != s.data_[j])
          {
            match = false;
            break;
          }
        if (match) return i;
      }
      return npos;
    }
    constexpr int compare(str const& other) const noexcept
    {
      std::size_t min_size = (size_ < other.size_) ? size_ : other.size_;
      for (std::size_t i = 0; i < min_size; ++i)
      {
        if (data_[i] < other.data_[i]) return -1;
        if (data_[i] > other.data_[i]) return 1;
      }
      if (size_ < other.size_) return -1;
      if (size_ > other.size_) return 1;
      return 0;
    }
    friend constexpr bool operator==(str const& lhs, str const& rhs) noexcept { return lhs.compare(rhs) == 0; }
    friend constexpr bool operator!=(str const& lhs, str const& rhs) noexcept { return lhs.compare(rhs) != 0; }
    friend constexpr bool operator<(str const& lhs, str const& rhs) noexcept { return lhs.compare(rhs) < 0; }
    friend constexpr bool operator<=(str const& lhs, str const& rhs) noexcept { return lhs.compare(rhs) <= 0; }
    friend constexpr bool operator>(str const& lhs, str const& rhs) noexcept { return lhs.compare(rhs) > 0; }
    friend constexpr bool operator>=(str const& lhs, str const& rhs) noexcept { return lhs.compare(rhs) >= 0; }
    constexpr std::size_t rfind(str const& s, std::size_t pos = npos) const
    {
      if (s.size_ == 0) return (pos > size_ ? size_ : pos);
      if (s.size_ > size_) return npos;
      std::size_t start = (pos > size_ - s.size_) ? (size_ - s.size_) : pos;
      for (int i = static_cast<int>(start); i >= 0; --i)
      {
        bool match = true;
        for (std::size_t j = 0; j < s.size_; ++j)
          if (data_[i + j] != s.data_[j])
          {
            match = false;
            break;
          }
        if (match) return static_cast<std::size_t>(i);
      }
      return npos;
    }
    KUMI_ABI constexpr std::size_t find_first_of(str const& s, std::size_t pos = 0) const
    {
      for (std::size_t i = pos; i < size_; ++i)
        for (std::size_t j = 0; j < s.size_; ++j)
          if (data_[i] == s.data_[j]) return i;
      return npos;
    }
    KUMI_ABI constexpr std::size_t find_last_of(str const& s, std::size_t pos = npos) const
    {
      if (size_ == 0) return npos;
      for (std::size_t i = (pos >= size_ ? size_ - 1 : pos);; --i)
      {
        for (std::size_t j = 0; j < s.size_; ++j)
          if (data_[i] == s.data_[j]) return i;
        if (i == 0) break;
      }
      return npos;
    }
    KUMI_ABI constexpr std::size_t find_first_not_of(str const& s, std::size_t pos = 0) const
    {
      for (std::size_t i = pos; i < size_; ++i)
      {
        bool found = false;
        for (std::size_t j = 0; j < s.size_; ++j)
          if (data_[i] == s.data_[j])
          {
            found = true;
            break;
          }
        if (!found) return i;
      }
      return npos;
    }
    KUMI_ABI constexpr std::size_t find_last_not_of(str const& s, std::size_t pos = npos) const
    {
      if (size_ == 0) return npos;
      for (std::size_t i = (pos >= size_ ? size_ - 1 : pos);; --i)
      {
        bool found = false;
        for (std::size_t j = 0; j < s.size_; ++j)
          if (data_[i] == s.data_[j])
          {
            found = true;
            break;
          }
        if (!found) return i;
        if (i == 0) break;
      }
      return npos;
    }
    constexpr str operator+(str const& other) const
    {
      std::size_t new_size = size_ + 1 + other.size_;
      if (new_size > max_size) throw "Overflow";
      str res{};
      res.size_ = static_cast<unsigned int>(new_size);
      for (std::size_t i = 0; i < size_; ++i) res.data_[i] = data_[i];
      res.data_[size_] = kumi::str::separator;
      for (std::size_t i = 0; i < other.size_; ++i) res.data_[size_ + 1 + i] = other.data_[i];
      res.data_[new_size] = '\0';
      return res;
    }
    static constexpr str from(char const* s, std::size_t n)
    {
      str res{};
      if (n > str::max_size) throw "Overflow";
      for (std::size_t i = 0; i < n; ++i) res.data_[i] = s[i];
      res.size_ = static_cast<unsigned int>(n);
      return res;
    }
  };
  inline namespace literals
  {
    constexpr auto operator""_str(char const* s, std::size_t n)
    {
      return kumi::str::from(s, n);
    }
  }
  struct unknown
  {
    constexpr inline operator kumi::str() const noexcept { return str{"kumi::unknown"}; }
    KUMI_ABI friend constexpr auto operator<=>(unknown const&, unknown const&) noexcept = default;
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, unknown const&) noexcept
    {
      return os << "kumi::unknown";
    }
  };
}
namespace kumi::_
{
  template<typename T> [[nodiscard]] KUMI_ABI consteval auto typer() noexcept
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
  template<kumi::_::valid_label T> consteval kumi::str make_str(T const& t)
  {
    if constexpr (requires { to_str(t); }) return to_str(t);
    else return kumi::_::typer<std::remove_cvref_t<T>>();
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
  template<typename T> [[nodiscard]] KUMI_ABI consteval str label_of() noexcept
  {
    if constexpr (kumi::_::field<T>) return kumi::_::label_of_t<T>{};
    else return kumi::unknown{};
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
    template<kumi::_::identifier auto Name, typename T> struct capture_field
    {
      using type = decltype(kumi::capture_field<Name>(std::declval<T>()));
    };
    template<typename U, typename T> struct field_cast
    {
      using type = decltype(kumi::field_cast<U, T>(std::declval<T>()));
    };
    template<typename T> using identifier_of_t = typename kumi::result::identifier_of<T>::type;
    template<typename T> using label_of_t = typename kumi::result::label_of<T>::type;
    template<typename T> using field_value_of_t = typename kumi::result::field_value_of<T>::type;
    template<_::identifier auto Name, typename T>
    using capture_field_t = typename kumi::result::capture_field<Name, T>::type;
    template<typename U, typename T> using field_cast_t = typename kumi::result::field_cast<U, T>::type;
  }
}
namespace kumi::_
{
  template<std::size_t N, typename T> struct leaf
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
  template<std::size_t N, typename T>
  requires(std::is_empty_v<T> && (!std::is_final_v<T>) && (!kumi::_::field<T>))
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
  template<std::size_t N, kumi::_::field T> struct leaf<N, T> : T
  {
    using T::operator();
    using index = std::integral_constant<std::size_t, N>;
    using key = kumi::_::identifier_of_t<T>;
    using inner_type = kumi::_::type_of_t<T>;
    KUMI_ABI constexpr T& operator()(index) & noexcept { return *this; }
    KUMI_ABI constexpr T&& operator()(index) && noexcept { return static_cast<T&&>(*this); }
    KUMI_ABI constexpr T const&& operator()(index) const&& noexcept { return static_cast<T const&&>(*this); }
    KUMI_ABI constexpr T const& operator()(index) const& noexcept { return *this; }
  };
  template<typename ISeq, typename... Ts> struct binder;
  template<std::size_t... Is, typename... Ts>
  struct binder<std::index_sequence<Is...>, Ts...> : kumi::_::leaf<Is, Ts>...
  {
    static constexpr bool is_homogeneous = false;
    using kumi::_::leaf<Is, Ts>::operator()...;
  };
  template<typename ISeq, typename... Ts> struct make_binder
  {
    using type = kumi::_::binder<ISeq, Ts...>;
  };
  template<typename ISeq, typename... Ts> using make_binder_t = typename kumi::_::make_binder<ISeq, Ts...>::type;
  template<typename... Ts> struct set : Ts...
  {
    using Ts::operator()...;
  };
  template<typename... Ts> struct make_set
  {
    using type = kumi::_::set<Ts...>;
  };
  template<typename... Ts> using make_set_t = typename kumi::_::make_set<Ts...>::type;
}
namespace kumi::_
{
  template<typename... Ts> inline constexpr bool no_references = (true && ... && !std::is_reference_v<Ts>);
  template<typename... Ts> inline constexpr bool no_empty = (true && ... && !std::is_empty_v<Ts>);
  template<typename T0, typename... Ts> inline constexpr bool all_the_same = (true && ... && std::is_same_v<T0, Ts>);
  template<typename T0, std::size_t N> struct binder_n
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
  template<std::size_t... Is, typename T0, typename T1, typename... Ts>
  requires(kumi::_::all_the_same<T0, T1, Ts...> && kumi::_::no_references<T0, T1, Ts...> &&
           kumi::_::no_empty<T0, T1, Ts...>)
  struct make_binder<std::index_sequence<Is...>, T0, T1, Ts...>
  {
    using type = kumi::_::binder_n<T0, 2 + sizeof...(Ts)>;
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
    template<typename T>
    concept non_empty_tuple = requires(T const& t) {
      typename std::tuple_element<0, std::remove_cvref_t<T>>::type;
      typename std::tuple_size<std::remove_cvref_t<T>>::type;
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
  }
  template<typename T> struct is_product_type : std::false_type
  {
  };
  template<typename T> inline constexpr auto is_product_type_v = kumi::is_product_type<T>::value;
  template<typename T, typename Enable = void> struct is_record_type : std::false_type
  {
  };
  template<typename T> struct is_record_type<T, typename T::is_record_type> : std::true_type
  {
  };
  template<typename T> inline constexpr auto is_record_type_v = kumi::is_record_type<T>::value;
  template<typename T> struct size : std::tuple_size<std::remove_cvref_t<T>>
  {
  };
  template<typename T> inline constexpr auto size_v = kumi::size<T>::value;
  template<std::size_t I, typename T> struct element : std::tuple_element<I, std::remove_cvref_t<T>>
  {
  };
  template<std::size_t I, typename T> using element_t = typename kumi::element<I, T>::type;
  template<std::size_t I, typename T> struct member
  {
    using type = decltype(get<I>(std::declval<T&&>()));
  };
  template<std::size_t I, typename T> using member_t = typename kumi::member<I, T>::type;
}
namespace kumi
{
  template<typename T> struct is_container : std::false_type
  {
    using value_type = T;
    using size = kumi::_::invalid;
  };
  template<typename T>
  requires kumi::_::container_like<T>
  struct is_container<T> : std::true_type
  {
    using value_type = typename T::value_type;
    using size = kumi::_::invalid;
  };
  template<template<class, std::size_t> typename Container, typename T, std::size_t N>
  requires kumi::_::container_like<Container<T, N>> && (N != static_cast<std::size_t>(-1))
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
  template<typename T> inline constexpr auto is_container_v = kumi::is_container<T>::value;
  template<typename T> struct container_size : kumi::is_container<std::remove_cvref_t<T>>::size
  {
  };
  template<typename T> inline constexpr auto container_size_v = kumi::container_size<T>::value;
  template<typename T> struct container_type : kumi::is_container<std::remove_cvref_t<T>>
  {
    using type = typename kumi::is_container<std::remove_cvref_t<T>>::value_type;
  };
  template<typename T> using container_type_t = typename kumi::container_type<T>::type;
}
namespace kumi
{
  template<typename T> struct is_homogeneous
  {
    static consteval bool check()
    {
      if constexpr (!kumi::is_product_type_v<T>) return false;
      else if constexpr (requires { T::is_homogeneous; }) return T::is_homogeneous;
      else if constexpr (kumi::is_record_type_v<T>) return false;
      else if constexpr (kumi::is_container_v<T>) return true;
      else if constexpr (kumi::size_v<T> == 0) return false;
      else if constexpr (kumi::size_v<T> == 1) return true;
      else
        return []<std::size_t... I>(std::index_sequence<I...>) {
          return kumi::_::all_the_same<kumi::element_t<I, T>...>;
        }(std::make_index_sequence<kumi::size_v<T>>{});
    }
    static constexpr bool value = check();
  };
  template<typename T> inline constexpr auto is_homogeneous_v = kumi::is_homogeneous<T>::value;
  template<typename T> struct has_static_size : std::false_type
  {
  };
  template<typename T>
  requires(kumi::_::contiguous_container_like<T>)
  struct has_static_size<T>
  {
    static constexpr bool value = !std::same_as<typename kumi::is_container<T>::size, kumi::_::invalid>;
  };
  template<typename T, std::size_t N> struct has_static_size<T[N]> : std::true_type
  {
  };
  template<typename T> inline constexpr auto has_static_size_v = kumi::has_static_size<T>::value;
  template<typename T> struct is_projection_map : std::false_type
  {
  };
  template<typename T>
  requires(T::is_projection_map)
  struct is_projection_map<T> : std::true_type
  {
  };
  template<typename T> inline constexpr auto is_projection_map_v = kumi::is_projection_map<T>::value;
  template<std::size_t I, typename T> struct stored_member
  {
    using type = kumi::member_t<I, T>;
  };
  template<std::size_t I, typename T>
  requires(kumi::is_record_type_v<std::remove_cvref_t<T>>)
  struct stored_member<I, T>
  {
    using field_type = decltype(get<I>(std::declval<T&&>()));
    using type = decltype(std::declval<field_type&&>()(typename std::remove_cvref_t<field_type>::identifier_type{}));
  };
  template<std::size_t I, typename T> using stored_member_t = typename kumi::stored_member<I, T>::type;
  template<std::size_t I, typename T> struct stored_element
  {
    using type = kumi::element_t<I, T>;
  };
  template<std::size_t I, typename T>
  requires(kumi::is_record_type<std::remove_cvref_t<T>>::value)
  struct stored_element<I, T>
  {
    using type = typename kumi::element_t<I, T>::type;
  };
  template<std::size_t I, typename T> using stored_element_t = typename kumi::stored_element<I, T>::type;
  template<typename Ints, typename... Ts> struct all_uniques;
  template<> struct all_uniques<std::index_sequence<>>
  {
    using type = std::true_type;
  };
  template<std::size_t... Ints, typename... Ts> struct all_uniques<std::index_sequence<Ints...>, Ts...>
  {
    struct all_uniques_inner : kumi::_::unique<Ints, Ts>...
    {
    };
    template<typename... Us>
    static consteval auto is_set(Us...) -> decltype(kumi::_::true_fn(static_cast<Us>(all_uniques_inner())...));
    static consteval std::false_type is_set(...);
    using type = decltype(is_set(std::type_identity<Ts>{}...));
  };
  template<typename... Ts>
  using all_uniques_t = typename kumi::all_uniques<std::index_sequence_for<Ts...>, Ts...>::type;
  template<typename... Ts> inline constexpr auto all_uniques_v = kumi::all_uniques_t<Ts...>::value;
  template<typename Ints, typename... Ts> struct all_unique_names;
  template<> struct all_unique_names<std::index_sequence<>>
  {
    using type = std::true_type;
  };
  template<std::size_t... Ints, typename... Ts> struct all_unique_names<std::index_sequence<Ints...>, Ts...>
  {
    struct all_uniques_inner : kumi::_::unique_name<Ints, Ts>...
    {
    };
    template<typename... Us>
    static consteval auto is_set(Us...) -> decltype(kumi::_::true_fn(static_cast<Us>(all_uniques_inner())...));
    static consteval std::false_type is_set(...);
    using type = decltype(is_set(kumi::_::get_key<Ints, Ts>()...));
  };
  template<typename... Ts>
  using all_unique_names_t = typename kumi::all_unique_names<std::index_sequence_for<Ts...>, Ts...>::type;
  template<typename... Ts> inline constexpr auto all_unique_names_v = kumi::all_unique_names_t<Ts...>::value;
  template<typename Seq, typename T, typename U> struct is_equivalent : std::false_type
  {
  };
  template<std::size_t... Is, typename T, typename U>
  requires(kumi::is_product_type_v<T> && kumi::is_product_type_v<U> && kumi::size_v<T> == kumi::size_v<U>)
  struct is_equivalent<std::index_sequence<Is...>, T, U>
  {
    struct match : kumi::_::unique_name<Is, kumi::element_t<Is, U>>...
    {
    };
    template<typename... Key>
    requires(sizeof...(Is) != 0)
    static consteval auto is_present(Key...) -> decltype(kumi::_::true_fn(static_cast<Key>(std::declval<match>())...));
    static consteval std::false_type is_present(...);
    static consteval std::true_type is_present(...)
    requires(sizeof...(Is) == 0);
    using type = decltype(is_present(kumi::_::get_key<Is, kumi::element_t<Is, T>>()...));
  };
  template<typename T, typename U>
  using is_equivalent_t = typename kumi::is_equivalent<std::make_index_sequence<kumi::size_v<T>>, T, U>::type;
  template<typename T, typename U> inline constexpr bool is_equivalent_v = kumi::is_equivalent_t<T, U>::value;
  template<typename Seq, typename T, typename U> struct is_equality_comparable : std::false_type
  {
  };
  template<std::size_t... Is, typename T, typename U>
  requires(kumi::is_record_type_v<T> && kumi::is_record_type_v<U> && kumi::size_v<T> == kumi::size_v<U>)
  struct is_equality_comparable<std::index_sequence<Is...>, T, U> : kumi::_::check_value<kumi::element_t<Is, T>>...
  {
    using kumi::_::check_value<kumi::element_t<Is, T>>::get...;
    static constexpr bool value = (kumi::_::comparable<decltype(get(std::declval<kumi::element_t<Is, U>>())),
                                                       kumi::_::type_of_t<kumi::element_t<Is, U>>> &&
                                   ...);
    using type = std::bool_constant<(sizeof...(Is) == 0) || value>;
  };
  template<std::size_t... Is, typename T, typename U>
  requires(kumi::is_product_type_v<T> && kumi::is_product_type_v<U> &&
           (!kumi::is_record_type_v<U> || !kumi::is_record_type_v<T>) && kumi::size_v<T> == kumi::size_v<U>)
  struct is_equality_comparable<std::index_sequence<Is...>, T, U>
    : std::bool_constant<(sizeof...(Is) == 0) ||
                         (kumi::_::comparable<kumi::element_t<Is, T>, kumi::element_t<Is, U>> && ...)>
  {
  };
  template<typename T, typename U>
  using is_equality_comparable_t =
    typename kumi::is_equality_comparable<std::make_index_sequence<kumi::size_v<T>>, T, U>::type;
  template<typename T, typename U>
  inline constexpr bool is_equality_comparable_v = kumi::is_equality_comparable_t<T, U>::value;
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
    using type = builder_make_t<T, typename Traits<kumi::element_t<Is, T>>::type...>;
  };
  template<template<typename...> typename Traits, typename T>
  requires kumi::is_product_type_v<std::remove_cvref_t<T>>
  using map_traits_t = typename kumi::map_traits<Traits, T>::type;
}
namespace kumi
{
#ifndef KUMI_DOXYGEN_INVOKED
  template<typename T>
  requires(kumi::_::std_tuple_compatible<T>)
  struct is_product_type<T> : std::true_type
  {
  };
  template<typename T>
  requires(kumi::is_container_v<T> && kumi::has_static_size_v<T> && kumi::_::std_tuple_compatible<T>)
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
  template<typename T> inline constexpr bool is_kumi_tuple_v = kumi::is_kumi_tuple<T>::value;
  template<typename T> struct is_kumi_record : std::false_type
  {
  };
  template<typename... Ts> struct is_kumi_record<kumi::record<Ts...>> : std::true_type
  {
  };
  template<typename T> inline constexpr bool is_kumi_record_v = kumi::is_kumi_record<T>::value;
#endif
}
namespace kumi
{
  namespace _
  {
    template<typename F, typename T, std::size_t... N> consteval auto can_apply(std::index_sequence<N...>)
    {
      return std::invocable<F, kumi::stored_member_t<N, T>...>;
    }
    template<typename F, typename T, std::size_t... N> consteval auto can_nothrow_apply(std::index_sequence<N...>)
    {
      return std::is_nothrow_invocable_v<F, kumi::stored_member_t<N, T>...>;
    }
    template<std::size_t I, typename F, typename... Ts> consteval auto can_call_impl()
    {
      return std::invocable<F, kumi::stored_member_t<I, Ts>...>;
    }
    template<typename F, typename... Ts, std::size_t... N> consteval auto can_call(std::index_sequence<N...>)
    {
      return (can_call_impl<N, F, Ts...>() && ...);
    }
    template<typename T, std::size_t... N> consteval auto can_transpose(std::index_sequence<N...>)
    {
      return ((kumi::size_v<kumi::stored_member_t<0, T>> == kumi::size_v<kumi::stored_member_t<N + 1, T>>) && ...);
    }
    template<typename F, typename T>
    concept supports_apply = can_apply<F, T>(std::make_index_sequence<kumi::size_v<T>>{});
    template<typename F, typename T>
    concept supports_nothrow_apply = can_nothrow_apply<F, T>(std::make_index_sequence<kumi::size_v<T>>{});
    template<typename F, typename... Ts>
    concept supports_call = can_call<F, Ts...>(std::make_index_sequence<kumi::_::max(kumi::size_v<Ts>...)>{});
    template<typename T>
    concept supports_transpose =
      (kumi::size_v<T> <= 1) || can_transpose<T>(std::make_index_sequence<kumi::size_v<T> - 1>{});
  }
  namespace concepts
  {
    template<typename T>
    concept product_type = kumi::is_product_type<std::remove_cvref_t<T>>::value;
    template<typename T>
    concept record_type = kumi::concepts::product_type<T> && kumi::is_record_type<std::remove_cvref_t<T>>::value;
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
      (sizeof...(Ts) == 0) || (kumi::concepts::fully_named<Ts...> &&
                               (kumi::all_uniques_v<kumi::_::value<std::remove_cvref_t<Ts>::label()>...>));
    template<typename T, typename... Ts>
    concept contains_type = kumi::_::can_get_field_by_type<T, Ts...>;
    template<typename Name, typename... Ts>
    concept contains_identifier = kumi::concepts::identifier<Name> && kumi::_::can_get_field_by_value<Name, Ts...>;
    template<typename Label, typename... Ts>
    concept contains_label =
      std::is_same_v<std::remove_cvref_t<decltype(std::remove_cvref_t<Label>::value)>, kumi::str> &&
      kumi::_::can_get_field_by_label<std::remove_cvref_t<Label>, Ts...>;
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
    template<template<typename...> typename Meta, typename Target, typename PT> consteval auto can_query()
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return !std::is_same_v<Meta<Target, kumi::element_t<I, PT>...>, std::false_type>;
      }(std::make_index_sequence<kumi::size_v<PT>>{});
    }
    template<typename Type, typename T>
    concept queryable_by_type = kumi::concepts::product_type<T> && can_query<kumi::_::find_by_type_t, Type, T>();
    template<typename Id, typename T>
    concept queryable_by_identifier =
      kumi::concepts::identifier<Id> && kumi::concepts::product_type<T> && can_query<kumi::_::find_by_tag_t, Id, T>();
    template<typename L, typename T>
    concept queryable_by_label =
      kumi::_::label<L> && kumi::concepts::product_type<T> && can_query<kumi::_::find_by_label_t, L, T>();
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
    friend constexpr kumi::str to_str(identifier const&) { return kumi::_::make_str(ID{}); }
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
    friend constexpr kumi::str to_str(name const&) { return ID; }
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
    template<auto N, typename... Ts> KUMI_ABI consteval auto contains_identifier()
    {
      if constexpr (std::integral<std::remove_cvref_t<decltype(N)>>) return false;
      else if constexpr (kumi::concepts::index<decltype(N)>) return false;
      else if constexpr (kumi::concepts::identifier<std::remove_cvref_t<decltype(N)>>) return false;
      else return kumi::_::can_get_field_by_value<kumi::name<N>, Ts...>;
    }
    template<auto N, typename... Ts> KUMI_ABI consteval auto contains_label()
    {
      if constexpr (std::integral<std::remove_cvref_t<decltype(N)>>) return false;
      else if constexpr (kumi::concepts::index<decltype(N)>) return false;
      else if constexpr (!std::is_same_v<std::remove_cvref_t<decltype(N)>, kumi::str>) return false;
      else return kumi::_::can_get_field_by_label<std::integral_constant<kumi::str, N>, Ts...>;
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
  template<std::size_t N> inline constexpr kumi::index_t<N> const index = {};
  template<kumi::str Label> struct label_t
  {
    using type = str;
    static constexpr kumi::str value = Label;
    constexpr inline operator kumi::str() const noexcept { return Label; }
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
      return kumi::_::get_index_by_type_v<U, kumi::stored_element_t<I, T>...>;
    }(std::make_index_sequence<kumi::size_v<T>>{});
  }
  template<kumi::concepts::identifier Id, kumi::concepts::product_type T>
  KUMI_ABI consteval auto get_index_of_field()
  requires(kumi::concepts::queryable_by_identifier<Id, T>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::_::get_index_by_value_v<Id, kumi::element_t<I, T>...>;
    }(std::make_index_sequence<kumi::size_v<T>>{});
  }
  template<kumi::str L, kumi::concepts::product_type T>
  KUMI_ABI consteval auto get_index_of_label()
  requires(kumi::concepts::queryable_by_label<kumi::label_t<L>, T>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::_::get_index_by_label_v<kumi::label_t<L>, kumi::element_t<I, T>...>;
    }(std::make_index_sequence<kumi::size_v<T>>{});
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
    struct value_at<I, kumi::projection_map<Head, Tail...>> : kumi::_::value_at<I - 1, kumi::projection_map<Tail...>>
    {
    };
    template<std::size_t I, auto... Vs> struct value_at<I, kumi::projection_map<Vs...> const>
    {
      static constexpr auto value = kumi::_::value_at<I, kumi::projection_map<Vs...>>::value;
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
    KUMI_ABI constexpr decltype(auto) operator[]([[maybe_unused]] kumi::index_t<I> i) const noexcept
    {
      return kumi::_::value_at<I, projection_map>::value;
    }
    template<std::size_t I>
    requires(I < sizeof...(V))
    [[nodiscard]] KUMI_ABI friend constexpr decltype(auto) get(projection_map const& pm) noexcept
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
  template<concepts::projection... Ts> KUMI_CUDA projection_map(Ts...) -> projection_map<Ts{}...>;
  template<concepts::index... Ts> [[nodiscard]] KUMI_ABI consteval auto indexes(Ts...) noexcept
  {
    return kumi::projection_map<Ts{}...>{};
  }
  template<std::convertible_to<std::size_t> auto... vs> [[nodiscard]] KUMI_ABI consteval auto make_indexes() noexcept
  {
    return kumi::projection_map<kumi::index<vs>...>{};
  }
  template<concepts::identifier... Ts>
  requires(kumi::all_uniques_v<Ts...>)
  [[nodiscard]] KUMI_ABI consteval auto identifiers(Ts...) noexcept
  {
    return kumi::projection_map<Ts{}...>{};
  }
  template<auto... Vs>
  requires(!kumi::concepts::projection<decltype(Vs)> && ...)
  struct projection_map<Vs...>
  {
    static_assert((kumi::concepts::projection<decltype(Vs)> && ...),
                  "Invalid projections in projection_map definition");
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
    using binder_t = kumi::_::make_binder_t<std::make_index_sequence<sizeof...(Ts)>, Ts...>;
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
      return impl(std::integral_constant<kumi::str, L>{});
    }
    template<kumi::str L>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<L>) && noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<L>, Ts...>)
    {
      return static_cast<binder_t&&>(impl)(std::integral_constant<kumi::str, L>{});
    }
    template<kumi::str L>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<L>) const&& noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<L>, Ts...>)
    {
      return static_cast<binder_t const&&>(impl)(std::integral_constant<kumi::str, L>{});
    }
    template<kumi::str L>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<L>) const& noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<L>, Ts...>)
    {
      return impl(std::integral_constant<kumi::str, L>{});
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
    [[nodiscard]] KUMI_ABI
#ifndef KUMI_DOXYGEN_INVOKED
      explicit(!kumi::_::piecewise_convertible<tuple<Ts const&...>, tuple<Us...>>)
#endif
        constexpr
        operator tuple<Us...>() const
    requires(sizeof...(Us) == sizeof...(Ts)) && (!std::same_as<tuple<Ts...>, tuple<Us...>>)
#ifndef KUMI_DOXYGEN_INVOKED
            && (kumi::_::piecewise_constructible<tuple<Ts const&...>, tuple<Us...>>)
#endif
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<Us...>{static_cast<Us>(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    [[nodiscard]] KUMI_ABI
#ifndef KUMI_DOXYGEN_INVOKED
      explicit(!kumi::_::piecewise_convertible<tuple<Ts&...>, tuple<Us...>>)
#endif
        constexpr
        operator tuple<Us...>()
    requires(sizeof...(Us) == sizeof...(Ts)) && (!std::same_as<tuple<Ts...>, tuple<Us...>>)
#ifndef KUMI_DOXYGEN_INVOKED
            && (kumi::_::piecewise_constructible<tuple<Ts&...>, tuple<Us...>>)
#endif
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<Us...>{static_cast<Us>(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    KUMI_ABI constexpr tuple& operator=(tuple<Us...> const& other)
#ifndef KUMI_DOXYGEN_INVOKED
    requires(kumi::_::piecewise_convertible<tuple, tuple<Us...>>)
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
    requires(kumi::_::piecewise_convertible<tuple, tuple<Us...>>)
#endif
    {
      [&]<std::size_t... I>(std::index_sequence<I...>) {
        ((get<I>(*this) = get<I>(KUMI_FWD(other))), ...);
      }(std::make_index_sequence<sizeof...(Ts)>{});
      return *this;
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator==(tuple const& self, tuple<Us...> const& other) noexcept
#ifndef KUMI_DOXYGEN_INVOKED
    requires(kumi::_::piecewise_comparable<tuple, tuple<Us...>>)
#endif
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return ((get<I>(self) == get<I>(other)) && ...);
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator!=(tuple const& self, tuple<Us...> const& other) noexcept
#ifndef KUMI_DOXYGEN_INVOKED
    requires(kumi::_::piecewise_comparable<tuple, tuple<Us...>>)
#endif
    {
      return !(self == other);
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator<(tuple const& lhs, tuple<Us...> const& rhs) noexcept
    requires(sizeof...(Ts) == sizeof...(Us))
#ifndef KUMI_DOXYGEN_INVOKED
            && (kumi::_::piecewise_ordered<tuple, tuple<Us...>>)
#endif
    {
      auto res = get<0>(lhs) < get<0>(rhs);
      auto const order = [&]<typename Index>(Index i) {
        auto y_less_x_prev = rhs[i] < lhs[i];
        auto x_less_y = lhs[kumi::index<Index::value + 1>] < rhs[kumi::index<Index::value + 1>];
        return x_less_y && !y_less_x_prev;
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return (res || ... || order(kumi::index_t<I>{}));
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
        ((os << kumi::_::make_streamable(t[index<I>]) << ", "), ...);
      }(std::make_index_sequence<kumi::size_v<tuple> - 1>{});
      os << kumi::_::make_streamable(t[index<kumi::size_v<tuple> - 1>]) << " )";
      return os;
    }
  };
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
  template<typename... Ts> KUMI_CUDA tuple(Ts&&...) -> tuple<std::unwrap_ref_decay_t<Ts>...>;
  template<typename... Ts> [[nodiscard]] KUMI_ABI constexpr auto tie(Ts&... ts) -> kumi::tuple<Ts&...>
  {
    return {ts...};
  }
  template<typename... Ts> [[nodiscard]] KUMI_ABI constexpr auto forward_as_tuple(Ts&&... ts) -> kumi::tuple<Ts&&...>
  {
    return {KUMI_FWD(ts)...};
  }
  template<typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto make_tuple(Ts&&... ts) -> kumi::tuple<std::unwrap_ref_decay_t<Ts>...>
  {
    return {KUMI_FWD(ts)...};
  }
  template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto to_ref(T&& t)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::forward_as_tuple(get<I>(KUMI_FWD(t))...);
    }(std::make_index_sequence<kumi::size_v<T>>{});
  }
  template<typename Type, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto from_tuple(tuple<Ts...> const& t)
  requires(!kumi::concepts::product_type<Type> && kumi::_::implicit_constructible<Type, Ts...>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return Type{get<I>(t)...};
    }(std::make_index_sequence<sizeof...(Ts)>{});
  }
  template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto to_tuple(T&& t)
  {
    if constexpr (kumi::concepts::empty_product_type<T>) return kumi::tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple{get<I>(KUMI_FWD(t))...};
      }(std::make_index_sequence<kumi::size_v<T>>{});
  }
  template<kumi::concepts::static_container S>
  [[nodiscard]] KUMI_ABI constexpr auto to_tuple(S&& s)
  requires(!kumi::concepts::product_type<S>)
  {
    constexpr auto N = kumi::container_size_v<S>;
    if constexpr (N == 0) return kumi::tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return kumi::tuple{KUMI_FWD(s)[I]...};
      }(std::make_index_sequence<N>{});
  }
  namespace _
  {
    template<kumi::concepts::product_type T,
             typename IndexSequence,
             template<typename...> class Meta = std::type_identity>
    struct as_tuple;
    template<kumi::concepts::product_type T, std::size_t... I> struct as_tuple<T, std::index_sequence<I...>>
    {
      using type = kumi::tuple<kumi::element_t<I, T>...>;
    };
    template<kumi::concepts::product_type T, std::size_t... I, template<typename...> class Meta>
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
  template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto members_of(as<T>) noexcept
  {
    if constexpr (kumi::concepts::sized_product_type<T, 0>) return kumi::tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return kumi::tuple{kumi::identifier_of<kumi::element_t<I, T>>()...};
      }(std::make_index_sequence<kumi::size_v<T>>{});
  }
  template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto values_of(T&& t) noexcept
  {
    if constexpr (kumi::concepts::sized_product_type<T, 0>) return kumi::tuple{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return kumi::tuple<kumi::result::field_value_of_t<kumi::member_t<I, T>>...>{
          kumi::field_value_of(get<I>(KUMI_FWD(t)))...};
      }(std::make_index_sequence<kumi::size_v<T>>{});
  }
  namespace result
  {
    template<kumi::concepts::product_type T> struct members_of
    {
      using type = decltype(kumi::members_of(as<T>{}));
    };
    template<kumi::concepts::product_type T> struct values_of
    {
      using type = decltype(kumi::values_of(std::declval<T>()));
    };
    template<kumi::concepts::product_type T> using members_of_t = typename kumi::result::members_of<T>::type;
    template<kumi::concepts::product_type T> using values_of_t = typename kumi::result::values_of<T>::type;
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
  template<kumi::concepts::product_type T>
  requires(!kumi::concepts::record_type<T>)
  struct builder<T>
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
  template<kumi::concepts::product_type... Ts>
  requires(!kumi::concepts::record_type<Ts> && ...)
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
      return impl(std::integral_constant<kumi::str, Name>{});
    }
    template<kumi::str Name>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<Name>) && noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<Name>, Ts...>)
    {
      return static_cast<set_t&&>(impl)(std::integral_constant<kumi::str, Name>{});
    }
    template<kumi::str Name>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<Name>) const&& noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<Name>, Ts...>)
    {
      return static_cast<set_t const&&>(impl)(std::integral_constant<kumi::str, Name>{});
    }
    template<kumi::str Name>
    KUMI_ABI constexpr decltype(auto) operator[](kumi::label_t<Name>) const& noexcept
    requires(kumi::concepts::contains_label<kumi::label_t<Name>, Ts...>)
    {
      return impl(std::integral_constant<kumi::str, Name>{});
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
        return tuple<stored_member_t<I, decltype(*this)>...>{kumi::field_value_of(get<I>(*this))...};
      }(std::make_index_sequence<sizeof...(Ts)>{});
    }
    [[nodiscard]] KUMI_ABI constexpr auto values() const noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return tuple<stored_member_t<I, decltype(*this)>...>{kumi::field_value_of(get<I>(*this))...};
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
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator==(record const& self, record<Us...> const& other) noexcept
#ifndef KUMI_DOXYGEN_INVOKED
    requires(kumi::_::fieldwise_comparable<record, record<Us...>>)
#endif
    {
      return ((get<kumi::identifier_of<Ts>()>(self) == get<kumi::identifier_of<Ts>()>(other)) && ...);
    }
    template<typename... Us>
    KUMI_ABI friend constexpr auto operator!=(record const& self, record<Us...> const& other) noexcept
#ifndef KUMI_DOXYGEN_INVOKED
    requires(kumi::_::fieldwise_comparable<record, record<Us...>>)
#endif
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
      }(std::make_index_sequence<kumi::size_v<record> - 1>{});
      os << t[kumi::index<kumi::size_v<record> - 1>] << " }";
      return os;
    }
  };
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
  template<typename... Ts> KUMI_CUDA record(Ts&&...) -> record<std::unwrap_ref_decay_t<Ts>...>;
  template<kumi::concepts::identifier auto... Fields, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto tie(Ts&... ts) -> kumi::record<kumi::field<decltype(Fields), Ts&>...>
  requires(sizeof...(Fields) == sizeof...(Ts))
  {
    return {ts...};
  }
  template<kumi::concepts::identifier auto... Fields, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto forward_as_record(Ts&&... ts)
    -> kumi::record<kumi::field<decltype(Fields), Ts&&>...>
  requires(sizeof...(Fields) == sizeof...(Ts))
  {
    return {KUMI_FWD(ts)...};
  }
  template<typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto make_record(Ts&&... ts) -> kumi::record<std::unwrap_ref_decay_t<Ts>...>
  requires(kumi::concepts::uniquely_named<Ts...> && kumi::concepts::fully_named<Ts...>)
  {
    return {KUMI_FWD(ts)...};
  }
  template<kumi::concepts::record_type R> [[nodiscard]] KUMI_ABI constexpr auto to_ref(R&& r)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return kumi::forward_as_record<kumi::identifier_of<kumi::element_t<I, R>>()...>(
        kumi::field_value_of(get<I>(KUMI_FWD(r)))...);
    }(std::make_index_sequence<kumi::size_v<R>>{});
  }
  template<kumi::concepts::record_type Type, typename... Ts>
  [[nodiscard]] KUMI_ABI constexpr auto from_record(record<Ts...> const& r)
  requires(
    kumi::concepts::equivalent<typename kumi::_::as_tuple<Type, std::make_index_sequence<kumi::size_v<Type>>>::type,
                               kumi::tuple<Ts...>>)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
      return Type{get<kumi::identifier_of<kumi::element_t<I, Type>>()>(r)...};
    }(std::make_index_sequence<kumi::size_v<Type>>());
  }
  template<kumi::concepts::record_type Type> [[nodiscard]] KUMI_ABI constexpr auto to_record(Type&& r)
  {
    if constexpr (kumi::concepts::empty_product_type<Type>) return kumi::record{};
    else
      return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return kumi::record{kumi::capture_field<kumi::identifier_of<kumi::element_t<I, Type>>()>(
          get<kumi::identifier_of<kumi::element_t<I, Type>>()>(KUMI_FWD(r)))...};
      }(std::make_index_sequence<kumi::size_v<Type>>{});
  }
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
    template<typename T> KUMI_ABI constexpr decltype(auto) unwrap_memptr(T&& obj)
    {
      if constexpr (kumi::_::is_reference_wrapper_v<std::remove_cvref_t<T>>) return KUMI_FWD(obj).get();
      else if constexpr (std::is_pointer_v<std::remove_cvref_t<T>>) return *KUMI_FWD(obj);
      else return KUMI_FWD(obj);
    }
    template<typename C, typename P, typename O, typename... Ts>
    KUMI_ABI constexpr decltype(auto) invoke_memptr(P C::* member, O&& o, Ts&&... ts)
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
      template<typename... Args> KUMI_ABI constexpr decltype(auto) operator()(Args&&... args) &
      {
        return impl(seq, *this, KUMI_FWD(args)...);
      }
      template<typename... Args> KUMI_ABI constexpr decltype(auto) operator()(Args&&... args) const&
      {
        return impl(seq, *this, KUMI_FWD(args)...);
      }
      template<typename... Args> KUMI_ABI constexpr decltype(auto) operator()(Args&&... args) &&
      {
        return impl(seq, std::move(*this), KUMI_FWD(args)...);
      }
      template<typename... Args> KUMI_ABI constexpr decltype(auto) operator()(Args&&... args) const&&
      {
        return impl(seq, std::move(*this), KUMI_FWD(args)...);
      }
      template<std::size_t... Is, typename Self, typename... Args>
      KUMI_ABI static constexpr decltype(auto) impl(std::index_sequence<Is...>, Self&& s, Args&&... args)
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
namespace kumi::function
{
  struct identity_t
  {
    template<typename T> KUMI_ABI constexpr T&& operator()(T&& t) const noexcept { return KUMI_FWD(t); }
  };
  inline constexpr identity_t identity{};
  struct builder_t
  {
    template<typename T, std::size_t... I> KUMI_ABI static consteval auto type(T&&, std::index_sequence<I...>)
    {
      return kumi::common_product_type_t<std::remove_cvref_t<kumi::element_t<I, T>>...>{};
    }
    template<typename T>
    using type_t =
      decltype(kumi::function::builder_t::type(std::declval<T>(), std::make_index_sequence<kumi::size_v<T>>{}));
    template<kumi::concepts::product_type T, std::size_t... I>
    KUMI_ABI constexpr auto operator()(T&& t, std::index_sequence<I...>) const
    {
      using res_t = kumi::builder_make_t<T, kumi::element_t<I, T>...>;
      return res_t{get<I>(KUMI_FWD(t))...};
    }
    template<typename T, std::size_t N, std::size_t... I>
    KUMI_ABI constexpr auto operator()(T&& t, std::integral_constant<std::size_t, N>, std::index_sequence<I...>) const
    {
      using U = type_t<T>;
      using res_t = kumi::builder_make_t<U, kumi::element_t<N, kumi::element_t<I, T>>...>;
      return res_t{get<N>(get<I>(KUMI_FWD(t)))...};
    }
    template<typename T, std::size_t... E, std::size_t... I>
    KUMI_ABI constexpr auto operator()(T&& t, std::index_sequence<E...>, std::index_sequence<I...>) const
    {
      using U = type_t<T>;
      using res_t = kumi::builder_make_t<U, kumi::element_t<E, kumi::element_t<I, T>>...>;
      return res_t{get<E>(get<I>(KUMI_FWD(t)))...};
    }
  };
  inline constexpr builder_t builder{};
}
namespace kumi::function
{
  struct cartesian_product_t
  {
    template<std::size_t... H, std::size_t... S>
    KUMI_ABI consteval auto operator()(std::index_sequence<H...>, kumi::index_t<S>...) const noexcept
    {
      return kumi::projection_map{kumi::_::digits(kumi::_::unflatten_index, std::make_index_sequence<sizeof...(S)>{},
                                                  std::index_sequence<H, S...>{})...};
    }
  };
  struct cat_t
  {
    template<std::size_t... Sizes> KUMI_ABI consteval auto operator()(std::index_sequence<Sizes...>) const noexcept
    {
      constexpr auto N = (Sizes + ... + 0ULL);
      constexpr auto Ids = std::index_sequence<Sizes...>{};
      return kumi::projection_map{kumi::_::digits(kumi::_::container_of_index, std::make_index_sequence<N>{}, Ids),
                                  kumi::_::digits(kumi::_::element_of_index, std::make_index_sequence<N>{}, Ids)};
    }
  };
  struct rotate_t
  {
    template<std::size_t... S, std::size_t R>
    KUMI_ABI consteval auto operator()(std::index_sequence<S...>, kumi::index_t<R>) const noexcept
    {
      return std::index_sequence<((S + R) % sizeof...(S))...>{};
    }
  };
  struct reduce_t
  {
    template<std::size_t... I, std::size_t N>
    KUMI_ABI consteval auto operator()(std::index_sequence<I...>, kumi::index_t<N>) const noexcept
    {
      return kumi::projection_map{std::index_sequence<(2 * I)...>{}, std::index_sequence<(2 * I + 1)...>{},
                                  kumi::index<N>};
    }
  };
  struct repeat_t
  {
    template<std::size_t E, std::size_t... I>
    KUMI_ABI consteval auto operator()(kumi::index_t<E>, std::index_sequence<I...>) const noexcept
    {
      return std::index_sequence<(I - I + E)...>{};
    }
  };
  struct reverse_t
  {
    template<std::size_t... I> KUMI_ABI consteval auto operator()(std::index_sequence<I...>) const noexcept
    {
      return std::index_sequence<(sizeof...(I) - 1 - I)...>{};
    }
  };
  struct shift_t
  {
    template<std::size_t N, std::size_t... I>
    KUMI_ABI consteval auto operator()(std::integral_constant<std::size_t, N>, std::index_sequence<I...>) const noexcept
    {
      return std::index_sequence<I + N...>{};
    }
  };
  struct split_t
  {
    template<std::size_t N, std::size_t... S>
    KUMI_ABI consteval auto operator()(kumi::index_t<N>, std::index_sequence<S...>) const noexcept
    {
      return kumi::projection_map{std::make_index_sequence<N>{}, std::index_sequence<(S + N)...>{}};
    }
  };
  struct tile_t
  {
    template<std::size_t Sz, std::size_t Extent, std::size_t Stride, std::size_t... Blocks>
    KUMI_ABI consteval auto operator()(kumi::index_t<Sz>,
                                       kumi::index_t<Extent>,
                                       kumi::index_t<Stride>,
                                       std::index_sequence<Blocks...>) const noexcept
    {
      using blocks = std::index_sequence<kumi::_::block_size(Blocks, Stride, Extent, Sz)...>;
      using offsets = std::index_sequence<(Blocks * Stride)...>;
      return kumi::projection_map{blocks{}, offsets{}};
    }
  };
  struct zip_t
  {
    template<std::size_t Count, std::size_t Size>
    KUMI_ABI consteval auto operator()(kumi::index_t<Count>, kumi::index_t<Size>) const noexcept
    {
      using tuples = std::make_index_sequence<Count>;
      using elements = std::make_index_sequence<Size>;
      return kumi::projection_map{tuples{}, elements{}};
    }
  };
  inline constexpr kumi::function::cartesian_product_t cartesian_producer{};
  inline constexpr kumi::function::cat_t concatenater{};
  inline constexpr kumi::function::rotate_t rotater{};
  inline constexpr kumi::function::reduce_t reducer{};
  inline constexpr kumi::function::repeat_t repeater{};
  inline constexpr kumi::function::shift_t shifter{};
  inline constexpr kumi::function::split_t splitter{};
  inline constexpr kumi::function::reverse_t reverser{};
  inline constexpr kumi::function::tile_t tiler{};
  inline constexpr kumi::function::zip_t zipper{};
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
    template<typename... Ts> struct make_multiset
    {
      using type = kumi::_::multiset<Ts...>;
    };
    template<typename... Ts> using make_multiset_t = typename kumi::_::make_multiset<Ts...>::type;
  }
  namespace function
  {
    struct unique_t
    {
      template<typename... Ts> KUMI_ABI consteval auto operator()(std::type_identity<Ts>...) const noexcept
      {
        using type = kumi::_::make_multiset_t<std::make_index_sequence<sizeof...(Ts)>, Ts...>;
        return this->unique_(type{}, std::make_index_sequence<sizeof...(Ts)>{}, std::type_identity<Ts>{}...);
      }
      template<typename T, std::size_t... I, typename... Ts>
      consteval auto unique_(T&&, std::index_sequence<I...>, std::type_identity<Ts>...) const noexcept
      {
        return this->expand_(std::integer_sequence<bool, (T{}(std::type_identity<Ts>{}) == I)...>{});
      }
      template<bool... b> consteval auto expand_(std::integer_sequence<bool, b...> bs) const noexcept
      {
        return this->build_(bs, std::make_index_sequence<(b + ... + 0)>{});
      }
      template<bool... b, std::size_t... I>
      consteval auto build_(std::integer_sequence<bool, b...>, std::index_sequence<I...>) const noexcept
      {
        return std::index_sequence<(kumi::_::nth_pos(I, b...))...>{};
      }
    };
    struct select_t
    {
      template<bool... Bs> KUMI_ABI consteval auto operator()(std::bool_constant<Bs>...) const noexcept
      {
        return this->select_(std::integer_sequence<bool, Bs...>{}, std::make_index_sequence<(Bs + ... + 0)>{},
                             std::make_index_sequence<(sizeof...(Bs) - (Bs + ... + 0))>{});
      }
      template<bool... b, std::size_t... I, std::size_t... J>
      consteval auto select_(std::integer_sequence<bool, b...>,
                             std::index_sequence<I...>,
                             std::index_sequence<J...>) const noexcept
      {
        return kumi::projection_map{std::index_sequence<(kumi::_::nth_pos(I, b...))...>{},
                                    std::index_sequence<(kumi::_::nth_pos(J, !b...))...>{}};
      }
    };
    struct adjacent_unicity_t
    {
      template<kumi::concepts::product_type T> KUMI_ABI consteval auto operator()(kumi::as<T>) const noexcept
      {
        return this->adjacent_unicity_(kumi::as<T>{}, std::make_index_sequence<kumi::size_v<T> - 1>{});
      }
      template<typename T, std::size_t... I>
      consteval auto adjacent_unicity_(kumi::as<T>, std::index_sequence<I...>) const noexcept
      {
        constexpr auto proj =
          std::integer_sequence<bool,
                                !std::is_same_v<kumi::stored_element_t<I, T>, kumi::stored_element_t<I + 1, T>>...>{};
        return this->expand_(proj);
      }
      template<bool... b> consteval auto expand_(std::integer_sequence<bool, b...> bs) const noexcept
      {
        return this->build_(bs, std::make_index_sequence<(b + ... + 0)>{});
      }
      template<bool... b, std::size_t... I>
      consteval auto build_(std::integer_sequence<bool, b...>, std::index_sequence<I...>) const noexcept
      {
        return std::index_sequence<0, (kumi::_::nth_pos(I, b...) + 1)...>{};
      }
    };
    inline constexpr kumi::function::adjacent_unicity_t uniqued{};
    inline constexpr kumi::function::unique_t uniquer{};
    inline constexpr kumi::function::select_t selector{};
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
  template<typename T, auto V> struct size_or
  {
    static constexpr auto value = [] {
      if constexpr (kumi::concepts::product_type<T>) return kumi::size_v<T>;
      else return V;
    }();
  };
  template<typename T, auto V> inline constexpr auto size_or_v = kumi::function::size_or<T, V>::value;
  template<std::size_t I, typename T, typename U> struct element_or
  {
    using type = typename decltype([] {
      if constexpr (kumi::concepts::product_type<T> && I < kumi::size_v<T>) return kumi::element<I, T>{};
      else return std::type_identity<U>{};
    }())::type;
  };
  template<std::size_t I, typename T, typename U>
  using element_or_t = typename kumi::function::element_or<I, T, U>::type;
  template<std::size_t I, typename T, typename V> [[nodiscard]] KUMI_ABI constexpr decltype(auto) get_or(T&& t, V&& v)
  {
    if constexpr (kumi::concepts::product_type<T> && I < kumi::size_v<T>) return get<I>(KUMI_FWD(t));
    else return KUMI_FWD(v);
  }
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
    KUMI_ABI constexpr decltype(auto) apply_(kumi::_::adl_tag_t, F&& f, T&& t, std::index_sequence<I...>)
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
      else return apply_(kumi::_::adl_tag, KUMI_FWD(f), KUMI_FWD(t), std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  struct apply_field_t
  {
    template<typename Function, kumi::concepts::record_type R>
    KUMI_ABI constexpr decltype(auto) operator()(Function&& f, R&& t) const
    {
      return apply_(kumi::_::adl_tag, KUMI_FWD(f), KUMI_FWD(t), std::make_index_sequence<kumi::size_v<R>>{});
    }
  };
  inline constexpr apply_t apply{};
  inline constexpr apply_field_t apply_field{};
  namespace result
  {
    template<typename Function, kumi::concepts::product_type T> struct apply
    {
      using type = decltype(kumi::apply(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, kumi::concepts::product_type T> using apply_t = typename apply<Function, T>::type;
    template<typename Function, kumi::concepts::record_type R> struct apply_field
    {
      using type = decltype(kumi::apply_field(std::declval<Function>(), std::declval<R>()));
    };
    template<typename Function, concepts::record_type R> using apply_field_t = typename apply_field<Function, R>::type;
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
  inline constexpr front_t front{};
  inline constexpr back_t back{};
  namespace result
  {
    template<kumi::concepts::product_type T> struct front : kumi::stored_member<0, T>
    {
    };
    template<kumi::concepts::product_type T> using front_t = typename kumi::result::front<T>::type;
    template<kumi::concepts::product_type T> struct back : kumi::stored_member<kumi::size_v<T> - 1, T>
    {
    };
    template<kumi::concepts::product_type T> using back_t = typename kumi::result::back<T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename Seq, std::size_t... I>
    KUMI_ABI constexpr auto cartesian_product_(kumi::_::adl_tag_t, T&& t, Seq&& s, std::index_sequence<I...>)
    {
      std::make_index_sequence<kumi::size_v<T>> ids{};
      return kumi::make_tuple((kumi::function::builder(KUMI_FWD(t), get<I>(s), ids))...);
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
        constexpr auto sq = std::make_index_sequence<(kumi::size_v<Ts> * ...)>{};
        constexpr auto idx = kumi::function::cartesian_producer(sq, kumi::index<kumi::size_v<Ts>>...);
        return cartesian_product_(kumi::_::adl_tag, kumi::forward_as_tuple(KUMI_FWD(ts)...), idx, sq);
      }
    }
  };
  inline constexpr cartesian_product_t cartesian_product{};
  namespace result
  {
    template<typename... Ts> struct cartesian_product
    {
      using type = decltype(kumi::cartesian_product(std::declval<Ts>()...));
    };
    template<typename... Ts> using cartesian_product_t = typename kumi::result::cartesian_product<Ts...>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename Target, typename T, std::size_t... I>
    KUMI_ABI constexpr decltype(auto) member_cast_(kumi::_::adl_tag_t, T&& t, std::index_sequence<I...>)
    {
      return kumi::builder<T>::make(kumi::field_cast<Target>(get<I>(KUMI_FWD(t)))...);
    }
  }
  template<typename Target> struct member_cast_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else if constexpr (kumi::concepts::record_type<T>)
        return member_cast_<Target>(kumi::_::adl_tag, KUMI_FWD(t), std::make_index_sequence<kumi::size_v<T>>{});
      else
      {
        using type = kumi::_::as_homogeneous_t<Target, kumi::size_v<T>>;
        return static_cast<type>(KUMI_FWD(t));
      }
    }
  };
  template<typename T> inline constexpr member_cast_t<T> member_cast{};
  namespace result
  {
    template<typename Target, kumi::concepts::product_type T> struct member_cast
    {
      using type = decltype(kumi::member_cast<Target>(std::declval<T>()));
    };
    template<typename Target, kumi::concepts::product_type T>
    using member_cast_t = typename kumi::result::member_cast<Target, T>::type;
  }
}
namespace kumi
{
  struct cat_t
  {
    template<kumi::concepts::product_type... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Ts&&... ts) const
    requires(kumi::concepts::follows_same_semantic<Ts...>)
    {
      if constexpr (sizeof...(Ts) == 0) return kumi::tuple{};
      else
      {
        constexpr auto pos = kumi::function::concatenater(std::index_sequence<kumi::size_v<Ts>...>{});
        return kumi::function::builder(kumi::forward_as_tuple(KUMI_FWD(ts)...), get<1>(pos), get<0>(pos));
      }
    }
  };
  inline constexpr cat_t cat{};
  namespace result
  {
    template<kumi::concepts::product_type... Ts> struct cat
    {
      using type = decltype(kumi::cat(std::declval<Ts>()...));
    };
    template<concepts::product_type... Ts> using cat_t = typename kumi::result::cat<Ts...>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename... Ts>
    inline constexpr bool contains = ((kumi::concepts::field<T> && std::invocable<T, kumi::_::tag_of_t<Ts>>) || ...);
    template<typename T, typename ID, std::size_t... I>
    KUMI_ABI constexpr auto contains_(kumi::_::adl_tag_t, T&&, ID const&, std::index_sequence<I...>)
    {
      return std::bool_constant<kumi::_::can_get_field_by_value<std::remove_cvref_t<ID>, kumi::element_t<I, T>...>>{};
    }
    template<typename T, std::size_t... I, typename... Is>
    KUMI_ABI constexpr auto contains_only_(kumi::_::adl_tag_t, T&&, std::index_sequence<I...>, Is const&...)
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
      else return contains_(kumi::_::adl_tag, KUMI_FWD(t), id, std::make_index_sequence<kumi::size_v<T>>{});
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
        return std::bool_constant<(decltype(contains_(kumi::_::adl_tag, std::declval<T>(), ids,
                                                      std::make_index_sequence<kumi::size_v<T>>{})){} ||
                                   ...)>{};
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
      else return contains_only_(kumi::_::adl_tag, KUMI_FWD(t), std::make_index_sequence<kumi::size_v<T>>{}, ids...);
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
  inline constexpr contains_t contains{};
  inline constexpr contains_any_t contains_any{};
  inline constexpr contains_only_t contains_only{};
  inline constexpr contains_none_t contains_none{};
  namespace result
  {
    template<kumi::concepts::product_type T, kumi::concepts::identifier ID> struct contains
    {
      using type = decltype(kumi::contains(std::declval<T>(), std::declval<ID>()));
    };
    template<kumi::concepts::product_type T, kumi::concepts::identifier ID>
    using contains_t = typename kumi::result::contains<T, ID>::type;
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs> struct contains_any
    {
      using type = decltype(kumi::contains_any(std::declval<T>(), std::declval<IDs>()...));
    };
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs>
    using contains_any_t = typename kumi::result::contains_any<T, IDs...>::type;
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs> struct contains_only
    {
      using type = decltype(kumi::contains_only(std::declval<T>(), std::declval<IDs>()...));
    };
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs>
    using contains_only_t = typename kumi::result::contains_only<T, IDs...>::type;
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs> struct contains_none
    {
      using type = decltype(kumi::contains_none(std::declval<T>(), std::declval<IDs>()...));
    };
    template<kumi::concepts::product_type T, kumi::concepts::identifier... IDs>
    using contains_none_t = typename kumi::result::contains_none<T, IDs...>::type;
  }
}
namespace kumi
{
  struct extract_t
  {
    template<std::size_t I0, std::size_t I1, kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, kumi::index_t<I0> i0, kumi::index_t<I1>) const noexcept
    {
      static_assert((I0 <= kumi::size_v<T>) && (I1 <= kumi::size_v<T>), "[KUMI] - Invalid index");
      return kumi::function::builder(KUMI_FWD(t), kumi::function::shifter(std::integral_constant<std::size_t, i0>{},
                                                                          std::make_index_sequence<I1 - I0>{}));
    }
    template<std::size_t I0, kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, kumi::index_t<I0> i0) const noexcept
    {
      static_assert(I0 <= kumi::size_v<T>, "[KUMI] - Invalid index");
      return (*this)(KUMI_FWD(t), i0, kumi::index<size_v<T>>);
    }
  };
  struct split_t
  {
    template<std::size_t I0, kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, [[maybe_unused]] kumi::index_t<I0> i0) const noexcept
    {
      static_assert(I0 <= kumi::size_v<T>, "[KUMI] - Invalid index");
      constexpr auto proj = kumi::function::splitter(kumi::index<I0>, std::make_index_sequence<kumi::size_v<T> - I0>{});
      return kumi::tuple{kumi::function::builder(KUMI_FWD(t), get<0>(proj)),
                         kumi::function::builder(KUMI_FWD(t), get<1>(proj))};
    }
  };
  inline constexpr extract_t extract{};
  inline constexpr split_t split{};
  namespace result
  {
    template<kumi::concepts::product_type T, std::size_t I0, std::size_t I1 = std::size_t(-1)> struct extract
    {
      using type = decltype(kumi::extract(std::declval<T>(), kumi::index_t<I0>{}, kumi::index_t<I1>{}));
    };
    template<kumi::concepts::product_type T, std::size_t I0> struct extract<T, I0>
    {
      using type = decltype(kumi::extract(std::declval<T>(), kumi::index_t<I0>{}));
    };
    template<kumi::concepts::product_type T, std::size_t I0, std::size_t I1 = std::size_t(-1)>
    using extract_t = typename kumi::result::extract<T, I0, I1>::type;
    template<kumi::concepts::product_type T, std::size_t I0> struct split
    {
      using type = decltype(kumi::split(std::declval<T>(), kumi::index_t<I0>{}));
    };
    template<kumi::concepts::product_type T, std::size_t I0> using split_t = typename kumi::result::split<T, I0>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename F, std::size_t... I>
    KUMI_ABI constexpr auto for_each_(kumi::_::adl_tag_t, F&& f, std::index_sequence<I...>)
    {
      using result_t = std::invoke_result_t<F, kumi::index_t<0>>;
      if constexpr (std::is_void_v<result_t>) return ((kumi::invoke(KUMI_FWD(f), kumi::index<I>)), ...);
      else return ((kumi::invoke(KUMI_FWD(f), kumi::index<I>)) && ...);
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
      {
        auto const invoker{[&](auto const I) {
          if constexpr (kumi::concepts::record_type<T>)
          {
            constexpr auto field = kumi::identifier_of<kumi::element_t<I, T>>();
            kumi::invoke(f, get<field>(KUMI_FWD(t)), get<field>(KUMI_FWD(ts))...);
          }
          else kumi::invoke(f, get<I>(KUMI_FWD(t)), get<I>(KUMI_FWD(ts))...);
        }};
        for_each_(kumi::_::adl_tag, invoker, std::make_index_sequence<kumi::size_v<T>>{});
      }
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
      {
        auto const invoker{[&](auto const I) { kumi::invoke(f, I, get<I>(KUMI_FWD(t)), get<I>(KUMI_FWD(ts))...); }};
        for_each_(kumi::_::adl_tag, invoker, std::make_index_sequence<kumi::size_v<T>>{});
      }
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
      {
        constexpr auto fields = kumi::members_of(as<R>{});
        auto const invoker = [&](auto const I) {
          constexpr auto field = get<I>(fields);
          kumi::invoke(f, kumi::_::make_str(field), get<field>(KUMI_FWD(r)), get<field>(KUMI_FWD(rs))...);
        };
        for_each_(kumi::_::adl_tag, invoker, std::make_index_sequence<kumi::size_v<R>>{});
      }
    }
  };
  inline constexpr for_each_t for_each{};
  inline constexpr for_each_index_t for_each_index{};
  inline constexpr for_each_field_t for_each_field{};
}
namespace kumi
{
  namespace _
  {
    template<typename Pred, typename T, std::size_t... I>
    constexpr auto locate_(kumi::_::adl_tag_t, Pred p, T&& t, std::index_sequence<I...>)
    {
      bool checks[] = {kumi::invoke(p, get<I>(KUMI_FWD(t)))...};
      for (std::size_t i = 0; i < kumi::size_v<T>; ++i)
        if (checks[i]) return i;
      return kumi::size_v<T>;
    }
  }
  struct locate_t
  {
    template<typename Pred, kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, Pred p) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return 0;
      else if constexpr (kumi::concepts::record_type<T>) return (*this)(kumi::values_of(KUMI_FWD(t)), p);
      else return locate_(kumi::_::adl_tag, p, KUMI_FWD(t), std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  inline constexpr locate_t locate{};
}
namespace kumi
{
  namespace _
  {
    struct flatten_all_case_t
    {
      template<typename T, typename V, typename F, typename Self>
      KUMI_ABI constexpr auto operator()(T&&, V&& v, F f, Self s) const
      {
        using FV = kumi::result::field_value_of_t<V>;
        if constexpr (kumi::concepts::record_type<FV> && kumi::concepts::record_type<T>)
          return kumi::capture_field<kumi::identifier_of<V>()>(s(kumi::field_value_of(KUMI_FWD(v)), f));
        else if constexpr (kumi::concepts::follows_same_semantic<T, V>) return s(KUMI_FWD(v), f);
        else if constexpr (kumi::concepts::record_type<T> && kumi::concepts::field<V>)
          return kumi::capture_field<kumi::identifier_of<V>()>(kumi::invoke(f, kumi::field_value_of(KUMI_FWD(v))));
        else return kumi::invoke(f, KUMI_FWD(v));
      }
    };
    inline constexpr flatten_all_case_t flatten_all_case{};
    struct flatten_case_t
    {
      template<typename T, typename V> KUMI_ABI constexpr auto operator()(T&&, V&& v, auto J) const
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
    };
    inline constexpr flatten_case_t flatten_case{};
    template<typename T, typename V, std::size_t... J, std::size_t... I>
    KUMI_ABI constexpr auto flatten_(
      kumi::_::adl_tag_t, T&& t, V visitor, std::index_sequence<J...>, std::index_sequence<I...>)
    {
      if constexpr (sizeof...(I) == 0) return kumi::builder<T>::make();
      else return kumi::builder<T>::make(visitor(KUMI_FWD(t), get<I>(KUMI_FWD(t)), kumi::index<J>)...);
    }
    template<typename T, typename V, typename F, typename S, std::size_t... I>
    KUMI_ABI constexpr auto flatten_all_(kumi::_::adl_tag_t, T&& t, V visitor, F f, S self, std::index_sequence<I...>)
    {
      return kumi::builder<T>::make(visitor(KUMI_FWD(t), get<I>(KUMI_FWD(t)), f, self)...);
    }
  }
  struct flatten_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else
      {
        constexpr auto proj = []<std::size_t... I>(std::index_sequence<I...>) {
          return kumi::function::concatenater(
            std::index_sequence<kumi::function::size_or_v<kumi::stored_element_t<I, T>, 1>...>{});
        }(std::make_index_sequence<kumi::size_v<T>>{});
        return flatten_(kumi::_::adl_tag, KUMI_FWD(t), kumi::_::flatten_case, get<1>(proj), get<0>(proj));
      }
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
                                                        (*this), std::make_index_sequence<kumi::size_v<T>>{}));
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
      return this->flatten_all_t::operator()(KUMI_FWD(t), [](auto& m) { return &m; });
    }
  };
  inline constexpr flatten_t flatten{};
  inline constexpr flatten_all_t flatten_all{};
  inline constexpr as_flat_ptr_t as_flat_ptr{};
  namespace result
  {
    template<kumi::concepts::product_type T> struct flatten
    {
      using type = decltype(kumi::flatten(std::declval<T>()));
    };
    template<kumi::concepts::product_type T> using flatten_t = typename kumi::result::flatten<T>::type;
    template<kumi::concepts::product_type T, typename Func = void> struct flatten_all
    {
      using type = decltype(kumi::flatten_all(std::declval<T>(), std::declval<Func>()));
    };
    template<kumi::concepts::product_type T> struct flatten_all<T>
    {
      using type = decltype(kumi::flatten_all(std::declval<T>()));
    };
    template<kumi::concepts::product_type T, typename Func = void>
    using flatten_all_t = typename kumi::result::flatten_all<T, Func>::type;
    template<kumi::concepts::product_type T> struct as_flat_ptr
    {
      using type = decltype(kumi::as_flat_ptr(std::declval<T>()));
    };
    template<kumi::concepts::product_type T> using as_flat_ptr_t = typename kumi::result::as_flat_ptr<T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename F, std::size_t... I>
    KUMI_ABI constexpr decltype(auto) generate_(kumi::_::adl_tag_t, F&& f, std::index_sequence<I...>) noexcept
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
    template<std::size_t N, typename Function> struct generate
    {
      using type = decltype(kumi::generate<N>(std::declval<Function>()));
    };
    template<std::size_t N, typename Function> using generate_t = typename kumi::result::generate<N, Function>::type;
    template<std::size_t N, typename T> struct fill
    {
      using type = decltype(kumi::fill<N>(std::declval<T>()));
    };
    template<std::size_t N, typename T> using fill_t = typename kumi::result::fill<N, T>::type;
    template<std::size_t N, typename T> struct iota
    {
      using type = decltype(kumi::iota<N>(std::declval<T>()));
    };
    template<std::size_t N, typename T> using iota_t = typename kumi::result::iota<N, T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename U, typename V, typename Sum, typename Prod, std::size_t... I>
    KUMI_ABI constexpr auto inner_product_(
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
    KUMI_ABI constexpr auto inner_product_fast_(
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
                              std::make_index_sequence<kumi::size_v<S1>>{});
    }
    template<kumi::concepts::product_type S1, kumi::concepts::sized_product_type<kumi::size_v<S1>> S2, typename T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(S1&& s1, S2&& s2, T init) const noexcept
    requires(kumi::concepts::compatible_product_types<S1, S2>)
    {
      if constexpr (kumi::concepts::empty_product_type<S1>) return init;
      else
        return inner_product_fast_(kumi::_::adl_tag, KUMI_FWD(s1), KUMI_FWD(s2), init,
                                   std::make_index_sequence<kumi::size_v<S1>>{});
    }
  };
  inline constexpr inner_product_t inner_product{};
  namespace result
  {
    template<kumi::concepts::product_type S1,
             kumi::concepts::sized_product_type<kumi::size_v<S1>> S2,
             typename T,
             typename Sum,
             typename Prod>
    struct inner_product
    {
      using type = decltype(kumi::inner_product(
        std::declval<S1>(), std::declval<S2>(), std::declval<T>(), std::declval<Sum>(), std::declval<Prod>()));
    };
    template<kumi::concepts::product_type S1, kumi::concepts::sized_product_type<kumi::size_v<S1>> S2, typename T>
    struct inner_product<S1, S2, T, void, void>
    {
      using type = decltype(kumi::inner_product(std::declval<S1>(), std::declval<S2>(), std::declval<T>()));
    };
    template<kumi::concepts::product_type S1,
             kumi::concepts::sized_product_type<kumi::size_v<S1>> S2,
             typename T,
             typename Sum = void,
             typename Prod = void>
    using inner_product_t = typename kumi::result::inner_product<S1, S2, T, Sum, Prod>::type;
  }
}
namespace kumi
{
  namespace _
  {
    struct map_t
    {
      template<typename F, typename T, typename... Ts>
      KUMI_ABI constexpr auto operator()(auto N, F f, T&& t, Ts&&... ts) const
      {
        if constexpr (kumi::concepts::record_type<T>)
        {
          constexpr auto field = kumi::identifier_of<kumi::element_t<N, T>>();
          return kumi::capture_field<field>(kumi::invoke(f, get<field>(KUMI_FWD(t)), get<field>(KUMI_FWD(ts))...));
        }
        else return kumi::invoke(f, get<N>(KUMI_FWD(t)), get<N>(KUMI_FWD(ts))...);
      }
    };
    struct map_index_t
    {
      KUMI_ABI constexpr auto operator()(auto N, auto f, auto&&... args) const
      {
        return kumi::invoke(f, N, get<N>(KUMI_FWD(args))...);
      }
    };
    struct map_field_t
    {
      template<typename F, typename T, typename... Ts>
      KUMI_ABI constexpr auto operator()(auto N, F f, T&& t, Ts&&... ts) const
      {
        constexpr auto field = kumi::identifier_of<kumi::element_t<N, T>>();
        return kumi::capture_field<field>(
          kumi::invoke(f, kumi::_::make_str(field), get<field>(KUMI_FWD(t)), get<field>(KUMI_FWD(ts))...));
      }
    };
    inline constexpr map_t map_case{};
    inline constexpr map_index_t map_index_case{};
    inline constexpr map_field_t map_field_case{};
    template<typename T, typename F, std::size_t... I>
    KUMI_ABI constexpr decltype(auto) map_(kumi::_::adl_tag_t, T&&, F&& f, std::index_sequence<I...>)
    {
      if constexpr (sizeof...(I) == 0) return kumi::builder<T>::make();
      else return kumi::builder<T>::make(kumi::invoke(KUMI_FWD(f), kumi::index<I>)...);
    }
  }
  struct map_t
  {
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t0, Ts&&... others) const
    requires(kumi::concepts::compatible_product_types<T, Ts...>) && (kumi::_::supports_call<Function, T &&, Ts && ...>)
    {
      using binded_t = kumi::_::bind_t<kumi::_::Binding::back, kumi::_::map_t , Function, T, Ts...>; 
      auto&& bound = binded_t{kumi::_::map_case, f, KUMI_FWD(t0), KUMI_FWD(others)...};
      return map_(kumi::_::adl_tag, KUMI_FWD(t0), KUMI_FWD(bound), std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  struct map_index_t
  {
    template<kumi::concepts::product_type T,
             typename Function,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t0, Ts&&... others) const
    requires(!kumi::concepts::record_type<T> && (!kumi::concepts::record_type<Ts> && ...))
    {
      using binded_t = kumi::_::bind_t<kumi::_::Binding::back, kumi::_::map_index_t , Function, T, Ts...>; 
      auto&& bound = binded_t{kumi::_::map_index_case, f, KUMI_FWD(t0), KUMI_FWD(others)...};
      return map_(kumi::_::adl_tag, KUMI_FWD(t0), KUMI_FWD(bound), std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  struct map_field_t
  {
    template<kumi::concepts::record_type T,
             typename Function,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t0, Ts&&... others) const
    requires(kumi::concepts::compatible_product_types<T, Ts...>)
    {
      using binded_t = kumi::_::bind_t<kumi::_::Binding::back, kumi::_::map_field_t , Function, T, Ts...>; 
      auto&& bound = binded_t{kumi::_::map_field_case, f, KUMI_FWD(t0), KUMI_FWD(others)...};
      return map_(kumi::_::adl_tag, KUMI_FWD(t0), KUMI_FWD(bound), std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  inline constexpr map_t map{};
  inline constexpr map_index_t map_index{};
  inline constexpr map_field_t map_field{};
  namespace result
  {
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    struct map
    {
      using type = decltype(kumi::map(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    };
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    using map_t = typename kumi::result::map<Function, T, Ts...>::type;
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    struct map_index
    {
      using type = decltype(kumi::map_index(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    };
    template<typename Function,
             kumi::concepts::product_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    using map_index_t = typename kumi::result::map_index<Function, T, Ts...>::type;
    template<typename Function,
             kumi::concepts::record_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    struct map_field
    {
      using type = decltype(kumi::map_field(std::declval<Function>(), std::declval<T>(), std::declval<Ts>()...));
    };
    template<typename Function,
             kumi::concepts::record_type T,
             kumi::concepts::sized_product_type<kumi::size_v<T>>... Ts>
    using map_field_t = typename kumi::result::map_field<Function, T, Ts...>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename V, std::size_t... I>
    KUMI_ABI constexpr auto push_front_(kumi::_::adl_tag_t, T&& t, V&& v, std::index_sequence<I...>)
    {
      return kumi::builder<T>::make(KUMI_FWD(v), get<I>(KUMI_FWD(t))...);
    }
    template<typename T, typename V, std::size_t... I>
    KUMI_ABI constexpr auto push_back_(kumi::_::adl_tag_t, T&& t, V&& v, std::index_sequence<I...>)
    {
      return kumi::builder<T>::make(get<I>(KUMI_FWD(t))..., KUMI_FWD(v));
    }
  }
  struct push_front_t
  {
    template<kumi::concepts::product_type T, typename V>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, V&& v) const
    {
      return push_front_(kumi::_::adl_tag, KUMI_FWD(t), KUMI_FWD(v), std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  struct pop_front_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return kumi::builder<T>::make();
      else
        return kumi::function::builder(KUMI_FWD(t),
                                       kumi::function::shifter(std::integral_constant<std::size_t, 1>{},
                                                               std::make_index_sequence<kumi::size_v<T> - 1>{}));
    }
  };
  struct push_back_t
  {
    template<kumi::concepts::product_type T, typename V>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t, V&& v) const
    {
      return push_back_(kumi::_::adl_tag, KUMI_FWD(t), KUMI_FWD(v), std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  struct pop_back_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return kumi::builder<T>::make();
      else return kumi::function::builder(KUMI_FWD(t), std::make_index_sequence<kumi::size_v<T> - 1>{});
    }
  };
  inline constexpr push_front_t push_front{};
  inline constexpr pop_front_t pop_front{};
  inline constexpr push_back_t push_back{};
  inline constexpr pop_back_t pop_back{};
  namespace result
  {
    template<kumi::concepts::product_type T, typename V> struct push_front
    {
      using type = decltype(kumi::push_front(std::declval<T>(), std::declval<V>()));
    };
    template<kumi::concepts::product_type T, typename V>
    using push_front_t = typename kumi::result::push_front<T, V>::type;
    template<kumi::concepts::product_type T> struct pop_front
    {
      using type = decltype(kumi::pop_front(std::declval<T>()));
    };
    template<kumi::concepts::product_type T> using pop_front_t = typename kumi::result::pop_front<T>::type;
    template<kumi::concepts::product_type T, typename V> struct push_back
    {
      using type = decltype(kumi::push_back(std::declval<T>(), std::declval<V>()));
    };
    template<kumi::concepts::product_type T, typename V>
    using push_back_t = typename kumi::result::push_back<T, V>::type;
    template<kumi::concepts::product_type T> struct pop_back
    {
      using type = decltype(kumi::pop_back(std::declval<T>()));
    };
    template<kumi::concepts::product_type T> using pop_back_t = typename kumi::result::pop_back<T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename F, typename T, typename V, std::size_t... I>
    KUMI_ABI constexpr auto fold_left_(kumi::_::adl_tag_t, F f, T&& t, V v, std::index_sequence<I...>)
    {
      return (kumi::function::foldable{v} >> ... >> kumi::bind_back(f, get<I>(KUMI_FWD(t))))();
    }
    template<typename F, typename T, typename V, std::size_t... I>
    KUMI_ABI constexpr auto fold_right_(kumi::_::adl_tag_t, F f, T&& t, V v, std::index_sequence<I...>)
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
      else return fold_left_(kumi::_::adl_tag, f, KUMI_FWD(t), init, std::make_index_sequence<kumi::size_v<T>>{});
    }
    template<typename Function, kumi::concepts::non_empty_product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(f, kumi::values_of(KUMI_FWD(t)));
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
      else
        return fold_left_(kumi::_::adl_tag, f, KUMI_FWD(t), get<0>(KUMI_FWD(t)),
                          kumi::function::shifter(std::integral_constant<std::size_t, 1>{},
                                                  std::make_index_sequence<kumi::size_v<T> - 1>{}));
    }
  };
  struct fold_right_t
  {
    template<typename Function, kumi::concepts::product_type T, typename Value>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t, Value init) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(f, kumi::values_of(KUMI_FWD(t)), init);
      else if constexpr (kumi::concepts::empty_product_type<T>) return init;
      else return fold_right_(kumi::_::adl_tag, f, KUMI_FWD(t), init, std::make_index_sequence<kumi::size_v<T>>{});
    }
    template<typename Function, kumi::concepts::non_empty_product_type T>
    [[nodiscard]] KUMI_ABI constexpr auto operator()(Function f, T&& t) const
    {
      if constexpr (kumi::concepts::record_type<T>) return (*this)(f, kumi::values_of(KUMI_FWD(t)));
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return get<0>(KUMI_FWD(t));
      else
        return fold_right_(kumi::_::adl_tag, f, KUMI_FWD(t), get<0>(KUMI_FWD(t)),
                           kumi::function::shifter(std::integral_constant<std::size_t, 1>{},
                                                   std::make_index_sequence<kumi::size_v<T> - 1>{}));
    }
  };
  inline constexpr fold_left_t fold_left{};
  inline constexpr fold_right_t fold_right{};
  namespace result
  {
    template<typename Function, kumi::concepts::product_type T, typename Value = void> struct fold_left
    {
      using type = decltype(kumi::fold_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, kumi::concepts::product_type T> struct fold_left<Function, T>
    {
      using type = decltype(kumi::fold_left(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, kumi::concepts::product_type T, typename Value = void>
    using fold_left_t = typename kumi::result::fold_left<Function, T, Value>::type;
    template<typename Function, kumi::concepts::product_type T, typename Value = void> struct fold_right
    {
      using type = decltype(kumi::fold_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, kumi::concepts::product_type T> struct fold_right<Function, T>
    {
      using type = decltype(kumi::fold_right(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, kumi::concepts::product_type T, typename Value = void>
    using fold_right_t = typename kumi::result::fold_right<Function, T, Value>::type;
  }
}
namespace kumi
{
  namespace _
  {
    struct minmax_case_t
    {
      template<typename V, typename F, typename C> KUMI_ABI constexpr auto operator()(V&& v, F f, C c) const
      {
        if constexpr (kumi::concepts::product_type<V>) return c(KUMI_FWD(v), f);
        else return kumi::invoke(f, KUMI_FWD(v));
      }
    };
    inline constexpr minmax_case_t minmax_case{};
    template<typename F, typename T, typename V, std::size_t... I>
    KUMI_ABI constexpr auto minmax_(kumi::_::adl_tag_t, F f, T&& t, V v, std::index_sequence<I...>)
    {
      return (kumi::function::foldable{v} >> ... >> kumi::bind_back(f, get<I + 1>(KUMI_FWD(t))))();
    }
    template<typename T, typename V, typename F, typename S, std::size_t... I>
    KUMI_ABI constexpr auto minmax_flat_(
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
        auto const f = [](auto cur, auto u) { return cur > u ? cur : u; };
        return minmax_(kumi::_::adl_tag, f, KUMI_FWD(t), get<0>(KUMI_FWD(t)),
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
        auto const c = [f](auto cur, auto const& u) { return cur > invoke(f, u) ? cur : invoke(f, u); };
        return minmax_(kumi::_::adl_tag, c, KUMI_FWD(t), kumi::invoke(f, get<0>(KUMI_FWD(t))),
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
                                                    std::make_index_sequence<kumi::size_v<T>>{}));
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
        auto const f = [](auto cur, auto u) { return cur < u ? cur : u; };
        return minmax_(kumi::_::adl_tag, f, KUMI_FWD(t), get<0>(KUMI_FWD(t)),
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
        auto const c = [f](auto cur, auto const& u) { return cur < invoke(f, u) ? cur : invoke(f, u); };
        return minmax_(kumi::_::adl_tag, c, KUMI_FWD(t), kumi::invoke(f, get<0>(KUMI_FWD(t))),
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
                                                    std::make_index_sequence<kumi::size_v<T>>{}));
    }
  };
  inline constexpr max_t max{};
  inline constexpr max_flat_t max_flat{};
  inline constexpr min_t min{};
  inline constexpr min_flat_t min_flat{};
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
    template<typename T, typename F = void> using max_t = typename kumi::result::max<T, F>::type;
    template<typename T, typename F> struct max_flat
    {
      using type = decltype(kumi::max_flat(std::declval<T>(), std::declval<F>()));
    };
    template<typename T, typename F> using max_flat_t = typename kumi::result::max_flat<T, F>::type;
    template<typename T, typename F = void> struct min
    {
      using type = decltype(kumi::min(std::declval<T>(), std::declval<F>()));
    };
    template<typename T> struct min<T, void>
    {
      using type = decltype(kumi::min(std::declval<T>()));
    };
    template<typename T, typename F = void> using min_t = typename kumi::result::min<T, F>::type;
    template<typename T, typename F> struct min_flat
    {
      using type = decltype(kumi::min_flat(std::declval<T>(), std::declval<F>()));
    };
    template<typename T, typename F> using min_flat_t = typename kumi::result::min_flat<T, F>::type;
  }
}
namespace kumi
{
  template<template<typename> typename Pred> struct partition_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const noexcept
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return kumi::tuple{builder<T>::make(), builder<T>::make()};
      else
      {
        constexpr auto pos = []<std::size_t... I>(std::index_sequence<I...>) {
          return kumi::function::selector(std::bool_constant<Pred<kumi::stored_element_t<I, T>>::value>{}...);
        }(std::make_index_sequence<kumi::size_v<T>>{});
        return kumi::tuple{kumi::function::builder(KUMI_FWD(t), get<0>(pos)),
                           kumi::function::builder(KUMI_FWD(t), get<1>(pos))};
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
        constexpr auto pos = []<std::size_t... I>(std::index_sequence<I...>) {
          return kumi::function::selector(std::bool_constant<Pred<kumi::stored_element_t<I, T>>::value>{}...);
        }(std::make_index_sequence<kumi::size_v<T>>{});
        return kumi::function::builder(KUMI_FWD(t), get<0>(pos));
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
        constexpr auto pos = []<std::size_t... I>(std::index_sequence<I...>) {
          return function::selector(std::bool_constant<Pred<kumi::stored_element_t<I, T>>::value>{}...);
        }(std::make_index_sequence<kumi::size_v<T>>{});
        return kumi::function::builder(KUMI_FWD(t), get<1>(pos));
      }
    }
  };
  template<template<typename> typename Pred> inline constexpr partition_t<Pred> partition{};
  template<template<typename> typename Pred> inline constexpr filter_t<Pred> filter{};
  template<template<typename> typename Pred> inline constexpr filter_not_t<Pred> filter_not{};
  namespace result
  {
    template<template<typename> typename Pred, kumi::concepts::product_type T> struct partition
    {
      using type = decltype(kumi::partition<Pred>(std::declval<T>()));
    };
    template<template<typename> typename Pred, kumi::concepts::product_type T>
    using partition_t = typename kumi::result::partition<Pred, T>::type;
    template<template<typename> typename Pred, kumi::concepts::product_type T> struct filter
    {
      using type = decltype(kumi::filter<Pred>(std::declval<T>()));
    };
    template<template<typename> typename Pred, kumi::concepts::product_type T>
    using filter_t = typename kumi::result::filter<Pred, T>::type;
    template<template<typename> typename Pred, kumi::concepts::product_type T> struct filter_not
    {
      using type = decltype(kumi::filter_not<Pred>(std::declval<T>()));
    };
    template<template<typename> typename Pred, kumi::concepts::product_type T>
    using filter_not_t = typename kumi::result::filter_not<Pred, T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename Pred, std::size_t... I>
    KUMI_ABI constexpr auto all_of_(kumi::_::adl_tag_t, T&& t, Pred p, std::index_sequence<I...>)
    {
      return (kumi::invoke(p, get<I>(KUMI_FWD(t))) && ...);
    }
    template<typename T, typename Pred, std::size_t... I>
    KUMI_ABI constexpr auto any_of_(kumi::_::adl_tag_t, T&& t, Pred p, std::index_sequence<I...>)
    {
      return (kumi::invoke(p, get<I>(KUMI_FWD(t))) || ...);
    }
    template<typename Pred, typename T, std::size_t... I>
    KUMI_ABI constexpr std::size_t count_if_(kumi::_::adl_tag_t, T&& t, Pred p, std::index_sequence<I...>)
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
      else return all_of_(kumi::_::adl_tag, KUMI_FWD(t), p, std::make_index_sequence<kumi::size_v<T>>{});
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
      else return any_of_(kumi::_::adl_tag, KUMI_FWD(t), p, std::make_index_sequence<kumi::size_v<T>>{});
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
    [[nodiscard]] KUMI_ABI constexpr bool operator()(T&& t, Pred p) const noexcept
    {
      return !kumi::any_of_t::operator()(KUMI_FWD(t), p);
    }
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr bool operator()(T&& t) const noexcept
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
      else return count_if_(kumi::_::adl_tag, KUMI_FWD(t), p, std::make_index_sequence<kumi::size_v<T>>{});
    }
  };
  struct count_t : private kumi::count_if_t
  {
    template<kumi::concepts::product_type T>
    [[nodiscard]] KUMI_ABI constexpr std::size_t operator()(T&& t) const noexcept
    {
      return kumi::count_if_t::operator()(KUMI_FWD(t), [](auto const& m) { return static_cast<bool>(m); });
    }
  };
  inline constexpr all_of_t all_of{};
  inline constexpr any_of_t any_of{};
  inline constexpr none_of_t none_of{};
  inline constexpr count_if_t count_if{};
  inline constexpr count_t count{};
}
namespace kumi
{
  namespace _
  {
    struct reindex_case_t
    {
      template<typename T, template<auto> class C, auto Old, auto P>
      KUMI_ABI constexpr auto operator()(T&& t, C<Old>, kumi::projection_map<P>) const
      {
        if constexpr (kumi::concepts::projection_map<decltype(P)>) return C<P>{}(KUMI_FWD(t));
        else
        {
          static_assert(requires { get<P>(std::declval<T>()); }, "[KUMI] - Invalid projection for input type");
          return get<P>(KUMI_FWD(t));
        }
      }
    };
    inline constexpr reindex_case_t reindex_case{};
    template<typename T, typename S, auto... E>
    KUMI_ABI constexpr auto reindex_(kumi::_::adl_tag_t, T&& t, S self, kumi::projection_map<E...>)
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
    template<kumi::concepts::product_type T, std::size_t... Idx> struct reorder
    {
      using type = decltype(kumi::reorder<Idx...>(std::declval<T>()));
    };
    template<kumi::concepts::product_type T, std::size_t... Idx>
    using reorder_t = typename kumi::result::reorder<T, Idx...>::type;
    template<kumi::concepts::product_type Tuple, kumi::concepts::identifier auto... Name> struct reorder_fields
    {
      using type = decltype(kumi::reorder_fields<Name...>(std::declval<Tuple>()));
    };
    template<kumi::concepts::product_type Tuple, kumi::concepts::identifier auto... Name>
    using reorder_fields_t = typename kumi::result::reorder_fields<Tuple, Name...>::type;
    template<kumi::concepts::product_type T, kumi::concepts::projection_map auto Indexes> struct reindex
    {
      using type = decltype(kumi::reindex<Indexes>(std::declval<T>()));
    };
    template<kumi::concepts::product_type T, kumi::concepts::projection_map auto Indexes>
    using reindex_t = typename kumi::result::reindex<T, Indexes>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename M, typename S, typename T, std::size_t N, std::size_t... F, std::size_t... L>
    KUMI_ABI constexpr auto reduce_(
      kumi::_::adl_tag_t, M&& m, S s, T&& t, kumi::index_t<N>, std::index_sequence<F...>, std::index_sequence<L...>)
    {
      if constexpr (N == 1)
        return s(KUMI_FWD(m), kumi::tuple{kumi::invoke(KUMI_FWD(m), get<F>(KUMI_FWD(t)), get<L>(KUMI_FWD(t)))...,
                                          get<kumi::size_v<T> - 1>(KUMI_FWD(t))});
      else return s(KUMI_FWD(m), kumi::tuple{kumi::invoke(KUMI_FWD(m), get<F>(KUMI_FWD(t)), get<L>(KUMI_FWD(t)))...});
    }
    template<typename M, typename T, typename F, typename S, std::size_t N, std::size_t... I, std::size_t... J>
    KUMI_ABI constexpr auto map_reduce_(kumi::_::adl_tag_t,
                                        M&& m,
                                        T&& t,
                                        F f,
                                        S s,
                                        kumi::index_t<N>,
                                        std::index_sequence<I...>,
                                        std::index_sequence<J...>)
    {
      if constexpr (N == 1)
        return s(KUMI_FWD(m), kumi::tuple{kumi::invoke(KUMI_FWD(m), kumi::invoke(f, get<I>(KUMI_FWD(t))),
                                                       kumi::invoke(f, get<J>(KUMI_FWD(t))))...,
                                          kumi::invoke(f, get<kumi::size_v<T> - 1>(KUMI_FWD(t)))});
      else
        return s(KUMI_FWD(m), kumi::tuple{kumi::invoke(KUMI_FWD(m), kumi::invoke(f, get<I>(KUMI_FWD(t))),
                                                       kumi::invoke(f, get<J>(KUMI_FWD(t))))...});
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
      else
      {
        constexpr auto sz = kumi::size_v<T>;
        constexpr auto pos = kumi::function::reducer(std::make_index_sequence<sz / 2>{}, index<sz % 2>);
        return reduce_(kumi::_::adl_tag, KUMI_FWD(m), (*this), KUMI_FWD(t), get<2>(pos), get<0>(pos), get<1>(pos));
      }
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
      else
      {
        constexpr auto sz = kumi::size_v<T>;
        constexpr auto pos = kumi::function::reducer(std::make_index_sequence<sz / 2>{}, index<sz % 2>);
        return map_reduce_(kumi::_::adl_tag, KUMI_FWD(m), KUMI_FWD(t), f, kumi::reduce_t{}, get<2>(pos), get<0>(pos),
                           get<1>(pos));
      }
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
  inline constexpr reduce_t reduce{};
  inline constexpr map_reduce_t map_reduce{};
  inline constexpr sum_t sum{};
  inline constexpr prod_t prod{};
  inline constexpr bit_and_t bit_and{};
  inline constexpr bit_or_t bit_or{};
  inline constexpr bit_xor_t bit_xor{};
  namespace result
  {
    template<kumi::concepts::monoid M, kumi::concepts::product_type T, typename Value = void> struct reduce
    {
      using type = decltype(kumi::reduce(std::declval<M>(), std::declval<T>(), std::declval<Value>()));
    };
    template<kumi::concepts::monoid M, kumi::concepts::product_type T> struct reduce<M, T>
    {
      using type = decltype(kumi::reduce(std::declval<M>(), std::declval<T>()));
    };
    template<typename F, kumi::concepts::monoid M, kumi::concepts::product_type T, typename Value = void>
    struct map_reduce
    {
      using type =
        decltype(kumi::map_reduce(std::declval<F>(), std::declval<M>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename F, kumi::concepts::monoid M, kumi::concepts::product_type T> struct map_reduce<F, M, T>
    {
      using type = decltype(kumi::map_reduce(std::declval<F>(), std::declval<M>(), std::declval<T>()));
    };
    template<kumi::concepts::product_type T, typename Value = void> struct sum
    {
      using type = decltype(kumi::sum(std::declval<T>(), std::declval<Value>()));
    };
    template<kumi::concepts::product_type T> struct sum<T>
    {
      using type = decltype(kumi::sum(std::declval<T>()));
    };
    template<kumi::concepts::product_type T, typename Value = void> struct prod
    {
      using type = decltype(kumi::prod(std::declval<T>(), std::declval<Value>()));
    };
    template<kumi::concepts::product_type T> struct prod<T>
    {
      using type = decltype(kumi::prod(std::declval<T>()));
    };
    template<kumi::concepts::product_type T, typename Value = void> struct bit_and
    {
      using type = decltype(kumi::bit_and(std::declval<T>(), std::declval<Value>()));
    };
    template<kumi::concepts::product_type T> struct bit_and<T>
    {
      using type = decltype(kumi::bit_and(std::declval<T>()));
    };
    template<kumi::concepts::product_type T, typename Value = void> struct bit_or
    {
      using type = decltype(kumi::bit_or(std::declval<T>(), std::declval<Value>()));
    };
    template<kumi::concepts::product_type T> struct bit_or<T>
    {
      using type = decltype(kumi::bit_or(std::declval<T>()));
    };
    template<kumi::concepts::product_type T, typename Value = void> struct bit_xor
    {
      using type = decltype(kumi::bit_xor(std::declval<T>(), std::declval<Value>()));
    };
    template<kumi::concepts::product_type T> struct bit_xor<T>
    {
      using type = decltype(kumi::bit_xor(std::declval<T>()));
    };
    template<kumi::concepts::monoid M, kumi::concepts::product_type T, typename Value = void>
    using reduce_t = typename kumi::result::reduce<M, T, Value>::type;
    template<typename F, kumi::concepts::monoid M, kumi::concepts::product_type T, typename Value = void>
    using map_reduce_t = typename kumi::result::map_reduce<F, M, T, Value>::type;
    template<kumi::concepts::product_type T, typename Value = void>
    using sum_t = typename kumi::result::sum<T, Value>::type;
    template<kumi::concepts::product_type T, typename Value = void>
    using prod_t = typename kumi::result::prod<T, Value>::type;
    template<kumi::concepts::product_type T, typename Value = void>
    using bit_and_t = typename kumi::result::bit_and<T, Value>::type;
    template<kumi::concepts::product_type T, typename Value = void>
    using bit_or_t = typename kumi::result::bit_or<T, Value>::type;
    template<kumi::concepts::product_type T, typename Value = void>
    using bit_xor_t = typename kumi::result::bit_xor<T, Value>::type;
  }
}
namespace kumi
{
  struct reverse_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return builder<T>::make();
      else
      {
        constexpr auto idx = kumi::function::reverser(std::make_index_sequence<kumi::size_v<T>>{});
        return kumi::function::builder(KUMI_FWD(t), idx);
      }
    }
  };
  inline constexpr reverse_t reverse{};
  namespace result
  {
    template<kumi::concepts::product_type T> struct reverse
    {
      using type = decltype(kumi::reverse(std::declval<T>()));
    };
    template<kumi::concepts::product_type T> using reverse_t = typename kumi::result::reverse<T>::type;
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
      {
        constexpr auto idxs =
          kumi::function::rotater(std::make_index_sequence<kumi::size_v<T>>{}, kumi::index<(R % kumi::size_v<T>)>);
        return kumi::function::builder(KUMI_FWD(t), idxs);
      }
    }
  };
  template<std::size_t R> struct rotate_right_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else if constexpr ((R % kumi::size_v<T>) == 0) return KUMI_FWD(t);
      else
      {
        constexpr auto F = R % kumi::size_v<T>;
        constexpr auto idxs =
          kumi::function::rotater(std::make_index_sequence<kumi::size_v<T>>{}, kumi::index<(kumi::size_v<T> - F)>);
        return kumi::function::builder(KUMI_FWD(t), idxs);
      }
    }
  };
  template<std::size_t R> inline constexpr rotate_left_t<R> rotate_left{};
  template<std::size_t R> inline constexpr rotate_right_t<R> rotate_right{};
  namespace result
  {
    template<std::size_t R, kumi::concepts::product_type T> struct rotate_left
    {
      using type = decltype(kumi::rotate_left<R>(std::declval<T>()));
    };
    template<std::size_t R, kumi::concepts::product_type T>
    using rotate_left_t = typename kumi::result::rotate_left<R, T>::type;
    template<std::size_t R, kumi::concepts::product_type T> struct rotate_right
    {
      using type = decltype(kumi::rotate_right<R>(std::declval<T>()));
    };
    template<std::size_t R, kumi::concepts::product_type T>
    using rotate_right_t = typename kumi::result::rotate_right<R, T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, typename V, typename F, typename O, std::size_t... I>
    KUMI_ABI constexpr auto inclusive_scan_left_(kumi::_::adl_tag_t, T&& t, V v, F f, O o, std::index_sequence<I...>)
    {
      return (kumi::function::scannable{o, kumi::invoke(f, v, get<0>(KUMI_FWD(t)))} >> ... >>
              kumi::bind_back(f, get<I + 1>(KUMI_FWD(t))))();
    }
    template<typename T, typename V, typename F, typename O, std::size_t... I>
    KUMI_ABI constexpr auto exclusive_scan_left_(kumi::_::adl_tag_t, T&& t, V v, F f, O o, std::index_sequence<I...>)
    {
      return (kumi::function::scannable{o, v} >> ... >> kumi::bind_back(f, get<I>(KUMI_FWD(t))))();
    }
    template<typename T, typename V, typename F, typename O, std::size_t... I>
    KUMI_ABI constexpr auto inclusive_scan_right_(kumi::_::adl_tag_t, T&& t, V v, F f, O o, std::index_sequence<I...>)
    {
      return (kumi::bind_front(f, get<I>(KUMI_FWD(t)))
              << ... << kumi::function::scannable{o, kumi::invoke(f, get<kumi::size_v<T> - 1>(KUMI_FWD(t)), v)})();
    }
    template<typename T, typename V, typename F, typename O, std::size_t... I>
    KUMI_ABI constexpr auto exclusive_scan_right_(kumi::_::adl_tag_t, T&& t, V v, F f, O o, std::index_sequence<I...>)
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
        auto op = [](auto&&... xs) { return kumi::make_tuple(KUMI_FWD(xs)...); };
        return inclusive_scan_left_(kumi::_::adl_tag, KUMI_FWD(t), init, f, op,
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
        auto op = [](auto&&... xs) { return kumi::make_tuple(KUMI_FWD(xs)...); };
        return exclusive_scan_left_(kumi::_::adl_tag, KUMI_FWD(t), init, f, op,
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
        auto op = [](auto&&... xs) { return kumi::make_tuple(KUMI_FWD(xs)...); };
        return inclusive_scan_right_(kumi::_::adl_tag, KUMI_FWD(t), init, f, op,
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
        auto op = [](auto&&... xs) { return kumi::make_tuple(KUMI_FWD(xs)...); };
        return exclusive_scan_right_(kumi::_::adl_tag, KUMI_FWD(t), init, f, op,
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
  inline constexpr inclusive_scan_left_t inclusive_scan_left{};
  inline constexpr exclusive_scan_left_t exclusive_scan_left{};
  inline constexpr inclusive_scan_right_t inclusive_scan_right{};
  inline constexpr exclusive_scan_right_t exclusive_scan_right{};
  namespace result
  {
    template<typename Function, kumi::concepts::product_type T, typename Value = void> struct inclusive_scan_right
    {
      using type =
        decltype(kumi::inclusive_scan_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, kumi::concepts::product_type T> struct inclusive_scan_right<Function, T>
    {
      using type = decltype(kumi::inclusive_scan_right(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, kumi::concepts::product_type T, typename Value = void>
    using inclusive_scan_right_t = typename kumi::result::inclusive_scan_right<Function, T, Value>::type;
    template<typename Function, kumi::concepts::product_type T, typename Value = void> struct exclusive_scan_right
    {
      using type =
        decltype(kumi::exclusive_scan_right(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, kumi::concepts::product_type T> struct exclusive_scan_right<Function, T>
    {
      using type = decltype(kumi::exclusive_scan_right(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, kumi::concepts::product_type T, typename Value = void>
    using exclusive_scan_right_t = typename kumi::result::exclusive_scan_right<Function, T, Value>::type;
    template<typename Function, kumi::concepts::product_type T, typename Value = void> struct inclusive_scan_left
    {
      using type =
        decltype(kumi::inclusive_scan_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, kumi::concepts::product_type T> struct inclusive_scan_left<Function, T>
    {
      using type = decltype(kumi::inclusive_scan_left(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, kumi::concepts::product_type T, typename Value = void>
    using inclusive_scan_left_t = typename kumi::result::inclusive_scan_left<Function, T, Value>::type;
    template<typename Function, kumi::concepts::product_type T, typename Value = void> struct exclusive_scan_left
    {
      using type =
        decltype(kumi::exclusive_scan_left(std::declval<Function>(), std::declval<T>(), std::declval<Value>()));
    };
    template<typename Function, kumi::concepts::product_type T> struct exclusive_scan_left<Function, T>
    {
      using type = decltype(kumi::exclusive_scan_left(std::declval<Function>(), std::declval<T>()));
    };
    template<typename Function, kumi::concepts::product_type T, typename Value = void>
    using exclusive_scan_left_t = typename kumi::result::exclusive_scan_left<Function, T, Value>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, std::size_t... B, std::size_t... E>
    KUMI_ABI constexpr auto tiles_(kumi::_::adl_tag_t, T&& t, std::index_sequence<B...>, std::index_sequence<E...>)
    {
      return kumi::tuple{
        kumi::function::builder(KUMI_FWD(t), kumi::function::shifter(std::integral_constant<std::size_t, E>{},
                                                                     std::make_index_sequence<B>{}))...};
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
        constexpr auto bs = std::integral_constant<std::size_t, kumi::_::nb_blocks(kumi::size_v<T>, O, N)>{};
        constexpr auto proj = kumi::function::tiler(kumi::index<kumi::size_v<T>>, kumi::index<N>, kumi::index<O>,
                                                    std::make_index_sequence<bs>{});
        return tiles_(kumi::_::adl_tag, KUMI_FWD(t), get<0>(proj), get<1>(proj));
      }
    }
  };
  template<std::size_t N, std::size_t O> inline constexpr tiles_t<N, O> tiles{};
  template<std::size_t N> inline constexpr tiles_t<N, 1> windows{};
  template<std::size_t N> inline constexpr tiles_t<N, N> chunks{};
  namespace result
  {
    template<std::size_t N, std::size_t O, kumi::concepts::product_type T> struct tiles
    {
      using type = decltype(kumi::tiles<N, O>(std::declval<T>()));
    };
    template<std::size_t N, std::size_t O, kumi::concepts::product_type T>
    using tiles_t = typename kumi::result::tiles<N, O, T>::type;
    template<std::size_t N, kumi::concepts::product_type T> struct windows
    {
      using type = decltype(kumi::windows<N>(std::declval<T>()));
    };
    template<std::size_t N, kumi::concepts::product_type T>
    using windows_t = typename kumi::result::windows<N, T>::type;
    template<std::size_t N, kumi::concepts::product_type T> struct chunks
    {
      using type = decltype(kumi::chunks<N>(std::declval<T>()));
    };
    template<std::size_t N, kumi::concepts::product_type T> using chunks_t = typename kumi::result::chunks<N, T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, std::size_t... I, std::size_t... J>
    KUMI_ABI constexpr decltype(auto) transpose_extern_(kumi::_::adl_tag_t,
                                                        T&& t,
                                                        std::index_sequence<I...>,
                                                        std::index_sequence<J...> is)
    {
      return kumi::make_tuple(kumi::function::builder(KUMI_FWD(t), std::integral_constant<std::size_t, I>{}, is)...);
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
        constexpr auto pos = kumi::function::zipper(kumi::index<c>, kumi::index<s>);
        return transpose_extern_(kumi::_::adl_tag, KUMI_FWD(t), get<1>(pos), get<0>(pos));
      }
    }
  };
  inline constexpr transpose_t transpose{};
  namespace result
  {
    template<kumi::concepts::product_type T> struct transpose
    {
      using type = decltype(kumi::transpose(std::declval<T>()));
    };
    template<kumi::concepts::product_type T> using transpose_t = typename kumi::result::transpose<T>::type;
  }
}
namespace kumi
{
  struct unique_t
  {
    template<kumi::concepts::product_type T> [[nodiscard]] KUMI_ABI constexpr auto operator()(T&& t) const
    {
      if constexpr (kumi::concepts::empty_product_type<T>) return KUMI_FWD(t);
      else if constexpr (kumi::concepts::sized_product_type<T, 1>) return KUMI_FWD(t);
      else
      {
        constexpr auto proj = kumi::function::uniqued(as<T>{});
        return kumi::function::builder(KUMI_FWD(t), proj);
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
        constexpr auto proj = []<std::size_t... I>(std::index_sequence<I...>) {
          return kumi::function::uniquer(std::type_identity<kumi::stored_element_t<I, T>>{}...);
        }(std::make_index_sequence<kumi::size_v<T>>{});
        return kumi::function::builder(KUMI_FWD(t), proj);
      }
    }
  };
  inline constexpr unique_t unique{};
  inline constexpr all_unique_t all_unique{};
  namespace result
  {
    template<kumi::concepts::product_type T> struct unique
    {
      using type = decltype(kumi::unique(std::declval<T>()));
    };
    template<kumi::concepts::product_type T> using unique_t = typename kumi::result::unique<T>::type;
    template<kumi::concepts::product_type T> struct all_unique
    {
      using type = decltype(kumi::all_unique(std::declval<T>()));
    };
    template<kumi::concepts::product_type T> using all_unique_t = typename kumi::result::all_unique<T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<typename T, std::size_t... I, std::size_t... J>
    KUMI_ABI constexpr auto zip_(kumi::_::adl_tag_t, T&& t, std::index_sequence<I...>, std::index_sequence<J...> is)
    {
      return kumi::make_tuple(kumi::function::builder(KUMI_FWD(t), std::integral_constant<std::size_t, I>{}, is)...);
    }
    template<typename T, std::size_t N, std::size_t... I>
    constexpr auto zip_intern_(T&& t, kumi::index_t<N>, std::index_sequence<I...>)
    {
      using U = kumi::common_product_type_t<std::remove_cvref_t<kumi::function::element_or_t<I, T, kumi::unit>>...>;
      return kumi::builder<U>::make(kumi::function::get_or<N>(get<I>(KUMI_FWD(t)), kumi::none)...);
    }
    template<typename T, std::size_t... I, std::size_t... J>
    constexpr auto zip_max_(kumi::_::adl_tag_t, T&& t, std::index_sequence<I...>, std::index_sequence<J...> is)
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
        constexpr auto pos = kumi::function::zipper(kumi::index<c>, kumi::index<kumi::size_v<T0>>);
        return zip_(kumi::_::adl_tag, kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...), get<1>(pos), get<0>(pos));
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
        constexpr auto pos = kumi::function::zipper(kumi::index<c>, kumi::index<m>);
        return zip_(kumi::_::adl_tag, kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...), get<1>(pos), get<0>(pos));
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
        constexpr auto pos = kumi::function::zipper(kumi::index<c>, kumi::index<m>);
        return zip_max_(kumi::_::adl_tag, kumi::forward_as_tuple(KUMI_FWD(t0), KUMI_FWD(ts)...), get<1>(pos),
                        get<0>(pos));
      }
    }
  };
  inline constexpr zip_t zip{};
  inline constexpr zip_min_t zip_min{};
  inline constexpr zip_max_t zip_max{};
  namespace result
  {
    template<kumi::concepts::product_type T0, kumi::concepts::sized_product_type<kumi::size_v<T0>>... Ts> struct zip
    {
      using type = decltype(kumi::zip(std::declval<T0>(), std::declval<Ts>()...));
    };
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts>
    using zip_t = typename kumi::result::zip<T0, Ts...>::type;
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts> struct zip_min
    {
      using type = decltype(kumi::zip_min(std::declval<T0>(), std::declval<Ts>()...));
    };
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts>
    using zip_min_t = typename kumi::result::zip_min<T0, Ts...>::type;
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts> struct zip_max
    {
      using type = decltype(kumi::zip_max(std::declval<T0>(), std::declval<Ts>()...));
    };
    template<kumi::concepts::product_type T0, kumi::concepts::product_type... Ts>
    using zip_max_t = typename kumi::result::zip_max<T0, Ts...>::type;
  }
}
#endif
