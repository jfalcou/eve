//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cosh.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::cosh return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cosh(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::cosh behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cosh(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::cosh(eve::inf(eve::as<T>())) , (eve::inf(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::cosh(eve::minf(eve::as<T>())), (eve::inf(eve::as<T>())) );
  }

  TTS_ULP_EQUAL(eve::cosh(T(1)), T(std::cosh(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::cosh(T(-1)),T(std::cosh(-1.0)), 0.5);

  using v_t = eve::element_type_t<T>;

  v_t ovl =  eve::Ieee_constant<v_t,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384
  v_t a[] = { v_t(1), v_t(-1), v_t(0), v_t(-0.0), v_t(10), v_t(-10), eve::maxlog(eve::as<v_t>())
            , ovl/2, ovl, 2*ovl, -eve::maxlog(eve::as<v_t>()), -ovl/2, -ovl, -2*ovl
            };

  for(auto v : a)
  {
    auto  res = eve::cosh(T(v));
    v_t   ref = std::cosh(double(v));

    TTS_ULP_EQUAL(res, (T(ref)), 0.5);
  }
}
