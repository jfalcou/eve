//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/math.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

TTS_CASE_TPL("Random check for eve::exp2", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  if constexpr(eve::integral_value<e_t>)
  {
    auto vmin = std::is_signed_v<e_t> ? -e_t(sizeof(e_t)*8-2) : e_t(0);
    auto vmax = e_t(sizeof(e_t)*8-2);
    auto std_exp2 = [](auto e) -> e_t { return std::exp2(e); };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_exp2, eve::exp2 );
  }
  else
  {
    auto vmin = eve::minlog2(eve::as<e_t>())+1;
    auto vmax = eve::maxlog2(eve::as<e_t>())-1;
    auto std_exp2 = [](auto e) -> e_t { return std::exp2(e); };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_exp2, eve::exp2 );
  }
};
