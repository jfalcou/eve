//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{

template<scalar_value U, typename N>
EVE_FORCEINLINE wide<U, N> convert_impl(EVE_REQUIRES(sve_), wide<float, N> v, as<U> tgt) noexcept
requires sve_abi<abi_t<float, N>>
{
  constexpr auto c_o = categorize<wide<U, N>>();

  auto const mask = sve_true<float>();

  auto from_f32 = [&](auto w)
  {
         if constexpr( std::same_as<U, double>        ) return svcvt_f64_z(mask, w);
    else if constexpr( std::same_as<U, std::int64_t>  ) return svcvt_s64_z(mask, w);
    else if constexpr( std::same_as<U, std::uint64_t> ) return svcvt_u64_z(mask, w);
  };

  auto sve_split = [&](auto w)
  {
    if constexpr(N::value == 1)
    {
      return wide<U, N>{from_f32(w)};
    }
    else
    {
      // SVE convert to larger types one every two lanes so we need to move data around
      // As the data end up in the lower level of the register, we use it directly without
      // needing an extra svext.
      using idx_t = wide<std::uint32_t, N>;
      auto const ll = svtbl(w, idx_t {[](auto i, auto) { return i / 2; }});
      auto const hh = svtbl(w, idx_t {[](auto i, auto c) { return i / 2 + c / 2; }});

      using t_t = wide<U, typename N::split_type>;
      return wide<U, N>(t_t {from_f32(ll)}, t_t {from_f32( hh)});
    }
  };

       if constexpr( sizeof(U) == 8               ) return sve_split(v);
  else if constexpr( match(c_o, category::int32)  ) return svcvt_s32_z(mask, v);
  else if constexpr( match(c_o, category::uint32) ) return svcvt_u32_z(mask, v);
  else                                              return convert_impl(EVE_TARGETS(cpu_), v, tgt);
}

template<scalar_value T, scalar_value U, typename N>
EVE_FORCEINLINE wide<U, N> convert_impl(EVE_REQUIRES(sve_), wide<T, N> v, as<U> tgt) noexcept
requires sve_abi<abi_t<T, N>>
{
  // TODO: OPTIMIZE
  return convert_impl(EVE_TARGETS(cpu_), v, tgt);
}

template<scalar_value T, scalar_value U, typename N>
EVE_FORCEINLINE auto convert_impl(EVE_REQUIRES(sve_), logical<wide<T, N>> v, as<logical<U>>) noexcept
requires sve_abi<abi_t<T, N>>
{
  return to_logical(convert(v.bits(), as<U>{}));
}
}
