//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_nez(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_nez(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_nez(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_nez
//==================================================================================================

EVE_TEST( "Check behavior of eve::is_nez(simd)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::ramp(0)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T  a0,  M const & )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_nez(a0), map([](auto e) -> eve::logical<v_t> { return  e != 0; }, a0));
//  TTS_EQUAL(eve::is_nez[t](a0), eve::if_else(t, eve::is_nez(a0), eve::false_(eve::as(a0))));
};
