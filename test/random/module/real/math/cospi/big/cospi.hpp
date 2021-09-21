//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/function/cospi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide random check on cospi", EVE_TYPE)
{
  auto my_stdcospi = [](auto x) -> EVE_VALUE {return boost::math::cos_pi(x); };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, my_stdcospi, eve::big(eve::cospi));
}

// #include <crlibm.h>
// TTS_CASE_TPL("wide random check on cospi", EVE_TYPE)
// {
//   ::crlibm_init();
//   auto my_stdcospi =  tts::vectorize<T>([](EVE_VALUE x){return EVE_VALUE(::cospi_rn(x)); });
//   eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
//   TTS_RANGE_CHECK(p, my_stdcospi, eve::big(eve::cospi));
// }
