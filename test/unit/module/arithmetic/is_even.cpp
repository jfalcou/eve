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
#include <eve/function/is_even.hpp>
#include <eve/module/arithmetic/constant/smallestposval.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_even(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_even(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_even(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_even
//==================================================================================================
EVE_TEST( "Check behavior of eve::is_even(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(0)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0,  M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_even(a0), map([](auto e) -> eve::logical<v_t> { return  (std::trunc(e/2)*2) == e; }, a0));
  TTS_EQUAL(eve::is_even[t](a0), eve::if_else(t, eve::is_even(a0), eve::false_(eve::as(a0))));
};

EVE_TEST( "Check behavior of eve::is_even(simd)"
        , eve::test::simd::integers
        , eve::test::generate ( eve::test::ramp(0)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0,  M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_even(a0), map([](auto e) -> eve::logical<v_t> { return  (e&1) == 0; }, a0));
  TTS_EQUAL(eve::is_even[t](a0), eve::if_else(t, eve::is_even(a0), eve::false_(eve::as(a0))));
};
