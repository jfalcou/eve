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
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of radinpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::radinpi(T())  , T);
  TTS_EXPR_IS( eve::radinpi(v_t()), v_t);
};

//==================================================================================================
// radinpi  tests
//==================================================================================================

EVE_TEST( "Check behavior of radinpi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  TTS_ULP_EQUAL( eve::radinpi(a0), a0*T(0.31830988618379067153776752674502872406891929148092), 2);
};
