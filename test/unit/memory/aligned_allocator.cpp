//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/memory/is_aligned.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <vector>

EVE_TEST_TYPES("aligned_allocator behavior", eve::test::simd::sizes)
<typename T>(eve::as_<T>)
{
  std::vector<char, eve::aligned_allocator<char, T::value>> x(1337);

  TTS_EXPECT(eve::is_aligned<T::value>(x.data()));
};

EVE_TEST_TYPES("aligned_allocator comparisons", eve::test::simd::sizes)
<typename T>(eve::as_<T>)
{
  eve::aligned_allocator<double , T::value>     a1, a2;
  eve::aligned_allocator<float  , T::value>     b1;
  eve::aligned_allocator<double , 2 * T::value> c1;

  TTS_EQUAL(a1, a2);
  TTS_NOT_EQUAL(a1, b1);
  TTS_NOT_EQUAL(a1, c1);
};

EVE_TEST_TYPES("aligned_allocator rebind", eve::test::simd::sizes)
<typename T>(eve::as_<T>)
{
  TTS_TYPE_IS ( (typename eve::aligned_allocator<double, T::value>::template rebind<float>::other)
              , (eve::aligned_allocator<float, T::value>)
              );
};
