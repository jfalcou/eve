//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include "unit/memory/page.hpp"

#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/write.hpp>

//==================================================================================================
// Write scalar to pointer-like entity
//==================================================================================================
EVE_TEST_TYPES( "Check write to pointers"
              , eve::test::scalar::all_types
              )
<typename T>(eve::as<T>)
{
  auto [data, idx] = page<T , eve::expected_cardinal_t<T> >();

  auto* ptr   = &data[idx];
  auto* uptr  = &data[idx] - 1;

  eve::write(eve::as_aligned(ptr), T{42});
  TTS_EQUAL( *ptr, T{42} );

  eve::write(uptr, T{42});
  TTS_EQUAL( *uptr, T{42} );
};

//==================================================================================================
// Write scalar to Contiguous Iterators
//==================================================================================================
EVE_TEST_TYPES( "Check write to Contiguous Iterators"
              , eve::test::scalar::all_types
              )
<typename T>(eve::as<T>)
{
  auto [data, idx] = page<T , eve::expected_cardinal_t<T> >();

  auto begin              = data.begin()  + idx;

  eve::write(begin, T{69});
  TTS_EQUAL( *begin, T{69});
};
