//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/inclusive_scan.hpp>

#include "transform_inplace_generic.hpp"

#include <algorithm>
#include <functional>
#include <vector>

EVE_TEST_TYPES("Check inlclusive_scan_inplace", algo_test::selected_types)
<typename T>(eve::as<T> tgt)
{
  algo_test::transform_inplace_generic_test(
    tgt,
    eve::algo::inclusive_scan_inplace,
    [](auto f, auto l, auto o, auto init) {
      std::inclusive_scan(f, l, o, std::plus<>{}, init);
    },
    eve::element_type_t<T>{10}
  );
};
