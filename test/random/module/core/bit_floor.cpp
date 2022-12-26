//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"

#include <cmath>
#include <bit>

TTS_CASE_TPL("Random check for eve::bit_floor", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
   if constexpr(eve::floating_value<e_t>)
  {
    auto std_bit_floor = [](auto e) -> e_t { return ((e <= 1) ? 0 : std::exp2l(std::floor(std::log2l(e)))); };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_bit_floor, eve::bit_floor );
  }
   else  if constexpr(eve::signed_value<e_t>)
  {
    auto std_bit_floor = [](auto e) -> e_t { return (e <1 ? 0 : std::bit_floor(eve::uint_(e))); };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_bit_floor, eve::bit_floor );
  }
  else
  {
    auto std_bit_floor = [](auto e) -> e_t { return std::bit_floor(e); };
    eve::uniform_prng<e_t> p(vmin, vmax);
    EVE_ULP_RANGE_CHECK(T, p, std_bit_floor, eve::bit_floor);
  }
};
