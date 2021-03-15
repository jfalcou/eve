/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/is_gtz.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
auto types_tests = []<typename T>(auto& runtime, bool verbose, auto const&, T)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::bit_xor(T(), T()  ) , T);
  TTS_EXPR_IS( eve::bit_xor(T(), v_t()) , T);
  TTS_EXPR_IS( eve::bit_xor(v_t(), v_t()) , v_t);

  using si_t = eve::as_integer_t<T, signed>;
  using ui_t = eve::as_integer_t<T, unsigned>;

  TTS_EXPR_IS( eve::bit_xor(T(), si_t()) , T);
  TTS_EXPR_IS( eve::bit_xor(T(), ui_t()) , T);

  using ssi_t = eve::as_integer_t<v_t, signed>;
  using sui_t = eve::as_integer_t<v_t, unsigned>;
  TTS_EXPR_IS( eve::bit_xor(T(), ssi_t()) , T);
  TTS_EXPR_IS( eve::bit_xor(T(), sui_t()) , T);

};

EVE_TEST_BED( "Check return types of bit_xor"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::no_data)
            , types_tests
            );

//==================================================================================================
//  bit_xor tests
//==================================================================================================
auto simd_tests = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0, T const& a1
                                )
{
  using eve::bit_xor;
  TTS_EQUAL( bit_xor(a0, a1), T([&](auto i, auto) { return a0.get(i)^a1.get(i); }));
};

EVE_TEST_BED( "Check behavior of bit_xor on integral types"
            , eve::test::simd::integers
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            , simd_tests
            );

auto simd_testsf = []<typename T>( auto& runtime, bool verbose, auto const&
                                , T const& a0, T const& a1
                                )
{
  using eve::as;
  using eve::bit_cast;
  using eve::bit_xor;
  using i_t = eve::as_integer_t<eve::element_type_t<T>, signed>;
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL( bit_xor(a0, a1), T([&](auto i, auto)
                                { return  bit_cast(eve::bit_cast(a0.get(i), eve::as(i_t()))
                                                 ^ eve::bit_cast(a1.get(i), eve::as(i_t())), as(v_t())); }
                                    ));
};

EVE_TEST_BED( "Check behavior of bit_xor on integral types"
            , eve::test::simd::ieee_reals
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            , simd_testsf
            );
