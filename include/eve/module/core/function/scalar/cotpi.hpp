//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_COTPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_COTPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/detail/scalar/cot_finalize.hpp>
#include <eve/module/core/detail/generic/rem2.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/mhalf.hpp>
#include <type_traits>

namespace eve::detail
{

  
  template<typename T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , T a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if (is_eqz(a0)) return rec(a0); 
      auto x = abs(a0); 
      if (is_not_less_equal(x, T(0.25))) return Nan<T>();
      a0 *= Pi<T>(); 
      return rec(tancot_eval(a0));
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
    }   
  }

  template<typename T, typename TAG>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_)
                                     , TAG const & tag
                                     , T const &a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(eve::is_trigonometric_tag_v<TAG>)
    {
      if (is_eqz(a0)) return rec(a0); 
      if (is_not_finite(a0)||is_flint(a0)) return Nan<T>();
      const T x =  abs(a0);
      auto [fn, xr, dxr] =  rem2(x); 
      return cot_finalize(a0*Pi<T>(), quadrant(fn), xr, dxr); 
    }
    else
    {
      static_assert(eve::is_trigonometric_tag_v<TAG>, "[tagged cotpi ]: Used tag is unsupported"); 
    }
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  requires(T, vectorizable<T>)
  {
    return big_(eve::cotpi)(a0); 
  }

}

#endif
