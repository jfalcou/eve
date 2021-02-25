//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/rsqrt.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/rec.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::pedantic(eve::rsqrt) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::rsqrt)(T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::rsqrt) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::pedantic(eve::rsqrt)(T(1)), T(1  ), 0.5);
  TTS_ULP_EQUAL(eve::pedantic(eve::rsqrt)(T(4)), T(0.5), 0.5);

  if constexpr(eve::floating_value<T> && eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL((eve::pedantic(eve::rsqrt)(eve::nan(eve::as<T>()))) , (eve::nan(eve::as<T>())));
    TTS_EQUAL(eve::pedantic(eve::rsqrt)((T(0)))               , eve::inf(eve::as<T>()));
  }

  using v_t = eve::element_type_t<T>;
  auto z = eve::mindenormal(eve::as<v_t>());

  TTS_ULP_EQUAL(eve::pedantic(eve::rsqrt)(eve::mindenormal(eve::as<T>()))   , T(eve::rec(std::sqrt(z)))   , 2.0);
  TTS_ULP_EQUAL(eve::pedantic(eve::rsqrt)(2*eve::mindenormal(eve::as<T>())) , T(eve::rec(std::sqrt(2*z))) , 2.0);
}
