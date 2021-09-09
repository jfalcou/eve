//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>

#include <eve/function/broadcast.hpp>

namespace eve::detail
{

template <typename T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE wide<T, N> slide_right_in_lanes(wide<T, N> x, wide<T, N> y, index_t<Shift>)
  requires (current_api == avx2)
{
  using i_t = as_integer_t<wide<T,N>, unsigned>;

  i_t lhs = eve::bit_cast(x, eve::as<i_t>{});
  i_t rhs = eve::bit_cast(y, eve::as<i_t>{});
  i_t res = _mm256_alignr_epi8(rhs, lhs, 16 - Shift * sizeof(T));

  return eve::bit_cast(res, eve::as(x));
}

template <simd_value Wide, std::ptrdiff_t Shift>
EVE_FORCEINLINE logical<Wide> slide_right_in_lanes(logical<Wide> x
                                                 , logical<Wide> y
                                                 , index_t<Shift> s)
{
  return bit_cast(slide_right_in_lanes(x.bits(), y.bits(), s), as<logical<Wide>>{});
}

template <int group_size, simd_value Wide, typename Op>
EVE_FORCEINLINE Wide scan_in_lanes(Wide x, Op op, Wide z)
{
  if constexpr (group_size == 1) return x;
  else
  {
    x = scan_in_lanes<group_size / 2>(x, op, z);
    return op(x, slide_right_in_lanes(z, x, eve::index<group_size / 2>));
  }
}

template <simd_value Wide, typename Op, typename Zero>
EVE_FORCEINLINE auto scan_(EVE_SUPPORTS(avx2_), Wide v, Op op, Zero z_)
  requires (current_api == avx2 && std::same_as<typename Wide::abi_type, x86_256_> )
{
  Wide z;
  if constexpr ( std::same_as<Zero, callable_zero_> ) z = z_(as<Wide>{});
  else                                                z = z_;

  v = scan_in_lanes<Wide::size() / 2>(v, op, z);
  Wide left_sum = broadcast(v, index<Wide::size() / 2 - 1>);
  return op(v, slide_right(z, left_sum, index<Wide::size() / 2>));
}

}
