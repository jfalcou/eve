/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of rshr"
              , eve::test::simd::unsigned_types
              )
<typename T>(eve::as<T>)
{
  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::as_integer_t<v_t, signed>;
  using vu_t = eve::as_integer_t<v_t, unsigned>;

  //regular
  TTS_EXPR_IS( eve::rshr(T(), T()  ) , T);
  TTS_EXPR_IS( eve::rshr(T(), v_t()) , T);
  TTS_EXPR_IS( eve::rshr(v_t(), T()) , T);
  TTS_EXPR_IS( eve::rshr(v_t(), v_t()) , v_t);
  TTS_EXPR_IS( eve::rshr(T(), i_t()  ) , T);
  TTS_EXPR_IS( eve::rshr(T(), u_t()) , T);
  TTS_EXPR_IS( eve::rshr(v_t(), i_t()) , T);
  TTS_EXPR_IS( eve::rshr(v_t(), u_t()) , T);
  TTS_EXPR_IS( eve::rshr(T(), vi_t()  ) , T);
  TTS_EXPR_IS( eve::rshr(T(), vu_t()) , T);
  TTS_EXPR_IS( eve::rshr(v_t(), vi_t()) , v_t);
  TTS_EXPR_IS( eve::rshr(v_t(), vu_t()) , v_t);

};

//==================================================================================================
// rshr tests
//==================================================================================================
auto shift_max = []< typename T>(eve::as<T> const &){ return static_cast<T>(sizeof(eve::element_type_t<T>))*8-1;};
auto shift_min = []< typename T>(eve::as<T> const &){ return -static_cast<T>(sizeof(eve::element_type_t<T>))*8+1; };

EVE_TEST( "Check behavior of rshr on integral types"
        , eve::test::simd::unsigned_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::as_signed_integer(eve::test::randoms(shift_min, shift_max))
                              )
        )
  <typename T, typename U>(T const& a0, U const& a1)
{
  using eve::rshr;
  TTS_EQUAL( rshr(a0, a1), map([&](auto e, auto f) { return rshr(e, f); }, a0, a1));

  auto val = a1.get(0);
  TTS_EQUAL( rshr(a0, val), map([&](auto e) { return rshr(e, val); }, a0));
};
