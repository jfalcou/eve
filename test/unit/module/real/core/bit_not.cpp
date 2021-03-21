/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/is_gtz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of bit_not"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::no_data)
        )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::bit_not(T()  ) , T);
  TTS_EXPR_IS( eve::bit_not(v_t()) , T);
  using eve::logical;
//   using ssi_t = eve::as_integer_t<v_t, signed>;
//   using sui_t = eve::as_integer_t<v_t, unsigned>;
  TTS_EXPR_IS( eve::bit_not[logical<T>()](T()) , T);
  TTS_EXPR_IS( eve::bit_not[logical<v_t>()](T()) , T);
  TTS_EXPR_IS( eve::bit_not[logical<T>()](v_t()) , T);
};

//==================================================================================================
//  bit_not tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_not on integral types"
        , eve::test::simd::integers
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>( T const& a0)
{
  using eve::bit_not;
  TTS_EQUAL( bit_not(a0), T([&](auto i, auto) { return ~a0.get(i); }));
};

EVE_TEST( "Check behavior of bit_not on integral types"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::as;
  using eve::bit_not;
  using eve::bit_cast;
  using i_t = eve::as_integer_t<eve::element_type_t<T>, signed>;
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL( bit_not(a0), T([&](auto i, auto)
                                 { return  bit_cast(~bit_cast(a0.get(i), as(i_t())), as(v_t())); }
                                ));
};
