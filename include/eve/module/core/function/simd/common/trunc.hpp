//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_TRUNC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_TRUNC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/toint.hpp>
#include <eve/function/tofloat.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto trunc_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
      return aggregate(eve::trunc, v);
    else if constexpr(is_emulated_v<ABI>)
      return map(eve::trunc, v);
    else if constexpr(std::is_floating_point_v<T>)
      return if_else(eve::abs(v) < Maxflint(as(v)),  eve::raw_(trunc)(v),  v);
    else
      return v;
  }
  
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto trunc_(EVE_SUPPORTS(cpu_)
                             , raw_type const & raw
                             , wide<T, N, ABI> const &v) noexcept
  {
    if constexpr( is_aggregated_v<ABI> ) return aggregate(eve::trunc, raw_, v);
    else if constexpr( is_emulated_v<ABI>) return map(eve::trunc, raw_, v);
    else if constexpr( std::is_floating_point_v<T> )  return tofloat(toint(v));
    else return v;
  }
}

#endif
