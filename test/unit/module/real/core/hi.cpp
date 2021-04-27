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
#include <eve/function/hi.hpp>
#include <eve/function/firstbitset.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of hi on wide"
            , eve::test::simd::all_types
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<T>;
  using vi_t = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::hi(T())  , i_t);
  TTS_EXPR_IS( eve::hi(v_t()), vi_t);
};


//==================================================================================================
// hi(simd) tests
//==================================================================================================
EVE_TEST( "Check behavior of hi(wide) on unsigned integral "
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::ramp(1))
        )
<typename T>(T const& a0)
{
  using vi_t = eve::as_integer_t<v_t>;
  TTS_EQUAL( eve::hi(a0), map([](auto e) ->vi_t{ return eve::hi(e); }, a0));
};
