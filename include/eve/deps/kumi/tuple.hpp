//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#ifndef KUMI_TUPLE_HPP_INCLUDED
#define KUMI_TUPLE_HPP_INCLUDED
#if defined( __ANDROID__ ) || defined(__APPLE__)
#include <type_traits>
namespace kumi
{
  template<typename From, typename To>
  concept convertible_to  =   std::is_convertible_v<From, To>
                          &&  requires { static_cast<To>(std::declval<From>()); };
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
namespace kumi
{
  template<typename T, typename Enable = void> struct is_product_type : std::false_type {};
  template<typename T> struct is_product_type<T, typename T::is_product_type> : std::true_type {};
  template<typename T> struct size : std::tuple_size<T>   {};
  template<typename T> struct size<T &>         : size<T> {};
  template<typename T> struct size<T &&>        : size<T> {};
  template<typename T> struct size<T const>     : size<T> {};
  template<typename T> struct size<T const &>   : size<T> {};
  template<typename T> struct size<T const &&>  : size<T> {};
  template<typename T> inline constexpr auto size_v = size<T>::value;
  template<std::size_t I, typename T> struct element              : std::tuple_element<I,T> {};
  template<std::size_t I, typename T> struct element<I,T&>        : element<I,T> {};
  template<std::size_t I, typename T> struct element<I,T&&>       : element<I,T> {};
  template<std::size_t I, typename T> struct element<I,T const&>  : element<I,T> {};
  template<std::size_t I, typename T> struct element<I,T const&&> : element<I,T> {};
  template<std::size_t I, typename T> using  element_t = typename element<I,T>::type;
  template<std::size_t I, typename T> struct member
  {
    using type = decltype( get<I>(std::declval<T&>()));
  };
  template<std::size_t I, typename T> using  member_t = typename member<I,T>::type;
}
namespace kumi
{
  template<typename T>
  struct is_homogeneous;
  template<typename T>
  requires( requires { T::is_homogeneous; } )
  struct is_homogeneous<T> : std::bool_constant<T::is_homogeneous>
  {};
  template<typename T>
  inline constexpr auto is_homogeneous_v = is_homogeneous<T>::value;
  template<typename... Ts> struct tuple;
}
#include <cstddef>
#include <utility>
namespace kumi::_
{
  template<typename T> concept non_empty_tuple = requires( T const &t )
  {
    typename std::tuple_element<0,std::remove_cvref_t<T>>::type;
    typename std::tuple_size<std::remove_cvref_t<T>>::type;
  };
  template<typename T> concept empty_tuple = (std::tuple_size<std::remove_cvref_t<T>>::value == 0);
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
  concept ordered = requires(From const& a, To const& b){ {a < b}; };
  template<template<class...> class Box, typename... From, typename... To>
  struct is_piecewise_ordered<Box<From...>, Box<To...>>
  {
    static constexpr bool value = (... && ordered<From,To> );
  };
  template<typename From, typename To>
  concept piecewise_convertible = _::is_piecewise_convertible<From, To>::value;
  template<typename From, typename To>
  concept piecewise_constructible = _::is_piecewise_constructible<From, To>::value;
  template<typename From, typename To>
  concept piecewise_ordered = _::is_piecewise_ordered<From, To>::value;
  template<typename T, typename... Args> concept implicit_constructible = requires(Args... args)
  {
    T {args...};
  };
  template<typename F, size_t I, typename... Tuples>
  concept supports_call_i = std::is_invocable_v<F, member_t<I,Tuples>...>;
  template<typename F, typename Indices, typename... Tuples> struct supports_call_t;
  template<typename F, size_t... Is, typename... Tuples>
  struct supports_call_t<F, std::index_sequence<Is...>, Tuples...>
      : std::bool_constant<(supports_call_i<F, Is, Tuples...> && ...)>
  {
  };
  template<typename F, typename Indices, typename Tuple> struct supports_apply_t;
  template<typename F, size_t... Is, typename Tuple>
  struct supports_apply_t<F, std::index_sequence<Is...>, Tuple>
      : std::is_invocable<F, member_t<Is,Tuple>...>
  {
  };
  template<typename F, typename Tuple>
  concept supports_apply = _::
      supports_apply_t<F, std::make_index_sequence<size<Tuple>::value>, Tuple>::value;
  template<typename F, typename... Tuples>
  concept supports_call = _::
      supports_call_t<F, std::make_index_sequence<(size<Tuples>::value, ...)>, Tuples...>::value;
  template<typename T, typename U>
  concept comparable = requires(T t, U u)
  {
    { t == u };
  };
}
#if defined(__GNUC__)
#   define KUMI_TRIVIAL [[gnu::always_inline, gnu::flatten, gnu::artificial]] inline
#   define KUMI_TRIVIAL_NODISCARD [[nodiscard, gnu::always_inline, gnu::flatten, gnu::artificial]] inline
#elif defined(_MSC_VER)
#   define KUMI_TRIVIAL __forceinline
#   define KUMI_TRIVIAL_NODISCARD [[nodiscard]]
#endif
#include <cstddef>
#include <utility>
namespace kumi::_
{
  template<int I, typename T> struct leaf
  {
    T value;
  };
  template<int I, typename T>
  KUMI_TRIVIAL constexpr T       &  get_leaf(leaf<I, T>       & a) noexcept { return a.value; }
  template<int I, typename T>
  KUMI_TRIVIAL constexpr T       && get_leaf(leaf<I, T>       &&a) noexcept { return static_cast<T&&>(a.value); }
  template<int I, typename T>
  KUMI_TRIVIAL constexpr T const && get_leaf(leaf<I, T> const &&a) noexcept { return static_cast<T const &&>(a.value); }
  template<int I, typename T>
  KUMI_TRIVIAL constexpr T const &  get_leaf(leaf<I, T> const & a) noexcept { return a.value; }
  template<typename ISeq, typename... Ts> struct binder;
  template<int... Is, typename... Ts>
  struct binder<std::integer_sequence<int,Is...>, Ts...> : leaf<Is, Ts>...
  {
    static constexpr bool is_homogeneous = false;
  };
  template<typename ISeq, typename... Ts>
  struct make_binder
  {
    using type = binder<ISeq,Ts...>;
  };
  template<typename ISeq, typename... Ts>
  using make_binder_t = typename make_binder<ISeq,Ts...>::type;
}
#include <cstddef>
#include <utility>
namespace kumi::_
{
  template<typename... Ts>
  inline constexpr bool no_references = (true && ... && !std::is_reference_v<Ts>);
  template<typename T0, typename... Ts>
  inline constexpr bool all_the_same = (true && ... && std::is_same_v<T0,Ts>);
  template<typename T0, int N> struct binder_n
  {
    static constexpr bool is_homogeneous = true;
    T0 members[N];
  };
  template<int... Is, typename T0, typename T1, typename... Ts>
  requires(all_the_same<T0,T1,Ts...> && no_references<T0,T1,Ts...>)
  struct make_binder<std::integer_sequence<int,Is...>, T0, T1, Ts...>
  {
    using type = binder_n<T0,2+sizeof...(Ts)>;
  };
  template<std::size_t I, typename T0, int N>
  KUMI_TRIVIAL constexpr auto& get_leaf(binder_n<T0,N> &arg)             noexcept { return arg.members[I]; }
  template<std::size_t I, typename T0, int N>
  KUMI_TRIVIAL constexpr auto const& get_leaf(binder_n<T0,N> const &arg) noexcept { return arg.members[I]; }
  template<std::size_t I, typename T0, int N>
  KUMI_TRIVIAL constexpr auto&& get_leaf(binder_n<T0,N> &&arg) noexcept
  {
    return static_cast<T0&&>(arg.members[I]);
  }
  template<std::size_t I, typename T0, int N>
  KUMI_TRIVIAL constexpr auto const&& get_leaf(binder_n<T0,N> const &&arg) noexcept
  {
    return static_cast<T0 const &&>(arg.members[I]);
  }
  template<>
  struct binder<std::integer_sequence<int>>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
  };
  template<typename T>
  requires(no_references<T>)
  struct binder<std::integer_sequence<int,0>,T>
  {
    static constexpr bool is_homogeneous = true;
    using kumi_specific_layout = void;
    using member0_type = T;
    member0_type member0;
  };
  template<typename T0, typename T1>
  requires(no_references<T0,T1>)
  struct binder<std::integer_sequence<int,0,1>,T0,T1>
  {
    static constexpr bool is_homogeneous = false;
    using kumi_specific_layout = void;
    using member0_type = T0;
    using member1_type = T1;
    member0_type member0;
    member1_type member1;
  };
  template<typename T0, typename T1, typename T2>
  requires(no_references<T0,T1,T2>)
  struct binder<std::integer_sequence<int,0,1,2>,T0,T1,T2>
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
  requires(no_references<T0,T1,T2,T3>)
  struct binder<std::integer_sequence<int,0,1,2,3>,T0,T1,T2,T3>
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
  requires(no_references<T0,T1,T2,T3,T4>)
  struct binder<std::integer_sequence<int,0,1,2,3,4>,T0,T1,T2,T3,T4>
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
  requires(no_references<T0,T1,T2,T3,T4,T5>)
  struct binder<std::integer_sequence<int,0,1,2,3,4,5>,T0,T1,T2,T3,T4,T5>
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
  template< typename T0, typename T1, typename T2, typename T3, typename T4
          , typename T5, typename T6
          >
  requires(no_references<T0,T1,T2,T3,T4,T5,T6>)
  struct binder<std::integer_sequence<int,0,1,2,3,4,5,6>,T0,T1,T2,T3,T4,T5,T6>
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
  template< typename T0, typename T1, typename T2, typename T3, typename T4
          , typename T5, typename T6, typename T7
          >
  requires(no_references<T0,T1,T2,T3,T4,T5,T6,T7>)
  struct binder<std::integer_sequence<int,0,1,2,3,4,5,6,7>,T0,T1,T2,T3,T4,T5,T6,T7>
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
  template< typename T0, typename T1, typename T2, typename T3, typename T4
          , typename T5, typename T6, typename T7, typename T8
          >
  requires(no_references<T0,T1,T2,T3,T4,T5,T6,T7,T8>)
  struct binder<std::integer_sequence<int,0,1,2,3,4,5,6,7,8>,T0,T1,T2,T3,T4,T5,T6,T7,T8>
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
  template< typename T0, typename T1, typename T2, typename T3, typename T4
          , typename T5, typename T6, typename T7, typename T8, typename T9
          >
  requires(no_references<T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>)
  struct binder<std::integer_sequence<int,0,1,2,3,4,5,6,7,8,9>,T0,T1,T2,T3,T4,T5,T6,T7,T8,T9>
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
  template<std::size_t I,typename Binder>
  requires requires(Binder) { typename Binder::kumi_specific_layout; }
  KUMI_TRIVIAL constexpr auto &get_leaf(Binder &arg) noexcept
  {
    if constexpr(I == 0) return arg.member0;
    if constexpr(I == 1) return arg.member1;
    if constexpr(I == 2) return arg.member2;
    if constexpr(I == 3) return arg.member3;
    if constexpr(I == 4) return arg.member4;
    if constexpr(I == 5) return arg.member5;
    if constexpr(I == 6) return arg.member6;
    if constexpr(I == 7) return arg.member7;
    if constexpr(I == 8) return arg.member8;
    if constexpr(I == 9) return arg.member9;
  }
  template<std::size_t I,typename Binder>
  requires requires(Binder) { typename Binder::kumi_specific_layout; }
  KUMI_TRIVIAL constexpr auto &&get_leaf(Binder &&arg) noexcept
  {
    if constexpr(I == 0) return static_cast<typename Binder::member0_type &&>(arg.member0);
    if constexpr(I == 1) return static_cast<typename Binder::member1_type &&>(arg.member1);
    if constexpr(I == 2) return static_cast<typename Binder::member2_type &&>(arg.member2);
    if constexpr(I == 3) return static_cast<typename Binder::member3_type &&>(arg.member3);
    if constexpr(I == 4) return static_cast<typename Binder::member4_type &&>(arg.member4);
    if constexpr(I == 5) return static_cast<typename Binder::member5_type &&>(arg.member5);
    if constexpr(I == 6) return static_cast<typename Binder::member6_type &&>(arg.member6);
    if constexpr(I == 7) return static_cast<typename Binder::member7_type &&>(arg.member7);
    if constexpr(I == 8) return static_cast<typename Binder::member8_type &&>(arg.member8);
    if constexpr(I == 9) return static_cast<typename Binder::member9_type &&>(arg.member9);
  }
  template<std::size_t I,typename Binder>
  requires requires(Binder) { typename Binder::kumi_specific_layout; }
  KUMI_TRIVIAL constexpr auto const &&get_leaf(Binder const &&arg) noexcept
  {
    if constexpr(I == 0) return static_cast<typename Binder::member0_type const&&>(arg.member0);
    if constexpr(I == 1) return static_cast<typename Binder::member1_type const&&>(arg.member1);
    if constexpr(I == 2) return static_cast<typename Binder::member2_type const&&>(arg.member2);
    if constexpr(I == 3) return static_cast<typename Binder::member3_type const&&>(arg.member3);
    if constexpr(I == 4) return static_cast<typename Binder::member4_type const&&>(arg.member4);
    if constexpr(I == 5) return static_cast<typename Binder::member5_type const&&>(arg.member5);
    if constexpr(I == 6) return static_cast<typename Binder::member6_type const&&>(arg.member6);
    if constexpr(I == 7) return static_cast<typename Binder::member7_type const&&>(arg.member7);
    if constexpr(I == 8) return static_cast<typename Binder::member8_type const&&>(arg.member8);
    if constexpr(I == 9) return static_cast<typename Binder::member9_type const&&>(arg.member9);
  }
  template<std::size_t I,typename Binder>
  requires requires(Binder) { typename Binder::kumi_specific_layout; }
  KUMI_TRIVIAL constexpr auto const &get_leaf(Binder const &arg) noexcept
  {
    if constexpr(I == 0) return arg.member0;
    if constexpr(I == 1) return arg.member1;
    if constexpr(I == 2) return arg.member2;
    if constexpr(I == 3) return arg.member3;
    if constexpr(I == 4) return arg.member4;
    if constexpr(I == 5) return arg.member5;
    if constexpr(I == 6) return arg.member6;
    if constexpr(I == 7) return arg.member7;
    if constexpr(I == 8) return arg.member8;
    if constexpr(I == 9) return arg.member9;
  }
}
namespace kumi
{
}
#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wmissing-braces"
#endif
#define KUMI_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)
#include <cstddef>
namespace kumi
{
  template<std::size_t N> struct index_t
  {
    static constexpr auto value = N;
    constexpr inline      operator std::size_t() const noexcept { return N; }
  };
  template<std::size_t N> inline constexpr index_t<N> const index = {};
  namespace literals
  {
    template<char... c> constexpr auto b10()
    {
      auto value = 0ULL;
      ((value = value * 10 + (c - '0')), ...);
      return value;
    }
    template<char... c> constexpr auto operator"" _c() noexcept { return index<b10<c...>()>; }
  }
  template<template<class> class Pred> [[nodiscard]] constexpr auto predicate() noexcept
  {
    return []<typename T>(T const&) constexpr { return Pred<T>::value; };
  }
}
#include <concepts>
#include <cstddef>
#include <type_traits>
#include <utility>
namespace kumi
{
  template<typename T>
  concept std_tuple_compatible = _::empty_tuple<T> || _::non_empty_tuple<T>;
  template<typename T>
  concept product_type = std_tuple_compatible<T> && is_product_type<std::remove_cvref_t<T>>::value;
  template<typename T, std::size_t N>
  concept sized_product_type = product_type<T> && (size<T>::value == N);
  template<typename T, std::size_t N>
  concept sized_product_type_or_more = product_type<T> && (size<T>::value >= N);
  template<typename T>
  concept non_empty_product_type = product_type<T> && (size<T>::value != 0);
  template<typename T>
  concept homogeneous_product_type = product_type<T> && is_homogeneous_v<std::remove_cvref_t<T>>;
  namespace _
  {
    template<typename T, typename U>
    constexpr auto check_equality()
    {
      return []<std::size_t...I>(std::index_sequence<I...>)
      {
        return (_::comparable<member_t<I,T>,member_t<I,U>> && ...);
      }(std::make_index_sequence<size<T>::value>{});
    }
  }
  template<typename T, typename U>
  concept equality_comparable = (size_v<T> == size_v<U>) && _::check_equality<T,U>();
}
namespace kumi
{
  template<typename Function, product_type Tuple>
  constexpr decltype(auto) apply(Function &&f, Tuple &&t)
  requires _::supports_apply<Function&&, Tuple&&>
  {
    if constexpr(sized_product_type<Tuple,0>) return  KUMI_FWD(f)();
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>) -> decltype(auto)
      {
        return KUMI_FWD(f)(get<I>(KUMI_FWD(t))...);
      }
      (std::make_index_sequence<size<Tuple>::value>());
    }
  }
  namespace result
  {
    template<typename Function, product_type Tuple>
    struct apply
    {
      using type = decltype(kumi::apply(std::declval<Function>(), std::declval<Tuple>()));
    };
    template<typename Function, product_type Tuple>
    using apply_t = typename apply<Function,Tuple>::type;
  }
}
namespace kumi
{
  template<typename Function, product_type Tuple, product_type... Tuples>
  constexpr void for_each(Function f, Tuple&& t, Tuples&&... ts)
  requires _::supports_call<Function&, Tuple, Tuples...>
  {
    if constexpr(sized_product_type<Tuple,0>) return;
    else
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        using std::get;
        [[maybe_unused]] auto call = [&]<typename M>(M)
                                        { f ( get<M::value>(KUMI_FWD(t))
                                            , get<M::value>(KUMI_FWD(ts))...
                                            );
                                        };
        ( call(std::integral_constant<std::size_t, I>{}), ... );
      }
      (std::make_index_sequence<size<Tuple>::value>());
    }
  }
  template<typename Function, product_type Tuple, product_type... Tuples>
  constexpr void for_each_index(Function f, Tuple&& t, Tuples&&... ts)
  {
    if constexpr(sized_product_type<Tuple,0>) return;
    else
    {
      auto const invoker{[&, f](auto const i)
      {
          f
          (
            i,
            get<i.value>(KUMI_FWD(t)),
            get<i.value>(KUMI_FWD(ts))...
          );
      }};
      [=]<std::size_t... I>(std::index_sequence<I...>)
      {
        (invoker( std::integral_constant<unsigned, I>{} ), ...);
      }(std::make_index_sequence<size<Tuple>::value>());
    }
  }
}
#include <array>
#include <type_traits>
#include <utility>
#if !defined(KUMI_DOXYGEN_INVOKED)
template<std::size_t I, typename Head, typename... Tail>
struct  std::tuple_element<I, kumi::tuple<Head, Tail...>>
      : std::tuple_element<I - 1, kumi::tuple<Tail...>>
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
template<typename... Ts>
struct std::tuple_size<kumi::tuple<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>
{
};
#if !defined( __ANDROID__ )
template< typename... Ts, typename... Us
        , template<class> class TQual, template<class> class UQual >
