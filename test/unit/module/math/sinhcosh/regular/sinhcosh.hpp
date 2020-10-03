//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinhcosh.hpp>
#include <eve/function/sinh.hpp>
#include <eve/function/cosh.hpp>
#include <eve/function/next.hpp>
#include <eve/function/all.hpp>
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
#include <array>
#include <cmath>

TTS_CASE("Check eve::sinhcosh return type")
{
  TTS_EXPR_IS(eve::sinhcosh(EVE_TYPE(0)), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check eve::sinhcosh behavior")
{
  if constexpr(eve::platform::supports_infinites)
  {
    std::array<EVE_VALUE, 3> a = {eve::nan(eve::as<EVE_VALUE>()), eve::inf(eve::as<EVE_VALUE>()), eve::minf(eve::as<EVE_VALUE>())};

    for(int i=0; i < 3 ; ++i)
    {
      auto [sh, ch] = eve::sinhcosh(EVE_TYPE(a[i]));
      TTS_IEEE_EQUAL(sh, (EVE_TYPE(std::sinh(a[i]))));
      TTS_IEEE_EQUAL(ch, (EVE_TYPE(std::cosh(a[i]))));
    }
  }

  EVE_VALUE ovflimit =  eve::Ieee_constant<EVE_VALUE,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384
  std::array<EVE_VALUE, 10> a = {EVE_VALUE(1), EVE_VALUE(-1), EVE_VALUE(0), EVE_VALUE(-0.0), EVE_VALUE(10), EVE_VALUE(-10)
                             , eve::maxlog(eve::as<EVE_VALUE>()), ovflimit/2, ovflimit, 2*ovflimit};

  for(size_t i=0; i < a.size(); ++i)
  {
    auto [sh, ch] = eve::sinhcosh(EVE_TYPE(a[i]));
    auto  sh1     = std::sinh(a[i]);
    auto  ch1     = std::cosh(a[i]);
    TTS_ULP_EQUAL(sh, (EVE_TYPE(sh1)), 0.5);
    TTS_ULP_EQUAL(ch, (EVE_TYPE(ch1)), 0.5);
  }

  {
    auto [sh, ch] = eve::sinhcosh(EVE_TYPE(-0.0));
    TTS_EXPECT(eve::all(eve::is_negative(sh)));
  }

  {
    auto [sh, ch] = eve::sinhcosh(EVE_TYPE(0.0));
    TTS_EXPECT(eve::all(eve::is_positive(sh)));
  }
}
