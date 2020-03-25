//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_COMBINE_HPP_INCLUDED
#define EVE_FUNCTION_COMBINE_HPP_INCLUDED

#include <eve/function/definition/combine.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto combine_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  {
    return wide<T, fixed<2>>(a, b);
  }

  template<typename T>
  EVE_FORCEINLINE auto
  combine_(EVE_SUPPORTS(cpu_), logical<T> const &a, logical<T> const &b) noexcept
  requires( logical<wide<T, fixed<2>>>, vectorizable<T> )
  {
    return logical<wide<T, fixed<2>>>(a, b);
  }

  ///////////////////////////////////////////////////////////////////////////////////
  //SIMD
  
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  combine_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &a, wide<T, N, ABI> const &b) noexcept
  {
    return wide<T, typename N::combined_type>{a, b};
  }

  //------------------------------------------------------------------------------------------------
  // Logical
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto combine_(EVE_SUPPORTS(cpu_),
                                logical<wide<T, N, ABI>> const &l,
                                logical<wide<T, N, ABI>> const &h) noexcept
  {
    return logical<wide<T, typename N::combined_type>>(l, h);
  }
}

#endif
