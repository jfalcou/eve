//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/diff/ceil.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of ceil"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::ceil(T())  , T);
  TTS_EXPR_IS( eve::ceil(v_t()), v_t);

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::ceil)(T())  , T);
    TTS_EXPR_IS( eve::diff(eve::ceil)(v_t()), v_t);
  }
};



//==================================================================================================
// ceil signed tests
//==================================================================================================
EVE_TEST( "Check behavior of ceil on wide"
        , eve::test::simd::all_types//ieee_reals
        , eve::test::generate(eve::test::randoms( eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL( eve::ceil(a0), T([&](auto i, auto) { return v_t(std::ceil(a0.get(i))); }));
    TTS_EQUAL( eve::diff(eve::ceil)(a0), eve::zero(as(a0)));
  }
  else
  {
    TTS_EQUAL( eve::ceil(a0),a0);
  }

};
