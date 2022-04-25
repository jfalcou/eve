//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of ufp on unsigned wide"
              , eve::test::simd::all_types
              )
  <typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::ufp(T())  , T);
  TTS_EXPR_IS( eve::ufp(v_t()), v_t);
};

//==================================================================================================
// ufp simd tests
//==================================================================================================
EVE_TEST( "Check behavior of ufp(wide) on unsigned integral types"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(0, +50)
                             , eve::test::logicals(0, 3))
        )
  <typename T, typename U>(T const& a0, U const & t)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::ufp(a0), map([](auto e) { return v_t(std::ufp(e)); }, a0));
  TTS_EQUAL( eve::ufp[t](a0), eve::if_else(t, eve::ufp(a0), a0));
};
