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
#include <eve/function/countr_one.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of countr_one on wide"
            , eve::test::simd::unsigned_integers
            , eve::test::generate(eve::test::no_data)
            )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::countr_one(T())  , T);
  TTS_EXPR_IS( eve::countr_one(v_t()), v_t);
};

//==================================================================================================
// countr_one signed tests
//==================================================================================================
EVE_TEST( "Check behavior of countr_one on unsigned integral wide"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  TTS_EQUAL( eve::countr_one(a0), T([&](auto i, auto) { return std::countr_one(a0.get(i)); }));
};
