//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/slide_right.hpp>
#include <eve/module/core/regular/broadcast.hpp>
#include <eve/detail/implementation.hpp>

#include <eve/module/core/constant/as_value.hpp>
#include <eve/function/broadcast.hpp>

namespace eve::detail
{

template <typename T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE wide<T, N> slide_right_in_lanes(wide<T, N> x, wide<T, N> y, index_t<Shift>);

template <std::ptrdiff_t Shift>
struct slide_right_in_lanes_lambda
{
  EVE_FORCEINLINE auto operator()(auto ... x) const
  {
    return slide_right_in_lanes(x..., index<Shift>);
  }
};

template <typename T, typename N, std::ptrdiff_t Shift>
EVE_FORCEINLINE wide<T, N> slide_right_in_lanes(wide<T, N> x, wide<T, N> y, index_t<Shift>)
  requires (current_api == avx2)
{
  if constexpr ( is_bundle_v<abi_t<T, N>> ) return wide<T, N>{kumi::map(slide_right_in_lanes_lambda<Shift>{}, x, y)};
  else
  {
    using i_t = as_integer_t<wide<T,N>, unsigned>;

  i_t lhs = eve::bit_cast(x, eve::as<i_t>{});
  i_t rhs = eve::bit_cast(y, eve::as<i_t>{});
  i_t res = _mm256_alignr_epi8(rhs, lhs, 16 - Shift * sizeof(T));

  return eve::bit_cast(res, eve::as(x));
  }
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

template <simd_value Wide>
auto use_scan_in_lanes(Wide) {
       if constexpr ( std::same_as<typename Wide::abi_type, x86_256_> ) return std::true_type{};
  else if constexpr ( is_bundle_v<typename Wide::abi_type> )
  {
    return kumi::fold_right([]<bool so_far, typename T>(std::bool_constant<so_far>, T) {
      return std::bool_constant<so_far && decltype(use_scan_in_lanes(T{}))::value>{};
    }, Wide{}, std::true_type{});
  }
  else return std::false_type{};
}

template <simd_value Wide, typename Op, typename Zero>
EVE_FORCEINLINE auto scan_(EVE_SUPPORTS(avx2_), Wide v, Op op, Zero z_)
  requires (current_api == avx2 )
{
  if constexpr ( decltype(use_scan_in_lanes(v))::value )
  {
    Wide z = as_value(z_, eve::as<Wide>{});

    v = scan_in_lanes<Wide::size() / 2>(v, op, z);
    Wide left_sum = broadcast(v, index<Wide::size() / 2 - 1>);
    return op(v, slide_right(z, left_sum, index<Wide::size() / 2>));
  }
  else return scan_(EVE_RETARGET(cpu_), v, op, z_);
}

}
