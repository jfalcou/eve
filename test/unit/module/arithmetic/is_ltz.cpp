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
#include <eve/function/is_ltz.hpp>
#include <eve/module/arithmetic/constant/smallestposval.hpp>
#include <eve/logical.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_ltz(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_ltz(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_ltz(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_ltz
//==================================================================================================

EVE_TEST( "Check behavior of eve::is_ltz(simd)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::ramp(-1.0)
                             ,  eve::test::ramp(1.0, -1.0)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, T const& a1,  M const & t)

{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_ltz(a0), map([](auto e) -> eve::logical<v_t> { return  e < v_t(0); }, a0));
  TTS_EQUAL(eve::is_ltz(a1), map([](auto e) -> eve::logical<v_t> { return  e < v_t(0); }, a1));
  TTS_EQUAL(eve::is_ltz[t](a0), eve::if_else(t, eve::is_ltz(a0), eve::false_(eve::as(a0))));
};
