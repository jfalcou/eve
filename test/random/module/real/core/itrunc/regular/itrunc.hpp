//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/trunc.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on itrunc", EVE_TYPE)
{
  using i_t =  eve::as_integer_t<EVE_VALUE>;
  if constexpr(eve::floating_value<T>)
  {
    auto std_itrunc =  [](auto e) -> i_t { return i_t(std::trunc(e)); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<i_t>()), eve::valmax(eve::as<i_t>()));
    TTS_RANGE_CHECK(p, std_itrunc,  eve::int_(eve::trunc));
  }
  else
  {
    auto std_itrunc = [](auto e)  -> i_t { return e; };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_itrunc,  eve::int_(eve::trunc));
  }
}
