//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ZERO_ELSE_ONE_HPP
#define IF_ZERO_ELSE_ONE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/logical.hpp> 
#include <eve/as.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL( "Check if_zero_else_one behavior on homogeneous wide"
            , fixed<1>,fixed<2>, fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
  using t_t = wide<Type,T>; 

  t_t  cond([](auto i, auto ) { return (i%2)*i; })
    , rhs1([](auto i, auto ) { return i%2+1; })
    , rhs2([](auto i, auto ) { return i%3; });

  auto z = eve::Zero<t_t>();
  auto o = eve::One<t_t>();
  auto z_= eve::zero_;
  auto o_= eve::one_; 
  TTS_EQUAL(eve::if_else(cond, z, o) , eve::if_else[eve::as(t_t())] (cond, z_, o_));
  TTS_EQUAL(eve::if_else(cond, z, o) , eve::if_else(cond, z_, o_));
  
}

#endif
