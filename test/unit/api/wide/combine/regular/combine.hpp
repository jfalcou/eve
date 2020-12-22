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

using eve::fixed;

TTS_CASE_TPL("Check combining for arithmetic values", EVE_TYPE)
{
  eve::wide<EVE_VALUE, fixed<2>> ref(13, 37);
  TTS_EQUAL((eve::combine(EVE_VALUE(13), EVE_VALUE(37))), ref);
}

TTS_CASE_TPL("Check combining for logical values", EVE_TYPE)
{
  using eve::logical;
  using eve::fixed;
  using eve::wide;

  logical<wide<EVE_VALUE, fixed<2>>> ref(true, false);
  TTS_EQUAL((eve::combine(logical<EVE_VALUE>(true), logical<EVE_VALUE>(false))), ref);
}

TTS_CASE_TPL("Check combining for arithmetic wide", EVE_TYPE)
{
  using eve::wide;
  using combined_cardinal = typename T::cardinal_type::combined_type;

  T                                   low ([](auto i, auto) { return 1 + i; });
  T                                   high([](auto i, auto) { return EVE_CARDINAL + 1 + i; });
  wide<EVE_VALUE, combined_cardinal>  ref ([](auto i, auto) { return 1 + i; });

  TTS_EQUAL((wide<EVE_VALUE, combined_cardinal>(low, high)), ref);
  TTS_EQUAL((eve::combine(low, high)), ref);
}

TTS_CASE_TPL("Check combining for logical wide", EVE_TYPE)
{
  using eve::logical;
  using eve::wide;

  using combined_cardinal = typename T::cardinal_type::combined_type;

  if constexpr(combined_cardinal::value < 128)
  {
    eve::as_logical_t<T>                        low (true);
    eve::as_logical_t<T>                        high(false);

    logical<wide<EVE_VALUE, combined_cardinal>> ref ( [](auto i, auto c){ return i < c/2; } );

    TTS_EQUAL((eve::combine(low, high)), ref);
    TTS_EQUAL((logical<wide<EVE_VALUE, combined_cardinal>>(low, high)), ref);
  }
  else
  {
    TTS_PASS("Registers larger than cache line size are not tested");
  }
}
