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
EVE_TEST( "Check return types of bit_width on wide"
            , eve::test::simd::unsigned_integers
            , eve::test::generate(eve::test::no_data)
            )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::bit_width(T())  , T);
  TTS_EXPR_IS( eve::bit_width(v_t()), v_t);
};

//==================================================================================================
// bit_width signed tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_width on unsigned integral wide"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using ui_t =  eve::as_integer_t<v_t,  unsigned>;
  TTS_EQUAL( eve::bit_width(a0), T([&](auto i, auto) { return (a0.get(i) < 0) ? 1 : std::bit_width(ui_t(a0.get(i))); }));
};
