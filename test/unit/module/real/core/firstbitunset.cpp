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
#include <eve/function/firstbitunset.hpp>
#include <eve/function/inc.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of firstbitunset on wide"
            , eve::test::simd::unsigned_integers
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::firstbitunset(T())  , T);
  TTS_EXPR_IS( eve::firstbitunset(v_t()), v_t);
};

//==================================================================================================
// firstbitunset signed tests
//==================================================================================================
EVE_TEST( "Check behavior of firstbitunset on unsigned integral wide"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::ramp(0))
        )
<typename T>(T const& a0)
{
  TTS_EQUAL( eve::firstbitunset(a0), T([&](auto i, auto) { auto e =  a0.get(i); return  ~e & eve::inc(e); }));
};
