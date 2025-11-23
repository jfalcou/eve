//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/regular/shuffle_v2/shuffle_v2_test.hpp"

namespace
{

using eve::na_;
using eve::we_;

auto return3 = [](auto...) { return 3; };

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1, std::ptrdiff_t... I>
void
run_any_api(eve::pattern_t<I...> p)
{
  shuffle_test::run<T, N, G>(return3, p);
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1>
void
run_any_api(eve::pattern_formula auto formula)
{
  run_any_api<T, N, G>(eve::fix_pattern<N>(formula));
}

template<typename T, std::ptrdiff_t G = 1>
void
run_any_api_expected_cardinal(auto pattern)
{
  run_any_api<T, eve::expected_cardinal_v<T>, G>(pattern);
}

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1>
void
run(auto pattern)
{
  if constexpr( eve::current_api >= api ) { run_any_api<T, N, G>(pattern); }
  else {
    TTS_PASS();
  }
}

TTS_CASE("and 0s")
{
  // masking 0s is free for these arches.
  if constexpr( eve::current_api >= eve::avx512 || eve::current_api >= eve::rvv
                || eve::current_api >= eve::sve )
  {
    TTS_PASS();
    return;
  }
  run_any_api_expected_cardinal<std::uint8_t>(
      [](int i, int /*size*/) -> std::ptrdiff_t
      {
        if( i == 3 ) return na_;
        if( i % 5 == 0 ) return we_;
        if( i % 7 == 0 ) return na_;
        return i;
      });
};

TTS_CASE("_mm_shuffle_epi8")
{
  run<eve::ssse3, std::uint8_t, 16>(
      eve::pattern<15, eve::na_, 11, eve::we_, 0, 1, 3, 15, 15, 14, 13, 12, 5, 8, 6, 4>);

  auto pattern = [](int i, int) -> std::ptrdiff_t
  {
    int base   = i / 16 * 16;
    int offset = (i + i / 16) % 16;

    if( offset == 3 ) return we_;
    if( offset == 7 ) return na_;

    if( offset == 0 ) return base + 1;
    if( offset == 12 ) return base + 10;

    return base + (offset + 3) % 16;
  };

  run<eve::ssse3, std::uint8_t, 16>(pattern);
  run<eve::avx2, std::uint8_t, 32>(pattern);
  run<eve::avx512, std::uint8_t, 64>(pattern);
};

}
