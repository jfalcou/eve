//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/forward.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/abs.hpp>
//#include <eve/function/div.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_equal.hpp>
#include <type_traits>
#include <cassert>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto rec_(EVE_SUPPORTS(simd_),
                            wide<T, N, ABI> const &v) noexcept requires(wide<T, N, ABI>,
                                                                        Arithmetic<T>)
  {
    using t_t = wide<T, N, ABI>;
    if constexpr(std::is_floating_point_v<T>)
    {
      return v; //TODO map(div, One<t_t>(), v); 
    }
    if constexpr(std::is_integral_v<T> && std::is_unsigned_v<T>)
      return if_else(v, if_else(v == One<t_t>(), One<t_t>(), Zero<t_t>()), Allbits<t_t>());
    
    if constexpr(std::is_integral_v<T> && std::is_signed_v<T>)
      return if_else(v, if_else(eve::abs(v) == One<t_t>(), v, Zero<t_t>()), Valmax<t_t>());
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, aggregated_> rec_(EVE_SUPPORTS(simd_),
                                               wide<T, N, aggregated_> const &v) noexcept
  {
    return aggregate(eve::rec, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation
  template<typename T, typename N>
  EVE_FORCEINLINE auto rec_(EVE_SUPPORTS(simd_)
                           , wide<T, N, emulated_> const &v) noexcept
  {
    return map(eve::rec, v);
    ;
  }

    template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto rec_(EVE_SUPPORTS(simd_)
                           , raw_type const &
                           , wide<T, N, ABI> const &v) noexcept requires(wide<T, N, ABI>,
                                                                        Arithmetic<T>)
    {
      return rec(v); 
    }
  
}

#endif
