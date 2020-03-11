//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/shl.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/one.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE("wide random check on bitofsign")
{

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    auto std_bitofsign = tts::vectorize<EVE_TYPE>( [](auto e) { return std::copysign(eve::One<EVE_VALUE>(), e); } );
    auto eve_bitofsign = [](auto e) { return eve::bit_xor(eve::bitofsign(e), eve::One<EVE_VALUE>()); }; 
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_bitofsign, eve_bitofsign);
  }
  else
  {
    auto std_bitofsign = tts::vectorize<EVE_TYPE>( [](auto e) {
                                                 using i_t = eve::detail::as_integer_t<EVE_VALUE>; 
                                                 return  EVE_VALUE(i_t(std::signbit(e)) << (sizeof(e)*8-1)); } );
    eve::rng_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
    TTS_RANGE_CHECK(p, std_bitofsign, eve::bitofsign);
  }
}
