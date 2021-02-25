//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/frexp.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <tuple>

TTS_CASE_TPL("Check frexp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::frexp)(T()), (std::tuple<T,T>));
}

TTS_CASE_TPL("Check eve::pedantic(eve::frexp) behavior", EVE_TYPE)
{
  {
    auto [p0, p1] = eve::pedantic(eve::frexp)(T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, T(1));
  }
  {
    auto [p0, p1] = eve::pedantic(eve::frexp)(T(0));
    TTS_EQUAL (p0 , T(0));
    TTS_EQUAL (p1, T(0));
  }
  if constexpr(eve::platform::supports_nans)
  {
    auto [r0, r1] = eve::pedantic(eve::frexp)(eve::nan(eve::as<T>()));

    TTS_IEEE_EQUAL(r0 , (eve::nan(eve::as<T>())));
    TTS_EQUAL     (r1, (T(0)));
  }
  if constexpr(eve::platform::supports_infinites)
  {
    auto [r0, r1] = eve::pedantic(eve::frexp)(eve::inf(eve::as<T>()));
    auto [q0, q1] = eve::pedantic(eve::frexp)(eve::minf(eve::as<T>()));

    TTS_IEEE_EQUAL(r0, (eve::inf(eve::as<T>())));
    TTS_EQUAL     (r1, T(0));

    TTS_IEEE_EQUAL(q0, (eve::minf(eve::as<T>())));
    TTS_EQUAL     (q1, T(0));
  }
  if constexpr(eve::platform::supports_denormals)
  {
    using v_t = eve::element_type_t<T>;
    auto [r0, r1] = eve::pedantic(eve::frexp)(eve::mindenormal(eve::as<T>()));

    TTS_ULP_EQUAL (r0, T(0.5), 1);
    TTS_EQUAL     (r1, T(eve::minexponent(eve::as<v_t>())-eve::nbmantissabits(eve::as<v_t>())+1));
  }
}
