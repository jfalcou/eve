//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/is_imag.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_imag(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_imag(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_imag(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_imag
//==================================================================================================

EVE_TEST( "Check behavior of eve::is_imag(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(0))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_imag(a0), map([](auto e) -> eve::logical<v_t> { return  e == v_t(0); }, a0));
};
