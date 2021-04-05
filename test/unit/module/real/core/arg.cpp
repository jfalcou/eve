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
#include <eve/function/arg.hpp>
#include <eve/function/diff/arg.hpp>
#include <eve/function/saturated/arg.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::arg(scalar)"
              , eve::test::scalar::ieee_reals
              )
<typename T>(eve::as_<T>)
{
  TTS_EXPR_IS( eve::arg(T())                    , T   );
  TTS_EXPR_IS( eve::pedantic(eve::arg)(T())     , T   );
  TTS_EXPR_IS( eve::diff(eve::arg)(T())         , T   );

};

EVE_TEST_TYPES( "Check return types of eve::arg(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as_<T>)
{
  TTS_EXPR_IS( eve::arg(T())                    , T   );
  TTS_EXPR_IS( eve::pedantic(eve::arg)(T())     , T   );
  TTS_EXPR_IS( eve::diff(eve::arg)(T())         , T   );

};


//==================================================================================================
// Tests for eve::arg
//==================================================================================================
EVE_TEST( "Check behavior of eve::arg(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(-1.0, 1.0))
        )
  <typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::arg(a0), map([](auto e) -> v_t { return  e >= 0 ? 0 : pi(as(v_t())); }, a0);
};

EVE_TEST( "Check behavior of eve::arg(eve::scalar)"
        , eve::test::scalar::ieee_reals
        , eve::test::generate ( eve::test::ramp(-1.0, 1.0))
        )
  <typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::arg(a0), map([](auto e) -> v_t { return  e >= 0 ? 0 : pi(as(v_t())); }, a0);
};


//==================================================================================================
// Tests for eve::pedantic(eve::arg)
//==================================================================================================
EVE_TEST( "Check behavior of eve::pedantic(eve::arg)(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(-1.0, 1.0))
        , eve::test::generate(eve::test::limits())
        )
  <typename T>(T a0, T a1 )
{
  TTS_EQUAL(eve::pedantic(eve::arg)(a0), map([](auto e) -> v_t { return  e >= 0 ? 0 : pi(as(v_t())); }, a0);
  TTS_IEEE_EQUAL( eve::pedantic(eve::arg)(cases.nan    ), cases.nan   );
};

EVE_TEST( "Check behavior of eve::pedantic(eve::arg)(eve::scalar)"
        , eve::test::scalar::ieee_reals
        , eve::test::generate ( eve::test::ramp(-1.0, 1.0))
        , eve::test::generate(eve::test::limits())
        )
  <typename T>(T a0, T a1 )
{
  TTS_EQUAL(eve::pedantic(eve::arg)(a0), map([](auto e) -> v_t { return  e >= 0 ? 0 : pi(as(v_t())); }, a0);
  TTS_IEEE_EQUAL( eve::pedantic(eve::arg)(cases.nan    ), cases.nan   );
};

//==================================================================================================
// Test for eve::diff(eve::arg)
//==================================================================================================
EVE_TEST( "Check behavior of eve::diff(eve::arg) on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL ( eve::diff(eve::arg)(a0)
            , map([](auto e) -> v_t { return e > 0 ? 1 : ((e <  0) ? -1 : 0); }, a0)
            );
};

EVE_TEST( "Check behavior of eve::diff(eve::arg) on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0 )
{
  using eve::detail::map;

  TTS_EQUAL ( eve::diff(eve::arg)(a0)
            , (a0 > 0 ? T(1) : (a0 < 0 ? T(-1) : T(0)))
            );
};
