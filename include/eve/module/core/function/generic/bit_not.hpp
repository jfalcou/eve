//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_BIT_NOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/detail/branch.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{

  template<real_value T>
  EVE_FORCEINLINE auto bit_not_(EVE_SUPPORTS(cpu_)
                               , T const &v) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(scalar_value<T> && integral_value<T>) return T(~v); 
      else                                               return eve::bit_xor(v, Allbits(as(v)));
    }
    else return apply_over(bit_not, v); 
  }

  template<value COND, real_value T>
  EVE_FORCEINLINE auto bit_not_(EVE_SUPPORTS(cpu_)
                               ,  COND const & cond 
                               , T const &v) noexcept
  {
    if constexpr(native<T>) return branch<scalar_value<COND>>(cond, bit_not)(v); 
    else                    return apply_over(bit_not, v); 
  }  
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<real_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto operator~(wide<T, N, ABI> const &v) noexcept
  -> decltype(bit_not(v))
  {
    return bit_not(v); 
  }
}

#endif
