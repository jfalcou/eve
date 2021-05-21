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
    auto divisible_by_cardinal = eve::algo::traits(eve::algo::divisible_by_cardinal);
    []<typename Traits>(Traits){
      TTS_CONSTEXPR_EXPECT(Traits::contains(eve::algo::divisible_by_cardinal));
    }(divisible_by_cardinal);
  }
}

TTS_CASE("eve.algo defaulting")
{
  {
    eve::algo::traits out =
      eve::algo::default_to(eve::algo::traits(eve::algo::unroll<1>), eve::algo::traits(eve::algo::unroll<4>));
    TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<decltype(out)>() == 1);
    TTS_CONSTEXPR_EXPECT(!decltype(out)::contains((eve::algo::divisible_by_cardinal)));
    TTS_CONSTEXPR_EXPECT(!decltype(out)::contains((eve::algo::no_aligning)));
  }
  {
    eve::algo::traits out = eve::algo::default_to(
      eve::algo::traits(eve::algo::divisible_by_cardinal),
      eve::algo::traits(eve::algo::unroll<4>,
                        eve::algo::no_aligning));
    TTS_CONSTEXPR_EXPECT(eve::algo::get_unrolling<decltype(out)>() == 4);
    TTS_CONSTEXPR_EXPECT(decltype(out)::contains((eve::algo::divisible_by_cardinal)));
    TTS_CONSTEXPR_EXPECT(decltype(out)::contains((eve::algo::no_aligning)));
  }
  {
    constexpr auto expected = eve::algo::traits(eve::algo::divisible_by_cardinal);
    constexpr auto actual = eve::algo::default_to(eve::algo::traits(), expected);

    TTS_TYPE_IS(decltype(expected), decltype(actual));
  }
}
