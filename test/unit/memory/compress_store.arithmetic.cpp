//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "compress_store.hpp"

EVE_TEST( "Check compress store behavior for arithmetic"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(1))
        )
<typename T> (T data)
{
  all_tests_for_v<eve::logical<T>>(data);
};

EVE_TEST( "Check compress store behavior arithmetic - uneven logical type"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(1))
        )
<typename T> (T data)
{
  smaller_test_v<eve::logical<eve::wide<std::uint8_t, eve::fixed<T::size()>>>>(data);
  smaller_test_v<eve::logical<eve::wide<std::uint16_t, eve::fixed<T::size()>>>>(data);
  smaller_test_v<eve::logical<eve::wide<std::uint32_t, eve::fixed<T::size()>>>>(data);
  smaller_test_v<eve::logical<eve::wide<std::uint64_t, eve::fixed<T::size()>>>>(data);
};
