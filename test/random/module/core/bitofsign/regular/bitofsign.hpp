//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/shl.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on bitofsign")
{

  if constexpr(eve::floating_value<T>)
  {
    auto std_bitofsign = [](auto e) { return std::copysign(EVE_VALUE(1), e); } );
    auto eve_bitofsign = [](auto e) { return eve::bit_xor(eve::bitofsign(e), EVE_VALUE(1)); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_bitofsign, eve_bitofsign);
  }
  else
  {
    auto std_bitofsign = [](auto e) {
                                                 using i_t = eve::detail::as_integer_t<EVE_VALUE>;
                                                 return  EVE_VALUE(i_t(std::signbit(e)) << (sizeof(e)*8-1)); } );
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_bitofsign, eve::bitofsign);
  }
}
