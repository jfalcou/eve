//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <cmath>

//==================================================================================================
// Specific generator - valmin or valmin+1 if T is signed
//==================================================================================================
auto minimal = []<typename T>(eve::as<T> const & tgt)
{
  constexpr auto sign = std::is_signed_v<T> ? 1 : 0;
  return eve::valmin(tgt) + sign;
};

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::abs", eve::test::simd::all_types)
<typename T>(eve::as<T>)
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

  TTS_EXPR_IS( eve::abs(v_t())                      , v_t );
  TTS_EXPR_IS( eve::abs[eve::logical<T>()](v_t())   , T );
  TTS_EXPR_IS( eve::abs[eve::logical<v_t>()](v_t()) , v_t );
  TTS_EXPR_IS( eve::abs[bool()](v_t())              , v_t );

  TTS_EXPR_IS( eve::saturated(eve::abs)(v_t())                      , v_t );
  TTS_EXPR_IS( eve::saturated(eve::abs[eve::logical<T>()])(v_t())   , T );
  TTS_EXPR_IS( eve::saturated(eve::abs[eve::logical<v_t>()])(v_t()) , v_t );
  TTS_EXPR_IS( eve::saturated(eve::abs[bool()])(v_t())              , v_t );

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::abs)(T()) , T );
    TTS_EXPR_IS( eve::diff(eve::abs)(v_t()) , v_t );
  }
};

//==================================================================================================
// Tests for eve::abs
//==================================================================================================
EVE_TEST( "Check behavior of eve::abs(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask)
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
<typename T>(T const& data )
{
  using type = typename T::value_type;
  for(auto a0 :data)
  {
    TTS_EQUAL(eve::abs(a0), (a0 > 0 ? type(a0) : type(-a0)) );
    TTS_EQUAL(eve::abs[true ](a0), eve::abs(a0)             );
    TTS_EQUAL(eve::abs[false](a0), a0                       );
  }
};

//==================================================================================================
// Tests for eve::saturated(eve::abs)
//==================================================================================================
EVE_TEST( "Check behavior of eve::saturated(eve::abs)(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
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

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::abs variants on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;

  if constexpr( eve::floating_real_value<type> )
  {
    TTS_IEEE_EQUAL( eve::abs(cases.nan    ) , cases.nan   );
    TTS_IEEE_EQUAL( eve::abs(cases.minf   ) , cases.inf   );
    TTS_EQUAL     ( eve::abs(cases.mzero  ) , type(0)     );
    TTS_EQUAL     ( eve::abs(cases.valmin ) , cases.valmax);
    TTS_EQUAL     ( eve::abs(cases.valmax ) , cases.valmax);

    TTS_IEEE_EQUAL( eve::saturated(eve::abs)(cases.nan    ) , cases.nan   );
    TTS_IEEE_EQUAL( eve::saturated(eve::abs)(cases.minf   ) , cases.inf   );
    TTS_EQUAL     ( eve::saturated(eve::abs)(cases.mzero  ) , type(0)     );
    TTS_EQUAL     ( eve::saturated(eve::abs)(cases.valmin ) , cases.valmax);
    TTS_EQUAL     ( eve::saturated(eve::abs)(cases.valmax ) , cases.valmax);
  }
  else
  {
    TTS_EQUAL( eve::abs(cases.valmin ) , cases.valmin);
    TTS_EQUAL( eve::abs(cases.valmax ) , cases.valmax);

    if constexpr( eve::signed_value<type> )
      TTS_EQUAL( eve::saturated(eve::abs)(cases.valmin ) , cases.valmax);
    else
      TTS_EQUAL( eve::saturated(eve::abs)(cases.valmin ) , cases.valmin);

    TTS_EQUAL( eve::saturated(eve::abs)(cases.valmax ) , cases.valmax);

  }
};
