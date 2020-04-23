//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/popcount.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/bit_shr.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide exhaustive check on popcount", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using u_t = eve::detail::as_integer_t<T, unsigned>;

  auto std_popcount = tts::vectorize<u_t>(  [](auto e)
                                            {
                                              unsigned int j = 0;
                                              for(std::size_t i = 0; i < sizeof(v_t)*8; ++i)
                                              {
                                                if (e&v_t(1)) ++j;
                                                e = eve::bit_shr(e, 1);
                                              }
                                              return j;
                                            }
                                        );

  eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_popcount, eve::popcount);
}
