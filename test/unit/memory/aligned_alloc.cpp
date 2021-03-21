//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/memory/is_aligned.hpp>
#include <eve/memory/aligned_alloc.hpp>
#include <eve/memory/aligned_dealloc.hpp>

EVE_TEST_TYPES( "aligned_alloc behavior", eve::test::simd::sizes)
<typename T>(eve::as_<T>)
{
  auto ptr = eve::aligned_alloc<T::value>( (3 + sizeof(float)) * T::value);
  TTS_EXPECT(eve::is_aligned<T::value>(ptr));

  eve::aligned_ptr<int, T::value> iptr = ptr;
  TTS_EXPECT(eve::is_aligned<T::value>(iptr));

  eve::aligned_dealloc(ptr);
};
