//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/function/coth.hpp>
#include <eve/function/diff/coth.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of coth"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::coth(T())  , T);
  TTS_EXPR_IS( eve::coth(v_t()), v_t);
};

//==================================================================================================
// coth  tests
//==================================================================================================
auto maxi = []<typename T>(eve::as_<T> const &)
{
  using v_t = eve::element_type_t<T>;
  v_t ovl =  eve::Ieee_constant<v_t,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384
  return T(ovl);
};
auto mini = []<typename T>(eve::as_<T> const & tgt)
{
  return -maxi(tgt);
};

EVE_TEST( "Check behavior of coth on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mini, maxi)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::coth;
  using eve::sinh;
  using eve::diff;
  TTS_ULP_EQUAL(coth(a0)      , map([](auto e) -> v_t { return 1.0/std::tanh(double(e)); }, a0), 2);
  TTS_ULP_EQUAL(coth(a1)      , map([](auto e) -> v_t { return 1.0/std::tanh(double(e)); }, a1), 2);
  TTS_ULP_EQUAL(diff(coth)(a0), map([](auto e) -> v_t { return -eve::sqr(eve::csch(e)); }, a0), 2);
  TTS_ULP_EQUAL(diff(coth)(a1), map([](auto e) -> v_t { return -eve::sqr(eve::csch(e)); }, a1), 2);

  TTS_IEEE_EQUAL(eve::coth(T( 0 )), eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::coth(T(-0.)), eve::minf(eve::as<T>()));

};
