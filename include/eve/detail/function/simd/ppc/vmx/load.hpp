//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_PPC_VMX_LOAD_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_PPC_VMX_LOAD_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#pragma GCC diagnostic ignored "-Wdeprecated"
#endif

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto  load( as_<wide<T,N>> const&, eve::ppc_ const&, T* ptr) noexcept
                        requires( typename wide<T,N>::storage_type
                                , Arithmetic<T>, If<(sizeof(T)<8)>
                                )
  {
    return vec_perm(vec_ld(0, ptr), vec_ld(16, ptr), vec_lvsl(0, ptr));
  }

  template<typename T, typename N, std::size_t Align>
  EVE_FORCEINLINE auto  load( as_<wide<T,N>> const& tgt, eve::ppc_ const& mode
                            , aligned_ptr<T,Align> ptr
                            ) noexcept
                        requires( typename wide<T,N>::storage_type
                                , Arithmetic<T>, If<(sizeof(T)<8)>
                                )
  {
    if constexpr( Align >= 16)
      return vec_ld(0, ptr.get());
    else
      return load(tgt,mode, ptr.get());
  }
}

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
