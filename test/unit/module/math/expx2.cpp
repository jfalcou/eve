//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of exp"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::expx2(T())  , T);
  TTS_EXPR_IS( eve::expx2(T())  , T);
  TTS_EXPR_IS( eve::expx2(v_t(), T()), T);
  TTS_EXPR_IS( eve::expx2(T(), v_t()), T);
  TTS_EXPR_IS( eve::expx2(v_t(), v_t()), v_t);
};


//==================================================================================================
// exp  tests
//==================================================================================================
auto mini = tts::constant([]<typename T>(eve::as<T> const & tgt) { return -eve::sqrt(eve::maxlog(tgt)); });
auto maxi = tts::constant([]<typename T>(eve::as<T> const & tgt) { return eve::sqrt(eve::maxlog(tgt)); });

TTS_CASE_WITH( "Check behavior of exp on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(mini, maxi)
                             , tts::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::expx2(a0), map([](auto e) -> v_t { long double le = e; return std::exp(le*le); }, a0), 200);
  TTS_ULP_EQUAL(eve::expx2(a1), map([](auto e) -> v_t { long double le = e; return std::exp(le*le); }, a1), 2);
  TTS_RELATIVE_EQUAL( eve::expx2(a0, a1)
               , map([](auto e, auto f) -> v_t { long double le = e; auto sig = eve::signnz(f); return std::exp(sig*le*le); }, a0, a1)
               , 0.001
               );
};

TTS_CASE_TPL( "Check expx2 2 parameters"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_ULP_EQUAL (eve::expx2(T(1)), eve::exp(T(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2(T(0)), T(1));
  TTS_IEEE_EQUAL(eve::expx2(T(4)), eve::exp(T(16)));
  TTS_IEEE_EQUAL(eve::expx2(T(-4)),eve::exp(T(16)));
  TTS_IEEE_EQUAL(eve::expx2(eve::nan(as<T>())) , eve::nan(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::inf(as<T>())) , eve::inf(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::minf(as<T>())), eve::inf(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(T(-0.)), T(1));
  TTS_ULP_EQUAL (eve::expx2(T(-1)) , eve::exp(T(1)), 0.5);

   TTS_ULP_EQUAL (eve::expx2(T(1), T(1)), eve::exp(T(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2(T(0), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::expx2(T(4), T(1)), eve::exp(T(16)));
  TTS_IEEE_EQUAL(eve::expx2(T(-4), T(1)),eve::exp(T(16)));
  TTS_IEEE_EQUAL(eve::expx2(eve::nan(as<T>()), T(1)) , eve::nan(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::inf(as<T>()), T(1)) , eve::inf(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::minf(as<T>()), T(1)), eve::inf(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(T(-0.), T(1)), T(1));
  TTS_ULP_EQUAL (eve::expx2(T(-1), T(1)) , eve::exp(T(1)), 0.5);

  TTS_ULP_EQUAL (eve::expx2(T(1), T(-1)), eve::exp(-T(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2(T(0), T(-1)), T(1));
  TTS_IEEE_EQUAL(eve::expx2(T(4), T(-1)), eve::exp(-T(16)));
  TTS_IEEE_EQUAL(eve::expx2(T(-4), T(-1)),eve::exp(-T(16)));
  TTS_IEEE_EQUAL(eve::expx2(eve::nan(as<T>()), T(-1)) , eve::nan(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::inf(as<T>()), T(-1)) , eve::zero(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::minf(as<T>()), T(-1)), eve::zero(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(T(-0.), T(-1)), T(1));
  TTS_ULP_EQUAL (eve::expx2(T(-1), T(-1)) , eve::exp(-T(1)), 0.5);
};
