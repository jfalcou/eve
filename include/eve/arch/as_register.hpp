//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/arch/spec.hpp>

#include <eve/arch/cpu/as_register.hpp>

#if !defined(EVE_NO_SIMD)
#  if defined(EVE_INCLUDE_X86_HEADER)
#    include <eve/arch/x86/as_register.hpp>
#  elif defined(EVE_INCLUDE_POWERPC_HEADER)
#    include <eve/arch/ppc/as_register.hpp>
#  elif defined(EVE_INCLUDE_ARM_SVE_HEADER)
#    include <eve/arch/arm/sve/as_register.hpp>
#  elif defined(EVE_INCLUDE_ARM_NEON_HEADER)
#    include <eve/arch/arm/neon/as_register.hpp>
#  elif defined(EVE_INCLUDE_RISCV_HEADER)
#    include <eve/arch/riscv/as_register.hpp>
#  endif
#endif

namespace eve
{
  template<typename T, typename N, typename ABI>
  consteval auto as_register(as<T> t, N n, ABI abi)
  {
    using found_type = decltype(find_register_type(t, n, abi));
    static_assert(!std::same_as<found_type, void>, "[EVE] - Type is not usable in a SIMD register");

    return found_type{};
  }

  template<typename T, typename N, typename ABI>
  using as_register_t = decltype(as_register(as<T>{}, N{}, ABI{}));

  template<typename T, typename N, typename ABI>
  consteval auto as_logical_register(as<T> t, N n, ABI abi)
  {
    using found_type = decltype(find_logical_register_type(t, n, abi));
    static_assert(!std::same_as<found_type, void>
                  , "[EVE] - Type is not usable in a SIMD register");

    return found_type{};
  }

  template<typename T, typename N, typename ABI>
  using as_logical_register_t = decltype(as_logical_register(as<T>{}, N{}, ABI{}));
}
