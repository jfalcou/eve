//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/ppc/predef.hpp>
#include <concepts>
#include <cstddef>

namespace eve::_
{
  // ---------------------------------------------------------------------------------------------
  // PPC
  template<typename T, std::size_t Size> extern no_register<void> ppc_register;

  template<std::size_t S> extern __vector float ppc_register<float, S>;

  template<std::size_t S> requires(spy::simd_instruction_set >= spy::vsx_)
  extern __vector double ppc_register<double, S>;

  template<std::signed_integral T> extern __vector signed char  ppc_register<T, 1>;
  template<std::signed_integral T> extern __vector signed short ppc_register<T, 2>;
  template<std::signed_integral T> extern __vector signed int   ppc_register<T, 4>;
  template<std::signed_integral T> requires(spy::simd_instruction_set >= spy::vsx_)
  extern __vector signed long ppc_register<T, 8>;

  template<std::unsigned_integral T> extern __vector unsigned char  ppc_register<T, 1>;
  template<std::unsigned_integral T> extern __vector unsigned short ppc_register<T, 2>;
  template<std::unsigned_integral T> extern __vector unsigned int   ppc_register<T, 4>;
  template<std::unsigned_integral T> requires(spy::simd_instruction_set >= spy::vsx_)
  extern __vector unsigned long ppc_register<T, 8>;

  // ---------------------------------------------------------------------------------------------
  // PPC
  template<typename T, std::size_t Size> extern no_register<void> ppc_logical_register;

  template<std::size_t S> extern __vector __bool int ppc_logical_register<float, S>;

  template<std::size_t S> requires(spy::simd_instruction_set >= spy::vsx_)
  extern __vector __bool long ppc_logical_register<double, S>;

  template<std::integral T> extern __vector __bool char  ppc_logical_register<T, 1>;
  template<std::integral T> extern __vector __bool short ppc_logical_register<T, 2>;
  template<std::integral T> extern __vector __bool int   ppc_logical_register<T, 4>;
  template<std::integral T> requires(spy::simd_instruction_set >= spy::vsx_)
  extern __vector __bool long ppc_logical_register<T, 8>;

  // ---------------------------------------------------------------------------------------------
  template<typename T, width_type N> requires(N <= 16 / sizeof(T))
  extern decltype(ppc_register<T, sizeof(T)>) as_register<T, N, eve::ppc_>;

  template<typename T, width_type N> requires(N <= 16 / sizeof(T))
  extern decltype(ppc_logical_register<T, sizeof(T)>) as_logical_register<T, N, eve::ppc_>;
}