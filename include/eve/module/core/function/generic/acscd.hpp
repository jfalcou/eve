//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ACSCD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ACSCD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/acsc.hpp>
#include <eve/function/indeg.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acscd_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept
  {
    if constexpr(native<T>) return indeg(acsc(a));
    else                    return apply_over(acscd, a);
  }

}

#endif
