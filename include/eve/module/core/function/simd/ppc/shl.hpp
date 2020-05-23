//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_SHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_SHL_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename I>
  EVE_FORCEINLINE wide<T, N, ppc_>
  shl_(EVE_SUPPORTS(vmx_),
       wide<T, N, ppc_> const &v0,
       wide<I, N, ppc_> const &v1) noexcept
  {
    using t_t = wide<T, N, ppc_>;
    using i_t = wide<as_integer_t<T, unsigned>, N>;
    return t_t(vec_sl(v0.storage(), bit_cast(v1,as_<i_t>()).storage()));
  }

  template<typename T, typename N, typename I>
  EVE_FORCEINLINE wide<T, N, ppc_> shl_(EVE_SUPPORTS(vmx_),
                            wide<T, N, ppc_> const &v0,
                            I v1) noexcept
  {
    using i_t = wide<as_integer_t<T, unsigned>, N>;
    return eve::shl(v0, i_t(v1));
  }
}

#endif
