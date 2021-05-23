//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sindcosd.hpp>
#include <eve/function/cosd.hpp>
#include <eve/function/sind.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/pi.hpp>
#include <tuple>

TTS_CASE_TPL("Check eve::restricted(eve::sindcosd) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted(eve::sindcosd)(T()), (kumi::tuple<T, T>));
}

TTS_CASE_TPL("Check eve::restricted(eve::sindcosd) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto base = v_t(180);

  v_t x[] = { base/8, -base/8, base/4, -base/4};

  for(auto v : x)
  {
    auto [sin_, cos_] = eve::restricted(eve::sindcosd)(T(v));
    TTS_ULP_EQUAL(sin_, eve::sind(T(v)), 0.5);
    TTS_ULP_EQUAL(cos_, eve::cosd(T(v)), 0.5);
  }
  {
    auto [sin_, cos_] = eve::restricted(eve::sindcosd)(T(base));
    TTS_IEEE_EQUAL(sin_, eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(cos_, eve::nan(eve::as<T>()));
  }

  {
    auto [sin_, cos_] = eve::restricted(eve::sindcosd)(T(-base));
    TTS_IEEE_EQUAL(sin_, eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(cos_, eve::nan(eve::as<T>()));
  }
}
