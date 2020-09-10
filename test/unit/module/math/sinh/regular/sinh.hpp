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
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::sinh return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sinh(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::sinh behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sinh(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::sinh(eve::inf(eve::as<T>())) , (eve::inf(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::sinh(eve::minf(eve::as<T>())), (eve::minf(eve::as<T>())) );
  }
  TTS_EXPECT(eve::all(eve::is_negative(eve::sinh(T(-0.)))) );
  TTS_EXPECT(eve::all(eve::is_positive(eve::sinh(T(0))))            );

  // 88.376251220703125f, 709.782712893384
  v_t ovflimit =  eve::Ieee_constant<v_t,0x42B0C0A4U, 0x40862E42FEFA39EFULL>();
  std::array<v_t, 10> a = {v_t(1), v_t(-1), v_t(0), v_t(-0.0), v_t(10), v_t(-10)
                             , eve::maxlog(eve::as<v_t>()), ovflimit/2, ovflimit, 2*ovflimit};

  for(size_t i=0; i < a.size(); ++i)
  {
    auto sh  = eve::sinh(T(a[i]));
    v_t sh1 = std::sinh(double(a[i]));
    TTS_ULP_EQUAL(sh, (T(sh1)), 0.5);
  }
}
