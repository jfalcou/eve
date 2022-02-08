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
EVE_TEST_TYPES( "Check return types of fsnm"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::fsnm(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::fsnm(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::fsnm(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::fsnm(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::fsnm(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::fsnm(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::fsnm(v_t(), v_t(), v_t()) , v_t);

  if constexpr(eve::floating_value<T>)
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS( eve::fsnm(T(), int(), int()  )  , T);
    TTS_EXPR_IS( eve::fsnm(T(), v_t(), int())  , T);
    TTS_EXPR_IS( eve::fsnm(v_t(), int(), T())  , T);
    TTS_EXPR_IS( eve::fsnm(int(), T(), int())  , T);
    TTS_EXPR_IS( eve::fsnm(wi_t(), int(), int())  , wi_t);
    TTS_EXPR_IS( eve::fsnm(char(), wi_t(), int()), wi_t);
  }

};

//==================================================================================================
// fsnm tests
//==================================================================================================
auto onepmileps = []<typename U>(eve::as<U>)
{
  return (eve::inc(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
};

auto onemmileps = []<typename U>(eve::as<U>)
{
  return (eve::oneminus(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
};

EVE_TEST( "Check precision behavior of fsnm on real types"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(onemmileps, onepmileps)
                              ,  eve::test::randoms(onemmileps, onepmileps)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::fsnm;
  using eve::fnms;
  using eve::detail::map;
  TTS_IEEE_EQUAL ( eve::pedantic(fsnm)( -eve::one(eve::as<T>()), a0, a1)
                 , eve::pedantic(fnms)( a0, a1,  -eve::one(eve::as<T>()))
                 );
};

//==================================================================================================
//== fsnm full range tests
//==================================================================================================
EVE_TEST( "Check behavior of fsnm on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::as;
  using eve::fsnm;
  using eve::fnms;
  using eve::detail::map;

  TTS_IEEE_EQUAL(fsnm(a0, a1, a2), fnms(a1, a2, a0));
  TTS_IEEE_EQUAL(eve::pedantic(fsnm)(a0, a1, a2), eve::pedantic(fnms)(a1, a2, a0) );
  TTS_IEEE_EQUAL(eve::numeric(fsnm)(a0, a1, a2), eve::pedantic(fnms)(a1, a2, a0));
};

//==================================================================================================
//== fsnm masked
//==================================================================================================
EVE_TEST( "Check behavior of fsnm on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::logicals(0, 3)
                              )
        )
<typename T, typename M>(  T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::as;
  using eve::fsnm;

  TTS_IEEE_EQUAL(fsnm[t](a0, a1, a2), eve::if_else(t,fsnm[t](a0, a1, a2), a0));
};
