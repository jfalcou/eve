//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/zip_iterator.hpp>

#include <eve/algo/ptr_iterator.hpp>

TTS_CASE("zip_iterator, sanity check, types test")
{
  using unaligned_float = eve::algo::unaligned_ptr_iterator<float, eve::fixed<8>>;
  using aligned_float   = eve::algo::aligned_ptr_iterator  <float, eve::fixed<8>>;
  using unaligned_short = eve::algo::unaligned_ptr_iterator<short, eve::fixed<8>>;
  using aligned_short   = eve::algo::aligned_ptr_iterator  <short, eve::fixed<8>>;

  using zip_a_a = eve::algo::zip_iterator<aligned_float,   aligned_short>;
  using zip_u_a = eve::algo::zip_iterator<unaligned_float, aligned_short>;
  using zip_a_u = eve::algo::zip_iterator<aligned_float,   unaligned_short>;
  using zip_u_u = eve::algo::zip_iterator<unaligned_float, unaligned_short>;

  using wide_value_type = eve::wide<kumi::tuple<float, short>>;

  // CTAD
  eve::algo::zip_iterator zi {unaligned_float{}, aligned_short{}};
  TTS_TYPE_IS(decltype(zi), zip_u_a);

  // Unaligned
  TTS_TYPE_IS(eve::algo::unaligned_t<zip_a_a>, zip_u_u);
  TTS_TYPE_IS(eve::algo::unaligned_t<zip_a_u>, zip_u_u);
  TTS_TYPE_IS(eve::algo::unaligned_t<zip_u_a>, zip_u_u);
  TTS_TYPE_IS(eve::algo::unaligned_t<zip_u_u>, zip_u_u);

  // Partially aligned
  TTS_TYPE_IS(eve::algo::partially_aligned_t<zip_a_a>, zip_a_a);
  TTS_TYPE_IS(eve::algo::partially_aligned_t<zip_a_u>, zip_a_u);
  TTS_TYPE_IS(eve::algo::partially_aligned_t<zip_u_a>, zip_u_a);
  TTS_TYPE_IS(eve::algo::partially_aligned_t<zip_u_u>, zip_a_u);

  // Load
  auto loaded = eve::load(zip_a_u{});
  TTS_TYPE_IS(decltype(loaded), wide_value_type);
}
