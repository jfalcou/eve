//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

TTS_CASE_TPL("Random check for eve::bitofsign", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  if constexpr(eve::floating_value<T>)
  {
    auto std_bitofsign = [](auto e) { return std::copysign(e_t(1), e); };
    auto eve_bitofsign = [](auto e) { return eve::bit_xor(eve::bitofsign(e), e_t(1)); };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_bitofsign, eve_bitofsign );
  }
  else
  {
    auto std_bitofsign = [](auto e) -> e_t {
      return e & eve::signmask(eve::as(e));
    };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_bitofsign, eve::bitofsign );
  }
};
