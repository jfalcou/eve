//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/all.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/function/minus.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::nb_values return type", EVE_TYPE)
{
  using r_t = eve::detail::as_integer_t<T, unsigned>;
  TTS_EXPR_IS((eve::nb_values(T(0), T(0))), (r_t));
}

TTS_CASE_TPL("Check eve::nb_values  behavior", EVE_TYPE)
{
  using eve::nb_values;
  TTS_EXPR_IS( nb_values(T(), T()), (eve::detail::as_integer_t<T, unsigned>));
  using r_t = eve::detail::as_integer_t<T, unsigned>;
  if constexpr(eve::floating_value<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(nb_values(eve::Inf<T>(), eve::Inf<T>()), eve::Zero<r_t>());
      TTS_EQUAL(nb_values(eve::Minf<T>(), eve::Minf<T>()), eve::Zero<r_t>());
      TTS_EQUAL(nb_values(eve::Nan<T>(), eve::Nan<T>()), eve::Valmax<r_t>());
    }

    TTS_EQUAL( nb_values(eve::One<T>(), eve::inc(eve::Eps<T>()))
             , r_t(1)
             );

    TTS_EQUAL( nb_values(eve::One<T>(), T(-eve::dec(eve::Eps<T>())))
             , r_t(2)
             );

    TTS_EQUAL( nb_values(eve::One<T>(), T(-eve::dec(eve::Eps<T>()/2)))
             , r_t(1)
             );
    TTS_EQUAL( nb_values(T(-0.), T(T( 0 )))
             , r_t(1)
             );
    TTS_EXPECT(eve::all(eve::is_odd(nb_values(T(-10), T(10)))));
  }
  else if constexpr(eve::signed_value<T>)
  {
    TTS_EXPECT(eve::all(eve::is_even(nb_values(T(-10), T(10)))));
  }
  else
  {
    TTS_EQUAL((nb_values(eve::One<T>(), T(10))), (r_t(9)));
    TTS_EQUAL(nb_values(T( 0 ), T( 0 )), eve::Zero<r_t>());
  }
}
