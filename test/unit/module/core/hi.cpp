//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of hi on wide"
            , eve::test::simd::unsigned_integers
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using sd_t= eve::detail::downgrade_t<v_t>;
  using d_t = eve::wide<sd_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS( eve::hi(T())  , d_t);
  TTS_EXPR_IS( eve::hi(v_t()), sd_t);
};


//==================================================================================================
// hi(simd) tests
//==================================================================================================
EVE_TEST( "Check behavior of hi(wide) on unsigned integral "
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using d_t = eve::detail::downgrade_t<v_t>;
  constexpr int s = sizeof(v_t)*4;
  if constexpr(s == 4)
  {
    TTS_EQUAL(eve::hi(a0),  map([&](auto e) ->v_t{ return d_t(eve::shr(e, s)); }, a0));
  }
  else
  {
    TTS_EQUAL(eve::hi(a0),  map([&](auto e) ->d_t{ return d_t(eve::shr(e, s)); }, a0));
  }
};
