/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of fsm"
              , eve::test::simd::all_types
              )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::fsm(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::fsm(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::fsm(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::fsm(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::fsm(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::fsm(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::fsm(v_t(), v_t(), v_t()) , v_t);

  if constexpr(eve::floating_value<T>)
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS( eve::fsm(T(), int(), int()  )  , T);
    TTS_EXPR_IS( eve::fsm(T(), v_t(), int())  , T);
    TTS_EXPR_IS( eve::fsm(v_t(), int(), T())  , T);
    TTS_EXPR_IS( eve::fsm(int(), T(), int())  , T);
    TTS_EXPR_IS( eve::fsm(wi_t(), int(), int())  , wi_t);
    TTS_EXPR_IS( eve::fsm(char(), wi_t(), int()), wi_t);
  }

};

//==================================================================================================
// fsm tests
//==================================================================================================
auto onepmileps = tts::constant([]<typename U>(eve::as<U>)
{
  return (eve::inc(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
});

auto onemmileps = tts::constant([]<typename U>(eve::as<U>)
{
  return (eve::oneminus(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
});

TTS_CASE_WITH( "Check precision behavior of fsm on real types"
        , eve::test::simd::ieee_reals
        , tts::generate (  tts::randoms(onemmileps, onepmileps)
                              ,  tts::randoms(onemmileps, onepmileps)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::fsm;
  using eve::fms;
  using eve::detail::map;
  TTS_IEEE_EQUAL ( eve::pedantic(fsm)( -eve::one(eve::as<T>()), a0, a1)
                 , eve::pedantic(fms)( a0, a1,  -eve::one(eve::as<T>()))
                 );
};

//==================================================================================================
//== fsm full range tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of fsm on all types full range"
        , eve::test::simd::all_types
        , tts::generate (  tts::randoms(eve::valmin, eve::valmax)
                              ,  tts::randoms(eve::valmin, eve::valmax)
                              ,  tts::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::as;
  using eve::fsm;
  using eve::fms;
  using eve::detail::map;

  TTS_IEEE_EQUAL(fsm(a0, a1, a2), fms(a1, a2, a0));
  TTS_IEEE_EQUAL(eve::pedantic(fsm)(a0, a1, a2), eve::pedantic(fms)(a1, a2, a0) );
  TTS_IEEE_EQUAL(eve::numeric(fsm)(a0, a1, a2), eve::pedantic(fms)(a1, a2, a0));
};

//==================================================================================================
//== fsm masked
//==================================================================================================
TTS_CASE_WITH( "Check behavior of fsm on all types full range"
        , eve::test::simd::all_types
        , tts::generate (  tts::randoms(eve::valmin, eve::valmax)
                              ,  tts::randoms(eve::valmin, eve::valmax)
                              ,  tts::randoms(eve::valmin, eve::valmax)
                              ,  tts::logicals(0, 3)
                              )
        )
<typename T, typename M>(  T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::as;
  using eve::fsm;

  TTS_IEEE_EQUAL(fsm[t](a0, a1, a2), eve::if_else(t,fsm[t](a0, a1, a2), a0));
};
