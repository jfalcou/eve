//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/popcount.hpp>
#include <eve/function/bit_shr.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/bit_shr.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"

TTS_CASE_TPL("wide exhaustive check on popcount", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using u_t =  eve::as_integer_t<T, unsigned>;

  auto std_popcount = tts::vectorize<u_t>(
    [](auto e) { unsigned int j = 0;
      for(unsigned int i = 0; i < sizeof(v_t)*8; ++i)
      {
        if (e&v_t(1)) ++j;
        e = eve::bit_shr(e, 1);
      }
      return j; }
  );

  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_popcount, eve::popcount);
}
