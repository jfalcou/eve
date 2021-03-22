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
#include <eve/function/countl_zero.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of countl_zero on wide"
            , eve::test::simd::unsigned_integers
            , eve::test::generate(eve::test::no_data)
            )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::countl_zero(T())  , T);
  TTS_EXPR_IS( eve::countl_zero(v_t()), v_t);
};

//==================================================================================================
// countl_zero signed tests
//==================================================================================================
EVE_TEST( "Check behavior of countl_zero on unsigned integral wide"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  TTS_EQUAL( eve::countl_zero(a0), T([&](auto i, auto) { return std::countl_zero(a0.get(i)); }));
};
