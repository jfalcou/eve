//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_SIMD_PPC_VMX_LOAD_HPP_INCLUDED
#define EVE_FUNCTION_SIMD_PPC_VMX_LOAD_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve { namespace detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto load(as_<pack<T,N>> const&, eve::ppc_ const&, T* ptr) noexcept
  {
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated"
    return vec_perm(vec_ld(0, ptr), vec_ld(16, ptr), vec_lvsl(0, ptr));
    #pragma GCC diagnostic pop
  }
} }

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
