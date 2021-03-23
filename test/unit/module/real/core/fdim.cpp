/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/fdim.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of fdim"
          , eve::test::simd::all_types

          )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::fdim(T(), T()  ) , T);
  TTS_EXPR_IS( eve::fdim(T(), v_t()) , T);
  TTS_EXPR_IS( eve::fdim(v_t(), T()) , T);
};

//==================================================================================================
//==  fdim tests
//==================================================================================================
auto mini = []< typename T>(eve::as_<T> const &){return eve::valmin(eve::as(eve::element_type_t<T>()))/4;};
auto maxi = []< typename T>(eve::as_<T> const &){return eve::valmax(eve::as(eve::element_type_t<T>()))/4;};

EVE_TEST( "Check behavior of fdim on signed types"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(mini, maxi)
                                  , eve::test::randoms(mini, maxi)
                                  )
            )
<typename T>(T const& a0, T const& a1)
{
  using eve::fdim;
  TTS_EQUAL( fdim(a0, a1), T([&](auto i, auto) { auto x = a0.get(i); auto y = a1.get(i);
                               return !(x <= y) ? x-y : eve::zero(eve::as(x-y)); }));
};
