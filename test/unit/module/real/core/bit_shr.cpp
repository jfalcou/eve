/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/bit_shr.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of bit_shr"
        , eve::test::simd::unsigned_types
        , eve::test::generate(eve::test::no_data)
        )
<typename T>(T)
{
  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using vi_t = eve::as_integer_t<v_t, signed>;
  using vu_t = eve::as_integer_t<v_t, unsigned>;

  //regular
  TTS_EXPR_IS( eve::bit_shr(T(), T()  ) , T);
  TTS_EXPR_IS( eve::bit_shr(T(), v_t()) , T);
  TTS_EXPR_IS( eve::bit_shr(v_t(), T()) , T);
  TTS_EXPR_IS( eve::bit_shr(v_t(), v_t()) , v_t);
  TTS_EXPR_IS( eve::bit_shr(T(), i_t()  ) , T);
  TTS_EXPR_IS( eve::bit_shr(T(), u_t()) , T);
  TTS_EXPR_IS( eve::bit_shr(v_t(), i_t()) , T);
  TTS_EXPR_IS( eve::bit_shr(v_t(), u_t()) , T);
  TTS_EXPR_IS( eve::bit_shr(T(), vi_t()  ) , T);
  TTS_EXPR_IS( eve::bit_shr(T(), vu_t()) , T);
  TTS_EXPR_IS( eve::bit_shr(v_t(), vi_t()) , v_t);
  TTS_EXPR_IS( eve::bit_shr(v_t(), vu_t()) , v_t);

};

//==================================================================================================
// bit_shr tests
//==================================================================================================
auto shift_max = []< typename T>(eve::as_<T> const &){return sizeof(eve::element_type_t<T>)*8-1;};

EVE_TEST( "Check behavior of bit_shr on integral types"
        , eve::test::simd::integers
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(0u, shift_max)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::bit_shr;
  TTS_EQUAL( bit_shr(a0, a1), T([&](auto i, auto) { return bit_shr(a0.get(i), a1.get(i)); }));

};

EVE_TEST( "Check behavior of bit_shr with scalar shift on integral types"
        , eve::test::simd::integers
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(0u, shift_max)
                              )
        )
<typename T, typename I>(T const& a0,I a1)
{
  using eve::bit_shr;
  auto val = a1.get(0);
  TTS_EQUAL( bit_shr(a0, val), T([&](auto i, auto) { return bit_shr(a0.get(i), val); }));
};
