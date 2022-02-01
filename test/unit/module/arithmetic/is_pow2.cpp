//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/function/is_pow2.hpp>
#include <eve/function/firstbitset.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of is_pow2 on wide"
            , eve::test::simd::unsigned_integers
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::is_pow2(T())  , eve::logical<T>);
  TTS_EXPR_IS( eve::is_pow2(v_t()), eve::logical<v_t>);
};


//==================================================================================================
// is_pow2(simd) tests
//==================================================================================================
EVE_TEST( "Check behavior of is_pow2(wide) on unsigned integral "
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::ramp(1))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using f_t = eve::as_floating_point_t<v_t>;
  TTS_EQUAL( eve::is_pow2(a0), map([](auto e) -> eve::logical<v_t> { return std::exp2(std::trunc(std::log2(f_t(e)))) == f_t(e); }, a0));
};
