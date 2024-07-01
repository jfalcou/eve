//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"
#include "unit/module/algo/algorithm/transform_keep_if_and_remove_generic_test.hpp"

#include <eve/module/algo.hpp>

template<typename TraitsSupport>
struct transform_keep_if_ignore_op_ : TraitsSupport
{
  auto operator()(auto&& rng, auto func)
  {
    auto pred = [&func](auto x) {
      return !get<1>(func(x));
    };
    return eve::algo::remove_if[TraitsSupport::get_traits()](rng, pred);
  }
};
auto transform_keep_if_ignore_op = eve::algo::function_with_traits<transform_keep_if_ignore_op_>[eve::algo::remove_if.get_traits()];

TTS_CASE_TPL("Check remove test", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  auto id = [](auto x) { return x; };
  transform_keep_if_generic_test_aligned_ptr(eve::as<T>{}, transform_keep_if_ignore_op, id);
  remove_generic_test_page_ends(eve::as<T>{}, eve::algo::remove);
  remove_generic_test_page_ends(eve::as<T>{}, eve::algo::remove[eve::algo::sparse_output]);
  if constexpr ( eve::current_api >= eve::sve)
    return;
  else
  {
    remove_generic_test_page_ends(eve::as<T>{}, eve::algo::remove[eve::algo::unroll<3>]);
    remove_generic_test_page_ends(eve::as<T>{}, eve::algo::remove[eve::algo::force_cardinal<T::size()>]);
  }
};
