//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/atanh.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on atanh", EVE_TYPE)
{
  auto std_atanh = [](auto e) { return std::atanh(e); };

  eve::uniform_prng<EVE_VALUE> p(-1, 1);
  TTS_RANGE_CHECK(p, std_atanh, eve::atanh);
}
