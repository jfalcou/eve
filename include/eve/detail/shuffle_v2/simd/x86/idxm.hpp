//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// idxm that needs some x86 math
// we don't test it individually, only through shuffles,
// since threre is no sense in hardcoding cryptic numbers.
namespace eve::detail::idxm
{

constexpr int
x86_shuffle_4_in_lane(std::span<const std::ptrdiff_t, 4> idxs)
{
  // we_ doesn't affect here
  int res = 0;
  if( idxs[0] == 1 ) res |= 1;
  if( idxs[1] == 1 ) res |= 1 << 1;
  if( idxs[2] == 3 ) res |= 1 << 2;
  if( idxs[3] == 3 ) res |= 1 << 3;
  return res;
}

constexpr int
x86_mm_shuffle_4(std::span<const std::ptrdiff_t, 2> _idxs)
{
  std::array<std::ptrdiff_t, 2> idxs = replace_na(replace_we(_idxs, 0), 0);
  idxs[0] *= 2;
  idxs[1] *= 2;
  return _MM_SHUFFLE(idxs[1] + 1, idxs[1], idxs[0] + 1, idxs[0]);
}

constexpr int
x86_mm_shuffle_4(std::span<const std::ptrdiff_t, 4> _idxs)
{
  std::array<std::ptrdiff_t, 4> idxs = replace_na(replace_we(_idxs, 0), 0);
  return _MM_SHUFFLE(idxs[3], idxs[2], idxs[1], idxs[0]);
}

constexpr int
x86_permute2f128_one_reg_mask(std::span<const std::ptrdiff_t, 2> _idxs)
{
  auto idxs = replace_we(_idxs, 0);
  if( idxs[0] == na_ ) idxs[0] = 0xf;
  if( idxs[1] == na_ ) idxs[1] = 0xf;
  return idxs[0] | idxs[1] << 4;
}

constexpr int
x86_blend_immediate_mask(std::span<const std::ptrdiff_t> idxs, std::ptrdiff_t g)
{
  int r = 0;
  int s = std::ssize(idxs);
  int pos = 0;
  for(auto i : idxs )
  {
    for (int j = 0; j != g; ++j) {
      // we_ < s
      if( i * g >= s ) { r |= 1 << pos; }
      ++pos;
    }
  }
  return r;
}

}
