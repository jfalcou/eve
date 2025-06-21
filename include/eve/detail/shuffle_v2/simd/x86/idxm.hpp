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
x86_shuffle_4_in_lane(std::span<const std::ptrdiff_t, 2> idxs)
{
  return x86_shuffle_4_in_lane(expand_group<2>(idxs));
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
x86_permute2f128_mask(std::span<const std::ptrdiff_t, 2> _idxs)
{
  auto idxs = replace_we(_idxs, na_);
  if( idxs[0] == na_ ) idxs[0] = 0xf;
  if( idxs[1] == na_ ) idxs[1] = 0xf;
  return idxs[0] | idxs[1] << 4;
}

constexpr int
x86_blend_immediate_mask(std::span<const std::ptrdiff_t> idxs, std::ptrdiff_t g)
{
  int r   = 0;
  int s   = std::ssize(idxs);
  int pos = 0;
  for( auto i : idxs )
  {
    for( int j = 0; j != g; ++j )
    {
      // we_ < s
      if( i * g >= s ) { r |= 1 << pos; }
      ++pos;
    }
  }
  return r;
}

template<std::ptrdiff_t G, std::size_t N>
constexpr auto x86_pshuvb_pattern(const std::array<std::ptrdiff_t, N>& idxs);

template<std::ptrdiff_t G, std::size_t N>
constexpr auto
x86_pshuvb_pattern(std::span<const std::ptrdiff_t, N> idxs)
{
  if constexpr( G != 1 ) return x86_pshuvb_pattern<1>(expand_group<G>(idxs));
  else
  {
    static_assert(N == 16 || N == 32 || N == 64);
    using arr_t = std::array<std::ptrdiff_t, N>;
    using res_t = std::optional<arr_t>;

    if( !shuffle_within_n(idxs, 16) ) return res_t {};

    arr_t res = {};
    for( std::size_t i = 0; i != N; ++i )
    {
      std::ptrdiff_t lb = i / 16 * 16;
      std::ptrdiff_t ub = lb + 16;
      if( idxs[i] < 0 )
      {
        res[i] = 0xff;
        continue;
      }
      if( idxs[i] < lb || idxs[i] > ub ) return res_t {};
      res[i] = idxs[i] - lb;
    }

    return res_t {res};
  }
}

template<std::ptrdiff_t G, std::size_t N>
constexpr auto
x86_pshuvb_pattern(const std::array<std::ptrdiff_t, N>& idxs)
{
  return x86_pshuvb_pattern<G>(std::span<const std::ptrdiff_t, N>(idxs));
}

template<std::size_t N>
constexpr std::optional<int>
mm512_shuffle_i64x2_idx(std::array<std::ptrdiff_t, N> idxs)
{
  if constexpr( N == 2 ) return mm512_shuffle_i64x2_idx(expand_group<2>(idxs));
  else if constexpr( N > 4 )
  {
    auto upscaled = upscale_pattern(idxs);
    if( upscaled ) return mm512_shuffle_i64x2_idx(*upscaled);
    else return std::nullopt;
  }
  else
  {
    if( idxs[0] >= 4 || idxs[1] >= 4 ) return std::nullopt;
    if( idxs[2] < 4 || idxs[3] < 4 ) return std::nullopt;
    idxs[2] -= 4;
    idxs[3] -= 4;
    return idxs[0] | (idxs[1] << 2) | (idxs[2] << 4) | (idxs[3] << 6);
  }
}

template<std::size_t N>
constexpr auto
slide_2_left_in_16_pattern(std::ptrdiff_t g_size, std::ptrdiff_t slide)
{
  std::ptrdiff_t                n16 = 16 / g_size;
  std::array<std::ptrdiff_t, N> res = {};

  for( std::ptrdiff_t i = 0; i != N; i += n16 )
  {
    for( std::ptrdiff_t j = 0; j != n16; ++j )
    {
      std::ptrdiff_t full = i + j;
      if( j < (n16 - slide) ) res[full] = full + slide;
      else res[full] = full + N - (n16 - slide);
    }
  }
  return res;
}

template<std::ptrdiff_t g_size, std::size_t N>
constexpr std::optional<int>
x86_shuffle_ps_2(std::span<const std::ptrdiff_t, N> idxs_)
{
  auto           idxs = expand_group<g_size / 4>(idxs_);
  std::ptrdiff_t size = std::ssize(idxs);
  std::ptrdiff_t res  = 0;

  for( std::ptrdiff_t i = 0; i != size; ++i )
  {
    if( idxs[i] < 0 ) { continue; }

    // 2 indexes from x, 2 indexes from y
    std::ptrdiff_t active_register_offset = (i & 2) * size / 2;
    std::ptrdiff_t within_register_offset = i / 4;
    std::ptrdiff_t offset                 = active_register_offset + within_register_offset;

    std::ptrdiff_t selected = idxs[i] - offset;

    if( selected < 0 || selected >= 4 ) { return std::nullopt; }

    res |= selected << (i * 2);
  }

  return static_cast<int>(res);
}

template<std::ptrdiff_t g_size, std::size_t N>
constexpr std::optional<int>
x86_shuffle_ps_2(const std::array<std::ptrdiff_t, N> idxs)
{
  return x86_shuffle_ps_2<g_size>(std::span<const std::ptrdiff_t, N>(idxs));
}

}
