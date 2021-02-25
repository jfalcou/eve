//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_shr.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_shr return type", EVE_TYPE)
{
  using ui_t = eve::as_integer_t<T, unsigned>;
  using si_t = eve::as_integer_t<T, signed>;

  TTS_EXPR_IS(eve::bit_shr(T(), int()),  T);
  TTS_EXPR_IS(eve::bit_shr(T(), ui_t()), T);
  TTS_EXPR_IS(eve::bit_shr(T(), si_t()), T);
}

TTS_CASE_TPL( "Check eve::bit_shr behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::bit_shr(T(4), 1), T(2) );
  TTS_EQUAL(eve::bit_shr(T(2), 1), T(1) );
  TTS_EQUAL(eve::bit_shr(T(1), 1), T(0) );
  TTS_EQUAL(eve::bit_shr(T(0), 1), T(0) );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::bit_shr( T(-1), (sizeof(v_t)*8-1)), T(1) );
    TTS_EQUAL(eve::bit_shr( T(-1), (sizeof(v_t)*8-2)), T(3) );
  }
  else
  {
    TTS_EQUAL(eve::bit_shr(eve::valmax(eve::as<T>()),(sizeof(v_t)*8-1)), T(1) );
    TTS_EQUAL(eve::bit_shr(eve::valmax(eve::as<T>()),(sizeof(v_t)*8-2)), T(3) );
  }
}
