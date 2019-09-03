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
//#include <eve/function/wide_cast.hpp>
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
      return map(eve::trunc, v);
    // TODO replace the map as soon wide_cast is available
    //       return if_else(eve::abs(a0) < Maxflint(as(v));,  eve::raw_(trunc)(v),  a0);
    else
      return v;
  }
}

// TODO uncomment when wide_cast available
//   template<typename T, typename N, typename ABI>
//   EVE_FORCEINLINE auto trunc_(EVE_SUPPORTS(cpu_)
//                              , raw_type const & raw
//                              , wide<T, N, ABI> const &v) noexcept
//   {
//     if constexpr( is_aggregated_v<ABI> )              return aggregate(eve::trunc, raw_, v);
//     else if constexpr( is_emulated_v<ABI>)           return map(eve::trunc, raw_, v);
//     else if constexpr( is_floating_point_v<T> )
//     {
//       using i_t = as_integer_t<T>;
//       return wide_cast[as(T)](wide_cast[as(i_t)](v));
//     }
//     else return v;
//   }
//}
#endif
