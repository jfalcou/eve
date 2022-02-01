//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/popcount.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/function/bit_shr.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide rng check on popcount", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  using u_t =  eve::as_integer_t<T, unsigned>;
  using su_t =  eve::element_type_t<u_t>;
  auto std_popcount = [](auto e) -> su_t { unsigned int j = 0;
                                   for(unsigned int i = 0; i < sizeof(EVE_VALUE)*8; ++i)
                                   {
                                     if (e&EVE_VALUE(1)) ++j;
                                     e = eve::bit_shr(e, 1);
                                   }
                                   return j; };
  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_popcount, eve::popcount);
};