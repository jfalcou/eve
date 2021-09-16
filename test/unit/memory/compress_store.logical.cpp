//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "compress_store.hpp"

EVE_TEST( "Check compress store behavior for logical"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::logicals(1,2))
        )
<typename L> (L logical_data)
{
  smaller_test_v<L>(logical_data);
};


EVE_TEST( "Check compress store behavior logical - uneven logical type"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::logicals(1,2))
        )
<typename L> (L logical_data)
{
  smaller_test_v<eve::logical<eve::wide<std::uint8_t, eve::fixed<L::size()>>>>(logical_data);
  smaller_test_v<eve::logical<eve::wide<std::uint64_t, eve::fixed<L::size()>>>>(logical_data);
};
