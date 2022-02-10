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
EVE_TEST_TYPES( "Check return types of shl"
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
  TTS_EXPR_IS( eve::shl(T(), T()  ) , T);
  TTS_EXPR_IS( eve::shl(T(), v_t()) , T);
  TTS_EXPR_IS( eve::shl(v_t(), T()) , T);
  TTS_EXPR_IS( eve::shl(v_t(), v_t()) , v_t);
  TTS_EXPR_IS( eve::shl(T(), i_t()  ) , T);
  TTS_EXPR_IS( eve::shl(T(), u_t()) , T);
  TTS_EXPR_IS( eve::shl(v_t(), i_t()) , T);
  TTS_EXPR_IS( eve::shl(v_t(), u_t()) , T);
  TTS_EXPR_IS( eve::shl(T(), vi_t()  ) , T);
  TTS_EXPR_IS( eve::shl(T(), vu_t()) , T);
  TTS_EXPR_IS( eve::shl(v_t(), vi_t()) , v_t);
  TTS_EXPR_IS( eve::shl(v_t(), vu_t()) , v_t);

};

//==================================================================================================
// shl tests
//==================================================================================================
auto shift_max = []< typename T>(eve::as<T> const &){return sizeof(eve::element_type_t<T>)*8-1;};

EVE_TEST( "Check behavior of shl on integral types"
        , eve::test::simd::unsigned_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(0u, shift_max)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::shl;
  TTS_EQUAL( shl(a0, a1), T([&](auto i, auto) { return shl(a0.get(i), a1.get(i)); }));

};

EVE_TEST( "Check behavior of shl with scalar shift on integral types"
        , eve::test::simd::unsigned_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(0u, shift_max)
                              )
        )
<typename T, typename I>(T const& a0,I a1)
{
  using eve::shl;
  auto val = a1.get(0);
  TTS_EQUAL( shl(a0, val), T([&](auto i, auto) { return shl(a0.get(i), val); }));

};
