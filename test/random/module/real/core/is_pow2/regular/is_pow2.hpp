//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/popcount.hpp>
#include <eve/logical.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on is_pow2", EVE_TYPE)
{
  auto std_is_pow2 = [](auto e) ->eve::logical<EVE_VALUE> {
    return ((e > 0) && (eve::popcount(e) == 1u));
  };

  eve::uniform_prng<EVE_VALUE> p(eve::zero(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_is_pow2, eve::is_pow2);
}
