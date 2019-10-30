//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ICEIL_HPP
#define ICEIL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/iceil.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/eps.hpp> 
#include <eve/constant/nan.hpp>
#include <eve/wide.hpp>
#include <eve/detail/meta.hpp>

using eve::fixed;

TTS_CASE_TPL("Check iceil behavior on wide",
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
  using i_t =  eve::detail::as_integer_t<wide<Type, T>>;
  using t_t = wide<Type, T>; 
  TTS_EQUAL(eve::iceil(t_t{0}), i_t(0));
  TTS_EQUAL(eve::iceil(t_t{2}), i_t(2));
  if constexpr(std::is_signed_v<Type>) { TTS_EQUAL(eve::iceil(t_t(-2)), i_t(-2)); }
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::iceil(eve::Inf<t_t>()), eve::Valmax<i_t>());
    TTS_EQUAL(eve::iceil(eve::Minf<t_t>()), eve::Valmin<i_t>());
    TTS_EQUAL(eve::iceil(eve::Mone<t_t>()), eve::Mone<i_t>());
    TTS_EQUAL(eve::iceil(eve::Nan<t_t>()), eve::Nan<i_t>());
    TTS_EQUAL(eve::iceil(eve::One<t_t>()), eve::One<i_t>());
    TTS_EQUAL(eve::iceil(eve::Valmax<t_t>()), eve::Valmax<i_t>());
    TTS_EQUAL(eve::iceil(t_t(3) / t_t(-2)), i_t(-1));
    TTS_EQUAL(eve::iceil(t_t(3) / t_t(2)), i_t(2));
  }  
}

#endif
