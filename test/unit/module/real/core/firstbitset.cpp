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
#include <eve/function/firstbitset.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::firstbitset(simd)"
              , eve::test::simd::unsigned_integers
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::firstbitset(T()), T  );
  TTS_EXPR_IS( eve::firstbitset(v_t()), v_t );
};

//==================================================================================================
// Tests for eve::firstbitset
//==================================================================================================
EVE_TEST( "Check behavior of eve::firstbitset(simd)"
        , eve::test::simd::unsigned_integers
        , eve::test::generate ( eve::test::ramp(0)
                              ,  eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, const M t)
{
  using eve::detail::map;
  using vi_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::firstbitset(a0), map([](auto e) -> vi_t { return eve::firstbitset(e);}, a0));
  TTS_EQUAL( eve::firstbitset[t](a0), eve::if_else(t, eve::firstbitset(a0), a0));
};
