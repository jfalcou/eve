//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/constant/one.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sin", EVE_TYPE)
<typename T>(::tts::type<T>)
{

  auto std_sin = [](auto e) { return std::sin(e); };
  auto l = eve::detail::Rempio2_limit(eve::full_circle_type(), eve::as<EVE_VALUE>());
  auto m = eve::one(eve::as(l));
  eve::uniform_prng<EVE_VALUE> p(m, l);
  TTS_RANGE_CHECK(p, std_sin, eve::full_circle(eve::sin));
};