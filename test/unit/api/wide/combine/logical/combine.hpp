//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/function/combine.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL("Check combining for logical values", EVE_TYPE)
{
  using eve::logical;
  using eve::fixed;
  using eve::wide;

  logical<wide<EVE_VALUE, fixed<2>>> ref(true, false);
  TTS_EQUAL((eve::combine(logical<EVE_VALUE>(true), logical<EVE_VALUE>(false))), ref);
}

TTS_CASE_TPL("Check combining for logical wide", EVE_TYPE)
{
  using eve::logical;
  using eve::wide;

  using combined_cardinal = typename T::cardinal_type::combined_type;

  eve::as_logical_t<T>                        low ([](auto i, auto) { return i % 2 < 2; });
  eve::as_logical_t<T>                        high([](auto i, auto) { return i % 2 > 3; });
  logical<wide<EVE_VALUE, combined_cardinal>> ref ([](auto i, auto c) { return i < int(c) / 2; });

  TTS_EQUAL((logical<wide<EVE_VALUE, combined_cardinal>>(low, high)), ref);
  TTS_EQUAL((eve::combine(low, high)), ref);
}