requires(sizeof...(Ts) == sizeof...(Us))
struct std::basic_common_reference<kumi::tuple<Ts...>, kumi::tuple<Us...>, TQual, UQual>
{
  using type = kumi::tuple<std::common_reference_t<TQual<Ts>, UQual<Us>>...>;
};
#endif

#if !defined(KUMI_NO_STD_ADAPTORS)
template< typename T, std::size_t N >
struct kumi::is_product_type<std::array<T , N>> : std::true_type {};
#endif

#endif
#include <iosfwd>
#include <type_traits>
namespace kumi
{
  template<typename... Ts> struct tuple
  {
    using is_product_type = void;
    using binder_t  = _::make_binder_t<std::make_integer_sequence<int,sizeof...(Ts)>, Ts...>;
    static constexpr bool is_homogeneous = binder_t::is_homogeneous;
    binder_t impl;
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_TRIVIAL constexpr decltype(auto) operator[]([[maybe_unused]] index_t<I> i) &noexcept
    {
      return _::get_leaf<I>(impl);
    }
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_TRIVIAL constexpr decltype(auto) operator[](index_t<I>) &&noexcept
    {
      return _::get_leaf<I>(static_cast<decltype(impl) &&>(impl));
    }
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_TRIVIAL constexpr decltype(auto) operator[](index_t<I>) const &&noexcept
    {
      return _::get_leaf<I>(static_cast<decltype(impl) const &&>(impl));
    }
    template<std::size_t I>
    requires(I < sizeof...(Ts))
    KUMI_TRIVIAL constexpr decltype(auto) operator[](index_t<I>) const &noexcept
    {
      return _::get_leaf<I>(impl);
    }
    KUMI_TRIVIAL_NODISCARD static constexpr  auto size() noexcept { return sizeof...(Ts); }
    KUMI_TRIVIAL_NODISCARD static constexpr  bool empty() noexcept { return sizeof...(Ts) == 0; }
    template<typename... Us>
    requires(   _::piecewise_convertible<tuple, tuple<Us...>>
            &&  (sizeof...(Us) == sizeof...(Ts))
            &&  (!std::same_as<Ts, Us> && ...)
            )
    [[nodiscard]] inline constexpr auto cast() const
    {
      return apply([](auto &&...elems) { return tuple<Us...> {static_cast<Us>(elems)...}; }, *this);
    }
    template<typename... Us>
    requires(_::piecewise_convertible<tuple, tuple<Us...>>) constexpr tuple &
    operator=(tuple<Us...> const &other)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>) { ((get<I>(*this) = get<I>(other)), ...); }
      (std::make_index_sequence<sizeof...(Ts)>());
      return *this;
    }
    template<typename... Us>
    requires(_::piecewise_convertible<tuple, tuple<Us...>>) constexpr tuple &
    operator=(tuple<Us...> &&other)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((get<I>(*this) = get<I>(KUMI_FWD(other))), ...);
      }
      (std::make_index_sequence<sizeof...(Ts)>());
      return *this;
    }
    template<typename... Us>
    friend constexpr auto operator==(tuple const &self, tuple<Us...> const &other) noexcept
    requires( equality_comparable<tuple,tuple<Us...>> )
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return ((get<I>(self) == get<I>(other)) && ...);
      }
      (std::make_index_sequence<sizeof...(Ts)>());
    }
    template<typename... Us>
    KUMI_TRIVIAL friend constexpr auto operator!=(tuple const &self, tuple<Us...> const &other) noexcept
    requires( equality_comparable<tuple,tuple<Us...>> )
    {
      return !(self == other);
    }
    template<typename... Us>
    friend constexpr auto operator<(tuple const &lhs, tuple<Us...> const &rhs) noexcept
    requires(sizeof...(Ts) == sizeof...(Us) && _::piecewise_ordered<tuple, tuple<Us...>>)
    {
      auto res = get<0>(lhs) < get<0>(rhs);
      auto const order = [&]<typename Index>(Index i)
      {
        auto y_less_x_prev  = rhs[i]  < lhs[i];
        auto x_less_y       = lhs[index_t<Index::value+1>{}] < rhs[index_t<Index::value+1>{}];
        res                 = res || (x_less_y && !y_less_x_prev);
      };
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        (order(index_t<I>{}),...);
      }
      (std::make_index_sequence<sizeof...(Ts)-1>());
      return res;
    }
    template<typename... Us>
    KUMI_TRIVIAL friend constexpr auto operator<=(tuple const &lhs, tuple<Us...> const &rhs) noexcept
    requires requires { rhs < lhs; }
    {
      return !(rhs < lhs);
    }
    template<typename... Us>
    KUMI_TRIVIAL friend constexpr auto operator>(tuple const &lhs, tuple<Us...> const &rhs) noexcept
    requires requires { rhs < lhs; }
    {
      return rhs < lhs;
    }
    template<typename... Us>
    KUMI_TRIVIAL friend constexpr auto operator>=(tuple const &lhs, tuple<Us...> const &rhs) noexcept
    requires requires { lhs < rhs; }
    {
      return !(lhs < rhs);
    }
    template<typename Function>
    KUMI_TRIVIAL constexpr decltype(auto) operator()(Function &&f) const&
    noexcept(noexcept(kumi::apply(KUMI_FWD(f), *this))) { return kumi::apply(KUMI_FWD(f), *this); }
