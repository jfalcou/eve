//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU 
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NEAREST_HPP
#define NEAREST_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/inc.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/wide.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

using eve::fixed;
 
TTS_CASE_TPL("Check nearest behavior on wide",
            fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::wide;
  
  wide<Type, T> lhs([](int i, int) { return Type(i%2 ? (i+2) :-i-2)/4; }),
    ref([](int i, int) { return eve::nearest(Type(i%2 ? i+2 :-i-2)/4); });

  TTS_EQUAL(ref, eve::nearest(lhs));
  
  if constexpr(std::is_floating_point_v<Type>)
  {
    using i_t =  eve::detail::as_integer_t<Type, unsigned>;
    using t_t = wide<Type, T>; 
    t_t vm(static_cast<Type>(eve::Valmax<i_t>())); 
    TTS_EQUAL(eve::inc(vm), eve::nearest(vm+Type(1)/2));
    TTS_EQUAL(vm, eve::nearest(vm+Type(1)/3));
  }
}

#endif
