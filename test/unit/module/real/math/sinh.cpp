//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/function/sinh.hpp>
#include <eve/function/cosh.hpp>
#include <eve/function/diff/sinh.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sinh"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sinh(T())  , T);
  TTS_EXPR_IS( eve::sinh(v_t()), v_t);
};

//==================================================================================================
// sinh  tests
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

EVE_TEST( "Check behavior of sinh on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mini, maxi)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::sinh;
  using eve::cosh;
  using eve::diff;
  TTS_ULP_EQUAL(sinh(a0)      , map([](auto e) -> v_t { return std::sinh(e); }, a0), 2);
  TTS_ULP_EQUAL(sinh(a1)      , map([](auto e) -> v_t { return std::sinh(e); }, a1), 2);
  TTS_ULP_EQUAL(diff(sinh)(a0), map([](auto e) -> v_t { return std::cosh(e); }, a0), 2);
  TTS_ULP_EQUAL(diff(sinh)(a1), map([](auto e) -> v_t { return std::cosh(e); }, a1), 2);
};
