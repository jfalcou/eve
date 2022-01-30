/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of fanm"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::fanm(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::fanm(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::fanm(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::fanm(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::fanm(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::fanm(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::fanm(v_t(), v_t(), v_t()) , v_t);

  if constexpr(eve::floating_value<T>)
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS( eve::fanm(T(), int(), int()  )  , T);
    TTS_EXPR_IS( eve::fanm(T(), v_t(), int())  , T);
    TTS_EXPR_IS( eve::fanm(v_t(), int(), T())  , T);
    TTS_EXPR_IS( eve::fanm(int(), T(), int())  , T);
    TTS_EXPR_IS( eve::fanm(wi_t(), int(), int())  , wi_t);
    TTS_EXPR_IS( eve::fanm(char(), wi_t(), int()), wi_t);
  }

};

//==================================================================================================
// fanm tests
//==================================================================================================
auto onepmileps = []<typename U>(eve::as<U>)
{
  return (eve::inc(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
};

auto onemmileps = []<typename U>(eve::as<U>)
{
  return (eve::oneminus(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
};

EVE_TEST( "Check precision behavior of fanm on real types"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(onemmileps, onepmileps)
                              ,  eve::test::randoms(onemmileps, onepmileps)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::fanm;
  using eve::fnma;
  using eve::detail::map;
  TTS_IEEE_EQUAL ( eve::pedantic(fanm)( -eve::one(eve::as<T>()), a0, a1)
                 , eve::pedantic(fnma)( a0, a1,  -eve::one(eve::as<T>()))
                 );
};

//==================================================================================================
//== fanm full range tests
//==================================================================================================
EVE_TEST( "Check behavior of fanm on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::as;
  using eve::fanm;
  using eve::fnma;
  using eve::detail::map;

  TTS_IEEE_EQUAL(fanm(a0, a1, a2), fnma(a1, a2, a0));
  TTS_IEEE_EQUAL(eve::pedantic(fanm)(a0, a1, a2), eve::pedantic(fnma)(a1, a2, a0) );
  TTS_IEEE_EQUAL(eve::numeric(fanm)(a0, a1, a2), eve::pedantic(fnma)(a1, a2, a0));
};

//==================================================================================================
//== fanm masked
//==================================================================================================
EVE_TEST( "Check behavior of fanm on all types full range"
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
  using eve::fanm;

  TTS_IEEE_EQUAL(fanm[t](a0, a1, a2), eve::if_else(t,fanm[t](a0, a1, a2), a0));
};
