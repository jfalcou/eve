//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/inclusive_scan.hpp>

#include "transform_to_generic_test.hpp"

#include <algorithm>
#include <functional>
#include <vector>

EVE_TEST_TYPES("Check inlclusive_scan_to", algo_test::selected_pairs_types)
<typename T>(eve::as<T> tgt)
{
  using e_t = eve::element_type_t<T>;
  using init_t = eve::common_type_t<std::tuple_element_t<0,e_t>, std::tuple_element_t<1,e_t>>;

  algo_test::transform_to_generic_test(
    tgt,
    eve::algo::inclusive_scan_to,
    [](auto f, auto l, auto o, auto init) {
      std::inclusive_scan(f, l, o, std::plus<>{}, init);
    },
    init_t{10}
  );
};
