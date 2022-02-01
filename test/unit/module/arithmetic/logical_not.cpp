//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/module/arithmetic/constant/smallestposval.hpp>
#include <eve/logical.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::logical_not(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::logical_not(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::logical_not(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::logical_not
//==================================================================================================

EVE_TEST( "Check behavior of eve::logical_not(simd)"
        , eve::test::simd::all_types
        , eve::test::generate (eve::test::logicals(0, 3))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::logical_not(a0), map([](auto e) -> v_t { return  !e; }, a0));
  TTS_EQUAL(eve::logical_not(true),  false);
  TTS_EQUAL(eve::logical_not(false),  true);
};
