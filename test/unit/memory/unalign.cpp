//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>


TTS_CASE("eve::unaligned_t")
{
  using v_i = std::vector<int>::const_iterator;
  using a_p = eve::aligned_ptr<int const, eve::fixed<2>>;
  using soa_a = eve::soa_ptr<a_p, int*>;
  using soa_u = eve::soa_ptr<int const*, int*>;

  TTS_TYPE_IS(eve::unaligned_t<int*>, int*);
  TTS_TYPE_IS(eve::unaligned_t<v_i>, v_i);

  TTS_TYPE_IS((eve::unaligned_t<a_p>), int const*);

  TTS_TYPE_IS(eve::unaligned_t<soa_a>, soa_u);
  TTS_TYPE_IS((eve::unaligned_t<eve::soa_ptr<soa_a, a_p>>),
              (eve::soa_ptr<soa_u, int const*>));
};
