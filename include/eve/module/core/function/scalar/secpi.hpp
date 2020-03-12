//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SECPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SECPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/detail/scalar/cos_finalize.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_even.hpp>
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
  EVE_FORCEINLINE constexpr auto secpi_(EVE_SUPPORTS(cpu_)
                                     , restricted_type const &
                                     , T a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto x = abs(a0); 
      if (is_not_less_equal(x, T(0.25))) return Nan<T>();
      a0 *= Pi<T>(); 
      auto x2 = sqr(a0);
      return rec(detail::cos_eval(x2));
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
    }   
  }

  template<typename T, typename TAG>
  EVE_FORCEINLINE constexpr auto secpi_(EVE_SUPPORTS(cpu_)
                                     , TAG const & tag
                                     , T const &a0) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(eve::is_trigonometric_tag_v<TAG>)
    {
      const T x =  abs(a0);
      if (is_not_finite(x))  return Nan<T>(); 
      if (x > Maxflint<T>()) return T(1);
      T fn = nearest(x*T(2));
      T xx = fma(fn, Mhalf<T>(), x); 
      T xr = xx*Pi<T>();
      T z = cos_finalize(quadrant(fn), xr, T(0));
      return (z) ? rec(cos_finalize(quadrant(fn), xr, T(0))) : Nan<T>() ;
    }
    else
    {
      static_assert(eve::is_trigonometric_tag_v<TAG>, "[tagged secpi ]: Used tag is unsupported"); 
    }
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto secpi_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  requires(T, vectorizable<T>)
  {
    return big_(eve::secpi)(a0); 
  }

}

#endif
