/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/is_gtz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of bit_mask"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::no_data)
        )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::bit_mask(T()  ) , T);
  TTS_EXPR_IS( eve::bit_mask(v_t()) , v_t);
  TTS_EXPR_IS( eve::bit_mask(eve::logical<T>()), T);
};

//==================================================================================================
//  bit_mask tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_mask on integral types"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>( T const& a0)
{
  using eve::bit_mask;
  TTS_EQUAL( bit_mask(a0), T([&](auto i, auto) { auto v = a0.get(i);  return v ? eve::allbits(eve::as(v)) : eve::zero(eve::as(v)); }));
};
