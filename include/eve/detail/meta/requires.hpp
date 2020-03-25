//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_META_REQUIRES_HPP_INCLUDED
#define EVE_DETAIL_META_REQUIRES_HPP_INCLUDED

#include <type_traits>

namespace eve::detail
{
  // Recurrent pseudo-concept checkers
  template<typename R, typename Enabler>
  struct require_impl;

  template<typename R>
  struct require_impl<R, void>
  {
    using type = R;
  };

  template<typename Return, typename... Ts>
  struct require_check : require_impl<Return, std::void_t< Ts...>>
  {
  };
}

// Pseudo require macro
#define Requires(...)->typename ::eve::detail::require_check < __VA_ARGS__> ::type

#endif
