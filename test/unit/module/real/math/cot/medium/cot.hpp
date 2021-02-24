//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::medium(eve::cot) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cot(T(0)), T);
}

TTS_CASE_TPL("Check eve::medium(eve::cot) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto my_stdcot =  [](auto x){return eve::rec(std::tan(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium(eve::cot)(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::medium(eve::cot)(eve::inf(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::medium(eve::cot)(eve::minf(eve::as<T>())), (eve::nan(eve::as<T>())) );
  }
  TTS_ULP_EQUAL(eve::medium(eve::cot)(T(1)), T(my_stdcot(1.0)), 1.0);
  TTS_ULP_EQUAL(eve::medium(eve::cot)(T(-1)),T(my_stdcot(-1.0)), 1.0);
  TTS_IEEE_EQUAL(eve::medium(eve::cot)(T(0)), (eve::inf(eve::as<T>())));
  TTS_IEEE_EQUAL(eve::medium(eve::cot)(T(-0.)), (eve::minf(eve::as<T>())));
  TTS_ULP_EQUAL((eve::medium(eve::cot)(eve::pio_4(eve::as<T>()))), (T(my_stdcot(eve::pio_4(eve::as<v_t>())))), 1.5);
  TTS_ULP_EQUAL((eve::medium(eve::cot)(-eve::pio_4(eve::as<T>()))),(T(my_stdcot(-eve::pio_4(eve::as<v_t>())))), 1.5);
  TTS_ULP_EQUAL((eve::medium(eve::cot)(T(100.0))), T(my_stdcot(v_t(100.0))), 1.5);
  TTS_ULP_EQUAL((eve::medium(eve::cot)(T(-100.0))),T(my_stdcot(v_t(-100.0))), 1.5);
  TTS_ULP_EQUAL((eve::medium(eve::cot)(T(100000.0))), T(my_stdcot(v_t(100000.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium(eve::cot)(T(-100000.0))),T(my_stdcot(v_t(-100000.0))), 0.5);
}

