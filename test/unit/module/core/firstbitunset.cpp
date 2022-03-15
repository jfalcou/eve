//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::firstbitunset(simd)"
              , eve::test::simd::unsigned_integers
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::firstbitunset(T()), T  );
  TTS_EXPR_IS( eve::firstbitunset(v_t()), v_t );
};

//==================================================================================================
// Tests for eve::firstbitunset
//==================================================================================================
EVE_TEST( "Check behavior of eve::firstbitunset(simd)"
        , eve::test::simd::unsigned_integers
        , eve::test::generate ( eve::test::ramp(0)
                              ,  eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, const M t)
{
  using eve::detail::map;
  using vi_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::firstbitunset(a0), map([](auto e) -> vi_t { return eve::firstbitunset(e);}, a0));
  TTS_EQUAL( eve::firstbitunset[t](a0), eve::if_else(t, eve::firstbitunset(a0), a0));
};
