//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_NEGATENZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_NEGATENZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/signnz.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  negatenz_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_signed_v<T>)
      return a0*signnz(a1);
    else
      return a0;
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  negatenz_(EVE_SUPPORTS(cpu_)
           , pedantic_type const &
           , T const &a0, T const &a1) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_signed_v<T>)
      return a0*pedantic_(signnz)(a1);
    else
      return a0;
  }
}

#endif
