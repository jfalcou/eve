//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
TTS_CASE_TPL("Check operator- return type", EVE_TYPE)
{
  TTS_EXPR_IS( -T(0)      , T );
  TTS_EXPR_IS( T(0) - T(0), T );
}

TTS_CASE_TPL("Check operator- behavior", EVE_TYPE)
{
  TTS_EQUAL(-T( 1), static_cast<T>(-1));
  TTS_EQUAL(-T(-1), static_cast<T>( 1));

  TTS_EQUAL((T(4) - T(2)), static_cast<T>(2));
  TTS_EQUAL((T(2) - T(4)), static_cast<T>(-2));
}
