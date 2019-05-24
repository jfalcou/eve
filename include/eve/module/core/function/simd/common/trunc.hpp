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
#include <cassert>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto trunc_(EVE_SUPPORTS(simd_),
                            wide<T, N, ABI> const &v) noexcept
  requires(wide<T, N, ABI>, Arithmetic<T>)
  {
    if constexpr( is_native_v<ABI> )
    {
      if constexpr(std::is_floating_point_v<T>)
        // TODO replace the map as soon wide_cast is available
        //       return if_else(eve::abs(a0) < Maxflint(as(v));,  trunc[raw_](v),  a0);
        return map(eve::trunc, v); 
      else  return v;
    }
    else
    {
      if constexpr( is_aggregated_v<ABI> ) return aggregate(eve::trunc, v);
      if constexpr( is_emulated_v<ABI>   ) return map(eve::trunc, v);
    }
  }
}

// TODO uncomment when wide_cast available
//   template<typename T, typename N, typename ABI>
//   EVE_FORCEINLINE auto trunc_(EVE_SUPPORTS(simd_)
//                              , raw_type const &
//                              , wide<T, N, ABI> const &v) noexcept
//   requires(wide<T, N, ABI>, Arithmetic<T>)
//   {
//     if constexpr( is_native_v<ABI> )
//     {
//       using i_t = as_integer_t<T>; 
//       if constexpr(std::is_floating_point_v<T>) return wide_cast[as(T)](wide_cast[as(i_t)](v)); 
//       else  return v;
//     }
//     else
//     {
//       if constexpr( is_aggregated_v<ABI> ) return aggregate(eve::trunc, v);
//       if constexpr( is_emulated_v<ABI>   ) return map(eve::trunc, v);
//     }
//   }
//}
#endif
