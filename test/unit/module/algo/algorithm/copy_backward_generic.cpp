//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>
#include <eve/module/algo.hpp>

#include "transform_to_generic_test.hpp"

#include <algorithm>

template <typename TraitsSupport>
struct copy_backward_no_static_assert_ : TraitsSupport
{
  template <typename R1, typename R2>
  EVE_FORCEINLINE void operator()(R1&& from, R2&& to) const
  {
    if constexpr (eve::algo::relaxed_iterator<R2>)
    {
      auto zipped = eve::views::zip(EVE_FWD(from), EVE_FWD(to));
      eve::algo::copy_backward[TraitsSupport::get_traits()](zipped);
    }
    else
    {
      eve::algo::copy_backward[TraitsSupport::get_traits()](EVE_FWD(from), EVE_FWD(to));
    }
  }
};

inline constexpr auto copy_backward_no_static_assert = eve::algo::function_with_traits<copy_backward_no_static_assert_>[eve::algo::copy_backward.get_traits()];


TTS_CASE_TPL("Check copy to a different range", algo_test::selected_pairs_types)
<typename T>(tts::type<T>)
{
  algo_test::transform_to_generic_test(
    eve::as<T>{},
    copy_backward_no_static_assert,
    [](auto f, auto l, auto o) {
      std::copy(f, l, o);
    }
  );
};
