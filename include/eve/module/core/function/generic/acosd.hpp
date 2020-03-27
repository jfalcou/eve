//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ACOSD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ACOSD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/indeg.hpp>
#include <eve/function/acos.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acosd_(EVE_SUPPORTS(cpu_)
                                       , T const &a0) noexcept
  {
    return indeg(eve::acos(a0));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acosd_ ( EVE_SUPPORTS(cpu_)
                                        , raw_type const &, T const &a0
                                        ) noexcept
  {
    return indeg(eve::raw_(eve::acos)(a0));
  }
}

#endif
