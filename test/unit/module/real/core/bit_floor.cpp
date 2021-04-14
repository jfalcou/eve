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
<typename T>(eve::as_<T>)
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
        , eve::test::generate(eve::test::randoms(0, +50))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::bit_floor(a0), map([](auto e) { return v_t(std::bit_floor(e)); }, a0));
};

//==================================================================================================
// bit_floor scalar tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_floor(scalar) on unsigned integral types"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(0, +50))
        )
<typename T>(T const& data)
{
  using v_t = eve::element_type_t<T>;
  for(auto a0 : data)
    TTS_EQUAL( eve::bit_floor(a0), v_t(std::bit_floor(a0)));
};
