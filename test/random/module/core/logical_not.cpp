//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"

#include <bit>

TTS_CASE_TPL("Random check for eve::is_pow2", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  auto std_is_pow2 = [](auto e) -> eve::logical<e_t>{
    using ui_t =  eve::as_integer_t<e_t, unsigned>;
    return ((e > 0) && (std::popcount(eve::bit_cast(e, eve::as<ui_t>())) == 1u));
  };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_is_pow2, eve::is_pow2 );
 };
