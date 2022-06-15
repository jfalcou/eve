/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of rshl"
              , eve::test::simd::unsigned_integers
              )
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::as_integer_t<v_t, signed>;
  using vu_t = eve::as_integer_t<v_t, unsigned>;

  //regular
  TTS_EXPR_IS( eve::rshl(T(), T()  ) , T);
  TTS_EXPR_IS( eve::rshl(T(), v_t()) , T);
  TTS_EXPR_IS( eve::rshl(v_t(), T()) , T);
  TTS_EXPR_IS( eve::rshl(v_t(), v_t()) , v_t);
  TTS_EXPR_IS( eve::rshl(T(), i_t()  ) , T);
  TTS_EXPR_IS( eve::rshl(T(), u_t()) , T);
  TTS_EXPR_IS( eve::rshl(v_t(), i_t()) , T);
  TTS_EXPR_IS( eve::rshl(v_t(), u_t()) , T);
  TTS_EXPR_IS( eve::rshl(T(), vi_t()  ) , T);
  TTS_EXPR_IS( eve::rshl(T(), vu_t()) , T);
  TTS_EXPR_IS( eve::rshl(v_t(), vi_t()) , v_t);
  TTS_EXPR_IS( eve::rshl(v_t(), vu_t()) , v_t);

};

//==================================================================================================
// rshl tests
//==================================================================================================
auto shift_max = []<typename T>(eve::as<T> const &){ return  static_cast<T>(sizeof(eve::element_type_t<T>))*8-1;};
auto shift_min = []<typename T>(eve::as<T> const &){ return -static_cast<T>(sizeof(eve::element_type_t<T>))*8+1; };

TTS_CASE_WITH ( "Check behavior of rshl on integral types"
              , eve::test::simd::unsigned_integers
              , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              , tts::as_signed_integer( tts::randoms( tts::constant(shift_min)
                                                                    , tts::constant(shift_max)
                                                                    )
                                                      )
                              )
              )
  <typename T, typename U>(T const& a0, U const& a1)
{
  using eve::rshl;
  TTS_EQUAL( rshl(a0, a1), map([&](auto e, auto f) { return rshl(e, f); }, a0, a1));
  auto val = a1.get(0);
  TTS_EQUAL( rshl(a0, val), map([&](auto e) { return rshl(e, val); }, a0));
};
