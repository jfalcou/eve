//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/algo/traits.hpp>

TTS_CASE("eve.algo basic traits testing")
{
  {
    []<typename Traits>(Traits) {
      TTS_CONSTEXPR_EXPECT_NOT(Traits::contains(eve::algo::unrolling));
      TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<Traits>() == 1);
    } (eve::algo::traits());
  }
  {
    auto just_unroll = eve::algo::traits(eve::algo::unroll<4>);
    []<typename Traits>(Traits){
      TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<Traits>() == 4);
    }(just_unroll);
  }
  {
    auto divisible_by_cardinal = eve::algo::traits(eve::algo::divisible_by_cardinal = true);
    []<typename Traits>(Traits){
      TTS_CONSTEXPR_EXPECT(Traits::contains(eve::algo::divisible_by_cardinal));
    }(divisible_by_cardinal);
  }
}
