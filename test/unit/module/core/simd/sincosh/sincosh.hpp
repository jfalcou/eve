//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FREXP_HPP
#define FREXP_HPP

#include <eve/function/sincosh.hpp>
#include <eve/function/sinh.hpp>
#include <eve/function/cosh.hpp>
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp> 
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <eve/detail/meta.hpp>
#include <utility>
#include <cstdlib>

using eve::fixed;


TTS_CASE_TPL("Check sincosh behavior on wide",
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
  using t_t =  wide<Type, T>; 
  TTS_EXPR_IS ( (eve::sincosh(t_t(0)))
              , (std::pair<t_t,t_t>)
              );
  {
    t_t m, e; 
    std::tie(m, e) = eve::sincosh(eve::Zero<t_t>());
    TTS_ULP_EQUAL(m  , t_t(0), 0.5);
    TTS_ULP_EQUAL(e ,  t_t(1), 0.5);
    TTS_EXPECT(eve::all(eve::is_positive(m))); 
  }
  {
    auto [m, e ] = eve::sincosh(eve::Mzero<t_t>());
    TTS_ULP_EQUAL(m  , t_t(0), 0.5);
    TTS_ULP_EQUAL(e ,  t_t(1), 0.5);
    TTS_EXPECT(eve::all(eve::is_negative(m))); 
  }
  {
    auto x = eve::Maxlog<Type>()+eve::Log_2<Type>()/2; 
    auto [m, e ] = eve::sincosh(t_t(x));
    TTS_ULP_EQUAL(m  , t_t(std::sinh(x)), 0.5);
    TTS_ULP_EQUAL(e ,  t_t(std::cosh(x)), 0.5);
  }
  {
    auto x = eve::Inf<Type>(); 
    auto [m, e ] = eve::sincosh(t_t(x));
    TTS_ULP_EQUAL(m  , eve::Inf<t_t>(), 0.5);
    TTS_ULP_EQUAL(e ,  eve::Inf<t_t>(), 0.5);
  }
   {
    auto x = eve::Minf<Type>(); 
    auto [m, e ] = eve::sincosh(t_t(x));
    TTS_ULP_EQUAL(m  , eve::Minf<t_t>(), 0.5);
    TTS_ULP_EQUAL(e ,  eve::Inf<t_t>(), 0.5);
  }
  
  for(Type i=1; i <eve::Maxlog<Type>() ; i*= 3)
  {
    t_t m, e; 
    std::tie(m, e) = eve::sincosh(t_t(i));
    TTS_ULP_EQUAL(e  , t_t(eve::cosh(i)), 0.5);
    TTS_ULP_EQUAL(m ,  t_t(eve::sinh(i)), 0.5);
  }
  
}

TTS_CASE_TPL("Check frexp behavior on wide",
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
  using t_t =  wide<Type, T>; 
  t_t lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return Type(i); });
  Type m[T::value];
  Type e[T::value];
  for(int i=0; i < T::value ; ++i)
  {
    std::tie(m[i], e[i]) = eve::sincosh(Type(i));
  }
  t_t refm([m](auto i, auto){return m[i]; }); 
  t_t refe([e](auto i, auto){return e[i]; }); 
  auto [vm, ve] =  eve::sincosh(lhs); 
  TTS_EQUAL(refm, vm);
  TTS_EQUAL(refe, ve);
}

#endif
