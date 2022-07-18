//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"
#include "unit/algo/algorithm/reduce_generic.hpp"

#include <eve/algo/transform_reduce.hpp>

template<typename TraitsSupport> struct transfrom_reduce_2_reduce_ : TraitsSupport
{
  EVE_FORCEINLINE auto operator()(auto&& rng, auto init) const
  {
    return eve::algo::transform_reduce[TraitsSupport::get_traits()](
        EVE_FWD(rng), [](auto x) { return x; }, init);
  }
};

inline constexpr auto transform_reduce_2_reduce = eve::algo::function_with_traits<
    transfrom_reduce_2_reduce_>[eve::algo::transform_reduce.get_traits()];

TTS_CASE_TPL("Check transform reduce generic", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  reduce_generic_all_test_cases(eve::as<T> {}, transform_reduce_2_reduce);
};
