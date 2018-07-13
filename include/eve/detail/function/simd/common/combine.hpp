//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_COMBINE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_COMBINE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif

namespace eve { namespace detail
{
  //------------------------------------------------------------------------------------------------
  // Emulation
  template<typename T, typename N>
  EVE_FORCEINLINE auto combine( cpu_ const&
                              , pack<T,N,emulated_> const& l
                              , pack<T,N,emulated_> const& h
                              ) noexcept
  {
    auto impl = [&](auto... I) { return pack<T,typename N::combined_type>{l[I]...,h[I]...}; };
    return apply<N::value>(impl);
  }

  //------------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE auto combine( cpu_ const&
                              , pack<T,N,aggregated_> const& l
                              , pack<T,N,aggregated_> const& h
                              ) noexcept
  {
    using that_t = pack<T,typename N::combined_type>;
    return that_t( typename that_t::storage_type{l,h} );
  }
} }

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
