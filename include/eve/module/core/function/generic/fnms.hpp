//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/add.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/numeric.hpp>
#include <eve/function/pedantic.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto fnms_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &c) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(fnms, a, b, c);
  }

  template<real_value T>
  EVE_FORCEINLINE T fnms_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &c) noexcept
      requires has_native_abi_v<T>
  {
    return -fma(a, b, c);
  }

  template<real_value T, real_value U, real_value V, decorator D>
  EVE_FORCEINLINE auto
  fnms_(EVE_SUPPORTS(cpu_), D const &, T const &a, U const &b, V const &c) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(D()(fnms), a, b, c);
  }

  template<real_value T, decorator D>
  EVE_FORCEINLINE T
  fnms_(EVE_SUPPORTS(cpu_), D const &, T const &a, T const &b, T const &c) noexcept
      requires has_native_abi_v<T>
  {
    return -D()(fma)(a, b, c);
  }
}

