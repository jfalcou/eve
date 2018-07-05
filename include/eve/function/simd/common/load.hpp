//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_SIMD_COMMON_LOAD_HPP_INCLUDED
#define EVE_FUNCTION_SIMD_COMMON_LOAD_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>

namespace eve { namespace detail
{
  //------------------------------------------------------------------------------------------------
  // Emulation
  template<typename Pack, typename Pointer>
  EVE_FORCEINLINE Pack load(as_<Pack> const&, eve::emulated_ const&, Pointer ptr) noexcept
  {
    auto impl = [&](auto... I)
                {
                  auto deref = [](auto& p, auto const&) { return *(p++); };
                  return Pack(deref(ptr,I)...);
                };

    return apply<Pack::size()>(impl);
  }

  //------------------------------------------------------------------------------------------------
  // Aggregation
  template<typename Pack, typename Pointer>
  EVE_FORCEINLINE Pack load(as_<Pack> const& tgt, eve::aggregated_ const&, Pointer ptr) noexcept
  {
    using storage_t = typename Pack::storage_type;
    using subpack_t = typename storage_t::value_type;

    auto next = ptr;
    std::advance(next,subpack_t::size());

    return Pack(storage_t{ subpack_t(ptr), subpack_t(next)});
  }
} }

#endif
