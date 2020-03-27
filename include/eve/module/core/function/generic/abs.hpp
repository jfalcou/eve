//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/minus.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T abs_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept
  {
    using t_abi = abi_type_t<T>;
    if constexpr(native<t_abi> || scalar_value<T>)
    {
           if constexpr(floating_value<T>              ) return bit_andnot(a, Mzero(as(a)));
      else if constexpr(unsigned_value<T>              ) return a;
      else if constexpr(signed_integral_scalar_value<T>) return a < T(0) ? -a : a;
      else if constexpr(signed_integral_simd_value<T>  ) return eve::max(a, -a);
    }
    else                                                 return apply_over(abs, a); 
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr T abs_(EVE_SUPPORTS(cpu_)
                                  , saturated_type const &
                                  , T const &a) noexcept
  {
    if constexpr(signed_integral_scalar_value<T>)
    {
      return ((a == Valmin(as(a))) ? Valmax(as(a)) : eve::abs(a));
    }
    else if constexpr(signed_integral_simd_value<T>)
    {
      using t_abi = abi_type_t<T>;
      if constexpr(native<t_abi>) return if_else(a == Valmin(as(a)), Valmax(as(a)), eve::abs(a));
      else                        return apply_over(saturated_(abs), a); 
    }
    else if constexpr(floating_value<T> || unsigned_value<T>)
    {
      return eve::abs(a);
    }
  }
}

#endif

