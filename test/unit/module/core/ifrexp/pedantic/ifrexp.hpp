//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ifrexp.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <tuple>

using i_t = eve::detail::as_integer_t<EVE_TYPE,signed>;

TTS_CASE("Check ifrexp return type")
{
  TTS_EXPR_IS(eve::pedantic(eve::ifrexp)(EVE_TYPE()), (std::tuple<EVE_TYPE,i_t>));
}

TTS_CASE("Check eve::pedantic(eve::ifrexp) behavior")
{
  {
    auto [p0, p1] = eve::pedantic(eve::ifrexp)(EVE_TYPE(1));
    TTS_EQUAL(p0, EVE_TYPE(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
  {
    auto [p0, p1] = eve::pedantic(eve::ifrexp)(EVE_TYPE(0));
    TTS_EQUAL (p0 , EVE_TYPE(0));
    TTS_EQUAL (p1, i_t(0));
  }
  if constexpr(eve::platform::supports_nans)
  {
    auto [r0, r1] = eve::pedantic(eve::ifrexp)(eve::nan(eve::as<EVE_TYPE>()));

    TTS_IEEE_EQUAL(r0 , (eve::nan(eve::as<EVE_TYPE>())));
    TTS_EQUAL     (r1, (i_t(0)));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    auto [r0, r1] = eve::pedantic(eve::ifrexp)(eve::inf(eve::as<EVE_TYPE>()));
    auto [q0, q1] = eve::pedantic(eve::ifrexp)(eve::minf(eve::as<EVE_TYPE>()));

    TTS_IEEE_EQUAL(r0, (eve::inf(eve::as<EVE_TYPE>())));
    TTS_EQUAL     (r1, i_t(0));

    TTS_IEEE_EQUAL(q0, (eve::minf(eve::as<EVE_TYPE>())));
    TTS_EQUAL     (q1, i_t(0));
  }
  if constexpr(eve::platform::supports_denormals)
  {
    auto [r0, r1] = eve::pedantic(eve::ifrexp)(eve::mindenormal(eve::as<EVE_TYPE>()));

    TTS_ULP_EQUAL (r0, EVE_TYPE(0.5), 1);
    TTS_EQUAL     (r1, i_t(eve::minexponent(eve::as<EVE_TYPE>())-eve::nbmantissabits(eve::as<EVE_TYPE>())+1));
  }
}
