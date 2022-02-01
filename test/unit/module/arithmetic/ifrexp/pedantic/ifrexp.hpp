//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/pedantic/ifrexp.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/arithmetic/constant/mindenormal.hpp>
#include <eve/module/arithmetic/constant/minexponent.hpp>
#include <eve/module/arithmetic/constant/nbmantissabits.hpp>
#include <tuple>

TTS_CASE_TPL("Check ifrexp return type", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  TTS_EXPR_IS(eve::pedantic(eve::ifrexp)(T()), (kumi::tuple<T,eve::as_integer_t<T,signed>>));
};

TTS_CASE_TPL("Check eve::pedantic(eve::ifrexp) behavior", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  using i_t = eve::as_integer_t<T,signed>;
  {
    auto [p0, p1] = eve::pedantic(eve::ifrexp)(T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
  {
    auto [p0, p1] = eve::pedantic(eve::ifrexp)(T(0));
    TTS_EQUAL (p0 , T(0));
    TTS_EQUAL (p1, i_t(0));
  }
  if constexpr(eve::platform::supports_nans)
  {
    auto [r0, r1] = eve::pedantic(eve::ifrexp)(eve::nan(eve::as<T>()));

    TTS_IEEE_EQUAL(r0 , (eve::nan(eve::as<T>())));
    TTS_EQUAL     (r1, (i_t(0)));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    auto [r0, r1] = eve::pedantic(eve::ifrexp)(eve::inf(eve::as<T>()));
    auto [q0, q1] = eve::pedantic(eve::ifrexp)(eve::minf(eve::as<T>()));

    TTS_IEEE_EQUAL(r0, (eve::inf(eve::as<T>())));
    TTS_EQUAL     (r1, i_t(0));

    TTS_IEEE_EQUAL(q0, (eve::minf(eve::as<T>())));
    TTS_EQUAL     (q1, i_t(0));
  }
  if constexpr(eve::platform::supports_denormals)
  {
    auto [r0, r1] = eve::pedantic(eve::ifrexp)(eve::mindenormal(eve::as<T>()));

    TTS_ULP_EQUAL (r0, T(0.5), 1);
    TTS_EQUAL     (r1, i_t(eve::minexponent(eve::as<T>())-eve::nbmantissabits(eve::as<T>())+1));
  }
};
