//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/frexp.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <tuple>

TTS_CASE_TPL("Check frexp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic_(eve::frexp)(T()), (std::tuple<T,T>));
}

TTS_CASE_TPL("Check eve::pedantic_(eve::frexp) behavior", EVE_TYPE)
{
  {
    auto [p0, p1] = eve::pedantic_(eve::frexp)(T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, T(1));
  }
  {
    auto [p0, p1] = eve::pedantic_(eve::frexp)(T(0));
    TTS_EQUAL (p0 , T(0));
    TTS_EQUAL (p1, T(0));
  }
  if constexpr(eve::platform::supports_nans)
  {
    auto [r0, r1] = eve::pedantic_(eve::frexp)(eve::Nan<T>());

    TTS_IEEE_EQUAL(r0 , (eve::Nan<T>()));
    TTS_EQUAL     (r1, (T(0)));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    auto [r0, r1] = eve::pedantic_(eve::frexp)(eve::Inf<T>());
    auto [q0, q1] = eve::pedantic_(eve::frexp)(eve::Minf<T>());

    TTS_IEEE_EQUAL(r0, (eve::Inf<T>()));
    TTS_EQUAL     (r1, T(0));

    TTS_IEEE_EQUAL(q0, (eve::Minf<T>()));
    TTS_EQUAL     (q1, T(0));
  }
  if constexpr(eve::platform::supports_denormals)
  {
    using v_t = eve::element_type_t<T>;
    auto [r0, r1] = eve::pedantic_(eve::frexp)(eve::Mindenormal<T>());

    TTS_ULP_EQUAL (r0, T(0.5), 1);
    TTS_EQUAL     (r1, T(eve::Minexponent<v_t>()-eve::Nbmantissabits<v_t>()+1));
  }
}
