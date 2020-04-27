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
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::cosh return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cosh(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::cosh behavior", EVE_TYPE)
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cosh(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::cosh(eve::Inf<T>()) , (eve::Inf<T>()) );
    TTS_IEEE_EQUAL(eve::cosh(eve::Minf<T>()), (eve::Inf<T>()) );
  }
  TTS_ULP_EQUAL(eve::cosh(T(1)), T(std::cosh(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::cosh(T(-1)),T(std::cosh(-1.0)), 0.5);
  v_t ovflimit =  eve::Ieee_constant<v_t,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384
  std::array<v_t, 14> a = {v_t(1), v_t(-1), v_t(0), v_t(-0.0), v_t(10), v_t(-10)
                             , eve::Maxlog<v_t>(), ovflimit/2, ovflimit, 2*ovflimit,
                               -eve::Maxlog<v_t>(), -ovflimit/2, -ovflimit, -2*ovflimit };

  for(size_t i=0; i < a.size(); ++i)
  {
    auto ch  = eve::cosh(T(a[i]));
    v_t ch1 = std::cosh(double(a[i]));
    TTS_ULP_EQUAL(ch, (T(ch1)), 0.5);
  }
}
