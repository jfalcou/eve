//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ELSE_ONE_HPP
#define IF_ELSE_ONE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/constant/one.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL( "Check if_else_one behavior on wide", EVE_WIDE_SIZE_RANGE())
{
  using eve::wide;
  using eve::is_nez;

  wide<Type,T>  cond([](auto i, auto ) { return (i%2)*i; })
              , rhs1([](auto i, auto ) { return i%2+1; })
              , rhs2([](auto i, auto ) { return i%3; });

  auto z = eve::One(as(cond));
  auto z_= eve::one_;

  TTS_IEEE_EQUAL(eve::if_else(cond, rhs1, z) , eve::if_else(cond, rhs1, z_));
  TTS_IEEE_EQUAL(eve::if_else(is_nez(cond), rhs1, z), eve::if_else(is_nez(cond), rhs1, z_));
}

#endif
