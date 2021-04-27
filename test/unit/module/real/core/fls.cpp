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
#include <eve/function/firstbitset.hpp>
#include <bit>
#include <cmath>

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
// fls(simd) tests
//==================================================================================================
EVE_TEST( "Check behavior of fls(wide) on unsigned integral "
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::ramp(1))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using f_t = eve::as_floating_point_t<v_t>;
  TTS_EQUAL( eve::fls(a0), map([](auto e) ->v_t{ return v_t(std::log2(f_t(e|1))); }, a0));
};
