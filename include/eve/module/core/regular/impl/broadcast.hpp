//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

namespace eve::detail
{
//==============================================================================================
// Detects <N,...,N> as a broadcast
template<int I0, int... I> inline constexpr bool is_broadcast = ((I0 != na_) && ... && (I0 == I));

template<simd_value Wide>
EVE_FORCEINLINE auto
broadcast_(EVE_SUPPORTS(cpu_), Wide v, auto Index) noexcept
{
  if constexpr( is_bundle_v<typename Wide::abi_type> )
  {
    return Wide(kumi::map([&]<typename T>(T m) { return broadcast(m, Index); }, v));
  }
  else { return Wide {v.get(Index)}; }
}

template<simd_value Wide, std::ptrdiff_t N>
EVE_FORCEINLINE auto
broadcast_(EVE_SUPPORTS(cpu_), Wide v, auto Index, fixed<N>) noexcept
{
  using that_t = as_wide_t<Wide, fixed<N>>;

  if constexpr( is_bundle_v<typename Wide::abi_type> )
  {
    return that_t(kumi::map([&]<typename T>(T m) { return broadcast(m, Index, fixed<N> {}); }, v));
  }
  else { return that_t {v.get(Index)}; }
}
}
