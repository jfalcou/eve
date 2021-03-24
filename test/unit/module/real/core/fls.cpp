//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/fls.hpp>
#include <eve/function/pedantic/fls.hpp>
#include <bit>
#include <strings.h>
extern "C"
{
  int fls(int);
  long int flsl(long int);
}

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of fls on wide"
            , eve::test::simd::unsigned_integers

            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::fls(T())  , T);
  TTS_EXPR_IS( eve::fls(v_t()), v_t);
};


//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check special values"
            , eve::test::simd::unsigned_integers

            )
<typename T>(eve::as_<T>)
{
  using elt_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::fls(T(1)), T(0));
  TTS_EQUAL(eve::fls(T(2)), T(1));
  TTS_EQUAL(eve::fls(T(3)), T(1));
  TTS_EQUAL(eve::fls(T(4)), T(2));
  TTS_EQUAL(eve::fls(T(~0)), T(T(sizeof(elt_t)*8-1)));
  TTS_EQUAL(eve::fls(T(1 << 4)), T(4));
  TTS_EQUAL(eve::fls(T(elt_t(1) << (sizeof(elt_t)*8-1))), T(sizeof(elt_t)*8-1));
  TTS_EQUAL(eve::fls(T(128)), T(7));

  TTS_EQUAL(eve::pedantic(eve::fls)(T(0)), T(sizeof(elt_t)*8));
};
