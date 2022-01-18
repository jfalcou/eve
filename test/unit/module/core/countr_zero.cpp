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
#include <eve/function/countr_zero.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of countr_zero on wide"
            , eve::test::simd::unsigned_integers
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::countr_zero(T())  , T);
  TTS_EXPR_IS( eve::countr_zero(v_t()), v_t);
};

//==================================================================================================
// countr_zero(simd) tests
//==================================================================================================
EVE_TEST( "Check behavior of countr_zero(wide) on unsigned integral "
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, const M t)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( eve::countr_zero(a0), map([](auto e) ->v_t{ return std::countr_zero(e); }, a0));
  TTS_EQUAL( eve::countr_zero[t](a0), eve::if_else(t, eve::countr_zero(a0), a0));
};
