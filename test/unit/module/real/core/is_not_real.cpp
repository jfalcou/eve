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
#include <eve/constant/false.hpp>
#include <eve/function/is_not_real.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/logical.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_not_real(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_not_real(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_not_real(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_not_real
//==================================================================================================

EVE_TEST( "Check behavior of eve::is_not_real(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(0)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0,  M const & t)
{
  TTS_EQUAL(eve::is_not_real(a0), eve::false_(eve::as(a0)));
  TTS_EQUAL(eve::is_not_real[t](a0), eve::if_else(t, eve::is_not_real(a0), eve::false_(eve::as(a0))));
};
