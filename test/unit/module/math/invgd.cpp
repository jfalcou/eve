//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of invgd"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::invgd(T())  , T);
  TTS_EXPR_IS( eve::invgd(v_t()), v_t);
};

//==================================================================================================
// invgd  tests
//==================================================================================================
auto maxi = []<typename T>(eve::as<T> const & tgt)
{
  return eve::pio_2(tgt);
};
auto mini = []<typename T>(eve::as<T> const & tgt)
{
  return -eve::pio_2(tgt);
};

EVE_TEST( "Check behavior of invgd on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mini, maxi)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::invgd;
  using eve::sinh;
  
  TTS_ULP_EQUAL(invgd(a0)      , map([](auto e) -> v_t { return std::atanh(std::sin(e)); }, a0), 2);
  TTS_ULP_EQUAL(invgd(a1)      , map([](auto e) -> v_t { return std::atanh(std::sin(e)); }, a1), 2);
  
  
};
