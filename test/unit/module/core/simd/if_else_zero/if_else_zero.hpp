//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ELSE_ZERO_HPP
#define IF_ELSE_ZERO_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/constant/zero.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL("Check if_else_zero behavior on wide", EVE_WIDE_SIZE_RANGE())
{
  using eve::is_nez;
  using eve::wide;

  wide<Type, T> cond([](auto i, auto) { return (i % 2) * i; }),
      rhs1([](auto i, auto) { return i % 2 + 1; }), rhs2([](auto i, auto) { return i % 3; });

  auto z  = eve::Zero(as(cond));
  auto z_ = eve::zero_;

  TTS_EQUAL(eve::if_else(cond, rhs1, z), eve::if_else(cond, rhs1, z_));
  TTS_EQUAL(eve::if_else(is_nez(cond), rhs1, z), eve::if_else(is_nez(cond), rhs1, z_));
}

#endif
