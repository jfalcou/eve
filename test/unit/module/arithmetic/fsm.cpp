/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/mone.hpp>
#include <eve/function/all.hpp>
#include <eve/function/fsm.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/pedantic/fsm.hpp>
#include <eve/function/numeric/fsm.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/round.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of fsm"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
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
auto onepmileps = []<typename U>(eve::as<U>)
{
  return (eve::inc(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
};

auto onemmileps = []<typename U>(eve::as<U>)
{
  return (eve::oneminus(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
};

EVE_TEST( "Check precision behavior of fsm on real types"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(onemmileps, onepmileps)
                              ,  eve::test::randoms(onemmileps, onepmileps)
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
EVE_TEST( "Check behavior of fsm on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
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
EVE_TEST( "Check behavior of fsm on all types full range"
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
  using eve::fsm;

  TTS_IEEE_EQUAL(fsm[t](a0, a1, a2), eve::if_else(t,fsm[t](a0, a1, a2), a0));
};
