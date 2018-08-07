//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VSX_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VSX_STORE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/arch/limits.hpp>
#include <eve/forward.hpp>

namespace eve { namespace detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(vsx_)
                              , pack<T,N,ppc_> const& value, T* ptr
                              ) noexcept
  {
    if constexpr(N::value*sizeof(T) == limits<vmx_>::bytes)
    {
      // 64bits integrals are not supported by vec_vsx_st on some compilers
      if constexpr(sizeof(T) == 8 && std::is_integral_v<T>)
        vec_vsx_st( (__vector double)(value.storage()), 0, (double*)(ptr));
      else
        vec_vsx_st(value.storage(), 0, ptr);
    }
    else
      apply<N::value>( [&](auto... I) { ((*ptr++ = value[I]), ...); } );
  }

  template<typename T, typename S, std::size_t N>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(vsx_)
                              , pack<T,S,ppc_> const& value, aligned_ptr<T,N> ptr
                              ) noexcept
  {
    store(value,ptr.get());
  }
} }

#endif
