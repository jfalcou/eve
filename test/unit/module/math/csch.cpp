//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of csch"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::csch(T())  , T);
  TTS_EXPR_IS( eve::csch(v_t()), v_t);
};

//==================================================================================================
// csch  tests
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

TTS_CASE_WITH ( "Check behavior of csch on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(tts::constant(mini), tts::constant(maxi))
                              , tts::randoms(-1.0, 1.0)
                              )
              )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::csch;
  using eve::coth;

  TTS_ULP_EQUAL(csch(a0)      , map([](auto e) -> v_t { return 1.0/std::sinh(e); }, a0), 2);
  TTS_ULP_EQUAL(csch(a1)      , map([](auto e) -> v_t { return 1.0/std::sinh(e); }, a1), 2);


};
