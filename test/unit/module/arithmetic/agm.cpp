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
#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of agm"
              , eve::test::simd::ieee_reals)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::agm(T(), T()  ) , T);
  TTS_EXPR_IS( eve::agm(v_t(), v_t()) , v_t);
};

//==================================================================================================
//== agm tests
//==================================================================================================
EVE_TEST( "Check behavior of agm(wide)"
            , eve::test::simd::ieee_reals
            , eve::test::generate ( eve::test::randoms(0, 100)
                                  , eve::test::randoms(0, 100)
                                  )
            )
<typename T>(T const& a0, T const& a1 )
{
  using eve::agm;
  using eve::detail::map;
  TTS_ULP_EQUAL( agm(a0, a1), ((a0+a1)/eve::ellint_1((a0-a1)/(a0+a1)))*eve::pio_4(eve::as(a0)), 5);
};


//==================================================================================================
//==  conditional agm tests
//==================================================================================================
EVE_TEST( "Check behavior of  agm[cond](wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(0, 127)
                              , eve::test::randoms(0, 127)
                              , eve::test::randoms(0, 127)
                              )
        )
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::agm;
  using eve::detail::map;
  using v_t =  eve::element_type_t<T>;
  TTS_ULP_EQUAL( agm[a2 > T(64)](a0, a1), map([](auto e, auto f, auto g) {return g > v_t(64) ? agm(e, f) :e; }, a0, a1, a2), 5);
};
