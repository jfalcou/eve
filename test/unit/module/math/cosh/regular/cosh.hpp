//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cosh.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::cosh return type")
{
  TTS_EXPR_IS(eve::cosh(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::eve::cosh behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cosh(eve::nan(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::cosh(eve::inf(eve::as<EVE_TYPE>())) , (eve::inf(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::cosh(eve::minf(eve::as<EVE_TYPE>())), (eve::inf(eve::as<EVE_TYPE>())) );
  }

  TTS_ULP_EQUAL(eve::cosh(EVE_TYPE(1)), EVE_TYPE(std::cosh(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::cosh(EVE_TYPE(-1)),EVE_TYPE(std::cosh(-1.0)), 0.5);


  EVE_VALUE ovl =  eve::Ieee_constant<EVE_VALUE,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384
  EVE_VALUE a[] = { EVE_VALUE(1), EVE_VALUE(-1), EVE_VALUE(0), EVE_VALUE(-0.0), EVE_VALUE(10), EVE_VALUE(-10), eve::maxlog(eve::as<EVE_VALUE>())
            , ovl/2, ovl, 2*ovl, -eve::maxlog(eve::as<EVE_VALUE>()), -ovl/2, -ovl, -2*ovl
            };

  for(auto v : a)
  {
    auto  res = eve::cosh(EVE_TYPE(v));
    EVE_VALUE   ref = std::cosh(double(v));

    TTS_ULP_EQUAL(res, (EVE_TYPE(ref)), 0.5);
  }
}
