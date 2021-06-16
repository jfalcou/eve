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
#include <eve/constant/mone.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/saturated/minus.hpp>
#include <eve/function/diff/minus.hpp>
#include <eve/function/minus.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::minus", eve::test::simd::signed_types)
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::minus(T())                      , T );
  TTS_EXPR_IS( eve::minus[eve::logical<T>()](T())   , T );
  TTS_EXPR_IS( eve::minus[eve::logical<v_t>()](T()) , T );
  TTS_EXPR_IS( eve::minus[bool()](T())              , T );

  TTS_EXPR_IS( eve::saturated(eve::minus)(T())                      , T );
  TTS_EXPR_IS( eve::saturated(eve::minus[eve::logical<T>()])(T())   , T );
  TTS_EXPR_IS( eve::saturated(eve::minus[eve::logical<v_t>()])(T()) , T );
  TTS_EXPR_IS( eve::saturated(eve::minus[bool()])(T())              , T );

  TTS_EXPR_IS( eve::minus(v_t())                      , v_t );
  TTS_EXPR_IS( eve::minus[eve::logical<T>()](v_t())   , T );
  TTS_EXPR_IS( eve::minus[eve::logical<v_t>()](v_t()) , v_t );
  TTS_EXPR_IS( eve::minus[bool()](v_t())              , v_t );

  TTS_EXPR_IS( eve::saturated(eve::minus)(v_t())                      , v_t );
  TTS_EXPR_IS( eve::saturated(eve::minus[eve::logical<T>()])(v_t())   , T );
  TTS_EXPR_IS( eve::saturated(eve::minus[eve::logical<v_t>()])(v_t()) , v_t );
  TTS_EXPR_IS( eve::saturated(eve::minus[bool()])(v_t())              , v_t );

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_EXPR_IS( eve::diff(eve::minus)(T()) , T );
    TTS_EXPR_IS( eve::diff(eve::minus)(v_t()) , v_t );
  }
};

//==================================================================================================
// Tests for eve::minus
//==================================================================================================
EVE_TEST( "Check behavior of eve::minus(eve::wide)"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::minus(a0)      , map([](auto e) -> v_t { return -e; }, a0) );
  TTS_EQUAL(eve::minus[mask](a0), eve::if_else(mask,eve::minus(a0),a0)                    );
};

EVE_TEST( "Check behavior of eve::minus(scalar) - signed types"
        , eve::test::scalar::signed_types
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& data )
{
  for(auto a0 :data)
  {
    TTS_EQUAL(eve::minus(a0), -a0                   );
    TTS_EQUAL(eve::minus[true ](a0), eve::minus(a0) );
    TTS_EQUAL(eve::minus[false](a0), a0             );
  }
};

//==================================================================================================
// Tests for eve::saturated(eve::minus)
//==================================================================================================
EVE_TEST( "Check behavior of eve::saturated(eve::minus)(eve::wide)"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>(T const& a0, M const& mask )
{
  using eve::detail::map;

  TTS_EQUAL ( eve::saturated(eve::minus)(a0)
            , map ( [](auto e)
                    {
                      return e == eve::valmin(eve::as(e)) ? eve::valmax(eve::as(e))
                        : eve::minus(e);
                    }
                  , a0
                  )
            );
  TTS_EQUAL ( eve::saturated(eve::minus[mask])(a0)
            , eve::if_else(mask,eve::saturated(eve::minus)(a0),a0)
            );
};

//==================================================================================================
// Test for eve::diff(eve::minus)
//==================================================================================================
EVE_TEST( "Check behavior of eve::diff(eve::minus) on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;

  TTS_EQUAL ( eve::diff(eve::minus)(a0)
            , eve::mone(eve::as(a0))
            );
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::minus variants on wide"
        , eve::test::simd::signed_types
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;

  if constexpr( eve::floating_real_value<type> )
  {
    TTS_IEEE_EQUAL( eve::minus(cases.nan    ) , cases.nan   );
    TTS_IEEE_EQUAL( eve::minus(cases.minf   ) , cases.inf   );
    TTS_EQUAL     ( eve::minus(cases.mzero  ) , type(0)     );
    TTS_EQUAL     ( eve::minus(cases.valmin ) , cases.valmax);
    TTS_EQUAL     ( eve::minus(cases.valmax ) , cases.valmin);
  }
  else
  {
    TTS_EQUAL( eve::saturated(eve::minus)(cases.valmin ) , cases.valmax);
    TTS_EQUAL( eve::minus(cases.valmax) , cases.valmin+1);
  }
};
