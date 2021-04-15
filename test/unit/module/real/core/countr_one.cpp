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
EVE_TEST_TYPES( "Check return types of countr_one on wide"
            , eve::test::simd::unsigned_integers
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::countr_one(T())  , T);
  TTS_EXPR_IS( eve::countr_one(v_t()), v_t);
};

//==================================================================================================
// countr_one(scalar) tests
//==================================================================================================
EVE_TEST( "Check behavior of countr_one(scalar) on unsigned integral "
        , eve::test::scalar::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using v_t = typename T::value_type;
  for(auto a :a0)
    TTS_EQUAL( eve::countr_one(a), v_t(std::countr_one(a)));
};

//==================================================================================================
// countr_one(simd) tests
//==================================================================================================
EVE_TEST( "Check behavior of countr_one(wide) on unsigned integral "
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::countr_one(a0), map([](auto e) ->v_t{ return std::countr_one(e); }, a0));
};
