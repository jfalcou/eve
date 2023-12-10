//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{

template<typename T>
EVE_FORCEINLINE T
sveindex(eve::element_type_t<T> start, eve::element_type_t<T> step)
{
  constexpr auto c = categorize<T>();

  if constexpr( has_aggregated_abi_v<T> )
  {
    using e_t    = eve::element_type_t<T>;
    using N      = typename T::cardinal_type;
    using half_N = typename N::split_type;
    using half_T = wide<e_t, half_N>;

    half_T lo = sveindex<half_T>(start, step);
    half_T hi = sveindex<half_T>(start + step * half_N{}(), step);
    return T{lo, hi};
  }
  else if constexpr( match(c, category::int8) ) return T {svindex_s8(start, step)};
  else if constexpr( match(c, category::int16) ) return T {svindex_s16(start, step)};
  else if constexpr( match(c, category::int32) ) return T {svindex_s32(start, step)};
  else if constexpr( match(c, category::int64) ) return T {svindex_s64(start, step)};
  else if constexpr( match(c, category::uint8) ) return T {svindex_u8(start, step)};
  else if constexpr( match(c, category::uint16) ) return T {svindex_u16(start, step)};
  else if constexpr( match(c, category::uint32) ) return T {svindex_u32(start, step)};
  else if constexpr( match(c, category::uint64) ) return T {svindex_u64(start, step)};
}

template<eve::integral_simd_value T>
EVE_FORCEINLINE T
iota_(EVE_REQUIRES(sve_), eve::callable_options auto const& opts, eve::as<T> tgt)
{
  using C = decltype(opts[condition_key]);

  if constexpr( C::is_complete && C::is_inverted) return sveindex<T>(0, 1);
  else return eve::iota.behavior(cpu_ {}, opts, tgt);
}
}
