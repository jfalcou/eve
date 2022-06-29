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
TTS_CASE_TPL( "Check return types of bit_not"
        , eve::test::simd::all_types
        )
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::bit_not(T()  ) , T);
  TTS_EXPR_IS( eve::bit_not(v_t()) , v_t);

  // conditional
  TTS_EXPR_IS( eve::bit_not[logical<T>()](T())  , T);
  TTS_EXPR_IS( eve::bit_not[logical<v_t>()](T()), T);
  TTS_EXPR_IS( eve::bit_not[logical<T>()](v_t()), T);
};

//==================================================================================================
//  bit_not simd tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of bit_not(simd) on integral types"
        , eve::test::simd::integers
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              ,  tts::logicals(0, 3))
        )
<typename T, typename U>(T const& a0, U const & t)
{
  using v_t = eve::element_type_t<T>;
  using eve::detail::map;
  using eve::bit_not;
  TTS_EQUAL( bit_not(a0), map([](auto e) -> v_t{ return ~e; }, a0));
  TTS_EQUAL( eve::bit_not[t](a0), eve::if_else(t, eve::bit_not(a0), a0));
};

TTS_CASE_WITH( "Check behavior of bit_not(simd) on floating types"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              ,  tts::logicals(0, 3))
        )
<typename T, typename U>(T const& a0, U const & t)
{
  using eve::as;
  using eve::bit_not;
  using eve::bit_cast;
  using eve::detail::map;
   using i_t = eve::as_integer_t<eve::element_type_t<T>, signed>;
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL( bit_not(a0), map([](auto e)
                                   { return  bit_cast(~bit_cast(e, as(i_t())), as(v_t())); }, a0
                                  ));
  TTS_IEEE_EQUAL( eve::bit_not[t](a0), eve::if_else(t, eve::bit_not(a0), a0));
};
