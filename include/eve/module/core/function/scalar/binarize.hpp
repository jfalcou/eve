//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BINARIZE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BINARIZE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

namespace eve::detail
{
  
  template<typename U>
  EVE_FORCEINLINE constexpr auto binarize_(EVE_SUPPORTS(cpu_),
                                           logical<U> const & cond) noexcept
  requires(U, Vectorizable<U>)
  {
    return  bitwise_and(U(1), cond.bits()); 
  }
  
  template<typename T,  typename U>
  EVE_FORCEINLINE constexpr auto binarize_(EVE_SUPPORTS(cpu_),
                                           logical<U> const & cond,
                                           T const &a0) noexcept
  requires(T, Vectorizable<T>,  Vectorizable<U>)
  {
    return bitwise_and(U(a0), cond.bits());
  }

  template<typename U>
  EVE_FORCEINLINE constexpr auto binarize_(EVE_SUPPORTS(cpu_)
                                          , logical<U> const & cond
                                          , eve::callable_allbits_ const & ) noexcept
  requires(U, Vectorizable<U>)
  {
    return  bitwise_cast<U>(cond.bits());
  }
  
  template<typename U>
  EVE_FORCEINLINE constexpr auto binarize_(EVE_SUPPORTS(cpu_)
                                          , logical<U> const & cond
                                          , eve::callable_mone_ const & ) noexcept
  requires(U, Vectorizable<U>)
  {
    if constexpr(std::is_integral_v<U>) 
      return bitwise_cast<U>(cond.bits());
    else
      return binarize(cond, U(-1));
  }
}

#endif
