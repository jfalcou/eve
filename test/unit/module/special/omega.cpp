//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of omega", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::omega(T()), T);
  TTS_EXPR_IS(eve::omega(v_t()), v_t);
};

//==================================================================================================
// omega  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of omega on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(1.0, 1000),
                            tts::randoms(0.01, 1.0),
                            tts::randoms(-10.0, 0.0)))
<typename T>(T a0, T a1, T a2)
{
  using elt_t = eve::element_type_t<T>;
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::omega(eve::nan(eve::as(a0))), eve::nan(eve::as(a0)), 0.0);
    TTS_ULP_EQUAL(eve::omega(eve::inf(eve::as(a0))), eve::inf(eve::as(a0)), 0.0);
    TTS_ULP_EQUAL(eve::omega(T(1)), T(1), 2.0);
    TTS_ULP_EQUAL(eve::omega(eve::zero(eve::as(a0))), T(0.56714329040978384011), 0.0);
    elt_t tol = 5000 * eve::eps(eve::as<elt_t>());
    {
      auto z = eve::omega(eve::mone(eve::as<elt_t>()));
      auto r = eve::log(z) + z;
      TTS_RELATIVE_EQUAL(eve::mone(eve::as<elt_t>()), r, tol);
    }
    {
      auto z = eve::omega(a0);
      auto r = eve::log(z) + z;
      TTS_RELATIVE_EQUAL(a0, r, tol);
    }
    {
      auto z = eve::omega(a1);
      auto r = eve::log(z) + z;
      TTS_RELATIVE_EQUAL(a1, r, tol);
    }
    {
      auto z = eve::omega(a2);
      auto r = eve::log(z) + z;
      TTS_RELATIVE_EQUAL(a2, r, tol);
    }
  }
};


//==================================================================================================
// Tests for masked omega
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::omega)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::omega[mask](a0),
            eve::if_else(mask, eve::omega(a0), a0));
};
