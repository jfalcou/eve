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
struct remove_ : TraitsSupport
{
  auto operator()(auto&& rng, auto to_remove)
  {
    auto func = [to_remove](auto x) {
      return kumi::make_tuple(x, eve::is_not_equal(x, to_remove));
    };
    return eve::algo::transform_keep_if[TraitsSupport::get_traits()](rng, func);
  }
};
auto transform_keep_if_as_remove = eve::algo::function_with_traits<remove_>[eve::algo::transform_keep_if.get_traits()];

TTS_CASE_TPL("Check transform_keep_if", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  auto op = [](auto x) { return x + x; };
  transform_keep_if_generic_test_aligned_ptr(eve::as<T>{}, eve::algo::transform_keep_if, op);
  remove_generic_test_page_ends(eve::as<T>{}, transform_keep_if_as_remove);
  if constexpr ( eve::current_api >= eve::sve)
    return;
  else
  {
    remove_generic_test_page_ends(eve::as<T>{}, transform_keep_if_as_remove[eve::algo::unroll<3>]);
    remove_generic_test_page_ends(eve::as<T>{}, transform_keep_if_as_remove[eve::algo::force_cardinal<T::size()>]);
  }
};
