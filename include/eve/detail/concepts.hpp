//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>

#include <concepts>

#if defined(SPY_STDLIB_IS_LIBCPP)
#include <type_traits>
#include <functional>
namespace std
{
  template<typename T> concept floating_point          = std::is_floating_point_v<T>;
  template<typename T> concept integral                = std::is_integral_v<T>;
  template<typename T> concept unsigned_integral       = std::is_unsigned_v<T>;
  template<typename T> concept signed_integral         = std::is_signed_v<T> && std::is_integral_v<T>;

  template<typename F, typename... Ts>
  concept invocable = requires(F&& f, Ts&&...ts)
                      { std::invoke(std::forward<F>(f), std::forward<Ts>(ts)...); };

  template<typename From, typename To>
  concept convertible_to  =   std::is_convertible_v<From, To>
                          &&  requires(std::add_rvalue_reference_t<From> (&f)())
                              { static_cast<To>(f()); };

  template< class Derived, class Base >
  concept derived_from  = std::is_base_of_v<Base, Derived> &&
                          std::is_convertible_v<const volatile Derived*, const volatile Base*>;

  // -----------------------------------------------------------------------------------------------
  // Plumbing for input_iterator concept
  template<typename I> struct indirectly_readable_traits { };

  template<typename T>
  struct indirectly_readable_traits<T*> { using value_type = std::remove_cv_t<T>; };

  template<typename T> requires std::is_array_v<T>
  struct indirectly_readable_traits<T>
  {
    using value_type = std::remove_cv_t<std::remove_extent_t<T>>;
  };

  template<typename T >
  struct indirectly_readable_traits<const T> : indirectly_readable_traits<T>
  {};

  template<typename T> requires requires { typename T::value_type; }
  struct indirectly_readable_traits<T>
  {
    using value_type = typename T::value_type;
  };

  template<typename T >
  using iter_reference_t = decltype(*std::declval<T&>());

  template<typename I> struct incrementable_traits {};

  template<typename T> requires std::is_object_v<T>
  struct incrementable_traits<T*>
  {
    using difference_type = std::ptrdiff_t;
  };

  template<typename T>
  struct incrementable_traits<const T> : incrementable_traits<T>
  {};

  template<typename T> requires requires { typename T::difference_type; }
  struct incrementable_traits<T>
  {
    using difference_type = typename T::difference_type;
  };

  template<typename I>
  concept input_iterator = requires(I i)
  {
    // Requires c++20 stdc++
    typename std::incrementable_traits<I>::difference_type;
    typename std::indirectly_readable_traits<I>::value_type;
    requires std::signed_integral<typename std::incrementable_traits<I>::difference_type>;

    // typename std::common_reference_t< std::iter_reference_t<I>&&
    //                                 , typename std::indirectly_readable_traits<I>::value_type&
    //                                 >;

    { *i++ };

    // typename std::common_reference_t< decltype(*i++)&&
    //                                 , typename std::indirectly_readable_traits<I>::value_type&
    //                                 >;
  };
}

#endif

