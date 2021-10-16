//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/popcount.hpp>
#include <eve/logical.hpp>
#include "producers.hpp"
#include <bit>

TTS_CASE_TPL("wide random check on is_pow2", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_is_pow2 = [] < typename U > (U e) ->eve::logical<U> {
    using ui_t =  eve::as_integer_t<U, unsigned>;
    return ((e > 0) && (std::popcount(eve::bit_cast(e, eve::as<ui_t>())) == 1u));
  };

  eve::uniform_prng<EVE_VALUE> p(eve::zero(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_is_pow2, eve::is_pow2);
};