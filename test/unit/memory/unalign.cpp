//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"

#include <eve/function/unalign.hpp>

TTS_CASE("eve::unaligned_t")
{
  using v_i = std::vector<int>::const_iterator;
  using a_p = eve::aligned_ptr<int const, eve::fixed<2>>;

  TTS_TYPE_IS(eve::unaligned_t<int*>, int*);
  TTS_TYPE_IS(eve::unaligned_t<v_i>, v_i);

  TTS_TYPE_IS((eve::unaligned_t<a_p>), int const*);
  TTS_TYPE_IS((eve::unaligned_t<kumi::tuple<a_p, kumi::tuple<a_p, int*>>>),
               (kumi::tuple<int const*, kumi::tuple<int const*, int*>>));
};
