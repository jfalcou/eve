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
#include <eve/function/bit_width.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/ldexp.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of bit_width on wide"
            , eve::test::simd::unsigned_integers
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::bit_width(T())  , T);
  TTS_EXPR_IS( eve::bit_width(v_t()), v_t);
};

//==================================================================================================
// bit_width(wide) tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_width(wide) on unsigned integrals"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::bit_width(a0), map([](auto e) -> v_t{ return  std::bit_width(e); }, a0));
};


//==================================================================================================
// bit_width(scalar) tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_width(wide) on unsigned integrals"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  for(auto a: a0)
    TTS_EQUAL( eve::bit_width(a), v_t(std::bit_width(a)));
};
