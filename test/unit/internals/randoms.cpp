//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <generator.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

using eve::valmin;
using eve::valmax;
using eve::as;

auto vmin2 = []<typename T>(eve::as_<T> const & tgt)
{
  return eve::valmin(tgt)/2;
};
auto vmax2 = []<typename T>(eve::as_<T> const & tgt)
{
  return eve::valmin(tgt)/8;
};

EVE_TEST( "Check behavior of eve::abs(eve::wide)"
        , eve::test::simd::unsigned_integers
        , eve::test::generate ( eve::test::randoms(0, +10)
                               , eve::test::randoms(valmin, valmax)
                               , eve::test::randoms(vmin2, vmax2)
                              )
        )
<typename T>(T const& a0, T const& a1, T const& a2 )
{
  std::cout << "a0 = " << a0 << std::endl;
  std::cout << "a1 = " << a1 << std::endl;
  std::cout << "a2 = " << a2 << std::endl;
  TTS_EXPECT(eve::all(a0 <= 10 && a0 >= 0));
  TTS_EXPECT(eve::all(a1 >= valmin(as<T>()) && a1 <= valmax(as<T>())));
  TTS_EXPECT(eve::all(a2 >= vmin2(as<T>()) && a2 <= vmax2(as<T>())));
};


EVE_TEST( "Check behavior of eve::abs(eve::wide)"
        , eve::test::simd::signed_types
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(vmin2, vmax2)
                              )
        )
  <typename T>(T const& a0, T const& a1, T const& a2 )
{
  std::cout << "a0 = " << a0 << std::endl;
  std::cout << "a1 = " << a1 << std::endl;
  std::cout << "a2 = " << a2 << std::endl;
  TTS_EXPECT(eve::all(a0 <= 10 && a0 >= -10));
  TTS_EXPECT(eve::all(a1 >= valmin(as<T>()) && a1 <= valmax(as<T>())));
  TTS_EXPECT(eve::all(a2 >= vmin2(as<T>()) && a2 <= vmax2(as<T>())));
};
