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
#include <eve/function/ffs.hpp>
#include <eve/function/firstbitset.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ffs on wide"
            , eve::test::simd::unsigned_integers
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::ffs(T())  , T);
  TTS_EXPR_IS( eve::ffs(v_t()), v_t);
};


//==================================================================================================
// ffs(simd) tests
//==================================================================================================
EVE_TEST( "Check behavior of ffs(wide) on unsigned integral "
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::ramp(1))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::ffs(a0), map([](auto e) ->v_t{ return v_t(std::log2(eve::firstbitset(e))); }, a0));
};
