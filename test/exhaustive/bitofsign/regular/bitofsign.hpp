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
#include <eve/constant/one.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on bitofsign", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_value<T>)
  {
    auto std_bitofsign = tts::vectorize<T>( [](auto e) { return std::copysign(eve::One<v_t>(), e); } );
    auto eve_bitofsign = [](auto e) { return eve::bit_xor(eve::bitofsign(e), eve::One<v_t>()); };

    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_bitofsign, eve_bitofsign);
  }
  else
  {
    auto std_bitofsign =  tts::vectorize<T>(  [](auto e)
                                              {
                                                using i_t = eve::detail::as_integer_t<v_t>;
                                                return v_t(i_t(std::signbit(e)) << (sizeof(e)*8-1));
                                              }
                                            );

    eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
    TTS_RANGE_CHECK(p, std_bitofsign, eve::bitofsign);
  }
}
