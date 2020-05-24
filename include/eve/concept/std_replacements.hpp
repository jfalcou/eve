//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONCEPT_STD_REPLACEMENTS_HPP_INCLUDED
#define EVE_CONCEPT_STD_REPLACEMENTS_HPP_INCLUDED

#include <concepts>
#include <iterator>
#include <type_traits>

namespace eve
{
  template<typename T> concept integral              = std::is_integral_v<T>;
  template<typename T> concept signed_integral       = integral<T> && std::is_signed_v<T>;
  template<typename T> concept unsigned_integral     = integral<T> && !std::is_signed_v<T>;
  template<typename T> concept floating_point        = std::is_floating_point_v<T>;
  template <class From, class To> concept convertible_to =
    std::is_convertible_v<From, To> &&
    requires(std::add_rvalue_reference_t<From> (&f)()) {
      static_cast<To>(f());
    };

  template<typename Derived, typename Base>
  concept derived_from =
    std::is_base_of_v<Base, Derived> &&
    std::is_convertible_v<const volatile Derived*, const volatile Base*>;

  template <typename I>
  concept input_iterator =
     requires { typename std::iterator_traits<I>::iterator_category; } &&
     derived_from<typename std::iterator_traits<I>::iterator_category, std::input_iterator_tag>;

  template< class F, class... Args >
  concept invocable =
  requires(F&& f, Args&&... args) {
      std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
      /* not required to be equality preserving */
  };

}

#endif
