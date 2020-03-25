//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_STORE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/arch/limits.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(vmx_),
                              wide<T, N, ppc_> const &value,
                              T *                     ptr) noexcept Requires(void, Vectorizable<T>)
  {
    if constexpr(N::value * sizeof(T) == limits<vmx_>::bytes)
    {
      if constexpr(current_api == eve::vmx)
      { *((typename wide<T, N, ppc_>::storage_type *)(ptr)) = value; }
      else if constexpr(current_api == eve::vsx)
      {
        // 64bits integrals are not supported by vec_vsx_st on some compilers
        if constexpr(sizeof(T) == 8 && std::is_integral_v<T>)
        { vec_vsx_st((__vector double)(value.storage()), 0, (double *)(ptr)); }
        else
        {
          vec_vsx_st(value.storage(), 0, ptr);
        }
      }
    }
    else
      apply<N::value>([&](auto... I) { ((*ptr++ = value[ I ]), ...); });
  }

  template<typename T, typename S, std::size_t N>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(vmx_),
                              wide<T, S, ppc_> const &value,
                              aligned_ptr<T, N>       ptr) noexcept Requires(void, Vectorizable<T>)
  {
    if constexpr((N >= limits<vmx_>::bytes) && current_api == eve::vmx)
    { vec_st(value.storage(), 0, ptr.get()); }
    else
    {
      store(value, ptr.get());
    }
  }
}

#endif
