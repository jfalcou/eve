//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/abs.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/forward.hpp>
#include <eve/assert.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto rec_(EVE_SUPPORTS(cpu_)
                           , wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
    {
      return aggregate(eve::rec, v);
    }
    else if  constexpr(is_emulated_v<ABI>)
    {
      return map(eve::rec, v);
    }
    else
    {
      if constexpr(std::is_floating_point_v<T>)
      {
        // Change to 1/v;
        return map(eve::rec, v);
      }
      else
      {
        if constexpr(std::is_unsigned_v<T>)
        {
          return if_else(v == One(as(v)), v, eve::zero_);
        }
        else
        {
          return if_else(eve::abs(v) == One(as(v)), v, eve::zero_);
        }
      }
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto rec_(EVE_SUPPORTS(cpu_)
                           , raw_type const&
                           , wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
    {
      return aggregate(raw_(eve::rec), v);
    }
    else if  constexpr(is_emulated_v<ABI>)
    {
      return map(raw_(eve::rec), v);
    }
    else
    {
      if constexpr(std::is_floating_point_v<T>)
      {
        // Change to 1/v;
        return map(raw_(eve::rec), v);
      }
      else
      {
        return rec(v);
      }
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto rec_ ( EVE_SUPPORTS(cpu_),
                              pedantic_type const&,
                              wide<T, N, ABI> const &v
                            ) noexcept
  {
    if constexpr(is_aggregated_v<ABI>)
    {
      return aggregate(eve::pedantic_(eve::rec), v);
    }
    else if  constexpr(is_emulated_v<ABI>)
    {
      return map(eve::pedantic_(eve::rec), v);
    }
    else
    {
      if constexpr(std::is_floating_point_v<T>)
      {
        // Change to 1/v;
        return map(eve::pedantic_(eve::rec), v);
      }
      else
      {
        if constexpr(std::is_unsigned_v<T>)
        {
          return if_else( is_eqz(v), eve::allbits_, eve::rec(v) );
        }
        else
        {
          return if_else( is_eqz(v), eve::Valmax(as(v)), eve::rec(v) );
        }
      }
    }
  }
}

#endif
