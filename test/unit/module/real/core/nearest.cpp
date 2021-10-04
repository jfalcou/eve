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
#include <eve/function/nearest.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/diff/nearest.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of nearest"
            , eve::test::simd::all_types
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::nearest(T())  , T);
  TTS_EXPR_IS( eve::nearest(v_t()), v_t);

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::nearest)(T())  , T);
    TTS_EXPR_IS( eve::diff(eve::nearest)(v_t()), v_t);
  }
};



//==================================================================================================
// neahalf_c signed tests
//==================================================================================================
EVE_TEST( "Check behavior of neahalf_c on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::randoms( -50, +50))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EQUAL( eve::nearest(a0), T([&](auto i, auto) { return v_t(std::nearbyint(a0.get(i))); }));
    TTS_EQUAL( eve::diff(eve::nearest)(a0), eve::zero(eve::as(a0)));
  }
  else
  {
    TTS_EQUAL( eve::nearest(a0),a0);
  }

};
