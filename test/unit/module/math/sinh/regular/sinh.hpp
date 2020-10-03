//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinh.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::sinh return type")
{
  TTS_EXPR_IS(eve::sinh(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::eve::sinh behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sinh(eve::nan(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::sinh(eve::inf(eve::as<EVE_TYPE>())) , (eve::inf(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::sinh(eve::minf(eve::as<EVE_TYPE>())), (eve::minf(eve::as<EVE_TYPE>())) );
  }
  TTS_EXPECT(eve::all(eve::is_negative(eve::sinh(EVE_TYPE(-0.)))) );
  TTS_EXPECT(eve::all(eve::is_positive(eve::sinh(EVE_TYPE(0))))            );

  // 88.376251220703125f, 709.782712893384
  EVE_VALUE ovflimit =  eve::Ieee_constant<EVE_VALUE,0x42B0C0A4U, 0x40862E42FEFA39EFULL>();
  std::array<EVE_VALUE, 10> a = {EVE_VALUE(1), EVE_VALUE(-1), EVE_VALUE(0), EVE_VALUE(-0.0), EVE_VALUE(10), EVE_VALUE(-10)
                             , eve::maxlog(eve::as<EVE_VALUE>()), ovflimit/2, ovflimit, 2*ovflimit};

  for(size_t i=0; i < a.size(); ++i)
  {
    auto sh  = eve::sinh(EVE_TYPE(a[i]));
    EVE_VALUE sh1 = std::sinh(double(a[i]));
    TTS_ULP_EQUAL(sh, (EVE_TYPE(sh1)), 0.5);
  }
}
