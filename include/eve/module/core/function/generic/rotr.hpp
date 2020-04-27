//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ROTR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ROTR_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/rotl.hpp>

namespace eve::detail
{
  template<integral_value T, integral_value U>
  EVE_FORCEINLINE  auto rotr_(EVE_SUPPORTS(cpu_)
                            , T const &a0
                            , U const &n) noexcept
  requires (contains<D>(types<regular_type, pedantic_type> {}))
  {
    return D()(rotl)(a0, U(-n));
  }

}

#endif
