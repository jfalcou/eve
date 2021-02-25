//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nb_values.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::nb_values return type", EVE_TYPE)
{
  using r_t = eve::as_integer_t<T, unsigned>;
  TTS_EXPR_IS((eve::nb_values(T(0), T(0))), (r_t));
}

TTS_CASE_TPL("Check eve::nb_values  behavior", EVE_TYPE)
{
  using r_t = eve::as_integer_t<T, unsigned>;

  if constexpr(eve::floating_value<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(eve::nb_values(eve::inf(eve::as<T>())  , eve::inf(eve::as<T>()))  , r_t(0)            );
      TTS_EQUAL(eve::nb_values(eve::minf(eve::as<T>()) , eve::minf(eve::as<T>())) , r_t(0)            );
      TTS_EQUAL(eve::nb_values(eve::nan(eve::as<T>())  , eve::nan(eve::as<T>()))  , eve::valmax(eve::as<r_t>()));
    }

    auto eps = eve::eps(eve::as<T>());

    TTS_EQUAL( eve::nb_values(T(1)  ,  eve::inc(eps)  ) , r_t(1));
    TTS_EQUAL( eve::nb_values(T(1)  , -eve::dec(eps)  ) , r_t(2));
    TTS_EQUAL( eve::nb_values(T(1)  , -eve::dec(eps/2)) , r_t(1));
    TTS_EQUAL( eve::nb_values(T(-0.), T(0)            ) , r_t(1));

    TTS_EXPECT(eve::all(eve::is_odd(eve::nb_values(T(-10), T(10)))));
  }
  else if constexpr(eve::signed_value<T>)
  {
    TTS_EXPECT(eve::all(eve::is_even(eve::nb_values(T(-10), T(10)))));
  }
  else
  {
    TTS_EQUAL(eve::nb_values(T(1), T(10)), r_t(9));
    TTS_EQUAL(eve::nb_values(T(0), T( 0)), r_t(0));
  }
}
