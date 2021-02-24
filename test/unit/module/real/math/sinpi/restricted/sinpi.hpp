//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::restricted(eve::sinpi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted(eve::sinpi)(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::sinpi behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::sinpi)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::sinpi)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::sinpi)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_EXPECT(eve::all(eve::is_positive(eve::restricted(eve::sinpi)(T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::restricted(eve::sinpi)(T(-0.)))));

  TTS_IEEE_EQUAL(eve::restricted(eve::sinpi)(T(0))   , T(0) );
  TTS_IEEE_EQUAL(eve::restricted(eve::sinpi)(T(-0.)) , T(0) );

  TTS_ULP_EQUAL((eve::restricted(eve::sinpi)(T(0.125)))  , T(0.38268343236508977172845998403039886676134456248563) , 0.5);
  TTS_ULP_EQUAL((eve::restricted(eve::sinpi)(-T(0.125))) , T(-0.38268343236508977172845998403039886676134456248563), 0.5);
}
