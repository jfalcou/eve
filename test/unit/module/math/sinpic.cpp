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
EVE_TEST_TYPES( "Check return types of sinpic"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sinpic(T())  , T);
  TTS_EXPR_IS( eve::sinpic(v_t()), v_t);
};

//==================================================================================================
// sinpic  tests
//==================================================================================================
auto mini= []<typename T>(eve::as<T> const & tgt)
{
  return eve::valmin(tgt)/4;
};
auto maxi= []<typename T>(eve::as<T> const & tgt)
{
  return eve::valmax(tgt)/4;
};

EVE_TEST( "Check behavior of sinpic on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(mini, maxi)
                            , eve::test::randoms(-10.0, 10.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using eve::sinpic;
  
  using v_t = eve::element_type_t<T>;
  v_t dpi = 3.1415926535897932384626433832795028841971693993751;
  auto ref = [dpi](auto e) -> v_t { return e ? eve::sinpi(e)/(dpi*e) : v_t(1); };
  TTS_ULP_EQUAL(sinpic(a0)                       , map(ref, a0), 3);
  TTS_ULP_EQUAL(sinpic(a1)                       , map(ref, a1), 3);
};
