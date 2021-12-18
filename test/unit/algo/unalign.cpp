//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"


#include <eve/memory/aligned_ptr.hpp>
#include <eve/algo/ptr_iterator.hpp>
#include <vector>

TTS_CASE("eve::algo::unaligned_t")
{
  TTS_TYPE_IS(eve::algo::unaligned_t<int*>, int*);
  TTS_TYPE_IS(eve::algo::unaligned_t<std::vector<int>::const_iterator>, std::vector<int>::const_iterator);
  TTS_TYPE_IS((eve::algo::unaligned_t<eve::aligned_ptr<const int, eve::fixed<2>>>), const int*);
  TTS_TYPE_IS((eve::algo::unaligned_t<eve::algo::aligned_ptr_iterator<int, eve::fixed<2>>>),
              (eve::algo::ptr_iterator<int*, eve::fixed<2>>));
};
