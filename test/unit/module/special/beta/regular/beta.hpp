//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/beta.hpp>
#include <eve/constant/halfeps.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::beta return type")
{
  TTS_EXPR_IS(eve::beta(EVE_TYPE(0), EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::beta behavior")
{
  using eve::as;
  using elt_t = eve::element_type_t<EVE_TYPE>;
  auto beta = [](auto x, auto y) { return eve::beta(x, y); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(beta(eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::nan(as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(beta(eve::inf(eve::as<EVE_TYPE>()), EVE_TYPE(1)), eve::nan(as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(beta(EVE_TYPE(1), eve::inf(eve::as<EVE_TYPE>())), eve::nan(as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(beta(eve::minf(eve::as<EVE_TYPE>()), eve::minf(eve::as<EVE_TYPE>())), eve::nan(as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(beta(eve::minf(eve::as<EVE_TYPE>()), EVE_TYPE(1)), eve::nan(as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(beta(EVE_TYPE(1), eve::minf(eve::as<EVE_TYPE>())), eve::nan(as<EVE_TYPE>()), 0);

    TTS_ULP_EQUAL(beta(eve::nan(eve::as<EVE_TYPE>()), eve::nan(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(beta(eve::nan(eve::as<EVE_TYPE>()), EVE_TYPE(1)), eve::nan(as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(beta(EVE_TYPE(1), eve::nan(eve::as<EVE_TYPE>())), eve::nan(as<EVE_TYPE>()), 0);
  }

  TTS_ULP_EQUAL(beta(EVE_TYPE(-0.0), EVE_TYPE(-0.0)), EVE_TYPE(std::beta(elt_t(-0.0) , elt_t(-0.0))), 0);
  TTS_ULP_EQUAL(beta(EVE_TYPE( 0.0), EVE_TYPE( 0.0)), EVE_TYPE(std::beta(elt_t(0.0)  , elt_t(0.0))), 0);
  TTS_ULP_EQUAL(beta(EVE_TYPE( 1.0), EVE_TYPE( 1.0)), EVE_TYPE(std::beta(elt_t(1.0)  , elt_t(1.0))), 0);
  TTS_ULP_EQUAL(beta(EVE_TYPE( 2.0), EVE_TYPE( 3.0)), EVE_TYPE(std::beta(elt_t(2.0)  , elt_t(3.0))), 0);
  TTS_ULP_EQUAL(beta(EVE_TYPE( 2.5), EVE_TYPE( 3.7)), EVE_TYPE(std::beta(elt_t(2.5)  , elt_t(3.7))), 0);
}
