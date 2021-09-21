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

EVE_TEST_TYPES("aligned_allocator behavior", eve::test::simd::cardinals)
<typename Lanes>(eve::as<Lanes>)
{
  using alloc_t = eve::aligned_allocator<char, Lanes>;
  std::vector<char, alloc_t> x(1337);

  TTS_EXPECT(eve::is_aligned(x.data(), Lanes{}));
};

EVE_TEST_TYPES("aligned_allocator comparisons", eve::test::simd::cardinals)
<typename Lanes>(eve::as<Lanes>)
{
  eve::aligned_allocator<double , Lanes>     a1, a2;
  eve::aligned_allocator<float  , Lanes>     b1;
  eve::aligned_allocator<double , typename Lanes::combined_type> c1;

  TTS_EQUAL(a1, a2);
  TTS_NOT_EQUAL(a1, b1);
  TTS_NOT_EQUAL(a1, c1);
};

EVE_TEST_TYPES("aligned_allocator rebind", eve::test::simd::cardinals)
<typename Lanes>(eve::as<Lanes>)
{
  TTS_TYPE_IS ( (typename eve::aligned_allocator<double, Lanes>::template rebind<float>::other)
              , (eve::aligned_allocator<float, Lanes>)
              );
};
