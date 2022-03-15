//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of radindeg"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::radindeg(T())  , T);
  TTS_EXPR_IS( eve::radindeg(v_t()), v_t);
};

//==================================================================================================
// radindeg  tests
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const & tgt)
{
  return eve::valmin(tgt)/60;
};
auto maxi = []<typename T>(eve::as<T> const & tgt)
{
  return eve::valmax(tgt)/60;
};

EVE_TEST( "Check behavior of radindeg on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(mini, maxi))
        )
<typename T>(T const& a0 )
{
  TTS_ULP_EQUAL( eve::radindeg(a0), a0*T(57.295779513082320876798154814105170332405472466565), 2);
};
