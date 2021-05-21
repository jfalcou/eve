//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinhcosh.hpp>
#include <eve/function/sinh.hpp>
#include <eve/function/cosh.hpp>
#include <eve/function/next.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/next.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <tuple>
#include <cmath>

TTS_CASE_TPL("Check eve::sinhcosh return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sinhcosh(T(0)), (std::tuple<T, T>));
}

TTS_CASE_TPL("Check eve::sinhcosh behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_infinites)
  {
    std::array<v_t, 3> a = {eve::nan(eve::as<v_t>()), eve::inf(eve::as<v_t>()), eve::minf(eve::as<v_t>())};

    for(int i=0; i < 3 ; ++i)
    {
      auto [sh, ch] = eve::sinhcosh(T(a[i]));
      TTS_IEEE_EQUAL(sh, (T(std::sinh(a[i]))));
      TTS_IEEE_EQUAL(ch, (T(std::cosh(a[i]))));
    }
  }
  v_t ovflimit =  eve::Ieee_constant<v_t,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384
  std::array<v_t, 10> a = {v_t(1), v_t(-1), v_t(0), v_t(-0.0), v_t(10), v_t(-10)
                             , eve::maxlog(eve::as<v_t>()), ovflimit/2, ovflimit, 2*ovflimit};

  for(size_t i=0; i < a.size(); ++i)
  {
    auto [sh, ch] = eve::sinhcosh(T(a[i]));
    auto  sh1     = std::sinh(a[i]);
    auto  ch1     = std::cosh(a[i]);
    TTS_ULP_EQUAL(sh, (T(sh1)), 0.5);
    TTS_ULP_EQUAL(ch, (T(ch1)), 0.5);
  }
  {
    auto [sh, ch] = eve::sinhcosh(T(-0.0));
    TTS_EXPECT(eve::all(eve::is_negative(sh)));
  }
  {
    auto [sh, ch] = eve::sinhcosh(T(0.0));
    TTS_EXPECT(eve::all(eve::is_positive(sh)));
  }
}
