//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ATAN2D_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ATAN2D_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/indeg.hpp>
#include <eve/function/atan2.hpp>
#include <eve/function/pedantic.hpp>


namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto atan2d_( EVE_SUPPORTS(cpu_)
                              , T const &a
                              , U const &b
                              ) noexcept
  {
    return arithmetic_call(atan2d, a, b);
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto atan2d_( EVE_SUPPORTS(cpu_)
                              , pedantic_type const &
                              , T const &a
                              , U const &b
                              ) noexcept
  {
    return arithmetic_call(pedantic_(atan2d), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto atan2d_( EVE_SUPPORTS(cpu_)
                              , T const &a
                              , T const &b
                              ) noexcept
  {
    return indeg(atan2(a, b));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto atan2d_( EVE_SUPPORTS(cpu_)
                              , pedantic_type const &
                              , T const &a
                              , T const &b
                              ) noexcept
  {
    return indeg(pedantic_(atan2)(a, b));
  }

}

#endif
