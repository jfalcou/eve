//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VMX_STORE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/arch/limits.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(vmx_),
                              wide<T, N, ppc_> const &value,
                              T *                     ptr) noexcept requires(void, Arithmetic<T>)
  {
    if constexpr(N::value * sizeof(T) == limits<vmx_>::bytes)
      *((typename wide<T, N, ppc_>::storage_type *)(ptr)) = value;
    else
      apply<N::value>([&](auto... I) { ((*ptr++ = value[ I ]), ...); });
  }

  template<typename T, typename S, std::size_t N>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(vmx_),
                              wide<T, S, ppc_> const &value,
                              aligned_ptr<T, N>       ptr) noexcept requires(void, Arithmetic<T>)
  {
    if constexpr(N >= limits<vmx_>::bytes)
      vec_st(value.storage(), 0, ptr.get());
    else
      store(value, ptr.get());
  }
}

#endif
