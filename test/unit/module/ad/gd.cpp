//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/ad.hpp>

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

//==================================================================================================
// Tests for eve::gd
//==================================================================================================
EVE_TEST( "Check behavior of eve::gd(eve::wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(mini, maxi)
                              )
        )
  <typename T>(T const& a0)
{

  using eve::var;
  using eve::val;
  using eve::der;
  using eve::diff;

  auto vda0 = var(a0);
  TTS_EQUAL(val(eve::gd(vda0))      , eve::gd(a0));
  TTS_EQUAL(der(eve::gd(vda0))      , diff(eve::gd)(a0));
};
