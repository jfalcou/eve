/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/function/all.hpp>
#include <eve/function/lerp.hpp>
#include <eve/function/pedantic/lerp.hpp>
#include <eve/function/numeric/lerp.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/round.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of lerp"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::lerp(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::lerp(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::lerp(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::lerp(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::lerp(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::lerp(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::lerp(v_t(), v_t(), v_t()) , v_t);
};

//==================================================================================================
// lerp tests
//==================================================================================================
auto mini = []<typename U>(eve::as<U>)
{
  return (-eve::sqrtvalmax(eve::as(eve::element_type_t<U>())));
};

EVE_TEST( "Check behavior of lerp on ieee floating"
        , eve::test::simd::ieee_reals
        , eve::test::generate (  eve::test::randoms(mini, eve::sqrtvalmax)
                              ,  eve::test::randoms(mini, eve::sqrtvalmax)
                              ,  eve::test::randoms(0.0, 1.0)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::lerp;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::raw(lerp) ((a0), (a1), (a2)), map([&](auto e , auto f, auto g) -> v_t { return std::lerp(e, f, g); }, a0, a1, a2), 8);
  TTS_ULP_EQUAL(lerp ((a0), (a1), (a2)), map([&](auto e , auto f, auto g) -> v_t { return std::lerp(e, f, g); }, a0, a1, a2), 8);
  TTS_ULP_EQUAL(eve::pedantic(lerp)((a0), (a1), (a2)), map([&](auto e , auto f, auto g) -> v_t {return std::lerp(e, f, g); }, a0, a1, a2), 4);
  TTS_ULP_EQUAL(eve::numeric(lerp)((a0), (a1), (a2)), map([&](auto e , auto f, auto g) -> v_t { return std::lerp(e, f, g); }, a0, a1, a2), 4);
};
