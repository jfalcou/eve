//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/pedantic/nextafter.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/function/nextafter.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::nextafter"
              , eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t   = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::nextafter(T(), T())        , T);
  TTS_EXPR_IS(eve::nextafter(T(), v_t())      , T);
  TTS_EXPR_IS(eve::nextafter(v_t(), T())      , T);
  TTS_EXPR_IS(eve::nextafter(v_t(), v_t())    , v_t);
};

//==================================================================================================
// Tests for eve::nextafter
//==================================================================================================
EVE_TEST( "Check behavior of eve::nextafter"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
  <typename T>(T const& a0, T const & a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_real_value < v_t>)
  {
    auto n = [](auto e, auto f) -> v_t { return std::nextafter(e, f); };
    TTS_EQUAL(eve::nextafter(a0, a1)      , map(n, a0, a1) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::nextafter)(eve::nan(eve::as<T>())  , T(1)           ), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic(eve::nextafter)(T(1)           , eve::nan(eve::as<T>())  ), eve::nan(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(eve::nextafter(a0, a1), eve::if_else(a0 > a1, eve::dec(a0), eve::if_else(a0 < a1, eve::inc(a0), a0)));
  }
};
