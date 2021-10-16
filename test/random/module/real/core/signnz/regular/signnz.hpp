//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/signnz.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"

TTS_CASE_TPL("wide random check on signnz", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  if constexpr(eve::signed_value<T>)
  {
    auto std_signnz = [](auto e) {  return e >= 0 ? EVE_VALUE(1) : EVE_VALUE(-1); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>())+1, eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_signnz, eve::signnz);
  }
  else
  {
    auto std_signnz = [](auto ) { return EVE_VALUE(1); };
    eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
    TTS_RANGE_CHECK(p, std_signnz, eve::signnz);
  }
};