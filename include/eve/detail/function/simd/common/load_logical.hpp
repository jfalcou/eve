//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_LOAD_LOGICAL_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_LOAD_LOGICAL_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/as.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Common logical case
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto  load( as_<pack<logical<T>,N>> const& tgt, ABI const& mode
                            , logical<T>* ptr
                            ) noexcept
                        requires( typename pack<logical<T>,N>::storage_type, Native<ABI>)
  {
    using type    = typename pack<logical<T>,N>::storage_type;
    return type( load(as_<pack<T,N>>{}, mode, (T*)ptr) );
  }

  template<typename T, typename N, std::size_t Align, typename ABI>
  EVE_FORCEINLINE auto  load( as_<pack<logical<T>,N>> const& tgt, ABI const& mode
                            , aligned_ptr<logical<T>,Align> ptr
                            ) noexcept
                        requires( typename pack<logical<T>,N>::storage_type, Native<ABI>)
  {
    using type    = typename pack<logical<T>,N>::storage_type;
    return type ( load( as_<pack<T,N>>{},mode
                      , aligned_ptr<T,Align>((T*)ptr.get())
                      )
                );
  }
}

#endif

