//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

TTS_CASE_TPL("Check for_each_selected", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  for( std::ptrdiff_t i = 0; i != 100; ++i )
  {
    std::vector<eve::element_type_t<T>> arr(i + 5, 1);

    auto predicate = [](T x) { return eve::true_(eve::as(x)); };

    std::size_t num_times_called = i;

    bool was_interupted = eve::algo::for_each_selected[eve::algo::force_cardinal<T::size()>](
        arr,
        predicate,
        [&, expected = std::ptrdiff_t(0)](typename std::vector<eve::element_type_t<T>>::iterator cur) mutable
        {
          std::ptrdiff_t j = cur - arr.begin();
          if( j >= i ) return true;
          --num_times_called;
          TTS_EQUAL(j, expected++, REQUIRED);
          return false;
        });

    TTS_EXPECT(was_interupted, REQUIRED) << i;
    TTS_EQUAL(0U, num_times_called, REQUIRED);

    num_times_called = i + 5;
    was_interupted =
        eve::algo::for_each_selected[eve::algo::force_cardinal<T::size()>](arr,
                                                                           predicate,
                                                                           [&](auto)
                                                                           {
                                                                             --num_times_called;
                                                                             return false;
                                                                           });

    TTS_EXPECT_NOT(was_interupted, REQUIRED) << i;
    TTS_EQUAL(0U, num_times_called, REQUIRED);
  }
};
