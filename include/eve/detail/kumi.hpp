//==================================================================================================
/*
  KUMI - Compact Tuple Tools
  Copyright : KUMI Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#ifndef KUMI_TUPLE_HPP_INCLUDED
#define KUMI_TUPLE_HPP_INCLUDED

#include <concepts>
#include <iosfwd>
#include <type_traits>
#include <utility>

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wmissing-braces"
#endif

#define KUMI_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

//==================================================================================================
//! @namespace kumi
//! @brief Main KUMI namespace
//==================================================================================================
namespace kumi
{
  //================================================================================================
  //! @defgroup utility   Helper types and function
  //! @brief    Tools for interacting with kumi::tuple
  //!
  //! @defgroup tuple     Tuple types and function
  //! @brief    Definition for kumi::tuple class and functions
  //!
  //! @defgroup algorithm Tuple Algorithms
  //! @brief    Algorithms for manipulating kumi::tuple
  //!
  //! @ingroup  algorithm
  //! @{
  //!   @defgroup transforms Tuple Transformations
  //!   @brief    Algorithms applying transformation to tuple
  //!
  //!   @defgroup queries Tuple Queries
  //!   @brief    Algorithms querying properties from tuples
  //!
  //!   @defgroup reductions Tuple Generalized Reductions
  //!   @brief    Algorithms performing reductions over tuples
  //!
  //!   @defgroup generators Tuple Generators
  //!   @brief    Algorithms generating tuples
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup utility
  //! @brief Integral constant type
  //!
  //! Defines a integral constant wrapper used to carry compile-time constant through API
  //================================================================================================
  template<std::size_t N> struct index_t
  {
    /// Value stored by the constant
    static constexpr auto value = N;

    /// Conversion operator to integer
    constexpr inline      operator std::size_t() const noexcept { return N; }
  };

  //================================================================================================
  //! @ingroup utility
  //! @brief Inline integral constant value for kumi::index_t
  //================================================================================================
  template<std::size_t N> inline constexpr index_t<N> const index = {};

  //================================================================================================
  //! @namespace literals
  //! @brief KUMI literals namespace
  //================================================================================================
  namespace literals
  {
    template<char... c> constexpr auto b10()
    {
      auto value = 0ULL;
      ((value = value * 10 + (c - '0')), ...);
      return value;
    }

    //==============================================================================================
    //! @ingroup utility
    //! @brief Forms a integral constant literal of the desired value.
    //! @return An instance of kumi::index_t for the specified integral value
    //! ## Example:
    //! @include doc/index.cpp
    //==============================================================================================
    template<char... c> constexpr auto operator"" _c() noexcept { return index<b10<c...>()>; }
  }

  namespace detail
  {
    //==============================================================================================
    // Helper concepts
    //==============================================================================================
    template<typename From, typename To> struct is_piecewise_constructible;
    template<typename From, typename To> struct is_piecewise_convertible;

    template<template<class...> class Box, typename... From, typename... To>
    struct is_piecewise_convertible<Box<From...>, Box<To...>>
    {
      static constexpr bool value = (... && std::convertible_to<From, To>);
    };

    template<template<class...> class Box, typename... From, typename... To>
    struct is_piecewise_constructible<Box<From...>, Box<To...>>
    {
      static constexpr bool value = (... && std::is_constructible_v<To, From>);
    };

    template<typename From, typename To>
    concept piecewise_convertible = detail::is_piecewise_convertible<From, To>::value;

    template<typename From, typename To>
    concept piecewise_constructible = detail::is_piecewise_constructible<From, To>::value;

    template<typename T, typename... Args> concept implicit_constructible = requires(Args... args)
    {
      T {args...};
    };

    //==============================================================================================
    // Tuple leaf binder tricks
    //==============================================================================================
    template<std::size_t I, typename T> struct leaf
    {
      T value;
    };

    template<std::size_t I, typename T> constexpr T &get_leaf(leaf<I, T> &arg) noexcept
    {
      return arg.value;
    }

    template<std::size_t I, typename T> constexpr T &&get_leaf(leaf<I, T> &&arg) noexcept
    {
      return static_cast<T &&>(arg.value);
    }

    template<std::size_t I, typename T>
    constexpr T const &&get_leaf(leaf<I, T> const &&arg) noexcept
    {
      return static_cast<T const &&>(arg.value);
    }

    template<std::size_t I, typename T> constexpr T const &get_leaf(leaf<I, T> const &arg) noexcept
    {
      return arg.value;
    }

    template<typename ISeq, typename... Ts> struct binder;

    template<auto... Is, typename... Ts>
    struct binder<std::index_sequence<Is...>, Ts...> : leaf<Is, Ts>...
    {
    };

    //==============================================================================================
    // Fold helpers
    //==============================================================================================
    template<typename F, typename T> struct foldable
    {
      F func;
      T value;

      template<typename W>
      friend constexpr decltype(auto) operator>>(foldable &&x, foldable<F, W> &&y)
      {
        return detail::foldable {x.func, x.func(y.value, x.value)};
      }

      template<typename W>
      friend constexpr decltype(auto) operator<<(foldable &&x, foldable<F, W> &&y)
      {
        return detail::foldable {x.func, x.func(x.value, y.value)};
      }
    };

    template<class F, class T> foldable(const F &, T &&) -> foldable<F, T>;
  }

  //================================================================================================
  //! @ingroup tuple
  //! @brief Opt-in traits for types behaving like a kumi::product_type
  //!
  //! To be treated like a tuple, an user defined type must supports structured bindings opt-in to
  //! kumi::product_type Semantic.
  //!
  //! This can be done in two ways:
  //!   - exposing an internal `is_product_type` type that evaluates to `void`
  //!   - specializing the `kumi::is_product_type` traits so it exposes a static constant member
  //!     `value` that evaluates to `true`
  //!
  //! ## Example:
  //! @include doc/adapt.cpp
  //==============================================================================================
  template<typename T, typename Enable = void> struct is_product_type : std::false_type {};
  template<typename T> struct is_product_type<T, typename T::is_product_type> : std::true_type {};

  //================================================================================================
  //! @ingroup tuple
  //! @brief Computes the number of elements of a kumi::product_type
  //!
  //! @param T kumi::product_type to inspect
  //!
  //! ## Helper value
  //! @code
  //!   template<typename T> inline constexpr auto size_v = size<T>::value;
  //! @endcode
  //================================================================================================
  template<typename T> struct size : std::tuple_size<T>   {};
  template<typename T> struct size<T &>         : size<T> {};
  template<typename T> struct size<T &&>        : size<T> {};
  template<typename T> struct size<T const>     : size<T> {};
  template<typename T> struct size<T const &>   : size<T> {};
  template<typename T> struct size<T const &&>  : size<T> {};

  template<typename T> inline constexpr auto size_v = size<T>::value;

  //================================================================================================
  //! @ingroup tuple
  //! @brief Concept specifying a type is non-empty standard tuple-like type.
  //================================================================================================
  template<typename T> concept non_empty_tuple = requires( T const &t )
  {
    typename std::tuple_element<0,std::remove_cvref_t<T>>::type;
    typename std::tuple_size<std::remove_cvref_t<T>>::type;
  };


  //================================================================================================
  //! @ingroup tuple
  //! @brief Concept specifying a type is an empty standard tuple-like type.
  //================================================================================================
  template<typename T> concept empty_tuple = (std::tuple_size<std::remove_cvref_t<T>>::value == 0);

  //================================================================================================
  //! @ingroup tuple
  //! @brief Concept specifying a type is a standard tuple-like type.
  //================================================================================================
  template<typename T> concept std_tuple_compatible = empty_tuple<T> || non_empty_tuple<T>;

  //================================================================================================
  //! @ingroup tuple
  //! @brief Concept specifying a type follows the Product Type semantic
  //!
  //! A type `T` models `kumi::product_type` if it opts in for the Product Type semantic and
  //! provides supports for structured bindings.
  //================================================================================================
  template<typename T>
  concept product_type = std_tuple_compatible<T> && is_product_type<std::remove_cvref_t<T>>::value;

  //================================================================================================
  //! @ingroup tuple
  //! @brief Concept specifying a type follows the Product Type semantic and has a known size
  //!
  //! A type `T` models `kumi::sized_product_type<N>` if it models `kumi::product_type` and has
  //! exactly `N` elements.
  //================================================================================================
  template<typename T, std::size_t N>
  concept sized_product_type = product_type<T> && (size<T>::value == N);

  //================================================================================================
  //! @ingroup tuple
  //! @brief Concept specifying a type follows the Product Type semantic and has a size lower bound
  //!
  //! A type `T` models `kumi::sized_product_type<N>` if it models `kumi::product_type` and has
  //! at least `N` elements.
  //================================================================================================
  template<typename T, std::size_t N>
  concept sized_product_type_or_more = product_type<T> && (size<T>::value >= N);

  template<typename... Ts> struct tuple;
}

//==================================================================================================
// Structured binding adaptation
//==================================================================================================
namespace std
{
  template<std::size_t I, typename Head, typename... Tail>
  struct tuple_element<I, kumi::tuple<Head, Tail...>> : tuple_element<I - 1, kumi::tuple<Tail...>>
  {
  };

  template<std::size_t I, typename... Ts> struct tuple_element<I, kumi::tuple<Ts...> const>
  {
    using type = typename tuple_element<I, kumi::tuple<Ts...>>::type const;
  };

  template<typename Head, typename... Tail> struct tuple_element<0, kumi::tuple<Head, Tail...>>
  {
    using type = Head;
  };

  template<typename... Ts>
  struct tuple_size<kumi::tuple<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>
  {
  };
}

namespace kumi
{
  //================================================================================================
  //! @ingroup tuple
  //! @brief Provides indexed access to the types of the elements of a kumi::product_type.
  //!
  //! @tparam I Index of the type to retrieve
  //! @tparam T kumi::product_type to access
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi
  //! {
  //!   template<std::size_t I, typename T> using element_t = typename element<I,T>::type;
  //! }
  //! @endcode
  //================================================================================================
  template<std::size_t I, typename T> struct element              : std::tuple_element<I,T> {};
  template<std::size_t I, typename T> struct element<I,T&>        : element<I,T> {};
  template<std::size_t I, typename T> struct element<I,T&&>       : element<I,T> {};
  template<std::size_t I, typename T> struct element<I,T const&>  : element<I,T> {};
  template<std::size_t I, typename T> struct element<I,T const&&> : element<I,T> {};

  template<std::size_t I, typename T> using  element_t = typename element<I,T>::type;

  //================================================================================================
  //! @ingroup tuple
  //! @brief Computes the return type of a call to kumi::get
  //!
  //! @tparam I Index of the type to retrieve
  //! @tparam T kumi::product_type to access
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi
  //! {
  //!   template<std::size_t I, typename T> using member_t = typename member<I,T>::type;
  //! }
  //! @endcode
  //================================================================================================
  template<std::size_t I, typename T> struct member
  {
    using type = decltype( get<I>(std::declval<T&>()));
  };

  template<std::size_t I, typename T> using  member_t = typename member<I,T>::type;

  //================================================================================================
  // Concept machinery to make our algorithms SFINAE friendly
  //================================================================================================
  namespace detail
  {
    template<typename F, size_t I, typename... Tuples>
    concept applicable_i = std::is_invocable_v<F, member_t<I,Tuples>...>;

    template<typename F, typename Indices, typename... Tuples> struct is_applicable;

    template<typename F, size_t... Is, typename... Tuples>
    struct is_applicable<F, std::index_sequence<Is...>, Tuples...>
        : std::bool_constant<(applicable_i<F, Is, Tuples...> && ...)>
    {
    };

    template<typename F, typename... Tuples>
    concept applicable = detail::
        is_applicable<F, std::make_index_sequence<(size<Tuples>::value, ...)>, Tuples...>::value;

    // Helper for checking if two tuples can == each others
    template<typename T, typename U>
    concept comparable = requires(T t, U u)
    {
      { t == u };
    };

    template<typename T, typename U> constexpr auto check_equality()
    {
      return comparable<T,U>;
    }

    template<product_type T, product_type U>
    constexpr auto check_equality()
    {
      return []<std::size_t...I>(std::index_sequence<I...>)
      {
        return (check_equality<member_t<I,T>,member_t<I,U>>() && ...);
      }(std::make_index_sequence<size<T>::value>{});
    }
  }

  //================================================================================================
  //! @ingroup transforms
  //! @brief Invoke the Callable object f with a tuple of arguments.
  //!
  //! @param f	Callable object to be invoked
  //! @param t  kumi::product_type whose elements to be used as arguments to f
  //! @return The value returned by f.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<typename Function, product_type Tuple> struct apply;
  //!
  //!   template<typename Function, product_type Tuple>
  //!   using apply_t = typename apply<Function,Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::apply
  //!
  //! ## Example
  //! @include doc/apply.cpp
  //================================================================================================
  template<typename Function, product_type Tuple>
  constexpr decltype(auto) apply(Function &&f, Tuple &&t)
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

  //================================================================================================
  //! @ingroup transforms
  //! @brief Applies the Callable object f on each element of a kumi::product_type.
  //!
  //! @note This function does not take part in overload resolution if `f` can't be applied to the
  //!       elements of `t` and/or `ts`.
  //!
  //! @param f	  Callable object to be invoked
  //! @param t    kumi::product_type whose elements to be used as arguments to f
  //! @param ts   Other kumi::product_type whose elements to be used as arguments to f
  //!
  //! @see kumi::for_each_index
  //!
  //! ## Example
  //! @include doc/for_each.cpp
  //================================================================================================
  template<typename Function, product_type Tuple, product_type... Tuples>
  constexpr void for_each(Function f, Tuple&& t, Tuples&&... ts)
  requires detail::applicable<Function, Tuple, Tuples...>
  {
    if constexpr(sized_product_type<Tuple,0>) return;
    else
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        // clang needs this for some reason
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

  //================================================================================================
  //! @ingroup transforms
  //! @brief Applies the Callable object f on each element of a kumi::product_type and its index.
  //!
  //! @note This function does not take part in overload resolution if `f` can't be applied to the
  //!       elements of `t` and/or `ts` and an integral constant.
  //!
  //! @param f	  Callable object to be invoked
  //! @param t    kumi::product_type whose elements to be used as arguments to f
  //! @param ts   Other kumi::product_type whose elements to be used as arguments to f
  //!
  //! @see kumi::for_each
  //!
  //! ## Example
  //! @include doc/for_each_index.cpp
  //================================================================================================
  template<typename Function, product_type Tuple, product_type... Tuples>
  constexpr void for_each_index(Function f, Tuple&& t, Tuples&&... ts)
  {
    if constexpr(sized_product_type<Tuple,0>) return;
    else
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        // clang needs this for some reason
        using std::get;
        [[maybe_unused]] auto call = [&]<typename M>(M idx)
                                        { f ( idx
                                            , get<M::value>(KUMI_FWD(t))
                                            , get<M::value>(KUMI_FWD(ts))...
                                            );
                                        };

        ( call(std::integral_constant<std::size_t, I>{}), ... );
      }
      (std::make_index_sequence<size<Tuple>::value>());
    }
  }

  //================================================================================================
  //! @ingroup tuple
  //! @class tuple
  //! @brief Fixed-size collection of heterogeneous values.
  //!
  //! kumi::tuple provides an aggregate based implementation of a tuple. It provides algorithms and
  //! functions designed to facilitate tuple's handling and transformations.
  //!
  //! kumi::tuple is also compatible with standard tuple operations and structured bindings.
  //!
  //! @tparam Ts Sequence of types stored inside kumi::tuple.
  //================================================================================================
  template<typename... Ts> struct tuple
  {
    using is_product_type = void;
    detail::binder<std::make_index_sequence<sizeof...(Ts)>, Ts...> impl;

    //==============================================================================================
    //! @name Accessors
    //! @{
    //==============================================================================================

    //==============================================================================================
    //! @brief Extracts the Ith element from a kumi::tuple
    //!
    //! @note Does not participate in overload resolution if `I` is not in [0, sizeof...(Ts)).
    //! @param  i Compile-time index of the element to access
    //! @return A reference to the selected element of current tuple.
    //!
    //! ## Example:
    //! @include doc/subscript.cpp
    //==============================================================================================
    template<std::size_t I>
    requires(I < sizeof...(Ts)) constexpr decltype(auto) operator[](index_t<I>) &noexcept
    {
      return detail::get_leaf<I>(impl);
    }

    /// @overload
    template<std::size_t I>
    requires(I < sizeof...(Ts)) constexpr decltype(auto) operator[](index_t<I>) &&noexcept
    {
      return detail::get_leaf<I>(static_cast<decltype(impl) &&>(impl));
    }

    /// @overload
    template<std::size_t I>
    requires(I < sizeof...(Ts)) constexpr decltype(auto) operator[](index_t<I>) const &&noexcept
    {
      return detail::get_leaf<I>(static_cast<decltype(impl) const &&>(impl));
    }

    /// @overload
    template<std::size_t I>
    requires(I < sizeof...(Ts)) constexpr decltype(auto) operator[](index_t<I>) const &noexcept
    {
      return detail::get_leaf<I>(impl);
    }

    //==============================================================================================
    //! @brief Extracts a sub-tuple from a kumi::tuple
    //!
    //! @note Does not participate in overload resolution if `I0` and `I1` do not verify that
    //!       `0 <= I0 <= I1 <= sizeof...(Ts)`.
    //! @param  i0 Compile-time index of the first element to extract.
    //! @param  i1 Compile-time index past the last element to extract. By default, `i1` is equal to
    //!         `sizeof...(Ts)`.
    //! @return A new kumi::tuple containing to the selected elements of current tuple.
    //!
    //! ## Example:
    //! @include doc/extract.cpp
    //==============================================================================================
    template<std::size_t I0, std::size_t I1>
    requires((I1 - I0) <= sizeof...(Ts))
    [[nodiscard]] constexpr auto extract(index_t<I0> const &, index_t<I1> const &) const noexcept
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N + I0, tuple>...> {(*this)[index<N + I0>]...};
      }
      (std::make_index_sequence<I1 - I0>());
    }

    /// @overload
    template<std::size_t I0>
    requires(I0 <= sizeof...(Ts))
    [[nodiscard]] constexpr auto extract(index_t<I0> const &) const noexcept
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N + I0, tuple>...> {(*this)[index<N + I0>]...};
      }
      (std::make_index_sequence<sizeof...(Ts) - I0>());
    }

    //==============================================================================================
    //! @brief Split a tuple into two
    //!
    //! Split a kumi::tuple in two kumi::tuple containing all the elements before and after
    //! a given index.
    //!
    //! @note Does not participate in overload resolution if `I0` is not in `[0, sizeof...(Ts)[`.
    //!
    //! @param  i0 Compile-time index of the first element to extract.
    //! @return A new kumi::tuple containing the two sub-tuple cut at index I.
    //!
    //!
    //! ## Helper type
    //! @code
    //! namespace kumi::result
    //! {
    //!   template<std::size_t I0, product_type Tuple> struct split;
    //!
    //!   template<std::size_t I0, product_type Tuple>
    //!   using split_t = typename split<I0,Tuple>::type;
    //! }
    //! @endcode
    //!
    //! Computes the type returned by a call to split.
    //!
    //! ## Example:
    //! @include doc/split.cpp
    //==============================================================================================
    template<std::size_t I0>
    requires(I0 <= sizeof...(Ts)) [[nodiscard]] constexpr auto split(index_t<I0> const&) const noexcept;

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Properties
    //! @{
    //==============================================================================================
    /// Returns the number of elements in a kumi::tuple
    [[nodiscard]] static constexpr auto size() noexcept { return sizeof...(Ts); }

    /// Returns `true` if a kumi::tuple contains 0 elements
    [[nodiscard]] static constexpr bool empty() noexcept { return sizeof...(Ts) == 0; }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Conversions
    //! @{
    //==============================================================================================

    //==============================================================================================
    //! @brief  Converts a tuple<Ts...> to a tuple<Us...>.
    //! @tparam Us Types composing the destination tuple
    //!
    //! ## Example:
    //! @include doc/cast.cpp
    //==============================================================================================
    template<typename... Us>
    requires(   detail::piecewise_convertible<tuple, tuple<Us...>>
            &&  (sizeof...(Us) == sizeof...(Ts))
            &&  (!std::same_as<Ts, Us> && ...)
            )
    [[nodiscard]] inline constexpr auto cast() const
    {
      return apply([](auto &&...elems) { return tuple<Us...> {static_cast<Us>(elems)...}; }, *this);
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @brief Replaces the contents of the tuple with the contents of another tuple.
    //! @param other kumi::tuple to copy or move from
    //! @return `*this`
    //==============================================================================================
    template<typename... Us>
    requires(detail::piecewise_convertible<tuple, tuple<Us...>>) constexpr tuple &
    operator=(tuple<Us...> const &other)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>) { ((get<I>(*this) = get<I>(other)), ...); }
      (std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    /// @overload
    template<typename... Us>
    requires(detail::piecewise_convertible<tuple, tuple<Us...>>) constexpr tuple &
    operator=(tuple<Us...> &&other)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((get<I>(*this) = get<I>(KUMI_FWD(other))), ...);
      }
      (std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    //==============================================================================================
    //! @name Comparison operators
    //! @{
    //==============================================================================================

    /// @ingroup tuple
    /// @related kumi::tuple
    /// @brief Compares a tuple with an other kumi::product_type for equality
    template<sized_product_type<sizeof...(Ts)> Other>
    friend constexpr auto operator==(tuple const &self, Other const &other) noexcept
    requires( (sizeof...(Ts) != 0 ) && detail::check_equality<tuple,Other>() )
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return ((get<I>(self) == get<I>(other)) && ...);
      }
      (std::make_index_sequence<sizeof...(Ts)>());
    }

#if !defined(KUMI_DOXYGEN_INVOKED)
    template<sized_product_type<0> Other>
    friend constexpr auto operator==(tuple const&, Other const &) noexcept
    {
      return true;
    }
#endif

    /// @ingroup tuple
    /// @related kumi::tuple
    /// @brief Compares a tuple with an other kumi::product_type for inequality
    template<sized_product_type<sizeof...(Ts)> Other>
    friend constexpr auto operator!=(tuple const &self, Other const &other) noexcept
    requires( (sizeof...(Ts) != 0 ) && detail::check_equality<tuple,Other>() )
    {
      return !(self == other);
    }

#if !defined(KUMI_DOXYGEN_INVOKED)
    template<sized_product_type<0> Other>
    friend constexpr auto operator!=(tuple const&, Other const &) noexcept
    {
      return false;
    }
#endif

    /// @ingroup tuple
    /// @related kumi::tuple
    /// @brief Compares tuple and product type value for lexicographical is less relation
    template<sized_product_type<sizeof...(Ts)> Other>
    friend constexpr auto operator<(tuple const &lhs, Other const &rhs) noexcept
    {
      // lexicographical order is defined as
      // (v0 < w0) || ... andnot(wi < vi, vi+1 < wi+1) ... || andnot(wn-1 < vn-1, vn < wn);
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

    /// @ingroup tuple
    /// @related kumi::tuple
    /// @brief Compares tuple and product type value for lexicographical is less or equal relation
    template<product_type Other>
    friend constexpr auto operator<=(tuple const &lhs, Other const &rhs) noexcept
    {
      return !(rhs < lhs);
    }

    /// @ingroup tuple
    /// @related kumi::tuple
    /// @brief Compares tuple and product type value for lexicographical is greater relation
    template<product_type Other>
    friend constexpr auto operator>(tuple const &lhs, Other const &rhs) noexcept
    {
      return rhs < lhs;
    }

    /// @ingroup tuple
    /// @related kumi::tuple
    /// @brief Compares tuple and product type value for lexicographical is greater relation relation
    template<product_type Other>
    friend constexpr auto operator>=(tuple const &lhs, Other const &rhs) noexcept
    {
      return !(lhs < rhs);
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @brief Invoke the Callable object f on each element of the current tuple.
    //!
    //! @param f	Callable object to be invoked
    //! @return The value returned by f.
    //!
    //==============================================================================================
    template<typename Function>
    constexpr decltype(auto) operator()(Function &&f) const&
    noexcept(noexcept(kumi::apply(KUMI_FWD(f), *this))) { return kumi::apply(KUMI_FWD(f), *this); }

#if !defined(KUMI_DOXYGEN_INVOKED)
    template<typename Function>
    constexpr decltype(auto) operator()(Function &&f) &
    noexcept(noexcept(kumi::apply(KUMI_FWD(f), *this)))
    {
      return kumi::apply(KUMI_FWD(f), *this);
    }

    template<typename Function>
    constexpr decltype(auto) operator()(Function &&f) const &&noexcept(
    noexcept(kumi::apply(KUMI_FWD(f), static_cast<tuple const &&>(*this))))
    {
      return kumi::apply(KUMI_FWD(f), static_cast<tuple const &&>(*this));
    }

    template<typename Function>
    constexpr decltype(auto) operator()(Function &&f) &&noexcept(
    noexcept(kumi::apply(KUMI_FWD(f), static_cast<tuple &&>(*this))))
    {
      return kumi::apply(KUMI_FWD(f), static_cast<tuple &&>(*this));
    }
#endif

    //==============================================================================================
    /// @ingroup tuple
    //! @related kumi::tuple
    //! @brief Inserts a kumi::tuple in an output stream
    //==============================================================================================
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

  //================================================================================================
  //! @name Tuple construction
  //! @{
  //================================================================================================

  //================================================================================================
  //! @ingroup tuple
  //! @related kumi::tuple
  //! @brief kumi::tuple deduction guide
  //! @tparam Ts  Type lists to build the tuple with.
  //================================================================================================
  template<typename... Ts> tuple(Ts &&...) -> tuple<std::unwrap_ref_decay_t<Ts>...>;

  //================================================================================================
  //! @ingroup tuple
  //! @related kumi::tuple
  //! @brief Creates a kumi::tuple of lvalue references to its arguments.
  //! @param ts	Zero or more lvalue arguments to construct the tuple from.
  //! @return A kumi::tuple object containing lvalue references.
  //! ## Example:
  //! @include doc/tie.cpp
  //================================================================================================
  template<typename... Ts> [[nodiscard]] constexpr tuple<Ts &...> tie(Ts &...ts) { return {ts...}; }

  //================================================================================================
  //! @ingroup tuple
  //! @related kumi::tuple
  //! @brief Creates a kumi::tuple of forwarding references to its arguments.
  //!
  //! Constructs a tuple of references to the arguments in args suitable for forwarding as an
  //! argument to a function. The tuple has rvalue reference data members when rvalues are used as
  //! arguments, and otherwise has lvalue reference data members.
  //!
  //! @note If the arguments are temporaries, `forward_as_tuple` does not extend their lifetime;
  //!       they have to be used before the end of the full expression.
  //!
  //! @param ts	Zero or more lvalue arguments to construct the tuple from.
  //! @return A kumi::tuple constructed as `kumi::tuple<Ts&&...>(std::forward<Ts>(args)...)`
  //! ## Example:
  //! @include doc/forward_as_tuple.cpp
  //================================================================================================
  template<typename... Ts> [[nodiscard]] constexpr tuple<Ts &&...> forward_as_tuple(Ts &&...ts)
  {
    return {KUMI_FWD(ts)...};
  }

  //================================================================================================
  //! @ingroup tuple
  //! @related kumi::tuple
  //! @brief Creates a tuple object, deducing the target type from the types of arguments.
  //!
  //! @param ts	Zero or more lvalue arguments to construct the tuple from.
  //! @return A kumi::tuple constructed from the ts or their inner references when ts is an instance
  //!         of `std::reference_wrapper`.
  //! ## Example:
  //! @include doc/make_tuple.cpp
  //================================================================================================
  template<typename... Ts>
  [[nodiscard]] constexpr tuple<std::unwrap_ref_decay_t<Ts>...> make_tuple(Ts &&...ts)
  {
    return {KUMI_FWD(ts)...};
  }

  //================================================================================================
  //! @ingroup tuple
  //! @related kumi::tuple
  //! @brief Creates a kumi::tuple of references given a reference to a kumi::product_type.
  //!
  //! @param    t Compile-time index of the element to access
  //! @return   A tuple equivalent to the result of `kumi::apply([]<typename... T>(T&&... e)
  //!           { return kumi::forward_as_tuple(std::forward<T>(e)...); }, t)`
  //!
  //! ## Example:
  //! @include doc/to_ref.cpp
  //================================================================================================
  template<product_type Type> [[nodiscard]] constexpr auto to_ref(Type&& that)
  {
    return apply( [](auto&&... elems)
                  {
                    return kumi::forward_as_tuple(KUMI_FWD(elems)...);
                  }
                , KUMI_FWD(that)
                );
  }

  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @name Conversions
  //! @{
  //================================================================================================

  //================================================================================================
  //! @brief Converts a kumi::tuple to an instance of an arbitrary type
  //!
  //! Constructs an instance of `Type` by passing elements of `t` to the appropriate constructor.
  //!
  //! @tparam Type Type to generate
  //! @param  t    kumi::tuple to convert
  //! @return An instance of `Type` constructed from each element of `t` in order.
  //!
  //! ## Example
  //! @include doc/from_tuple.cpp
  //================================================================================================
  template<typename Type, typename... Ts>
  requires(!product_type<Type> && detail::implicit_constructible<Type, Ts...>)
  [[nodiscard]] constexpr auto from_tuple(tuple<Ts...> const &t)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>) { return Type {get<I>(t)...}; }
    (std::make_index_sequence<sizeof...(Ts)>());
  }

  //================================================================================================
  //! @brief Converts a kumi::product_type to an instance kumi::tuple
  //!
  //! Constructs an instance kumi::tuple from the elements of the kumi::product_type parameters
  //!
  //! @param  t    kumi::product_type to convert
  //! @return An instance of kumi::tuple constructed from each elements of `t` in order.
  //!
  //! ## Example
  //! @include doc/to_tuple.cpp
  //================================================================================================
  template<product_type Type>
  [[nodiscard]] inline constexpr auto to_tuple(Type&& t)
  {
    return apply([](auto &&...elems) { return tuple{elems...}; }, KUMI_FWD(t));
  }

  //================================================================================================
  //! @}
  //================================================================================================

  template<typename... Ts>
  template<std::size_t I0>
  requires(I0 <= sizeof...(Ts))
  [[nodiscard]] constexpr auto tuple<Ts...>::split(index_t<I0> const &) const noexcept
  {
    return kumi::make_tuple(extract(index<0>, index<I0>), extract(index<I0>));
  }

  namespace result
  {
    template<product_type T, std::size_t I0> struct split
    {
      using type = decltype ( std::declval<T>().split(kumi::index_t<I0>{}) );
    };

    template<product_type T, std::size_t I0> using split_t = typename split<T,I0>::type;
  }

  //================================================================================================
  //! @name Accessors
  //! @{
  //================================================================================================

  //================================================================================================
  //! @ingroup tuple
  //! @brief Extracts the Ith element from a kumi::tuple
  //!
  //! @note Does not participate in overload resolution if `I` is not in [0, sizeof...(Ts)).
  //! @tparam   I Compile-time index of the element to access
  //! @param    t Compile-time index of the element to access
  //! @return   A reference to the selected element of t.
  //! @related kumi::tuple
  //!
  //! ## Example:
  //! @include doc/get.cpp
  //================================================================================================
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) [[nodiscard]] constexpr decltype(auto) get(tuple<Ts...> &arg) noexcept
  {
    return arg[index<I>];
  }

  /// @overload
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) [[nodiscard]] constexpr decltype(auto)
  get(tuple<Ts...> &&arg) noexcept
  {
    return static_cast<tuple<Ts...> &&>(arg)[index<I>];
  }

  /// @overload
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) [[nodiscard]] constexpr decltype(auto)
  get(tuple<Ts...> const &arg) noexcept
  {
    return arg[index<I>];
  }

  /// @overload
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) [[nodiscard]] constexpr decltype(auto)
  get(tuple<Ts...> const &&arg) noexcept
  {
    return static_cast<tuple<Ts...> const &&>(arg)[index<I>];
  }

  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup transforms
  //! @brief Apply the Callable object f on each tuples' elements
  //!
  //! Applies the given function to all the tuples passed as arguments and stores the result in
  //! another tuple, keeping the original elements order.
  //!
  //! @note Does not participate in overload resolution if tuples' size are not equal or if `f`
  //!       can't be called on each tuple's elements.
  //!
  //! @param f      Callable function to apply
  //! @param t0     Tuple  to operate on
  //! @param others Tuples to operate on
  //! @return The tuple of `f` calls results.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<typename Function, product_type T, product_type... Ts> struct map;
  //!
  //!   template<typename Function, product_type T, product_type... Ts>
  //!   using map_t = typename map<Function,Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::map
  //!
  //! ## Example
  //! @include doc/map.cpp
  //================================================================================================
  template<product_type Tuple, typename Function, sized_product_type<size<Tuple>::value>... Tuples>
  constexpr auto
  map(Function     f,
      Tuple  &&t0,
      Tuples &&...others) requires detail::applicable<Function, Tuple&&, Tuples&&...>
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

  //================================================================================================
  //! @ingroup transforms
  //! @brief Apply the Callable object f on each tuples' elements and their indexes
  //!
  //! Applies the given function to all the tuples passed as arguments along with their indexes  and
  //! stores the result in another tuple, keeping the original elements order.
  //!
  //! @note Does not participate in overload resolution if tuples' size are not equal or if `f`
  //!       can't be called on each tuple's elements and their indexes.
  //!
  //! @param f      Callable function to apply
  //! @param t0     Tuple  to operate on
  //! @param others Tuples to operate on
  //! @return The tuple of `f` calls results.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<typename Function, product_type T, product_type... Ts> struct map_index;
  //!
  //!   template<typename Function, product_type T, product_type... Ts>
  //!   using map_index_t = typename map_index<Function,Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::map_index
  //!
  //! ## Example
  //! @include doc/map_index.cpp
  //================================================================================================
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

  //================================================================================================
  //! @ingroup reductions
  //! @brief Computes the generalized sum of all elements using a tail recursive tail.
  //!
  //! @param f      Binary callable function to apply
  //! @param t      Tuple to operate on
  //! @param init   Initial value of the sum
  //! @return   The value of `f( f( f(init, get<0>(t)), ...), get<N-1>(t))`
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<typename Function, product_type Tuple, typename Value> struct fold_left;
  //!
  //!   template<typename Function, product_type Tuple, typename Value>
  //!   using fold_left_t = typename fold_left_t<Function,Tuple,Value>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::fold_left
  //!
  //! ## Example
  //! @include doc/fold_left.cpp
  //================================================================================================
  template<typename Function, product_type Tuple, typename Value>
  [[nodiscard]] constexpr auto fold_left(Function f, Tuple&& t, Value init)
  {
    if constexpr(sized_product_type<Tuple,0>) return init;
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return (detail::foldable {f, get<I>(KUMI_FWD(t))} >> ... >> detail::foldable {f, init}).value;
      }
      (std::make_index_sequence<size<Tuple>::value>());
    }
  }

  //================================================================================================
  //! @ingroup reductions
  //! @brief Computes the generalized sum of all elements using a non-tail recursive tail.
  //!
  //! @param f      Binary callable function to apply
  //! @param t      Tuple to operate on
  //! @param init   Initial value of the sum
  //! @return   The value of `f(get<0>(t), f(... , f(get<N-1>(t), init))`
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<typename Function, product_type Tuple, typename Value> struct fold_right;
  //!
  //!   template<typename Function, product_type Tuple, typename Value>
  //!   using fold_right_t = typename fold_right_t<Function,Tuple,Value>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::fold_right
  //!
  //! ## Example
  //! @include doc/fold_right.cpp
  //================================================================================================
  template<typename Function, product_type Tuple, typename Value>
  [[nodiscard]] constexpr auto fold_right(Function f, Tuple&& t, Value init)
  {
    if constexpr(size<Tuple>::value ==0) return init;
    else
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return (detail::foldable {f, init} << ... << detail::foldable {f, get<I>(KUMI_FWD(t))}).value;
      }
      (std::make_index_sequence<size<Tuple>::value>());
    }
  }

  namespace result
  {
    template<typename Function, product_type Tuple, typename Value>
    struct fold_right
    {
      using type = decltype ( kumi::fold_right( std::declval<Function>()
                                              , std::declval<Tuple>()
                                              , std::declval<Value>()
                                              )
                            );
    };

    template<typename Function, product_type Tuple, typename Value>
    struct fold_left
    {
      using type = decltype ( kumi::fold_left ( std::declval<Function>()
                                              , std::declval<Tuple>()
                                              , std::declval<Value>()
                                              )
                            );
    };

    template<typename Function, product_type Tuple, typename Value>
    using fold_right_t = typename fold_right<Function,Tuple,Value>::type;

    template<typename Function, product_type Tuple, typename Value>
    using fold_left_t = typename fold_left<Function,Tuple,Value>::type;
  }

  //================================================================================================
  //! @ingroup generators
  //! @brief Concatenates tuples in a single one
  //!
  //! @param ts Tuples to concatenate
  //! @return   A tuple made of all element of all input tuples in order
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type... Tuples> struct cat;
  //!
  //!   template<product_type... Tuples>
  //!   using cat_t = typename cat<Tuples...>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::cat
  //!
  //! ## Example
  //! @include doc/cat.cpp
  //================================================================================================
  template<product_type... Tuples> [[nodiscard]] constexpr auto cat(Tuples&&... ts)
  {
    if constexpr(sizeof...(Tuples) == 0) return tuple{};
    else
    {
      // count is at least 1 so MSVC don't cry when we use a 0-sized array
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
        return type{get<pos.e[N]>(get<pos.t[N]>(tuples))...};
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

  //================================================================================================
  //! @ingroup generators
  //! @brief Constructs a tuple by adding a value v at the beginning of t
  //!
  //! @param t Base tuple
  //! @param v Value to insert in front of t
  //! @return A tuple composed of v followed by all elements of t in order.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple, typename T> struct push_front;
  //!
  //!   template<product_type Tuple, typename T>
  //!   using push_front_t = typename push_front<Tuples...>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::push_front
  //!
  //! ## Example
  //! @include doc/push_front.cpp
  //================================================================================================
  template<product_type Tuple, typename T>
  [[nodiscard]] constexpr auto push_front(Tuple const& t, T&& v)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return make_tuple(KUMI_FWD(v), get<I>(KUMI_FWD(t))...);
    }
    (std::make_index_sequence<Tuple::size()>());
  }

  //================================================================================================
  //! @ingroup generators
  //! @brief Remove the first (if any) element of a kumi::product_type.
  //!
  //! @param t Base tuple
  //! @return A tuple composed of all elements of t except its first. Has no effect on empty t.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple> struct pop_front;
  //!
  //!   template<product_type Tuple>
  //!   using pop_front_t = typename pop_front<Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::pop_front
  //!
  //! ## Example
  //! @include doc/pop_front.cpp
  //================================================================================================
  template<product_type Tuple>
  [[nodiscard]] constexpr auto pop_front(Tuple const& t)
  {
    if constexpr(Tuple::size()>0) return t.extract(index<1>);
    else                          return tuple<>{};
  }

  //================================================================================================
  //! @ingroup generators
  //! @brief Constructs a tuple by adding a value v at the end of t
  //!
  //! @param t Base tuple
  //! @param v Value to insert in front of t
  //! @return A tuple composed of all elements of t in order followed by v.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple, typename T> struct push_back;
  //!
  //!   template<product_type Tuple, typename T>
  //!   using push_back_t = typename push_back<Tuple,T>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::push_back
  //!
  //! ## Example
  //! @include doc/push_back.cpp
  //================================================================================================
  template<product_type Tuple, typename T>
  [[nodiscard]] constexpr auto push_back(Tuple const& t, T&& v)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return make_tuple(get<I>(KUMI_FWD(t))..., KUMI_FWD(v));
    }
    (std::make_index_sequence<Tuple::size()>());
  }

  //================================================================================================
  //! @ingroup generators
  //! @brief Remove the last (if any) element of a kumi::product_type.
  //!
  //! @param t Base tuple
  //! @return A tuple composed of all elements of t except its last. Has no effect on empty t.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple> struct pop_back;
  //!
  //!   template<product_type Tuple>
  //!   using pop_back_t = typename pop_back<Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::pop_back
  //!
  //! ## Example
  //! @include doc/pop_back.cpp
  //================================================================================================
  template<product_type Tuple>
  [[nodiscard]] constexpr auto pop_back(Tuple const& t)
  {
    if constexpr(Tuple::size()>1) return t.extract(index<0>, index<Tuple::size()-1>);
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

  //================================================================================================
  //! @ingroup generators
  //! @brief Converts a tuple of tuples into a tuple of all elements.
  //!
  //! @param ts Tuple to flatten
  //! @return A tuple composed of all elements of t flattened non-recursively
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple> struct flatten;
  //!
  //!   template<product_type Tuple>
  //!   using flatten_t = typename flatten<Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::flatten
  //!
  //! ## Example
  //! @include doc/flatten.cpp
  //================================================================================================
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

  //================================================================================================
  //! @ingroup generators
  //! @brief Recursively converts a tuple of tuples into a tuple of all elements.
  //!
  //! Recursively converts a tuple of tuples `t` into a tuple of all elements of said tuples.
  //! If the Callable object f is provided, non-tuple elements are processed by `f` before being
  //! inserted.
  //!
  //! @param ts Tuple to flatten
  //! @param f  Optional Callable object to apply when a sub-tuple is flattened
  //! @return A tuple composed of all elements of t flattened recursively
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple, typename Func = void> struct flatten_all;
  //!
  //!   template<product_type Tuple, typename Func = void>
  //!   using flatten_all_t = typename flatten_all<Tuple, Func>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::flatten_all
  //!
  //! ## Example
  //! @include doc/flatten_all.cpp
  //================================================================================================
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

  /// @overload
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

  //================================================================================================
  //! @ingroup generators
  //! @brief Convert a kumi::product_type to a flat tuple of pointers to each its components.
  //!
  //! @param ts Tuple to convert
  //! @return A flat tuple composed of pointers to each elements of t.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple> struct as_flat_ptr;
  //!
  //!   template<product_type Tuple>
  //!   using as_flat_ptr_t = typename as_flat_ptr<Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::as_flat_ptr
  //!
  //! ## Example
  //! @include doc/as_flat_ptr.cpp
  //================================================================================================
  template<product_type Tuple>
  [[nodiscard]] auto as_flat_ptr(Tuple&& t) noexcept
  {
    return kumi::flatten_all(KUMI_FWD(t), [](auto& m) { return &m; });
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

  //================================================================================================
  //! @ingroup generators
  //! @brief Constructs a tuple where the ith element is the tuple of all ith elements of ts...
  //!
  //! @param t0 Tuple to convert
  //! @param ts Tuples to convert
  //! @return The tuple of all combination of elements from t0, ts...
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple> struct zip;
  //!
  //!   template<product_type Tuple>
  //!   using zip_t = typename zip<Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::zip
  //!
  //! ## Example
  //! @include doc/zip.cpp
  //================================================================================================
  template<product_type T0, sized_product_type<size_v<T0>>... Ts>
  [[nodiscard]] constexpr auto zip(T0 const &t0, Ts const &...tuples)
  {
    return kumi::map([](auto const &m0, auto const &...ms) { return kumi::make_tuple(m0, ms...); },
                     t0,
                     tuples...);
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


  //================================================================================================
  //! @ingroup generators
  //! @brief Transpose a tuple of tuples by shifting elements in their transposed position
  //!
  //! @param t Tuple to transpose
  //! @return A tuple containing the transposed elements of t.
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple> struct transpose;
  //!
  //!   template<product_type Tuple>
  //!   using transpose_t = typename transpose<Tuple>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::transpose
  //!
  //! ## Example
  //! @include doc/transpose.cpp
  //================================================================================================
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

//================================================================================================
  //! @ingroup generators
  //! @brief Reorder elements of a kumi::product_type
  //!
  //! This function does not participate in overload resolution if any IDx is outside [0, size_v<T>[.
  //!
  //! @note Nothing prevent the number of reordered index to be lesser or greater than t size or
  //!       the fact they can appear multiple times.
  //!
  //! @tparam Idx Reordered index of elements
  //! @param  t kumi::product_type to reorder
  //! @return A tuple equivalent to kumi::make_tuple(t[index<Idx>]...);
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<product_type Tuple,std::size_t... Idx> struct reorder;
  //!
  //!   template<product_type Tuple,std::size_t... Idx>
  //!   using reorder_t = typename reorder<Tuple,Idx...>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::reorder
  //!
  //! ## Example
  //! @include doc/reorder.cpp
  //================================================================================================
  template<std::size_t... Idx, product_type Tuple>
  requires((Idx < size<Tuple>::value) && ...) [[nodiscard]] constexpr auto reorder(Tuple &&t)
  {
    return kumi::make_tuple(KUMI_FWD(t)[index<Idx>]...);
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

  //================================================================================================
  namespace detail
  {
    template<std::size_t N, typename T>
    constexpr auto const& eval(T const& v) noexcept { return v; }
  }

  //================================================================================================
  //! @ingroup generators
  //! @brief Creates a kumi::tuple containing `N` copies of `v`.
  //!
  //! @tparam N Number of replications
  //! @param  v Value to replicate
  //! @return A tuple containing `N` copy of `v`
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<std::size_t N, typename T> struct generate;
  //!
  //!   template<std::size_t N, typename T>
  //!   using generate_t = typename generate<N, T>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::generate
  //!
  //! ## Example
  //! @include doc/generate.cpp
  //================================================================================================
  template<std::size_t N, typename T> [[nodiscard]] constexpr auto generate(T const& v) noexcept
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return kumi::tuple{detail::eval<I>(v)...};
    }(std::make_index_sequence<N>{});
  }


  //================================================================================================
  //! @ingroup generators
  //! @brief Creates a kumi::tuple containing an increasing ramp of values.
  //!
  //! @tparam N Number of replications
  //! @param  v Seed value
  //! @return A tuple containing `{v, v + 1, ..., v + N-1}`
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi::result
  //! {
  //!   template<std::size_t N, typename T> struct iota;
  //!
  //!   template<std::size_t N, typename T>
  //!   using iota_t = typename iota<N, T>::type;
  //! }
  //! @endcode
  //!
  //! Computes the return type of a call to kumi::iota
  //!
  //! ## Example
  //! @include doc/iota.cpp
  //================================================================================================
  template<std::size_t N, typename T> [[nodiscard]] constexpr auto iota(T v) noexcept
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return kumi::tuple{T(v+I)...};
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

  //================================================================================================
  //! @ingroup reductions
  //! @brief Computes the maximum value of applications of f to all elements of t.
  //! @param t Tuple to inspect
  //! @param f Unary Callable object
  //! @return The maximum value of f over all elements of t
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi
  //! {
  //!   template<typename T, typename F> struct max;
  //!
  //!   template<typename T, typename F>
  //!   using max_t = typename max<T, F>::type;
  //! }
  //! @endcode
  //!
  //! Computes the type returned by a call to kumi::max.
  //!
  //! ## Example:
  //! @include doc/max.cpp
  //================================================================================================
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

  //================================================================================================
  //! @ingroup reductions
  //! @brief Computes the maximum value of applications of f to all elements of kumi::flatten_all(t).
  //! @param t Tuple to inspect
  //! @param f Unary Callable object
  //! @return The maximum value of f over all elements of a flattened version of t
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi
  //! {
  //!   template<typename T, typename F> struct max_flat;
  //!
  //!   template<typename T, typename F>
  //!   using max_flat_t = typename max_flat<T, F>::type;
  //! }
  //! @endcode
  //!
  //! Computes the type returned by a call to kumi::max_flat.
  //!
  //! ## Example:
  //! @include doc/max_flat.cpp
  //================================================================================================
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
    template<typename T, typename F> struct max
    {
      using type = decltype( kumi::max( std::declval<T>(), std::declval<F>() ) );
    };

    template<typename T, typename F> struct max_flat
    {
      using type = decltype( kumi::max_flat( std::declval<T>(), std::declval<F>() ) );
    };

    template<typename T, typename F> using max_t      = typename max<T,F>::type;
    template<typename T, typename F> using max_flat_t = typename max_flat<T,F>::type;
  }

  //================================================================================================
  //! @ingroup reductions
  //! @brief Computes the minimum value of applications of f to all elements of t.
  //! @param t Tuple to inspect
  //! @param f Unary Callable object
  //! @return The minimum value of f over all elements of t
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi
  //! {
  //!   template<typename T, typename F> struct min;
  //!
  //!   template<typename T, typename F>
  //!   using min_t = typename min<T, F>::type;
  //! }
  //! @endcode
  //!
  //! Computes the type returned by a call to kumi::min.
  //!
  //! ## Example:
  //! @include doc/min.cpp
  //================================================================================================
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

  //================================================================================================
  //! @ingroup reductions
  //! @brief Computes the minimum value of applications of f to all elements of kumi::flatten_all(t).
  //! @param t Tuple to inspect
  //! @param f Unary Callable object
  //! @return The minimum value of f over all elements of a flattened version of t
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi
  //! {
  //!   template<typename T, typename F> struct min_flat;
  //!
  //!   template<typename T, typename F>
  //!   using min_flat_t = typename min_flat<T, F>::type;
  //! }
  //! @endcode
  //!
  //! Computes the type returned by a call to kumi::min_flat.
  //!
  //! ## Example:
  //! @include doc/min_flat.cpp
  //================================================================================================
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
    template<typename T, typename F> struct min
    {
      using type = decltype( kumi::min( std::declval<T>(), std::declval<F>() ) );
    };

    template<typename T, typename F> struct min_flat
    {
      using type = decltype( kumi::min_flat( std::declval<T>(), std::declval<F>() ) );
    };

    template<typename T, typename F> using min_t      = typename min<T,F>::type;
    template<typename T, typename F> using min_flat_t = typename min_flat<T,F>::type;
  }

  //================================================================================================
  //! @ingroup utility
  //! @brief Convert a unary template meta-program in a running predicate
  //! @tparam Pred Unary template meta-program to convert.
  //! @return A Callable Object applying Pred to the type of its arguments
  //================================================================================================
  template<template<class> class Pred> [[nodiscard]] constexpr auto predicate() noexcept
  {
    return []<typename T>(T const&) constexpr { return Pred<T>::value; };
  }

  //================================================================================================
  //! @ingroup queries
  //! @brief  Checks if unary predicate p returns true for all elements in the tuple t.
  //! @param  t Tuple to process
  //! @param  p Unary predicate. p must return a value convertible to `bool` for every element of t.
  //! @return `true` if all elements of t satisfy p.
  //! ## Example:
  //! @include doc/all_of.cpp
  //================================================================================================
  template<typename Pred, product_type Tuple>
  [[nodiscard]] constexpr bool all_of( Tuple const& t, Pred p) noexcept
  {
    return kumi::apply( [&](auto const&... m) { return (p(m) && ... && true); }, t );
  }

  //================================================================================================
  //! @ingroup queries
  //! @brief  Checks if unary predicate p returns true for at least one element in the tuple t.
  //! @param  t Tuple to process
  //! @param  p Unary predicate. p must return a value convertible to `bool` for every element of t.
  //! @return `true` if at least one of elements of t satisfy p.
  //! ## Example:
  //! @include doc/any_of.cpp
  //================================================================================================
  template<typename Pred, product_type Tuple>
  [[nodiscard]] constexpr bool any_of( Tuple const& ts, Pred p) noexcept
  {
    return kumi::apply( [&](auto const&... m) { return (p(m) || ... || false); }, ts );
  }

  //================================================================================================
  //! @ingroup queries
  //! @brief  Checks if unary predicate p returns true for at no elements in the tuple t.
  //! @param  t Tuple to process
  //! @param  p Unary predicate. p must return a value convertible to `bool` for every element of t.
  //! @return `true` if at no elements of t satisfy p.
  //! ## Example:
  //! @include doc/none_of.cpp
  //================================================================================================
  template<typename Pred, product_type Tuple>
  [[nodiscard]] constexpr bool none_of( Tuple const& ts, Pred p) noexcept
  {
    return !any_of(ts,p);
  }

  //================================================================================================
  //! @ingroup queries
  //! @brief  Counts the number of elements of t satisfying predicates p.
  //! @param  t Tuple to process
  //! @param  p Unary predicate. p must return a value convertible to `bool` for every element of t.
  //! @return Number of elements satisfying the condition.
  //! ## Example:
  //! @include doc/count_if.cpp
  //================================================================================================
  template<typename Pred, product_type Tuple>
  [[nodiscard]] constexpr std::size_t count_if( Tuple const& ts, Pred p) noexcept
  {
    return kumi::apply( [&](auto const&... m) { return ( (p(m)? 1 : 0)+ ... + 0); }, ts );
  }

  //================================================================================================
  //! @ingroup queries
  //! @brief  Counts the number of elements of t not equivalent to false.
  //! @param  t Tuple to process
  //! @return Number of elements not equivalent to `false`.
  //! ## Example:
  //! @include doc/count.cpp
  //================================================================================================
  template<product_type Tuple>
  [[nodiscard]] constexpr std::size_t count( Tuple const& ts ) noexcept
  {
    return count_if(ts, [](auto const& m) { return static_cast<bool>(m); } );
  }

  //================================================================================================
  //! @ingroup queries
  //! @brief  Return the index of a value which type satisfies a given predicate
  //! @param  t Tuple to process
  //! @param  p Unary predicate. p must return a value convertible to `bool` for every element of t.
  //! @return Integral index of the element inside the tuple if present, kumi::size<tuple<T...>>::value
  //!         otherwise.
  //! ## Example:
  //! @include doc/locate.cpp
  //================================================================================================
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

  //================================================================================================
  namespace detail
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

  // MSVC chokes on the other code for empty calls
#if !defined(KUMI_DOXYGEN_INVOKED)
  [[nodiscard]] constexpr auto cartesian_product() { return kumi::tuple<>{}; }
#endif

  //================================================================================================
  //! @ingroup generators
  //! @brief  Return the Cartesian Product of all elements of its arguments product types
  //! @param  ts Tuples to process
  //! @return a tuple containing all the tuple build from all combination of all ts' elements
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi
  //! {
  //!   template<product_type... Tuples> struct cartesian_product;
  //!
  //!   template<product_type... Tuples>
  //!   using cartesian_product_t = typename cartesian_product<Tuples...>::type;
  //! }
  //! @endcode
  //!
  //! Computes the type returned by a call to kumi::cartesian_product.
  //!
  //! ## Example:
  //! @include doc/cartesian_product.cpp
  //================================================================================================
  template<product_type... Ts>
  [[nodiscard]] constexpr auto cartesian_product(Ts&&... ts)
  {
    auto maps = [&]<std::size_t... I>(auto k, std::index_sequence<I...>)
    {
      constexpr auto dg = detail::digits<sizeof...(Ts),kumi::size_v<Ts>...>(k);
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

  //================================================================================================
  namespace detail
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

  //================================================================================================
  //! @ingroup utility
  //! @brief Generate a kumi::tuple type from a kumi::product_type
  //!
  //! Compute the exact kumi::tuple type containing the same element as `Tuple`, an arbitrary type
  //! modeling kumi::product_type. A template meta-function can be optionally passed to be applied
  //! to each of those types when types are computed.
  //!
  //! @tparam Tuple kumi::product_type to tranform
  //! @tparam Meta  Unary template meta-function to apply to each types.
  //!               Defaults to `std::type_identity`
  //!
  //! ## Helper type
  //! @code
  //! namespace kumi
  //! {
  //!   template<product_type Tuple, template<typename...> class Meta = std::type_identity>
  //!   using as_tuple_t = typename as_tuple<Tuple, Meta>::type;
  //! }
  //! @endcode
  //!
  //! ## Example:
  //! @include doc/as_tuple.cpp
  //================================================================================================
  template<typename Tuple, template<typename...> class Meta = std::type_identity>
  struct as_tuple : detail::as_tuple< Tuple
                                    , std::make_index_sequence<kumi::size<Tuple>::value>
                                    , Meta
                                    >
  {};

  template<product_type Tuple, template<typename...> class Meta = std::type_identity>
  using as_tuple_t =  typename as_tuple<Tuple, Meta>::type;
}

#undef KUMI_FWD
#endif
