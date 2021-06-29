/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/rshl.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of rshl"
              , eve::test::simd::unsigned_types
              )
<typename T>(eve::as_<T>)
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
auto shift_max = []< typename T>(eve::as_<T> const &){return sizeof(eve::element_type_t<T>)*8-1;};
auto shift_min = []< typename T>(eve::as_<T> const &){return -sizeof(eve::element_type_t<T>)*8+1;};

EVE_TEST( "Check behavior of rshl on integral types"
        , eve::test::simd::unsigned_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::as_signed_integer(eve::test::randoms(shift_min, shift_max))
                              )
        )
  <typename T, typename U>(T const& a0, U const& a1)
{
  using eve::rshl;
  TTS_EQUAL( rshl(a0, a1), map([&](auto e, auto f) { return rshl(e, f); }, a0, a1));
  auto val = a1.get(0);
  TTS_EQUAL( rshl(a0, val), map([&](auto e) { return rshl(e, val); }, a0));
};
