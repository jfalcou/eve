//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/shl.hpp>
#include <eve/function/shr.hpp>

auto shift_data = []<typename T>(eve::as_<T>, auto seed)
{
  using e_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<e_t>;
  using d_t = std::array<e_t,eve::cardinal_v<T>>;
  using s_t = std::array<i_t,eve::cardinal_v<T>>;

  std::mt19937 gen;
  gen.seed(seed);

  d_t d0;
  eve::prng<e_t> dist(-50,50);
  std::for_each(d0.begin(),d0.end(), [&](auto& e) { e = dist(gen); });

  s_t s;
  eve::prng<i_t> disti(0,8*sizeof(i_t)-1);
  std::for_each(s.begin(),s.end(), [&](auto& e) { e = disti(gen); });

  return std::make_tuple(d0, s);
};

auto shift_tests = []<typename T, typename I>
                  ( auto& runtime, bool verbose, auto const&
                  , T a0, I s
                  )
{
  T ref_shl([&](auto i, auto) { return eve::shl(a0.get(i), s.get(i)); });
  T ref_shr([&](auto i, auto) { return eve::shr(a0.get(i), s.get(i)); });

  TTS_EXPR_IS( a0 << s, T);
  TTS_EXPR_IS( a0 >> s, T);

  TTS_EQUAL( (a0 << s), ref_shl );
  TTS_EQUAL( (a0 >> s), ref_shr );
};

EVE_TEST_BED( "Check behavior of shift operators on eve::wide"
            , eve::test::simd::integers
            , shift_data, shift_tests
            );
