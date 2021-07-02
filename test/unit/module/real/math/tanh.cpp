//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/function/tanh.hpp>
#include <eve/function/sech.hpp>
#include <eve/function/diff/tanh.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of tanh"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::tanh(T())  , T);
  TTS_EXPR_IS( eve::tanh(v_t()), v_t);
};

//==================================================================================================
// tanh  tests
//==================================================================================================
auto maxi = []<typename T>(eve::as<T> const &)
{
  using v_t = eve::element_type_t<T>;
  v_t ovl =  eve::Ieee_constant<v_t,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384
  return T(ovl);
};
auto mini = []<typename T>(eve::as<T> const & tgt)
{
  return -maxi(tgt);
};

EVE_TEST( "Check behavior of tanh on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mini, maxi)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::tanh;
  using eve::diff;
  TTS_ULP_EQUAL(tanh(a0)      , map([](auto e) -> v_t { return std::tanh(double(e)); }, a0), 2);
  TTS_ULP_EQUAL(tanh(a1)      , map([](auto e) -> v_t { return std::tanh(double(e)); }, a1), 2);
  TTS_ULP_EQUAL(diff(tanh)(a0), map([](auto e) -> v_t { return eve::sqr(eve::sech(e)); }, a0), 2);
  TTS_ULP_EQUAL(diff(tanh)(a1), map([](auto e) -> v_t { return eve::sqr(eve::sech(e)); }, a1), 2);
};
