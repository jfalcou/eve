//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"
#include "generator.hpp"


TTS_CASE_TPL("Random check for eve::oneminus", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  auto std_oneminus = [](auto e) -> e_t { return 1-e; };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_oneminus, eve::oneminus);
  auto std_saturated_oneminus = [ = ](auto e) -> e_t {
    if constexpr(eve::floating_value<e_t>) return 1-e;
    else if constexpr(eve::signed_value<e_t>) return e <= vmin+1 ? vmax : e_t(1)-e;
    else if constexpr(eve::unsigned_value<e_t>) return (e <= 1) ? e_t(1)-e : e_t(0);
  };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax)
                     , std_saturated_oneminus, eve::saturated(eve::oneminus));

};
