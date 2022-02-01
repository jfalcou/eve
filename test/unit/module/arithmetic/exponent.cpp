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
#include <eve/function/exponent.hpp>
#include <eve/function/convert.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::exponent(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using i_t = eve::as_integer_t<T>;
  using v_t = eve::element_type_t<T>;
  using vi_t = eve::element_type_t<i_t>;
  TTS_EXPR_IS( eve::exponent(T()), i_t  );
  TTS_EXPR_IS( eve::exponent(v_t()), vi_t );
};

//==================================================================================================
// Tests for eve::exponent
//==================================================================================================
EVE_TEST( "Check behavior of eve::exponent(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::between(-1.0, 1.0)
                              , eve::test::logicals(0,3))
        )
<typename T,  typename M>(T const& a0,  M const & t)
{
  using eve::detail::map;
  using i_t = eve::as_integer_t<T>;
  using vi_t = eve::element_type_t<i_t>;

  TTS_EQUAL(eve::exponent(a0), map([](auto e) -> vi_t { int ee; std::frexp(e, &ee); return ee-1; }, a0));
  TTS_EQUAL( eve::exponent[t](a0), eve::if_else(t, eve::exponent(a0), eve::convert(a0, eve::as<vi_t>())));
};

//==================================================================================================
// special tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::exponent(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using i_t = eve::as_integer_t<T>;
  using v_t = eve::element_type_t<T>;
  using vi_t = eve::element_type_t<i_t>;

  TTS_EQUAL(eve::exponent(T(0)), i_t(0));
  TTS_EQUAL(eve::exponent(v_t(0)), vi_t(0));
  TTS_EQUAL(eve::exponent(T(1)), i_t(0));
  TTS_EQUAL(eve::exponent(v_t(1)), vi_t(0)); 
};
