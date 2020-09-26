//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitofsign.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE_TPL("Check bitofsign return type", EVE_TYPE)
{
  using eve::bitofsign;
  TTS_EXPR_IS(bitofsign(T()), T);
}

TTS_CASE_TPL("Check eve::bitofsign behavior", EVE_TYPE)
{
  using eve::all;
  using eve::bitofsign;
  using eve::is_positive;
  using eve::is_negative;

  if constexpr( eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_infinites )
    {
      TTS_EQUAL( bitofsign(eve::inf(eve::as<T>()) ), T(0)           );
      TTS_EQUAL( bitofsign(eve::minf(eve::as<T>())), T(-0.));
      TTS_EXPECT( all(is_positive(bitofsign( eve::inf(eve::as<T>())))) );
      TTS_EXPECT( all(is_negative(bitofsign(eve::minf(eve::as<T>())))) );
    }

    TTS_EQUAL (bitofsign(T(0))  , T(0));
    TTS_EQUAL (bitofsign(T(-0.)), T(-0.));
    TTS_EXPECT( all(is_positive(bitofsign(T(0)))) );
    TTS_EXPECT( all(is_negative(bitofsign(T(-0.)))) );

    TTS_EQUAL (bitofsign(T(1)), T(0));
    TTS_EXPECT( all(is_positive(bitofsign(T(1)))) );

    TTS_EQUAL (bitofsign(T(-1)), T(-0.));
    TTS_EXPECT( all(is_negative(bitofsign(T(-1)))) );
  }
  else if constexpr( eve::unsigned_value<T> )
  {
    using v_t = eve::element_type_t<T>;

    TTS_EQUAL(bitofsign(T(1)), T(0));
    TTS_EQUAL(bitofsign(eve::valmax(eve::as<T>())), T(1ull << (sizeof(v_t)*8-1)));
  }
  else
  {
    using v_t = eve::element_type_t<T>;

    TTS_EQUAL(bitofsign(T(-1)), T(1ull << (sizeof(v_t)*8-1)));
    TTS_EQUAL(bitofsign(T( 1)), T(0));
    TTS_EQUAL(bitofsign(T( 0)), T(0));
  }
}
