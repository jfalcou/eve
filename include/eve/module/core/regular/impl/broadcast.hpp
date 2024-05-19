//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<callable_options O, scalar_value T>
  EVE_FORCEINLINE auto broadcast_(EVE_REQUIRES(cpu_), O const&, T v) noexcept
  {
    return as_wide_t<T>{v};
  }
  template<callable_options O, scalar_value T, std::ptrdiff_t N>
  EVE_FORCEINLINE auto broadcast_(EVE_REQUIRES(cpu_), O const&, T v, fixed<N>) noexcept
  {
    return as_wide_t<T, fixed<N>>{v};
  }

  //==============================================================================================
  // TODO: Replace in broadcast_lane
  // Detects <N,...,N> as a broadcast
  template<int I0, int... I> inline constexpr bool is_broadcast = ((I0 != na_) && ... && (I0 == I));

  // TODO: Remove as being duplicates
  template<callable_options O, simd_value Wide>
  EVE_FORCEINLINE auto broadcast_(EVE_REQUIRES(cpu_), O const&, Wide v, auto Index) noexcept
  {
    if constexpr( is_bundle_v<typename Wide::abi_type> )
    {
      return Wide(kumi::map([&]<typename T>(T m) { return broadcast(m, Index); }, v));
    }
    else { return Wide {v.get(Index)}; }
  }

  template<callable_options O, simd_value Wide, std::ptrdiff_t N>
  EVE_FORCEINLINE auto broadcast_(EVE_REQUIRES(cpu_), O const&, Wide v, auto Index, fixed<N>) noexcept
  {
    using that_t = as_wide_t<Wide, fixed<N>>;

    if constexpr( is_bundle_v<typename Wide::abi_type> )
    {
      return that_t(kumi::map([&]<typename T>(T m) { return broadcast(m, Index, fixed<N> {}); }, v));
    }
    else { return that_t {v.get(Index)}; }
  }
}
