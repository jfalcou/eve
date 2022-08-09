//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/inclusive_scan.hpp>

#include "transform_inplace_generic_test.hpp"

#include <algorithm>
#include <functional>

TTS_CASE_TPL("Check inclusive_scan_inplace", algo_test::selected_types)
<typename T>(tts::type<T>)
{
  algo_test::transform_inplace_generic_test(
    eve::as<T>{},
    eve::algo::inclusive_scan_inplace,
    [](auto f, auto l, auto o, auto init) {
      std::inclusive_scan(f, l, o, std::plus<>{}, init);
    },
    eve::element_type_t<T>{10}
  );
};
