//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "transform_copy_if_generic_test.hpp"

template <typename TraitsSupport>
struct copy_if_ignore_op_ : TraitsSupport
{
  auto operator()(auto&& in, auto&& out, auto func)
  {
    auto p = [&](auto x) { return get<1>(func(x)); };
    return eve::algo::copy_if[TraitsSupport::get_traits()](in, out, p);
  }
};
auto copy_if_ignore_op = eve::algo::function_with_traits<copy_if_ignore_op_>[eve::algo::copy_if.get_traits()];

TTS_CASE_TPL("Check copy_if", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  auto id = [](auto x) { return x; };
  algo_test::transform_copy_if_generic_test(eve::as<T>{}, copy_if_ignore_op, id);
};
