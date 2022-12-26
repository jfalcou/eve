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

TTS_CASE_TPL("Random check for eve::bit_width", eve::test::simd::unsigned_integers)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  auto std_bit_width = [](auto e) -> e_t { return sizeof(e_t)*8-std::countl_zero(e); };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_bit_width, eve::bit_width );
};
