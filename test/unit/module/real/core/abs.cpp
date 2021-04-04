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
#include <eve/function/abs.hpp>
#include <eve/function/diff/abs.hpp>
#include <eve/function/saturated/abs.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Specific generator - valmin or valmin+1 if T is signed
//==================================================================================================
auto minimal = []<typename T>(eve::as_<T> const & tgt)
{
  constexpr auto sign = std::is_signed_v<T> ? 1 : 0;
  return eve::valmin(tgt) + sign;
};

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::abs(scalar)", eve::test::scalar::all_types)
<typename T>(eve::as_<T>)
{
  TTS_EXPR_IS( eve::abs(T())                    , T   );
  TTS_EXPR_IS( eve::abs[eve::logical<T>()](T()) , T   );
  TTS_EXPR_IS( eve::abs[bool()](T())            , T   );

  TTS_EXPR_IS( eve::saturated(eve::abs)(T())                   , T   );
  TTS_EXPR_IS( eve::saturated(eve::abs[eve::logical<T>()])(T()), T   );
  TTS_EXPR_IS( eve::saturated(eve::abs[bool()])(T())           , T   );

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::abs)(T()) , T );
  }
};

EVE_TEST_TYPES( "Check return types of eve::abs(wide)", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::abs(T())                      , T );
  TTS_EXPR_IS( eve::abs[eve::logical<T>()](T())   , T );
  TTS_EXPR_IS( eve::abs[eve::logical<v_t>()](T()) , T );
  TTS_EXPR_IS( eve::abs[bool()](T())              , T );

  TTS_EXPR_IS( eve::saturated(eve::abs)(T())                      , T );
  TTS_EXPR_IS( eve::saturated(eve::abs[eve::logical<T>()])(T())   , T );
  TTS_EXPR_IS( eve::saturated(eve::abs[eve::logical<v_t>()])(T()) , T );
  TTS_EXPR_IS( eve::saturated(eve::abs[bool()])(T())              , T );

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::abs)(T()) , T );
  }
};

//==================================================================================================
// Tests for eve::abs
//==================================================================================================
EVE_TEST( "Check behavior of eve::abs(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(minimal, eve::valmax)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask )
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::abs(a0)      , map([](auto e) -> v_t { return e > 0 ? e : -e; }, a0) );
  TTS_EQUAL(eve::abs[mask](a0), eve::if_else(mask,eve::abs(a0),a0)                    );
};

EVE_TEST( "Check behavior of eve::abs(scalar) - signed types"
        , eve::test::scalar::all_types
        , eve::test::generate(eve::test::randoms(minimal, eve::valmax))
        )
<typename T>(T const& a0 )
{
  TTS_EQUAL(eve::abs(a0), (a0 > 0 ? T(a0) : T(-a0)) );
  TTS_EQUAL(eve::abs[true ](a0), eve::abs(a0)       );
  TTS_EQUAL(eve::abs[false](a0), a0                 );
};

//==================================================================================================
// Tests for eve::saturated(eve::abs)
//==================================================================================================
EVE_TEST( "Check behavior of eve::saturated(eve::abs)(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(minimal, eve::valmax)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask )
{
  using v_t = eve::element_type_t<T>;
  using eve::detail::map;

  if constexpr(std::is_signed_v<v_t>)
  {
    TTS_EQUAL ( eve::saturated(eve::abs)(a0)
              , map ( [](auto e)
                      {
                        return e == eve::valmin(eve::as(e)) ? eve::valmax(eve::as(e))
                                                            : eve::abs(e);
                      }
                    , a0
                    )
              );
  }
  else
  {
    TTS_EQUAL(eve::saturated(eve::abs)(a0), a0);
  }

  TTS_EQUAL ( eve::saturated(eve::abs[mask])(a0)
            , eve::if_else(mask,eve::saturated(eve::abs)(a0),a0)
            );
};

EVE_TEST( "Check behavior of eve::saturated(eve::abs)(scalar)"
        , eve::test::scalar::all_types
        , eve::test::generate ( eve::test::randoms(minimal, eve::valmax))
        )
<typename T>(T const& a0)
{
  if constexpr(std::is_signed_v<T>)
  {
    TTS_EQUAL ( eve::saturated(eve::abs)(a0)
              , (a0 == eve::valmin(eve::as(a0)) ? eve::valmax(eve::as(a0)) : eve::abs(a0))
              );
  }
  else
  {
    TTS_EQUAL(eve::saturated(eve::abs)(a0), a0);
  }

  TTS_EQUAL(eve::saturated(eve::abs[true ])(a0), eve::saturated(eve::abs)(a0) );
  TTS_EQUAL(eve::saturated(eve::abs[false])(a0), a0                           );
};

//==================================================================================================
// Test for eve::diff(eve::abs)
//==================================================================================================
EVE_TEST( "Check behavior of eve::diff(eve::abs) on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL ( eve::diff(eve::abs)(a0)
            , map([](auto e) -> v_t { return e > 0 ? 1 : ((e <  0) ? -1 : 0); }, a0)
            );
};

EVE_TEST( "Check behavior of eve::diff(eve::abs) on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  using eve::detail::map;

  TTS_EQUAL ( eve::diff(eve::abs)(a0)
            , (a0 > 0 ? T(1) : (a0 < 0 ? T(-1) : T(0)))
            );
};
