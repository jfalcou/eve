//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
TTS_CASE_TPL("Check operator% return type", EVE_TYPE)
{
  TTS_EXPR_IS((T()         % T()        ), T);
  TTS_EXPR_IS((T()         % EVE_VALUE()), T);
  TTS_EXPR_IS((EVE_VALUE() % T()        ), T);
}

TTS_CASE_TPL("Check operator% behavior", EVE_TYPE)
{
  using v_t = EVE_VALUE;

  TTS_EQUAL((T( 0) % T(3)), (T(0)));
  TTS_EQUAL((T( 1) % T(3)), (T(1)));
  TTS_EQUAL((T( 2) % T(3)), (T(2)));
  TTS_EQUAL((T( 3) % T(3)), (T(0)));
  TTS_EQUAL((T( 4) % T(3)), (T(1)));
  TTS_EQUAL((T( 6) % T(3)), (T(0)));
  TTS_EQUAL((T( 8) % T(3)), (T(2)));

  TTS_EQUAL((v_t( 0) % T(3)), (T(0)));
  TTS_EQUAL((v_t( 1) % T(3)), (T(1)));
  TTS_EQUAL((v_t( 2) % T(3)), (T(2)));
  TTS_EQUAL((v_t( 3) % T(3)), (T(0)));
  TTS_EQUAL((v_t( 4) % T(3)), (T(1)));
  TTS_EQUAL((v_t( 6) % T(3)), (T(0)));
  TTS_EQUAL((v_t( 8) % T(3)), (T(2)));

  TTS_EQUAL((T( 0) % v_t(3)), (T(0)));
  TTS_EQUAL((T( 1) % v_t(3)), (T(1)));
  TTS_EQUAL((T( 2) % v_t(3)), (T(2)));
  TTS_EQUAL((T( 3) % v_t(3)), (T(0)));
  TTS_EQUAL((T( 4) % v_t(3)), (T(1)));
  TTS_EQUAL((T( 6) % v_t(3)), (T(0)));
  TTS_EQUAL((T( 8) % v_t(3)), (T(2)));
}
