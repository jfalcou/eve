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
#include <eve/function/bit_floor.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/ldexp.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of bit_floor on unsigned wide"
              , eve::test::simd::all_types
              )
  <typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::bit_floor(T())  , T);
  TTS_EXPR_IS( eve::bit_floor(v_t()), v_t);
};

//==================================================================================================
// bit_floor simd tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_floor(wide) on unsigned integral types"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(0, +50)
                             , eve::test::logicals(0, 3))
        )
  <typename T, typename U>(T const& a0, U const & t)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::bit_floor(a0), map([](auto e) { return v_t(std::bit_floor(e)); }, a0));
  TTS_EQUAL( eve::bit_floor[t](a0), eve::if_else(t, eve::bit_floor(a0), a0));
};