#if !defined(KUMI_DOXYGEN_INVOKED)
    template<typename Function>
    KUMI_TRIVIAL constexpr decltype(auto) operator()(Function &&f) &
    noexcept(noexcept(kumi::apply(KUMI_FWD(f), *this)))
    {
      return kumi::apply(KUMI_FWD(f), *this);
    }
    template<typename Function>
    KUMI_TRIVIAL constexpr decltype(auto) operator()(Function &&f) const &&noexcept(
    noexcept(kumi::apply(KUMI_FWD(f), static_cast<tuple const &&>(*this))))
    {
      return kumi::apply(KUMI_FWD(f), static_cast<tuple const &&>(*this));
    }
    template<typename Function>
    KUMI_TRIVIAL constexpr decltype(auto) operator()(Function &&f) &&noexcept(
    noexcept(kumi::apply(KUMI_FWD(f), static_cast<tuple &&>(*this))))
    {
      return kumi::apply(KUMI_FWD(f), static_cast<tuple &&>(*this));
    }
#endif
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &os,
                                                         tuple const &t) noexcept
    {
      os << "( ";
      kumi::for_each([&os](auto const &e) { os << e << " "; }, t);
      os << ")";
      return os;
    }
  };
  template<typename... Ts> tuple(Ts &&...) -> tuple<typename std::unwrap_ref_decay<Ts>::type...>;
  template<typename... Ts> KUMI_TRIVIAL_NODISCARD constexpr tuple<Ts &...> tie(Ts &...ts) { return {ts...}; }
  template<typename... Ts> KUMI_TRIVIAL_NODISCARD constexpr tuple<Ts &&...> forward_as_tuple(Ts &&...ts)
  {
    return {KUMI_FWD(ts)...};
  }
  template<typename... Ts>
  KUMI_TRIVIAL_NODISCARD constexpr tuple<typename std::unwrap_ref_decay<Ts>::type...> make_tuple(Ts &&...ts)
  {
    return {KUMI_FWD(ts)...};
  }
  template<product_type Type> KUMI_TRIVIAL_NODISCARD constexpr auto to_ref(Type&& t)
  {
    return apply( [](auto&&... elems)
                  {
                    return kumi::forward_as_tuple(KUMI_FWD(elems)...);
                  }
                , KUMI_FWD(t)
                );
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) KUMI_TRIVIAL_NODISCARD constexpr decltype(auto) get(tuple<Ts...> &t) noexcept
  {
    return t[index<I>];
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) KUMI_TRIVIAL_NODISCARD constexpr decltype(auto)
  get(tuple<Ts...> &&arg) noexcept
  {
    return static_cast<tuple<Ts...> &&>(arg)[index<I>];
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) KUMI_TRIVIAL_NODISCARD constexpr decltype(auto)
  get(tuple<Ts...> const &arg) noexcept
  {
    return arg[index<I>];
  }
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) KUMI_TRIVIAL_NODISCARD constexpr decltype(auto)
  get(tuple<Ts...> const &&arg) noexcept
  {
    return static_cast<tuple<Ts...> const &&>(arg)[index<I>];
  }
}
namespace kumi
{
  template< template<typename...> typename Traits
          , product_type Tuple
          , typename Seq = std::make_index_sequence<size<Tuple>::value>
          >
  struct apply_traits;
  template< template<typename...> typename Traits
          , product_type Tuple
          , std::size_t... Is
          >
  requires( requires {typename Traits<element_t<Is,Tuple>...>::type;})
  struct  apply_traits<Traits, Tuple, std::index_sequence<Is...>>
  {
    using type = typename Traits<element_t<Is,Tuple>...>::type;
  };
  template< template<typename...> typename Traits
          , product_type Tuple
          >
  using apply_traits_t = typename apply_traits<Traits, Tuple>::type;
}
namespace kumi
{
}
namespace kumi
{
  template<product_type Tuple>
  KUMI_TRIVIAL_NODISCARD constexpr decltype(auto) front(Tuple&& t) requires( size_v<Tuple> != 0)
  {
    return get<0>(KUMI_FWD(t));
  }
  template<product_type Tuple>
  KUMI_TRIVIAL_NODISCARD constexpr decltype(auto) back(Tuple&& t) requires( size_v<Tuple> != 0)
  {
    return get<size_v<Tuple>-1>(KUMI_FWD(t));
  }
  namespace result
  {
    template<product_type Tuple> struct front : member<0,Tuple> {};
    template<product_type Tuple> struct back  : member<size_v<Tuple>-1,Tuple> {};
    template<product_type Tuple> using front_t = typename front<Tuple>::type;
    template<product_type Tuple> using back_t  = typename back<Tuple>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t N, std::size_t... S> constexpr auto digits(std::size_t v) noexcept
    {
      struct { std::size_t data[N]; } digits = {};
      std::size_t shp[] = {S...};
      std::size_t i = 0;
      while(v != 0)
      {
        digits.data[i] = v % shp[i];
        v /= shp[i++];
      }
      return digits;
    }
  }
#if !defined(KUMI_DOXYGEN_INVOKED)
  KUMI_TRIVIAL_NODISCARD constexpr auto cartesian_product() { return kumi::tuple<>{}; }
#endif
  template<product_type... Ts>
  [[nodiscard]] constexpr auto cartesian_product(Ts&&... ts)
  {
    auto maps = [&]<std::size_t... I>(auto k, std::index_sequence<I...>)
    {
      constexpr auto dg = _::digits<sizeof...(Ts),kumi::size_v<Ts>...>(k);
      using tuple_t = kumi::tuple<std::tuple_element_t<dg.data[I],std::remove_cvref_t<Ts>>...>;
      return tuple_t{kumi::get<dg.data[I]>(std::forward<Ts>(ts))...};
    };
    return [&]<std::size_t... N>(std::index_sequence<N...>)
    {
      return kumi::make_tuple(maps( kumi::index<N>, std::make_index_sequence<sizeof...(ts)>{})...);
    }(std::make_index_sequence<(kumi::size_v<Ts> * ...)>{});
  }
  namespace result
  {
    template<typename... T> struct cartesian_product
    {
      using type = decltype( kumi::cartesian_product( std::declval<T>()... ) );
    };
    template<typename... T> using cartesian_product_t = typename cartesian_product<T...>::type;
  }
}
namespace kumi
{
  template<product_type... Tuples>
  KUMI_TRIVIAL_NODISCARD constexpr auto cat(Tuples&&... ts)
  {
    if constexpr(sizeof...(Tuples) == 0) return tuple{};
    else
    {
      constexpr auto count = (1ULL + ... + kumi::size<Tuples>::value);
      constexpr auto pos = [&]()
      {
        struct { std::size_t t[count],e[count]; } that{};
        std::size_t k = 0, offset = 0;
        auto locate = [&]<std::size_t... I>(std::index_sequence<I...>)
        {
          (((that.t[I+offset] = k),(that.e[I+offset] = I)),...);
          offset += sizeof...(I);
          k++;
        };
        (locate(std::make_index_sequence<kumi::size<Tuples>::value>{}),...);
        return that;
      }();
      return [&]<std::size_t... N>(auto&& tuples, std::index_sequence<N...>)
      {
        using ts  = std::remove_cvref_t<decltype(tuples)>;
        using type =  kumi::tuple
                      < std::tuple_element_t< pos.e[N]
                                            , std::remove_cvref_t<std::tuple_element_t<pos.t[N],ts>>
                                            >...
                      >;
        return type{get<pos.e[N]>(get<pos.t[N]>(KUMI_FWD(tuples)))...};
      }(kumi::forward_as_tuple(KUMI_FWD(ts)...), std::make_index_sequence<count-1>{});
    }
  }
  namespace result
  {
    template<product_type... Tuples> struct cat
    {
      using type = decltype( kumi::cat( std::declval<Tuples>()... ) );
    };
    template<product_type... Tuples> using cat_t  = typename cat<Tuples...>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template< product_type Tuple
            , typename IndexSequence
            , template<typename...> class Meta = std::type_identity
            >
    struct as_tuple;
    template< product_type Tuple
            , std::size_t... I
            >
    struct as_tuple<Tuple, std::index_sequence<I...>>
    {
      using type = kumi::tuple< element_t<I,Tuple>... >;
    };
    template< product_type Tuple
            , std::size_t... I
            , template<typename...> class Meta
            >
    struct as_tuple<Tuple, std::index_sequence<I...>, Meta>
    {
      using type = kumi::tuple< typename Meta<element_t<I,Tuple>>::type... >;
    };
  }
  template<typename T>
  requires( !requires { T::is_homogeneous; } )
  struct is_homogeneous<T> : is_homogeneous<typename _::as_tuple<T,std::make_index_sequence<size_v<T>>>::type>
  {};
  template<typename Type, typename... Ts>
  requires(!product_type<Type> && _::implicit_constructible<Type, Ts...>)
  [[nodiscard]] constexpr auto from_tuple(tuple<Ts...> const &t)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) { return Type {get<I>(t)...}; }
    (std::make_index_sequence<sizeof...(Ts)>());
  }
  template<product_type Type>
  [[nodiscard]] inline constexpr auto to_tuple(Type&& t)
  {
    return apply([](auto &&...elems) { return tuple{elems...}; }, KUMI_FWD(t));
  }
  template<typename T, template<typename...> class Meta = std::type_identity>
  struct as_tuple;
  template<typename T, template<typename...> class Meta>
  requires( product_type<T> )
  struct as_tuple<T, Meta> : _::as_tuple <T,std::make_index_sequence<size_v<T>>, Meta>
  {};
  template<typename T, template<typename...> class Meta>
  requires( !product_type<T> )
  struct as_tuple<T, Meta>
  {
    using type = kumi::tuple< typename Meta<T>::type >;
  };
  template<typename T, template<typename...> class Meta = std::type_identity>
  using as_tuple_t =  typename as_tuple<T, Meta>::type;
}
namespace kumi
{
  template<std::size_t I0, std::size_t I1, product_type Tuple>
  requires( (I0 <= size_v<Tuple>) && (I1 <= size_v<Tuple>) )
  [[nodiscard]] constexpr
  auto extract( Tuple const& t
              , [[maybe_unused]] index_t<I0> i0
              , [[maybe_unused]] index_t<I1> i1
              ) noexcept
  {
    return [&]<std::size_t... N>(std::index_sequence<N...>)
    {
      return kumi::tuple<std::tuple_element_t<N + I0, Tuple>...> {get<N + I0>(t)...};
    }
    (std::make_index_sequence<I1 - I0>());
  }
  template<std::size_t I0, product_type Tuple>
  requires(I0<= size_v<Tuple>)
  KUMI_TRIVIAL_NODISCARD constexpr  auto extract(Tuple const& t, index_t<I0> i0) noexcept
  {
    return extract(t,i0, index<size_v<Tuple>>);
  }
  template<std::size_t I0, product_type Tuple>
  requires(I0 <= size_v<Tuple>)
  [[nodiscard]] constexpr auto split( Tuple const& t
                                    , [[maybe_unused]] index_t<I0> i0
                                    ) noexcept
  {
    return kumi::make_tuple(extract(t,index<0>, index<I0>), extract(t,index<I0>));
  }
  namespace result
  {
    template<product_type T, std::size_t I0, std::size_t I1 = std::size_t(-1)>
    struct extract
    {
      using type = decltype ( kumi::extract ( std::declval<T>()
                                            , kumi::index_t<I0>{},kumi::index_t<I1>{}
                                            )
                            );
    };
    template<product_type T, std::size_t I0>
    struct extract<T,I0>
    {
      using type = decltype(kumi::extract(std::declval<T>(),kumi::index_t<I0>{}) );
    };
    template<product_type T, std::size_t I0>
    struct split
    {
      using type = decltype(kumi::split(std::declval<T>(),kumi::index_t<I0>{}) );
    };
    template<product_type T, std::size_t I0, std::size_t I1 = std::size_t(-1)>
    using extract_t = typename extract<T,I0,I1>::type;
    template<product_type T, std::size_t I0>
    using split_t = typename split<T,I0>::type;
  }
}
namespace kumi
{
  template<typename Pred, typename... Ts>
  [[nodiscard]] constexpr auto locate( tuple<Ts...> const& t, Pred p ) noexcept
  {
    auto locator = [&](auto const&... m)
    {
      bool checks[] = { p(m)...  };
      for(std::size_t i=0;i<sizeof...(Ts);++i)
        if(checks[i]) return i;
      return sizeof...(Ts);
    };
    return kumi::apply(locator, t);
  }
}
namespace kumi
{
  template<product_type Tuple> [[nodiscard]] constexpr auto flatten(Tuple const &ts)
  {
    if constexpr(sized_product_type<Tuple,0>) return ts;
    else
    {
      return kumi::apply( [](auto&&... m)
                          {
                            auto v_or_t = []<typename V>(V&& v)
                            {
                              if constexpr(product_type<V>) return KUMI_FWD(v);
                              else                          return kumi::tuple{KUMI_FWD(v)};
                            };
                            return cat( v_or_t(KUMI_FWD(m))... );
                          }
                        , ts
                        );
    }
  }
  template<product_type Tuple, typename Func>
  [[nodiscard]] constexpr auto flatten_all(Tuple&& ts, Func&& f)
  {
    if constexpr(sized_product_type<Tuple,0>) return KUMI_FWD(ts);
    else
    {
      return kumi::apply( [&](auto&&... m)
                          {
                            auto v_or_t = [&]<typename V>(V&& v)
                            {
                              if constexpr(product_type<V>)
                                return flatten_all(KUMI_FWD(v),KUMI_FWD(f));
                              else
                                return kumi::tuple{KUMI_FWD(f)(KUMI_FWD(v))};
                            };
                            return cat( v_or_t(KUMI_FWD(m))... );
                          }
                        , ts
                        );
    }
  }
  template<product_type Tuple> [[nodiscard]] constexpr auto flatten_all(Tuple&& ts)
  {
    if constexpr(sized_product_type<Tuple,0>) return ts;
    else
    {
      return kumi::apply( [](auto&&... m)
                          {
                            auto v_or_t = []<typename V>(V&& v)
                            {
                              if constexpr(product_type<V>) return flatten_all(KUMI_FWD(v));
                              else                          return kumi::tuple{KUMI_FWD(v)};
                            };
                            return cat( v_or_t(KUMI_FWD(m))... );
                          }
                        , ts
                        );
    }
  }
  namespace result
  {
    template<product_type Tuple> struct flatten
    {
      using type = decltype( kumi::flatten( std::declval<Tuple>() ) );
    };
    template<product_type Tuple, typename Func = void> struct flatten_all
    {
      using type = decltype( kumi::flatten_all( std::declval<Tuple>(), std::declval<Func>() ) );
    };
    template<product_type Tuple> struct flatten_all<Tuple>
    {
      using type = decltype( kumi::flatten_all( std::declval<Tuple>() ) );
    };
    template<product_type Tuple> using flatten_t      = typename flatten<Tuple>::type;
    template<product_type Tuple, typename Func = void>
    using flatten_all_t  = typename flatten_all<Tuple, Func>::type;
  }
  template<product_type Tuple>
  KUMI_TRIVIAL_NODISCARD auto as_flat_ptr(Tuple&& ts) noexcept
  {
    return kumi::flatten_all(KUMI_FWD(ts), [](auto& m) { return &m; });
  }
  namespace result
  {
    template<product_type T> struct as_flat_ptr
    {
      using type = decltype( kumi::as_flat_ptr( std::declval<T>() ) );
    };
    template<product_type T>
    using as_flat_ptr_t = typename as_flat_ptr<T>::type;
  }
}
namespace kumi
{
  namespace _
  {
    template<std::size_t N, typename T>
    constexpr auto const& eval(T const& v) noexcept { return v; }
  }
  template<std::size_t N, typename T> [[nodiscard]] constexpr auto generate(T const& v) noexcept
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return kumi::tuple{_::eval<I>(v)...};
    }(std::make_index_sequence<N>{});
  }
  template<std::size_t N, typename T> [[nodiscard]] constexpr auto iota(T v) noexcept
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return kumi::tuple{static_cast<T>(v+I)...};
    }(std::make_index_sequence<N>{});
  }
  namespace result
  {
    template<std::size_t N, typename T> struct generate
    {
      using type = decltype( kumi::generate<N>( std::declval<T>() ) );
    };
    template<std::size_t N, typename T> struct iota
    {
      using type = decltype( kumi::iota<N>( std::declval<T>() ) );
    };
    template<std::size_t N, typename T>
    using generate_t = typename generate<N,T>::type;
    template<std::size_t N, typename T>
    using iota_t = typename iota<N,T>::type;
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
      template<typename W>
      friend constexpr decltype(auto) operator>>(foldable &&x, foldable<F, W> &&y)
      {
        return _::foldable {x.func, x.func(y.value, x.value)};
      }
      template<typename W>
      friend constexpr decltype(auto) operator<<(foldable &&x, foldable<F, W> &&y)
      {
        return _::foldable {x.func, x.func(x.value, y.value)};
      }
    };
    template<class F, class T> foldable(const F &, T &&) -> foldable<F, T>;
  }
  template< product_type S1, sized_product_type<S1::size()> S2, typename T
          , typename Sum, typename Prod
          >
  [[nodiscard]] constexpr auto inner_product( S1 const& s1, S2 const& s2, T init
                                            , Sum sum, Prod prod
                                            ) noexcept
  {
    if constexpr(sized_product_type<S1,0>) return init;
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return  (  _::foldable {sum, prod(get<I>(KUMI_FWD(s1)),get<I>(KUMI_FWD(s2)))}
                >> ...
                >> _::foldable {sum, init}
                ).value;
      }
      (std::make_index_sequence<size<S1>::value>());
    }
  }
  template<product_type S1, sized_product_type<S1::size()> S2, typename T>
  [[nodiscard]] constexpr auto inner_product(S1 const& s1, S2 const& s2, T init) noexcept
  {
    if constexpr(sized_product_type<S1,0>) return init;
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return (init + ... + (get<I>(s1) * get<I>(s2)));
      }(std::make_index_sequence<size<S1>::value>());
    }
  }
  namespace result
  {
    template< product_type S1, sized_product_type<S1::size()> S2, typename T
            , typename Sum, typename Prod
            >
    struct inner_product
    {
      using type = decltype ( kumi::inner_product ( std::declval<S1>(), std::declval<S2>()
                                                  , std::declval<T>()
                                                  , std::declval<Sum>(), std::declval<Prod>()
                                                  )
                            );
    };
    template< product_type S1, sized_product_type<S1::size()> S2, typename T>
    struct inner_product<S1,S2,T,void,void>
    {
      using type = decltype ( kumi::inner_product ( std::declval<S1>(), std::declval<S2>()
                                                  , std::declval<T>()
                                                  )
                            );
    };
    template< product_type S1, sized_product_type<S1::size()> S2, typename T
            , typename Sum = void, typename Prod = void
            >
    using inner_product_t  = typename inner_product<S1,S2,T,Sum,Prod>::type;
  }
}
namespace kumi
{
  template<product_type Tuple, typename Function, sized_product_type<size<Tuple>::value>... Tuples>
  constexpr auto
  map(Function     f,
      Tuple  &&t0,
      Tuples &&...others) requires _::supports_call<Function, Tuple&&, Tuples&&...>
  {
    if constexpr(sized_product_type<Tuple,0>) return std::remove_cvref_t<Tuple>{};
    else
    {
      auto const call = [&]<std::size_t N, typename... Ts>(index_t<N>, Ts &&... args)
      {
        return f(get<N>(args)...);
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return kumi::make_tuple(call(index<I>, KUMI_FWD(t0), KUMI_FWD(others)...)...);
      }(std::make_index_sequence<size<Tuple>::value>());
    }
  }
  namespace result
  {
    template<typename Function, product_type T, sized_product_type<size<T>::value>... Ts>
    struct map
    {
      using type = decltype ( kumi::map ( std::declval<Function>()
                                        , std::declval<T>()
                                        , std::declval<Ts>()...
                                        )
                            );
    };
    template<typename Function, product_type T, sized_product_type<size<T>::value>... Ts>
    using map_t = typename map<Function,T,Ts...>::type;
  }
  template<product_type Tuple, typename Function, sized_product_type<size<Tuple>::value>... Tuples>
  constexpr auto map_index(Function     f,Tuple  &&t0,Tuples &&...others)
  {
    if constexpr(sized_product_type<Tuple,0>) return std::remove_cvref_t<Tuple>{};
    else
    {
      auto const call = [&]<std::size_t N, typename... Ts>(index_t<N> idx, Ts &&... args)
      {
        return f(idx, get<N>(args)...);
      };
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return kumi::make_tuple(call(index<I>, KUMI_FWD(t0), KUMI_FWD(others)...)...);
      }(std::make_index_sequence<size<Tuple>::value>());
    }
  }
  namespace result
  {
    template<typename Function, product_type T, sized_product_type<size<T>::value>... Ts>
    struct map_index
    {
      using type = decltype ( kumi::map_index ( std::declval<Function>()
                                                , std::declval<T>()
                                                , std::declval<Ts>()...
                                                )
                            );
    };
    template<typename Function, product_type T, sized_product_type<size<T>::value>... Ts>
    using map_index_t = typename map_index<Function,T,Ts...>::type;
  }
}
namespace kumi
{
  template<product_type Tuple, typename T>
  [[nodiscard]] constexpr auto push_front(Tuple const& t, T&& v)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return kumi::make_tuple(KUMI_FWD(v), get<I>(KUMI_FWD(t))...);
    }
    (std::make_index_sequence<Tuple::size()>());
  }
  template<product_type Tuple>
  [[nodiscard]] constexpr auto pop_front(Tuple const& t)
  {
    if constexpr(Tuple::size()>0) return extract(t, index<1>);
    else                          return tuple<>{};
  }
  template<product_type Tuple, typename T>
  [[nodiscard]] constexpr auto push_back(Tuple const& t, T&& v)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return kumi::make_tuple(get<I>(KUMI_FWD(t))..., KUMI_FWD(v));
    }
    (std::make_index_sequence<Tuple::size()>());
  }
  template<product_type Tuple>
  [[nodiscard]] constexpr auto pop_back(Tuple const& t)
  {
    if constexpr(Tuple::size()>1) return extract(t,index<0>, index<Tuple::size()-1>);
    else                          return tuple<>{};
  }
  namespace result
  {
    template<product_type Tuple, typename T> struct push_front
    {
      using type = decltype( kumi::push_front( std::declval<Tuple>(), std::declval<T>() ) );
    };
    template<product_type Tuple> struct pop_front
    {
      using type = decltype( kumi::pop_front( std::declval<Tuple>() ) );
    };
    template<product_type Tuple, typename T> struct push_back
    {
      using type = decltype( kumi::push_back( std::declval<Tuple>(), std::declval<T>() ) );
    };
    template<product_type Tuple> struct pop_back
    {
      using type = decltype( kumi::pop_back( std::declval<Tuple>() ) );
    };
    template<product_type Tuple, typename T>
    using push_front_t  = typename push_front<Tuple, T>::type;
    template<product_type Tuple>
    using pop_front_t  = typename pop_front<Tuple>::type;
    template<product_type Tuple, typename T>
    using push_back_t  = typename push_back<Tuple, T>::type;
    template<product_type Tuple>
    using pop_back_t  = typename pop_back<Tuple>::type;
  }
}
namespace kumi
{
  template<typename Function, product_type Tuple, typename Value>
  [[nodiscard]] constexpr auto fold_left(Function f, Tuple&& t, Value init)
  {
    if constexpr(sized_product_type<Tuple,0>) return init;
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return (_::foldable {f, get<I>(KUMI_FWD(t))} >> ... >> _::foldable {f, init}).value;
      }
      (std::make_index_sequence<size<Tuple>::value>());
    }
  }
  template<typename Function, sized_product_type_or_more<1> Tuple>
  [[nodiscard]] constexpr auto fold_left(Function f, Tuple&& t)
  {
    if constexpr(sized_product_type<Tuple,1>) return get<0>(t);
    else
    {
      auto&&[heads, tail] = split(KUMI_FWD(t), index<2>);
      return fold_left(f, tail, kumi::apply(f,heads));
    }
  }
  template<typename Function, product_type Tuple, typename Value>
  [[nodiscard]] constexpr auto fold_right(Function f, Tuple&& t, Value init)
  {
    if constexpr(size<Tuple>::value ==0) return init;
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return (_::foldable {f, init} << ... << _::foldable {f, get<I>(KUMI_FWD(t))}).value;
      }
      (std::make_index_sequence<size<Tuple>::value>());
    }
  }
  template<typename Function, sized_product_type_or_more<1> Tuple>
  [[nodiscard]] constexpr auto fold_right(Function f, Tuple&& t)
  {
    if constexpr(sized_product_type<Tuple,1>) return get<0>(t);
    else
    {
      auto&&[head, tails] = split(KUMI_FWD(t), index<size_v<Tuple>-2>);
      return fold_left(f, head, kumi::apply(f,tails));
    }
  }
  namespace result
  {
    template<typename Function, product_type Tuple, typename Value = void>
    struct fold_right
    {
      using type = decltype ( kumi::fold_right( std::declval<Function>()
                                              , std::declval<Tuple>()
                                              , std::declval<Value>()
                                              )
                            );
    };
    template<typename Function, product_type Tuple>
    struct fold_right<Function,Tuple>
    {
      using type = decltype ( kumi::fold_right( std::declval<Function>()
                                              , std::declval<Tuple>()
                                              )
                            );
    };
    template<typename Function, product_type Tuple, typename Value = void>
    struct fold_left
    {
      using type = decltype ( kumi::fold_left ( std::declval<Function>()
                                              , std::declval<Tuple>()
                                              , std::declval<Value>()
                                              )
                            );
    };
    template<typename Function, product_type Tuple>
    struct fold_left<Function,Tuple>
    {
      using type = decltype ( kumi::fold_left ( std::declval<Function>()
                                              , std::declval<Tuple>()
                                              )
                            );
    };
    template<typename Function, product_type Tuple, typename Value = void>
    using fold_right_t = typename fold_right<Function,Tuple,Value>::type;
    template<typename Function, product_type Tuple, typename Value = void>
    using fold_left_t = typename fold_left<Function,Tuple,Value>::type;
  }
}
namespace kumi
{
  template<typename T>
  [[nodiscard]] constexpr auto max(T const& t) noexcept
  {
    if constexpr ( !kumi::product_type<T> ) return t;
    else if constexpr( T::size() == 1 )     return get<0>(t);
    else
    {
      auto base = get<0>(t);
      return kumi::fold_left( []<typename U>(auto cur, U u)
                              {
                                return cur > u ? cur : u;
                              }
                            , t, base
                            );
    }
  }
  template<typename T, typename F>
  [[nodiscard]] constexpr auto max(T const& t, F f) noexcept
  {
    if constexpr ( !kumi::product_type<T> ) return f(t);
    else if constexpr( T::size() == 1 )     return f( get<0>(t) );
    else
    {
      auto base = f( get<0>(t) );
      return kumi::fold_left( [f]<typename U>(auto cur, U const& u)
                              {
                                return cur > f(u) ? cur : f(u);
                              }
                            , t, base
                            );
    }
  }
  template<typename T, typename F>
  [[nodiscard]] constexpr auto max_flat(T const& t, F f) noexcept
  {
    if constexpr ( !kumi::product_type<T> ) return f(t);
    else
    {
      auto flat_t = kumi::flatten_all(t);
      return max(flat_t, f);
    }
  }
  namespace result
  {
    template<typename T, typename F = void> struct max
    {
      using type = decltype( kumi::max( std::declval<T>(), std::declval<F>() ) );
    };
    template<typename T> struct max<T,void>
    {
      using type = decltype( kumi::max( std::declval<T>() ) );
    };
    template<typename T, typename F> struct max_flat
    {
      using type = decltype( kumi::max_flat( std::declval<T>(), std::declval<F>() ) );
    };
    template<typename T, typename F = void> using max_t      = typename max<T,F>::type;
    template<typename T, typename F>        using max_flat_t = typename max_flat<T,F>::type;
  }
  template<typename T>
  [[nodiscard]] constexpr auto min(T const& t) noexcept
  {
    if constexpr ( !kumi::product_type<T> ) return t;
    else if constexpr( T::size() == 1 )     return get<0>(t);
    else
    {
      auto base = get<0>(t);
      return kumi::fold_left( []<typename U>(auto cur, U u)
                              {
                                return cur < u ? cur : u;
                              }
                            , t, base
                            );
    }
  }
  template<typename T, typename F>
  [[nodiscard]] constexpr auto min(T const& t, F f) noexcept
  {
    if constexpr ( !kumi::product_type<T> ) return f(t);
    else if constexpr( T::size() == 1 )     return f( get<0>(t) );
    else
    {
      auto base = f( get<0>(t) );
      return kumi::fold_left( [f]<typename U>(auto cur, U const& u)
                              {
                                return cur < f(u) ? cur : f(u);
                              }
                            , t, base
                            );
    }
  }
  template<typename T, typename F>
  [[nodiscard]] constexpr auto min_flat(T const& t, F f) noexcept
  {
    if constexpr ( !kumi::product_type<T> ) return f(t);
    else
    {
      auto flat_t = kumi::flatten_all(t);
      return min(flat_t, f);
    }
  }
  namespace result
  {
    template<typename T, typename F = void> struct min
    {
      using type = decltype( kumi::min( std::declval<T>(), std::declval<F>() ) );
    };
    template<typename T> struct min<T,void>
    {
      using type = decltype( kumi::min( std::declval<T>() ) );
    };
    template<typename T, typename F> struct min_flat
    {
      using type = decltype( kumi::min_flat( std::declval<T>(), std::declval<F>() ) );
    };
    template<typename T, typename F = void> using min_t      = typename min<T,F>::type;
    template<typename T, typename F>        using min_flat_t = typename min_flat<T,F>::type;
  }
}
namespace kumi
{
  template<template<typename> typename Pred, kumi::product_type T>
  constexpr auto partition(T&& tup) noexcept
  {
    constexpr auto pos = [&]()
    {
      struct { std::size_t count = {}, cut = {}, t[1+kumi::size<T>::value]; } that{};
      auto locate = [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        (( Pred<kumi::element_t<I,T>>::value ? (that.t[that.count++] = I) : I),...);
        that.cut = that.count;
        ((!Pred<kumi::element_t<I,T>>::value ? (that.t[that.count++] = I) : I),...);
      };
      locate(std::make_index_sequence<kumi::size<T>::value>{});
      return that;
    }();
    auto select = [&]<typename O, std::size_t... I>(O, std::index_sequence<I...>)
    {
      using type = kumi::tuple<std::tuple_element_t< pos.t[O::value+I], std::remove_cvref_t<decltype(tup)>>...>;
      return type{get<pos.t[O::value+I]>(KUMI_FWD(tup))...};
    };
    return kumi::tuple{ select(kumi::index<0>      , std::make_index_sequence<pos.cut>{})
                      , select(kumi::index<pos.cut>, std::make_index_sequence<kumi::size<T>::value - pos.cut>{})
                      };
  }
  namespace result
  {
    template<template<typename> typename Pred, kumi::product_type T> struct partition
    {
      using type = decltype( kumi::partition<Pred>( std::declval<T>() ) );
    };
    template<template<typename> typename Pred, kumi::product_type T>
    using partition_t = typename partition<Pred, T>::type;
  }
}
namespace kumi
{
  template<typename Pred, typename T>
  [[nodiscard]] constexpr auto all_of(T const& ts, Pred p) noexcept
  {
    if constexpr( !product_type<T> ) return p(ts);
    else
    {
      if      constexpr(size_v<T> == 0) return true;
      else if constexpr(size_v<T> == 1) return p(get<0>(ts));
      else return kumi::apply( [&](auto const&... m) { return (p(m) && ... && p(get<0>(ts))); }, extract(ts,index<1>));
    }
  }
  template<typename T>
  [[nodiscard]] constexpr auto all_of(T const& ts) noexcept
  {
    if constexpr( !product_type<T> ) return !!ts;
    else
    {
      if      constexpr(size_v<T> == 0) return true;
      else if constexpr(size_v<T> == 1) return !!get<0>(ts);
      else return kumi::apply( [&](auto const&... m) { return (m && ... && get<0>(ts)); }, extract(ts,index<1>) );
    }
  }
  template<typename Pred, typename T>
  [[nodiscard]] constexpr auto any_of(T const& ts, Pred p) noexcept
  {
    if constexpr( !product_type<T> ) return p(ts);
    else
    {
      if      constexpr(size_v<T> == 0) return true;
      else if constexpr(size_v<T> == 1) return p(get<0>(ts));
      else return kumi::apply( [&](auto const&... m) { return (p(m) || ... || p(get<0>(ts))); }, extract(ts,index<1>));
    }
  }
  template<typename T>
  [[nodiscard]] constexpr auto any_of(T const& ts) noexcept
  {
    if constexpr( !product_type<T> ) return !!ts;
    else
    {
      if      constexpr(size_v<T> == 0) return false;
      else if constexpr(size_v<T> == 1) return !!get<0>(ts);
      else return kumi::apply( [&](auto const&... m) { return (m || ... || get<0>(ts)); }, extract(ts,index<1>) );
    }
  }
  template<typename Pred, typename Tuple>
  KUMI_TRIVIAL_NODISCARD constexpr bool none_of( Tuple const& ts, Pred p) noexcept
  {
    return !any_of(ts,p);
  }
  template<typename Tuple>
  KUMI_TRIVIAL_NODISCARD constexpr bool none_of(Tuple const& ts) noexcept
  {
    return !any_of(ts);
  }
  template<typename Pred, typename T>
  [[nodiscard]] constexpr std::size_t count_if( T const& ts, Pred p) noexcept
  {
    constexpr std::size_t o = 1ULL;
    constexpr std::size_t z = 0ULL;
    if constexpr( !product_type<T> ) return p(ts) ? o : z;
    else
    {
      if constexpr(size_v<T> == 0) return z;
      else return  kumi::apply( [&](auto const&... m) { return ( (p(m)? o : z) + ... + z); }, ts );
    }
  }
  template<typename T>
  KUMI_TRIVIAL_NODISCARD constexpr std::size_t count( T const& ts ) noexcept
  {
    return count_if(ts, [](auto const& m) { return static_cast<bool>(m); } );
  }
}
namespace kumi
{
  template<std::size_t... Idx, product_type Tuple>
  requires((Idx < size_v<Tuple>) && ...)
  KUMI_TRIVIAL_NODISCARD constexpr auto reorder(Tuple &&t)
  {
    return kumi::make_tuple( get<Idx>(KUMI_FWD(t))...);
  }
  namespace result
  {
    template<product_type Tuple, std::size_t... Idx>
    struct reorder
    {
      using type = decltype( kumi::reorder<Idx...>( std::declval<Tuple>() ) );
    };
    template<product_type Tuple, std::size_t... Idx>
    using reorder_t = typename reorder<Tuple,Idx...>::type;
  }
}
namespace kumi
{
  template<product_type Tuple, typename Value>
  [[nodiscard]] constexpr auto sum(Tuple&& t, Value init)
  {
    if constexpr(_::empty_tuple<Tuple>) return init;
    else return kumi::apply( [init](auto const&... m) { return (m + ... + init); }, KUMI_FWD(t) );
  }
  template<product_type Tuple>
  [[nodiscard]] constexpr auto sum(Tuple&& t)
  {
    return sum(kumi::extract(t,index<1>),get<0>(t));
  }
  template<product_type Tuple, typename Value>
  [[nodiscard]] constexpr auto prod(Tuple&& t, Value init)
  {
    if constexpr(_::empty_tuple<Tuple>) return init;
    else return kumi::apply( [init](auto const&... m) { return (m * ... * init); }, KUMI_FWD(t) );
  }
  template<product_type Tuple>
  [[nodiscard]] constexpr auto prod(Tuple&& t)
  {
    return prod(kumi::extract(t,index<1>),get<0>(t));
  }
  template<product_type Tuple, typename Value>
  [[nodiscard]] constexpr auto bit_and(Tuple&& t, Value init)
  {
    if constexpr(_::empty_tuple<Tuple>) return init;
    else return kumi::apply( [init](auto const&... m) { return (m & ... & init); }, KUMI_FWD(t) );
  }
  template<product_type Tuple>
  [[nodiscard]] constexpr auto bit_and(Tuple&& t)
  {
    return bit_and(kumi::extract(t,index<1>),get<0>(t));
  }
  template<product_type Tuple, typename Value>
  [[nodiscard]] constexpr auto bit_or(Tuple&& t, Value init)
  {
    if constexpr(_::empty_tuple<Tuple>) return init;
    else return kumi::apply( [init](auto const&... m) { return (m | ... | init); }, KUMI_FWD(t) );
  }
  template<product_type Tuple>
  [[nodiscard]] constexpr auto bit_or(Tuple&& t)
  {
    return bit_or(kumi::extract(t,index<1>),get<0>(t));
  }
  namespace result
  {
    template<product_type Tuple, typename Value = void>
    struct sum
    {
      using type = decltype(kumi::sum(std::declval<Tuple>(), std::declval<Value>()));
    };
    template<product_type Tuple> struct sum<Tuple>
    {
      using type = decltype(kumi::sum(std::declval<Tuple>()));
    };
    template<product_type Tuple, typename Value = void>
    struct prod
    {
      using type = decltype(kumi::prod(std::declval<Tuple>(), std::declval<Value>()));
    };
    template<product_type Tuple>
    struct prod<Tuple>
    {
      using type = decltype(kumi::prod(std::declval<Tuple>()));
    };
    template<product_type Tuple, typename Value = void>
    struct bit_and
    {
      using type = decltype(kumi::bit_and(std::declval<Tuple>(), std::declval<Value>()));
    };
    template<product_type Tuple>
    struct bit_and<Tuple>
    {
      using type = decltype(kumi::bit_and(std::declval<Tuple>()));
    };
    template<product_type Tuple, typename Value = void>
    struct bit_or
    {
      using type = decltype(kumi::bit_or(std::declval<Tuple>(), std::declval<Value>()));
    };
    template<product_type Tuple>
    struct bit_or<Tuple>
    {
      using type = decltype(kumi::bit_or(std::declval<Tuple>()));
    };
    template<product_type Tuple, typename Value = void>
    using sum_t = typename sum<Tuple,Value>::type;
    template<product_type Tuple, typename Value = void>
    using prod_t = typename prod<Tuple,Value>::type;
    template<product_type Tuple, typename Value = void>
    using bit_and_t = typename bit_and<Tuple,Value>::type;
    template<product_type Tuple, typename Value = void>
    using bit_or_t = typename bit_or<Tuple,Value>::type;
  }
}
namespace kumi
{
  template<product_type Tuple>
  [[nodiscard]] constexpr auto reverse(Tuple &&t)
  {
    if constexpr(sized_product_type<Tuple,0>) return kumi::tuple<>{};
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return kumi::make_tuple(get<(size_v<Tuple> - 1 - I)>(KUMI_FWD(t))...);
      }
      (std::make_index_sequence<size<Tuple>::value>());
    }
  }
  namespace result
  {
    template<product_type Tuple>
    struct reverse
    {
      using type = decltype( kumi::reverse( std::declval<Tuple>() ) );
    };
    template<product_type Tuple>
    using reverse_t = typename reverse<Tuple>::type;
  }
}
namespace kumi
{
  template<product_type Tuple> [[nodiscard]] constexpr auto transpose(Tuple const &t)
  {
    if constexpr(sized_product_type<Tuple,0>) return t;
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        constexpr auto uz = []<typename N>(N const &, auto const &u) {
          return apply([](auto const &...m) { return kumi::make_tuple(get<N::value>(m)...); }, u);
        };
        return kumi::make_tuple(uz(index_t<I> {}, t)...);
      }
      (std::make_index_sequence<size<element_t<0,Tuple>>::value>());
    }
  }
  namespace result
  {
    template<product_type Tuple> struct transpose
    {
      using type = decltype( kumi::transpose( std::declval<Tuple>() ) );
    };
    template<product_type Tuple>
    using transpose_t = typename transpose<Tuple>::type;
  }
}
namespace kumi
{
  template<product_type T0, sized_product_type<size_v<T0>>... Ts>
  [[nodiscard]] constexpr auto zip(T0 const &t0, Ts const &...ts)
  {
    return kumi::map( [](auto const &m0, auto const &...ms) { return kumi::make_tuple(m0, ms...); }
                    , t0,ts...
                    );
  }
  namespace result
  {
    template<product_type T0, product_type... Ts>
    struct zip
    {
      using type = decltype( kumi::zip( std::declval<T0>(), std::declval<Ts>()... ) );
    };
    template<product_type T0, product_type... Ts>
    using zip_t = typename zip<T0,Ts...>::type;
  }
}
#undef KUMI_FWD
#endif
