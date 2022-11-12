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
EVE_FORCEINLINE auto
convert_impl(EVE_SUPPORTS(sve_), wide<float, N> const& v, as<U> const& tgt) noexcept -> wide<U, N>
requires sve_abi<abi_t<float, N>>
{
  constexpr auto c_o = categorize<wide<U, N>>();
  using enum detail::category;

  auto const mask = sve_true<float>();

  auto sve_split = [&](auto w)
  {
    // SVE convert to larger types one every two lanes so we need to move data around
    // As the data end up in the lower level of the register, we use it directly without
    // needing an extra svext.
    auto const ll = svtbl(w,wide<std::uint32_t,N>{[](auto i,auto  ) { return i/2; }});
    auto const hh = svtbl(w,wide<std::uint32_t,N>{[](auto i,auto c) { return i/2 + c/2; }});

    using t_t   = wide<U,typename N::split_type>;
    if constexpr( std::same_as<U,double> )
      return wide<U, N>(t_t{svcvt_f64_z(mask, ll)}, t_t{svcvt_f64_z(mask, hh)});
    else if constexpr( std::same_as<U,std::int64_t> )
      return wide<U, N>(t_t{svcvt_s64_z(mask, ll)}, t_t{svcvt_s64_z(mask, hh)});
    else if constexpr( std::same_as<U,std::uint64_t> )
      return wide<U, N>(t_t{svcvt_u64_z(mask, ll)}, t_t{svcvt_u64_z(mask, hh)});
  };

  if constexpr( sizeof(U) == 8 )  return sve_split(v);
  else if constexpr( match(c_o, int32 ) ) return svcvt_s32_z(mask, v);
  else if constexpr( match(c_o, uint32) ) return svcvt_u32_z(mask, v);
  else return convert_impl(EVE_RETARGET(cpu_), v, tgt);
}

template<scalar_value T, scalar_value U, typename N>
EVE_FORCEINLINE auto
convert_impl(EVE_SUPPORTS(sve_), wide<T, N> const& v, as<U> const& tgt) noexcept -> wide<U, N>
requires sve_abi<abi_t<T, N>>
{
  //TODO: OPTIMIZE
  return convert_impl(EVE_RETARGET(cpu_), v, tgt);
}

template<scalar_value T, scalar_value U, typename N>
EVE_FORCEINLINE auto
convert_impl(EVE_SUPPORTS(sve_), logical<wide<T, N>> const& v, as<logical<U>> const&) noexcept
requires sve_abi<abi_t<T, N>>
{
  return to_logical(convert(v.bits(), as<U>{}));
}
}
