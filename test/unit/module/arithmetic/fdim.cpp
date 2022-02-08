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
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::fdim(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::fdim(T(), T())                        , T   );
  TTS_EXPR_IS( eve::fdim(v_t(), T())                      , T   );
  TTS_EXPR_IS( eve::fdim(T(), v_t())                      , T   );
  TTS_EXPR_IS( eve::fdim(v_t(), v_t())                    , v_t );
  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff_1st(eve::fdim)(T(), v_t())     , T   );
    TTS_EXPR_IS( eve::diff_1st(eve::fdim)(v_t(), T())     , T   );
    TTS_EXPR_IS( eve::diff_1st(eve::fdim)(T(), T())       , T   );
    TTS_EXPR_IS( eve::diff_1st(eve::fdim)(v_t(), v_t())   , v_t );
    TTS_EXPR_IS( eve::diff_2nd(eve::fdim)(T(), v_t())     , T   );
    TTS_EXPR_IS( eve::diff_2nd(eve::fdim)(v_t(), T())     , T   );
    TTS_EXPR_IS( eve::diff_2nd(eve::fdim)(T(), T())       , T   );
    TTS_EXPR_IS( eve::diff_2nd(eve::fdim)(v_t(), v_t())   , v_t );
  }
};

//==================================================================================================
//== Tests for eve::fdim
//==================================================================================================
EVE_TEST( "Check behavior of eve::fdim(simd) floating"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::between(-1, 1)
                              , eve::test::between( 1,-1))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using eve::as;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::fdim(a0, a1), map([](auto e,  auto f) -> v_t { return  (e >= f) ? e-f : eve::zero(as(e)); }, a0, a1));
  TTS_EQUAL ( eve::diff_1st(eve::fdim)(a0, a1), map([](auto e,  auto f) -> v_t { return  (e >= f) ? eve::one(as(e)) : eve::zero(as(e)); }, a0, a1));
  TTS_EQUAL ( eve::diff_2nd(eve::fdim)(a0, a1), map([](auto e,  auto f) -> v_t { return  (e >= f) ? eve::mone(as(e)) : eve::zero(as(e)); }, a0, a1));
};

EVE_TEST( "Check behavior of eve::fdim(simd) integral"
        , eve::test::simd::integers
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using eve::as;
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::fdim(a0, a1), map([](auto e,  auto f) -> v_t { return  (e >= f) ? v_t(e-f) : eve::zero(eve::as<v_t>()); }, a0, a1));
};
