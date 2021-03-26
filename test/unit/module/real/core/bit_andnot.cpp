/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/is_gtz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST( "Check return types of bit_andnot"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::no_data)
        )
<typename T>(T)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::bit_andnot(T(), T()  ) , T);
  TTS_EXPR_IS( eve::bit_andnot(T(), v_t()) , T);
  TTS_EXPR_IS( eve::bit_andnot(v_t(), v_t()) , v_t);

  using si_t = eve::as_integer_t<T, signed>;
  using ui_t = eve::as_integer_t<T, unsigned>;

  TTS_EXPR_IS( eve::bit_andnot(T(), si_t()) , T);
  TTS_EXPR_IS( eve::bit_andnot(T(), ui_t()) , T);

  using ssi_t = eve::as_integer_t<v_t, signed>;
  using sui_t = eve::as_integer_t<v_t, unsigned>;
  TTS_EXPR_IS( eve::bit_andnot(T(), ssi_t()) , T);
  TTS_EXPR_IS( eve::bit_andnot(T(), sui_t()) , T);
};

//==================================================================================================
//  bit_andnot tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_andnot on integral types"
          , eve::test::simd::integers
          , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                , eve::test::randoms(eve::valmin, eve::valmax)
                                )
            )
<typename T>( T const& a0, T const& a1 )
{
  using eve::bit_andnot;
  TTS_EQUAL( bit_andnot(a0, a1), T([&](auto i, auto) { return a0.get(i)&~a1.get(i); }));
};

EVE_TEST( "Check behavior of bit_andnot on integral types"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(eve::valmin, eve::valmax)
                              )
            )
<typename T>( T const& a0, T const& a1)
{
  using eve::as;
  using eve::bit_cast;
  using eve::bit_andnot;
  using i_t = eve::as_integer_t<eve::element_type_t<T>, signed>;
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL( bit_andnot(a0, a1), T([&](auto i, auto)
                                { return bit_cast(bit_cast(a0.get(i), as(i_t()))
                                               & ~bit_cast(a1.get(i), as(i_t())), as(v_t())); }
                               ));
};
