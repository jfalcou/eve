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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <tuple>

TTS_CASE_TPL("Check ifrexp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic_(eve::ifrexp)(T()), (std::tuple<T,eve::detail::as_integer_t<T,signed>>));
}

TTS_CASE_TPL("Check eve::pedantic_(eve::ifrexp) behavior", EVE_TYPE)
{
  using i_t = eve::detail::as_integer_t<T,signed>;
  {
    auto [p0, p1] = eve::pedantic_(eve::ifrexp)(T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
  {
    auto [p0, p1] = eve::pedantic_(eve::ifrexp)(T(0));
    TTS_EQUAL (p0 , T(0));
    TTS_EQUAL (p1, i_t(0));
  }
  if constexpr(eve::platform::supports_nans)
  {
    auto [r0, r1] = eve::pedantic_(eve::ifrexp)(eve::nan(eve::as<T>()));

    TTS_IEEE_EQUAL(r0 , (eve::nan(eve::as<T>())));
    TTS_EQUAL     (r1, (i_t(0)));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    auto [r0, r1] = eve::pedantic_(eve::ifrexp)(eve::inf(eve::as<T>()));
    auto [q0, q1] = eve::pedantic_(eve::ifrexp)(eve::minf(eve::as<T>()));

    TTS_IEEE_EQUAL(r0, (eve::inf(eve::as<T>())));
    TTS_EQUAL     (r1, i_t(0));

    TTS_IEEE_EQUAL(q0, (eve::minf(eve::as<T>())));
    TTS_EQUAL     (q1, i_t(0));
  }
  if constexpr(eve::platform::supports_denormals)
  {
    auto [r0, r1] = eve::pedantic_(eve::ifrexp)(eve::mindenormal(eve::as<T>()));

    TTS_ULP_EQUAL (r0, T(0.5), 1);
    TTS_EQUAL     (r1, i_t(eve::minexponent(eve::as<T>())-eve::Nbmantissabits<T>()+1));
  }
}
