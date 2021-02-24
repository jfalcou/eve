//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
TTS_CASE_TPL("Check operator* return type", EVE_TYPE)
{
  TTS_EXPR_IS( T()         * T()         , T );
  TTS_EXPR_IS( EVE_VALUE() * T()         , T );
  TTS_EXPR_IS( T()         * EVE_VALUE() , T );
}

TTS_CASE_TPL("Check operator* behavior", EVE_TYPE)
{
  TTS_EQUAL((T( 0) * T(1)), (T(0  )));
  TTS_EQUAL((T( 1) * T(1)), (T(1  )));
  TTS_EQUAL((T(12) * T(4)), (T(48 )));

  TTS_EQUAL((EVE_VALUE( 0) * T(1)), (T(0  )));
  TTS_EQUAL((EVE_VALUE( 1) * T(1)), (T(1  )));
  TTS_EQUAL((EVE_VALUE(12) * T(4)), (T(48 )));

  TTS_EQUAL((T( 0) * EVE_VALUE(1)), (T(0  )));
  TTS_EQUAL((T( 1) * EVE_VALUE(1)), (T(1  )));
  TTS_EQUAL((T(12) * EVE_VALUE(4)), (T(48 )));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL((T(-1) * T(1)) , (T(-1)));
    TTS_EQUAL((T(-6) * T(-2)), (T(12)));

    TTS_EQUAL((EVE_VALUE(-1) * T(1)) , (T(-1)));
    TTS_EQUAL((EVE_VALUE(-6) * T(-2)), (T(12)));

    TTS_EQUAL((T(-1) * EVE_VALUE(1)) , (T(-1)));
    TTS_EQUAL((T(-6) * EVE_VALUE(-2)), (T(12)));
  }
}
