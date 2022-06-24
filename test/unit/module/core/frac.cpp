//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::frac(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::frac(T())                    , T   );

  TTS_EXPR_IS( eve::frac(v_t())                  , v_t );

};

//==================================================================================================
// Tests for eve::frac
//==================================================================================================
EVE_TEST( "Check behavior of eve::frac(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::between(-1.0, 1.0))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::frac(a0), map([](auto e) -> v_t { return  e-std::trunc(e); }, a0));
};
