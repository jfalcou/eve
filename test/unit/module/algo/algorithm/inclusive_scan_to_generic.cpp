//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include "transform_to_generic_test.hpp"

#include <algorithm>
#include <functional>
#include <vector>

TTS_CASE_TPL("Check inclusive_scan_to", algo_test::selected_pairs_types)
<typename T>(tts::type<T>)
{
  using init_t = std::tuple_element_t<1, eve::element_type_t<T>>;

  algo_test::transform_to_generic_test(
    eve::as<T>{},
    eve::algo::inclusive_scan_to,
    [](auto f, auto l, auto o, auto init) {
      std::inclusive_scan(f, l, o, std::plus<>{}, init);
    },
    init_t{10}
  );
};
