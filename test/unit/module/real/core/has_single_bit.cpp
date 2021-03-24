//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/has_single_bit.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of has_single_bit on wide"
            , eve::test::simd::integers

            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;
  TTS_EXPR_IS( eve::has_single_bit(T())  , logical<T>);
  TTS_EXPR_IS( eve::has_single_bit(v_t()), logical<v_t>);
};

//==================================================================================================
// has_single_bit signed tests
//==================================================================================================
EVE_TEST( "Check behavior of has_single_bit on unsigned integral wide"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::ramp(0))
        )
<typename T>(T const& a0)
{
  using eve::as_logical_t;
  TTS_EQUAL( eve::has_single_bit(a0), as_logical_t<T>([&](auto i, auto) { return std::popcount(size_t(a0.get(i))) == 1; }));
};
