//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_EXTRACT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_EXTRACT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto extract_ ( EVE_SUPPORTS(simd_),
                                  wide<T, N, ABI> const &v0,
                                  U const& u) noexcept
  {
    return v0[ u ];
  }
  
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto extract_ ( EVE_SUPPORTS(simd_),
                                  logical<wide<T, N, ABI>> const &v0,
                                  U const& u) noexcept
  {
    {
      return logical<T>( extract( v0.bits(), u) );
    }
  }
}

#endif
  
