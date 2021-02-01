//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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
