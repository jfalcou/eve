//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/pedantic/ifrexp.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on ifrexp", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  using i_t = eve::as_integer_t<EVE_VALUE>;
  auto std_ifrexp = [](auto e) { int y; auto x = std::frexp(e, &y); return std::make_tuple(x, i_t(y)); };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_ifrexp, eve::pedantic(eve::ifrexp));
};