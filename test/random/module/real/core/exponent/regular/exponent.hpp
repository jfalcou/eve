//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/exponent.hpp>
#include <eve/function/dec.hpp>
#include <eve/module/arithmetic/constant/smallestposval.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on exponent", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  using i_t = eve::as_integer_t<EVE_VALUE>;

  auto internal_f = [](auto e){  int exp; std::frexp(e, &exp); return i_t(exp); };

  auto std_exponent = [ internal_f ](auto e) { return eve::dec(internal_f(e)); };

  eve::uniform_prng<EVE_VALUE> p(eve::smallestposval(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_exponent, eve::exponent);
};