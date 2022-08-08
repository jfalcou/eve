//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/special.hpp>

#include <cmath>

#include <boost/math/special_functions/lambert_w.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of lambert", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using kT   = kumi::tuple<T, T>;
  using kv_t = kumi::tuple<v_t, v_t>;
  TTS_EXPR_IS(eve::lambert(T()), kT);
  TTS_EXPR_IS(eve::lambert(v_t()), kv_t);
};

//==================================================================================================
// lambert  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of lambert on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-0.367879, 0.367879),
                            tts::randoms(-0.367879, 0.0),
                            tts::randoms(0, 10.0),
                            tts::randoms(-0.367879, -0.367879 + 1.0e-6)))
<typename T>(T a0, T a1, T a2, T a3)
{
  using elt_t = eve::element_type_t<T>;
  if constexpr( eve::platform::supports_invalids )
  {
    {
      auto [w0, wm1] = eve::lambert(eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::nan(eve::as<T>()));
    }
    {
      auto [w0, wm1] = eve::lambert(eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::inf(eve::as<T>()));
    }
    {
      auto [w0, wm1] = eve::lambert(eve::mone(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::nan(eve::as<T>()));
    }
  }
  {
    auto [w0, wm1] = eve::lambert(eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(wm1, eve::zero(eve::as<T>()));
  }
  {
    auto [w0, wm1] = eve::lambert(eve::mzero(eve::as<T>()));
    TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(wm1, eve::minf(eve::as<T>()));
  }
  {
    using v_t    = eve::element_type_t<T>;
    auto std_w0  = [](auto v) -> v_t { return boost::math::lambert_w0(v); };
    auto std_wm1 = [](auto v) -> v_t
    { return eve::is_positive(v) ? boost::math::lambert_w0(v) : boost::math::lambert_wm1(v); };
    {
      auto [w0, wm1] = eve::lambert(a0);
      TTS_ULP_EQUAL(w0, map(std_w0, a0), 10.0);
      TTS_RELATIVE_EQUAL(wm1, map(std_wm1, a0), 0.001);
    }
    {
      auto [w0, wm1] = eve::lambert(a1);
      TTS_ULP_EQUAL(w0, map(std_w0, a1), 512.0);
      TTS_RELATIVE_EQUAL(wm1, map(std_wm1, a1), 0.001);
    }
    {
      elt_t tol      = 10000 * eve::eps(eve::as<elt_t>());
      auto [w0, wm1] = eve::lambert(a2);
      TTS_ABSOLUTE_EQUAL(w0, map(std_w0, a2), tol);
      TTS_ABSOLUTE_EQUAL(wm1, map(std_wm1, a2), tol);
    }
    {
      elt_t tol      = 10000 * eve::eps(eve::as<elt_t>());
      auto [w0, wm1] = eve::lambert(a3);
      TTS_ABSOLUTE_EQUAL(w0, map(std_w0, a3), tol);
      TTS_RELATIVE_EQUAL(wm1, map(std_wm1, a3), 0.001);
    }
  }
};

TTS_CASE_WITH("Check behavior of lambert on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-0.367879, 0.367879),
                            tts::randoms(-0.367879, 0.0),
                            tts::randoms(0, 10.0),
                            tts::randoms(-0.367879, -0.367879 + 1.0e-6)))
<typename T>(T a0, T a1, T a2, T a3)
{
  using elt_t = eve::element_type_t<T>;
  if constexpr( eve::platform::supports_invalids )
  {
    {
      auto [w0, wm1] = eve::lambert(eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::nan(eve::as<T>()));
    }
    {
      auto [w0, wm1] = eve::lambert(eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::inf(eve::as<T>()));
    }
    {
      auto [w0, wm1] = eve::lambert(eve::mone(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::nan(eve::as<T>()));
    }
  }
  {
    auto [w0, wm1] = eve::lambert(eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(wm1, eve::zero(eve::as<T>()));
  }
  {
    auto [w0, wm1] = eve::lambert(eve::mzero(eve::as<T>()));
    TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(wm1, eve::minf(eve::as<T>()));
  }
  {
    using v_t    = eve::element_type_t<T>;
    auto std_w0  = [](auto v) -> v_t { return boost::math::lambert_w0(v); };
    auto std_wm1 = [](auto v) -> v_t
    { return eve::is_positive(v) ? boost::math::lambert_w0(v) : boost::math::lambert_wm1(v); };
    {
      auto [w0, wm1] = eve::lambert(a0);
      TTS_ULP_EQUAL(w0, map(std_w0, a0), 10.0);
      TTS_RELATIVE_EQUAL(wm1, map(std_wm1, a0), 0.001);
    }
    {
      auto [w0, wm1] = eve::lambert(a1);
      TTS_ULP_EQUAL(w0, map(std_w0, a1), 512.0);
      TTS_RELATIVE_EQUAL(wm1, map(std_wm1, a1), 0.001);
    }
    {
      elt_t tol      = 10000 * eve::eps(eve::as<elt_t>());
      auto [w0, wm1] = eve::lambert(a2);
      TTS_ABSOLUTE_EQUAL(w0, map(std_w0, a2), tol);
      TTS_ABSOLUTE_EQUAL(wm1, map(std_wm1, a2), tol);
    }
    {
      elt_t tol      = 10000 * eve::eps(eve::as<elt_t>());
      auto [w0, wm1] = eve::lambert(a3);
      TTS_ABSOLUTE_EQUAL(w0, map(std_w0, a3), tol);
      TTS_RELATIVE_EQUAL(wm1, map(std_wm1, a3), 0.001);
    }
  }
};
