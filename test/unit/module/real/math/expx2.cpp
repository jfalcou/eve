//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/function/diff/expx2.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/sqrt.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of exp"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
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
auto mini = []<typename T>(eve::as_<T> const & tgt)
{
  return -eve::sqrt(eve::maxlog(tgt));
};
auto maxi = []<typename T>(eve::as_<T> const & tgt)
{
  return eve::sqrt(eve::maxlog(tgt));
};

EVE_TEST( "Check behavior of exp on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(mini, maxi)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::expx2(a0)      , map([](auto e) -> v_t { long double le = e; return std::exp(le*le); }, a0), 100);
  TTS_ULP_EQUAL(eve::expx2(a1)      , map([](auto e) -> v_t { long double le = e; return std::exp(le*le); }, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::expx2)(a0), 2*a0*eve::expx2(a0), 2);
  TTS_ULP_EQUAL(eve::diff(eve::expx2)(a1), 2*a1*eve::expx2(a1), 2);
  TTS_ULP_EQUAL(eve::expx2(a0, a1)      , map([](auto e, auto f) -> v_t { long double le = e; auto sig = eve::signnz(f); return std::exp(sig*le*le); }, a0, a1), 100);
};

EVE_TEST_TYPES( "Check expx2 2 parameters"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
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
