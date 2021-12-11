//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/lambert.hpp>
#include <eve/function/diff/lambert.hpp>
#include <boost/math/special_functions/lambert_w.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of lambert"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using kT  = kumi::tuple<T,T>;
  using kv_t= kumi::tuple<v_t, v_t>;
  TTS_EXPR_IS( eve::lambert(T())  ,kT);
  TTS_EXPR_IS( eve::lambert(v_t()), kv_t);
};

//==================================================================================================
// lambert  tests
//==================================================================================================
EVE_TEST( "Check behavior of lambert on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-0.367879, 0.367879)
                             , eve::test::randoms(-0.367879,0.0)
                             , eve::test::randoms(0, 10.0)
                             , eve::test::randoms(-0.367879, -0.367879+1.0e-6)
                             )
        )
  <typename T>(T a0, T a1, T a2,  T a3)
{
  using elt_t = eve::element_type_t<T>;
  if constexpr( eve::platform::supports_invalids )
  {
    {
      auto[w0, wm1] = eve::lambert(eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::nan(eve::as<T>()));
    }
    {
      auto[w0, wm1] = eve::lambert(eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::inf(eve::as<T>()));
    }
    {
      auto[w0, wm1] = eve::lambert(eve::mone(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::nan(eve::as<T>()));
    }
  }
  {
    auto[w0, wm1] = eve::lambert(eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(wm1, eve::zero(eve::as<T>()));
  }
  {
    auto[w0, wm1] = eve::lambert(eve::mzero(eve::as<T>()));
    TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(wm1, eve::minf(eve::as<T>()));
  }
  {
    using v_t =  eve::element_type_t<T>;
    auto std_w0  = [](auto v)->v_t{return boost::math::lambert_w0(v); };
    auto std_wm1 = [](auto v)->v_t{return eve::is_positive(v) ? boost::math::lambert_w0(v) : boost::math::lambert_wm1(v); };
    {
      auto[w0, wm1] = eve::lambert(a0);
      TTS_ULP_EQUAL(w0, map(std_w0, a0), 10.0);
      TTS_ULP_EQUAL(wm1,map(std_wm1, a0), 10.0);
    }
    {
      auto[w0, wm1] = eve::lambert(a1);
      TTS_ULP_EQUAL(w0, map(std_w0, a1), 10.0);
      TTS_ULP_EQUAL(wm1,map(std_wm1, a1), 3.0);
    }
    {
      auto[w0, wm1] = eve::lambert(a2);
      TTS_ULP_EQUAL(w0, map(std_w0, a2), 3.0);
      TTS_ULP_EQUAL(wm1,map(std_wm1, a2), 3.0);
    }
    {
      elt_t tol = 5000*eve::eps(eve::as<elt_t>());
      auto[w0, wm1] = eve::lambert(a3);
      TTS_ABSOLUTE_EQUAL(w0, map(std_w0, a3), tol);
      TTS_ABSOLUTE_EQUAL(wm1,map(std_wm1, a3), tol);
    }
 }
};

EVE_TEST( "Check behavior of lambert on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-0.367879, 0.367879)
                             , eve::test::randoms(-0.367879,0.0)
                             , eve::test::randoms(0, 10.0)
                             , eve::test::randoms(-0.367879, -0.367879+1.0e-6)
                             )
        )
  <typename T>(T a0, T a1, T a2,  T a3)
{
  using elt_t = eve::element_type_t<T>;
  if constexpr( eve::platform::supports_invalids )
  {
    {
      auto[w0, wm1] = eve::lambert(eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::nan(eve::as<T>()));
    }
    {
      auto[w0, wm1] = eve::lambert(eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::inf(eve::as<T>()));
    }
    {
      auto[w0, wm1] = eve::lambert(eve::mone(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::nan(eve::as<T>()));
    }
  }
  {
    auto[w0, wm1] = eve::lambert(eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(wm1, eve::zero(eve::as<T>()));
  }
  {
    auto[w0, wm1] = eve::lambert(eve::mzero(eve::as<T>()));
    TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(wm1, eve::minf(eve::as<T>()));
  }
  {
    using v_t =  eve::element_type_t<T>;
    auto std_w0  = [](auto v)->v_t{return boost::math::lambert_w0(v); };
    auto std_wm1 = [](auto v)->v_t{return eve::is_positive(v) ? boost::math::lambert_w0(v) : boost::math::lambert_wm1(v); };
    {
      auto[w0, wm1] = eve::lambert(a0);
      TTS_ULP_EQUAL(w0, map(std_w0, a0), 10.0);
      TTS_ULP_EQUAL(wm1,map(std_wm1, a0), 10.0);
    }
    {
      auto[w0, wm1] = eve::lambert(a1);
      TTS_ULP_EQUAL(w0, map(std_w0, a1), 10.0);
      TTS_ULP_EQUAL(wm1,map(std_wm1, a1), 3.0);
    }
    {
      auto[w0, wm1] = eve::lambert(a2);
      TTS_ULP_EQUAL(w0, map(std_w0, a2), 3.0);
      TTS_ULP_EQUAL(wm1,map(std_wm1, a2), 3.0);
    }
    {
      elt_t tol = 5000*eve::eps(eve::as<elt_t>());
      auto[w0, wm1] = eve::lambert(a3);
      TTS_ABSOLUTE_EQUAL(w0, map(std_w0, a3), tol);
      TTS_ABSOLUTE_EQUAL(wm1,map(std_wm1, a3), tol);
    }
 }
};

EVE_TEST( "Check behavior of lambert diff on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-0.367879, 0.367879)
                             , eve::test::randoms(-0.367879,0.0)
                             , eve::test::randoms(0, 10.0)
                             )
        )
  <typename T>(T a0, T a1, T a2)
{
  using eve::diff;
  if constexpr( eve::platform::supports_invalids )
  {
    {
      auto[w0, wm1] = diff(eve::lambert)(eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::nan(eve::as<T>()));
    }
    {
      auto[w0, wm1] = diff(eve::lambert)(eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::zero(eve::as<T>()));
    }
    {
      auto[w0, wm1] = diff(eve::lambert)(eve::mone(eve::as<T>()));
      TTS_IEEE_EQUAL(w0, eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(wm1, eve::nan(eve::as<T>()));
    }
  }
  {
    auto[w0, wm1] = diff(eve::lambert)(eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(wm1, eve::zero(eve::as<T>()));
  }
  {
    auto[w0, wm1] = diff(eve::lambert)(eve::mzero(eve::as<T>()));
    TTS_IEEE_EQUAL(w0, eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(wm1, eve::minf(eve::as<T>()));
  }
  {
    using v_t =  eve::element_type_t<T>;
    auto dstd_w0  = [](auto v)->v_t{return boost::math::lambert_w0_prime(v); };
    auto dstd_wm1 = [](auto v)->v_t{return eve::is_positive(v) ? boost::math::lambert_w0_prime(v) : boost::math::lambert_wm1_prime(v); };
    {
      auto[w0, wm1] = diff(eve::lambert)(a0);
      TTS_ULP_EQUAL(w0, map(dstd_w0, a0), 10.0);
      TTS_ULP_EQUAL(wm1,map(dstd_wm1, a0), 10.0);
    }
    {
      auto[w0, wm1] = diff(eve::lambert)(a1);
      TTS_ULP_EQUAL(w0, map(dstd_w0, a1), 10.0);
      TTS_ULP_EQUAL(wm1,map(dstd_wm1, a1),10.0);
    }
    {
      auto[w0, wm1] = diff(eve::lambert)(a2);
      TTS_ULP_EQUAL(w0, map(dstd_w0, a2), 3.0);
      TTS_ULP_EQUAL(wm1,map(dstd_wm1, a2), 3.0);
    }
 }
};
