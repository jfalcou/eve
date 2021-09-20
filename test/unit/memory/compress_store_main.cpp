//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "compress_store_test.hpp"

#include <eve/function/compress_store.hpp>

EVE_TEST( "Check compress store behavior"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(1),eve::test::logicals(1,2))
        )
<typename T, typename L> (T data, L logical_data)
{
  all_tests_for_v<eve::logical<T>>(data);

  (void)logical_data;

  //using N = eve::fixed<T::size()>;

  //smaller_test_v<eve::logical<eve::wide<std::uint8_t,  N>>>(data);
  // smaller_test_v<eve::logical<eve::wide<std::uint16_t, N>>>(data);
  // smaller_test_v<eve::logical<eve::wide<std::uint32_t, N>>>(data);
  // smaller_test_v<eve::logical<eve::wide<std::uint64_t, N>>>(data);

  //smaller_test_v<L>(logical_data);
  // smaller_test_v<eve::logical<eve::wide<std::uint8_t,  N>>>(logical_data);
  // smaller_test_v<eve::logical<eve::wide<std::uint16_t, N>>>(logical_data);
  // smaller_test_v<eve::logical<eve::wide<std::uint32_t, N>>>(logical_data);
  // smaller_test_v<eve::logical<eve::wide<std::uint64_t, N>>>(logical_data);
};
