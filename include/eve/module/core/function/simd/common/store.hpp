//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_STORE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_STORE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename N> EVE_FORCEINLINE
  void store_(EVE_SUPPORTS(cpu_), wide<T,N,emulated_> const& value, T* ptr) noexcept
  {
    apply<N::value>( [&](auto... I) { ((*ptr++ = value[I]), ...); } );
  }

  template<typename T, typename N> EVE_FORCEINLINE
  void store_(EVE_SUPPORTS(cpu_), wide<T,N,aggregated_> const& value, T* ptr) noexcept
  {
    store( value.storage()[0], ptr );
    store( value.storage()[1], ptr + value.storage()[1].size() );
  }

  // -----------------------------------------------------------------------------------------------
  // Aligned case
  template<typename T, typename S, std::size_t N>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(cpu_)
                              , wide<T,S,emulated_> const& value, aligned_ptr<T,N> ptr
                              , std::enable_if_t<(wide<T,S,emulated_>::static_alignment <= N)>* = 0
                              ) noexcept
  {
    store(value, ptr.get());
  }

  template< typename T, typename S, std::size_t N>
  EVE_FORCEINLINE void store_ ( EVE_SUPPORTS(cpu_)
                              , wide<T,S,aggregated_> const& value, aligned_ptr<T,N> ptr
                              , std::enable_if_t<(wide<T,S,aggregated_>::static_alignment <= N)>* = 0
                              ) noexcept
  {
    store( value.storage()[0], ptr );
    store( value.storage()[1], ptr + value.storage()[1].size() );
  }
}

#endif
