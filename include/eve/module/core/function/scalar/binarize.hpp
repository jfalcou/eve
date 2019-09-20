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

namespace eve::detail
{
  template<typename T,  typename COND>
  EVE_FORCEINLINE constexpr auto binarize_(EVE_SUPPORTS(cpu_),
                                           COND const & cond,
                                           T const &a0) noexcept
  requires(T, Vectorizable<T>,  Vectorizable<COND)
  {
    return bitwise_cast<T>(cond)&a0; 
  }

  template<typename COND>
  EVE_FORCEINLINE constexpr auto binarize_(EVE_SUPPORTS(cpu_),
                                           COND const & cond) noexcept
  requires(bool, Vectorizable<COND>)
  {
    return cond; 
  }

  
}

#endif
