//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/regular/store.hpp>

#include <array>
#include <numeric>

namespace
{
//==================================================================================================
// Unaligned store tests
//==================================================================================================
EVE_TEST( "Check store behavior with unaligned pointers"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(1),eve::test::logicals(1,2))
        )
<typename T, typename L> (T data, L logical_data)
{
  std::array<eve::element_type_t<T>, 3 * T::size()> ref;
  std::array<eve::element_type_t<L>, 3 * T::size()> logical_ref;

  for(int i = 0; i < T::size(); ++i)
  {
    ref[ i              ] =  1 + i;
    ref[ i + T::size()  ] =  1 + i;
    ref[ i + 2*T::size()] =  1 + i;

    logical_ref[ i              ] = ((1+i) % 2) == 0;
    logical_ref[ i + T::size()  ] = ((1+i) % 2) == 0;
    logical_ref[ i + 2*T::size()] = ((1+i) % 2) == 0;
  }

  std::array<eve::element_type_t<T>, 3 * T::size()> target;
  std::array<eve::element_type_t<L>, 3 * T::size()> logical_target;

  eve::store(data, &target[ 0            ]);
  eve::store(data, &target[ T::size()    ]);
  eve::store(data, &target[ 2 * T::size()]);

  eve::store(logical_data, &logical_target[ 0            ]);
  eve::store(logical_data, &logical_target[ T::size()    ]);
  eve::store(logical_data, &logical_target[ 2 * T::size()]);

  TTS_ALL_EQUAL(target        , ref         );
  TTS_ALL_EQUAL(logical_target, logical_ref );
};
}
