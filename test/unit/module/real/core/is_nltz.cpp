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
#include <eve/function/is_nltz.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_nltz(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as_<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_nltz(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_nltz(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_nltz
//==================================================================================================

EVE_TEST( "Check behavior of eve::is_nltz(simd)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::ramp(-1.0)
                             ,  eve::test::ramp(1.0, -1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_nltz(a0), map([](auto e) -> eve::logical<v_t> { return  !(e < v_t(0)); }, a0));
  TTS_EQUAL(eve::is_nltz(a1), map([](auto e) -> eve::logical<v_t> { return  !(e < v_t(0)); }, a1));
};
