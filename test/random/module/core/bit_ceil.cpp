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

TTS_CASE_TPL("Random check for eve::bit_ceil", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto std_bit_ceil = [](auto e) -> e_t { return ((e <= 1) ? 1 : std::exp2l(std::ceil(std::log2l(double(e))))); };

  if constexpr(eve::floating_value<e_t>)
  {
    auto vmax = eve::valmax(eve::as<e_t>());
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_bit_ceil, eve::bit_ceil );
  }
  else
  {
    auto vmax = (1ul << (sizeof(e_t)*8-2));
    eve::uniform_prng<e_t> p(vmin, vmax);
    EVE_ULP_RANGE_CHECK(T, p, std_bit_ceil, eve::bit_ceil);
  }
};
