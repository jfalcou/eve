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
#include <eve/function/fma.hpp>
#include <eve/function/pedantic/fma.hpp>
#include <eve/function/numeric/fma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/round.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of fma"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::fma(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::fma(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::fma(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::fma(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::fma(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::fma(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::fma(v_t(), v_t(), v_t()) , v_t);

  if constexpr(eve::floating_value<T>)
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS( eve::fma(T(), int(), int()  )  , T);
    TTS_EXPR_IS( eve::fma(T(), v_t(), int())  , T);
    TTS_EXPR_IS( eve::fma(v_t(), int(), T())  , T);
    TTS_EXPR_IS( eve::fma(int(), T(), int())  , T);
    TTS_EXPR_IS( eve::fma(wi_t(), int(), int())  , wi_t);
    TTS_EXPR_IS( eve::fma(char(), wi_t(), int()), wi_t);
  }

};

//==================================================================================================
// fma tests
//==================================================================================================
auto onepmileps = []<typename U>(eve::as<U>)
{
  return (eve::inc(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
};

auto onemmileps = []<typename U>(eve::as<U>)
{
  return (eve::oneminus(1000*eve::eps(eve::as(eve::element_type_t<U>()))));
};

EVE_TEST( "Check precision behavior of fma on real types"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(onemmileps, onepmileps)
                              ,  eve::test::randoms(onemmileps, onepmileps)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::fma;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL ( eve::pedantic(fma)(a0, a1, -eve::one(eve::as<T>()))
                , map([&](auto e , auto f) -> v_t { return eve::pedantic(fma)(e, f, v_t(-1)); }, a0, a1)
                , 2
                );
};

//==================================================================================================
// fma full range tests
//==================================================================================================
EVE_TEST( "Check behavior of fma on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::as;
  using eve::fma;
  using eve::detail::map;

  using v_t = eve::element_type_t<T>;

  if (eve::all(eve::fma(onemmileps(eve::as(a0)), onepmileps(eve::as(a0)), T(-1)) == eve::pedantic(eve::fma)(onemmileps(eve::as(a0)), onepmileps(eve::as(a0)), T(-1))))
  {
    TTS_ULP_EQUAL(fma((a0), (a1), (a2)), map([&](auto e , auto f, auto g) -> v_t { return eve::pedantic(fma)(e, f, g); }, a0, a1, a2), 2);
  }
  else
  {
    TTS_ULP_EQUAL(fma((a0), (a1), (a2)), map([&](auto e , auto f, auto g) -> v_t { return e*f+g; }, a0, a1, a2), 2);
  }
  TTS_ULP_EQUAL(eve::pedantic(fma)((a0), (a1), (a2)), map([&](auto e , auto f, auto g) -> v_t { return eve::pedantic(fma)(e, f, g); }, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric(fma)((a0), (a1), (a2)), map([&](auto e , auto f, auto g) -> v_t { return eve::pedantic(fma)(e, f, g); }, a0, a1, a2), 2);
};

//==================================================================================================
// fma masked
//==================================================================================================
EVE_TEST( "Check behavior of fma on all types full range"
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
  using eve::fma;

  TTS_IEEE_EQUAL(fma[t](a0, a1, a2), eve::if_else(t,fma[t](a0, a1, a2), a0));
};
