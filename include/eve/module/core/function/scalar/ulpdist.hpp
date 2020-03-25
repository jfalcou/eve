//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ULPDIST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ULPDIST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <eve/function/is_equal.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/constant/nan.hpp>
#include <eve/concept/vectorizable.hpp>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  ulpdist_(EVE_SUPPORTS(cpu_)
          , T const &a
          , T const &b ) noexcept
  Requires(T, Vectorizable<T>)
  {
    if (numeric_(is_equal)(a, b)) return T(0);
    if (is_unordered(a, b)) return Nan<T>(); 
    return nb_values(a , b )/2.0;
  }
}

#endif
