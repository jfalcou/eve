//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_SATURATE_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_SATURATE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(saturate_, saturate);

  template<typename Target, typename Arg>
  EVE_FORCEINLINE constexpr Arg saturate(Arg const &a0) noexcept
  {
    return saturate_(a0, as_<Target>{});
  }
}

#endif
