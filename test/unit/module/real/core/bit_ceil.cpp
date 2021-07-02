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
#include <eve/function/bit_ceil.hpp>
#include <eve/function/exponent.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of bit_ceil on wide"
            , eve::test::simd::all_types
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::bit_ceil(T())  , T);
  TTS_EXPR_IS( eve::bit_ceil(v_t()), v_t);
};

//==================================================================================================
// bit_ceil simd tests
//==================================================================================================
auto maxi = []< typename T>(eve::as<T> const &){return eve::valmax(eve::as<T>())/2; }; // over valmax/2 bit_ceil is UB so don't test
auto mini = []< typename T>(eve::as<T> const &){return eve::valmin(eve::as<T>())/4; }; //negative values all return 1;
EVE_TEST( "Check behavior of bit_ceil(wide) on integral types"
        , eve::test::simd::integers
        , eve::test::generate(eve::test::randoms(mini, maxi))
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using u_t = eve::as_integer_t<v_t, unsigned>;
  using eve::detail::map;
  TTS_EQUAL( eve::bit_ceil(a0), map([](auto e) { return v_t(eve::bit_ceil(u_t((e > 0) ? e : 0))); }, a0));
};

EVE_TEST( "Check behavior of bit_ceil(wide) on floating"
            , eve::test::simd::ieee_reals
            , eve::test::generate(eve::test::randoms(-10, eve::valmax))
            )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using eve::exponent;
  using eve::ldexp;
  using eve::detail::map;
  TTS_EQUAL( eve::bit_ceil(a0), map([](auto x) {
                                    auto v = x;
                                    if(v <= v_t(1)) return v_t(1);
                                    else {
                                      auto e =  eve::exponent(v);
                                      auto res = ldexp(v_t(1), e);
                                      if (res < v) res*= v_t(2);
                                      return res;
                                    };
                                  }, a0
                                 )
           );
};
