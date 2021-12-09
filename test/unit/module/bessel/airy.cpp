//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/airy_ai.hpp>
#include <eve/function/airy_bi.hpp>
#include <eve/function/airy.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>
#include <boost/math/special_functions/airy.hpp>

EVE_TEST_TYPES( "Check return types of airy_ai"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using kv_t =  kumi::tuple<v_t, v_t>;
  using kT =    kumi::tuple<T, T>;
  TTS_EXPR_IS(eve::airy(T(0)), kT);
  TTS_EXPR_IS(eve::airy(v_t(0)), kv_t);
};

 EVE_TEST( "Check behavior of airy on wide"
         , eve::test::simd::ieee_reals
         , eve::test::generate(eve::test::randoms(-20.0, 0.0),
                               eve::test::randoms(0.0, 20.0)
                              )
         )
   <typename T>(T a0, T a1)
{
  using v_t = eve::element_type_t<T>;
  v_t abstol = 1000*eve::eps(eve::as<v_t>());
  auto eve_airy =  [](auto x) { return eve::airy(x); };
  auto std_airy_ai =  [](auto x)->v_t { return eve::airy_ai(x); };
  auto std_airy_bi =  [](auto x)->v_t { return eve::airy_bi(x); };

  {
    auto [ai, bi]= eve_airy(a0);
    TTS_ABSOLUTE_EQUAL(ai, map(std_airy_ai, a0), abstol);
    TTS_RELATIVE_EQUAL(bi, map(std_airy_bi, a0), 0.0004);
  }
  {
    auto [ai, bi]= eve_airy(a1);
    TTS_ABSOLUTE_EQUAL(ai, map(std_airy_ai, a1), abstol);
    TTS_RELATIVE_EQUAL(bi, map(std_airy_bi, a1), 0.0004);
  }

};
