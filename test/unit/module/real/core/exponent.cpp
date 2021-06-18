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
#include <eve/function/exponent.hpp>
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
        , eve::test::generate ( eve::test::between(-1.0, 1.0))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using i_t = eve::as_integer_t<T>;
  using vi_t = eve::element_type_t<i_t>;

  TTS_EQUAL(eve::exponent(a0), map([](auto e) -> vi_t { int ee; std::frexp(e, &ee); return ee-1; }, a0));
};
