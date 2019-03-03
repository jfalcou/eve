//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_LOGICAL_NOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_not.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/constant/zero.hpp>
#include <eve/as_logical.hpp>
#include <eve/logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(simd_),wide<T, N, ABI> const &v) noexcept
  {
    if constexpr( is_native_v<ABI> )
    {
      return eve::is_equal(v, as(v));
    }
    else
    {
      if( std::is_same_v<ABI,aggregated_>)  return aggregate(eve::logical_not, v);
      if( std::is_same_v<ABI,emulated_> )   return map(eve::logical_not, v);
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(simd_), logical<wide<T, N, ABI>> const &v) noexcept
  {
    if constexpr( is_native_v<ABI> )
    {
      using t_t = wide<T, N, ABI>;
      return eve::bitwise_cast<as_logical_t<t_t>>(eve::bitwise_not(eve::bitwise_cast<t_t>(v)));
    }
    else
    {
      if( std::is_same_v<ABI,aggregated_> ) return aggregate(eve::logical_not, v);
      if( std::is_same_v<ABI,emulated_> )   return map(eve::logical_not, v);
    }
  }
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator!(wide<T, N, ABI> const &v) noexcept
  {
    return eve::logical_not(v);
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator!(logical<wide<T, N, ABI>> const &v) noexcept
  {
    return eve::logical_not(v);
  }
}

#endif
