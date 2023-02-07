//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"
#include "unit/module/algo/algorithm/reduce_generic.hpp"

#include <eve/module/algo.hpp>

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

template<typename TraitsSupport> struct transfrom_reduce_2_reduce_fuse_ : TraitsSupport
{
  EVE_FORCEINLINE auto operator()(auto&& rng, auto init) const
  {
    return eve::algo::transform_reduce[TraitsSupport::get_traits()][eve::algo::fuse_operations](
        EVE_FWD(rng), []<typename Sum, typename N>(auto x, eve::wide<Sum, N> sum) {
          return eve::convert(x, eve::as<Sum>{}) + sum; }, init);
  }
};

inline constexpr auto transfrom_reduce_2_reduce_fuse = eve::algo::function_with_traits<
    transfrom_reduce_2_reduce_fuse_>[eve::algo::transform_reduce.get_traits()];


TTS_CASE_TPL("Check transform reduce generic", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  reduce_generic_all_test_cases(eve::as<T> {}, transform_reduce_2_reduce);
  reduce_generic_all_test_cases(eve::as<T> {}, transfrom_reduce_2_reduce_fuse);
};
