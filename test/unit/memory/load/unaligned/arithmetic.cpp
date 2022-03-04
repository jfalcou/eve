//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include "unit/memory/page.hpp"

#include <array>
#include <list>

//==================================================================================================
// Load into wide from a (non-contiguous) range
//==================================================================================================
EVE_TEST( "Check load to wides from non-contiguous range"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(1))
        )
<typename T>(T reference)
{
  std::list<eve::element_type_t<T>> ref_range(T::size());

  std::ptrdiff_t i = 0;
  for(auto &e : ref_range) e = reference.get(i++);

  T from_range(ref_range);
  T from_begin_end(ref_range.begin(), ref_range.end());

  TTS_EQUAL(from_range, reference);
  TTS_EQUAL(from_begin_end, reference);
};

//==================================================================================================
// Load into wide from an unaligned pointer
//==================================================================================================
EVE_TEST( "Check load to wides from unaligned pointer"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::ramp(0))
        )
<typename T>(T reference)
{
  using v_t = eve::element_type_t<T>;

  auto [data  ,idx  ] = page<v_t , eve::fixed<T::size()>>();

  auto* ptr              = &data[idx] - 1;
  auto const* const_ptr  = ptr;

  TTS_EQUAL(T(ptr)                                        , reference         );
  TTS_EQUAL(T(const_ptr)                                  , reference         );
  TTS_EQUAL((eve::load(ptr        , eve::lane<T::size()>)), reference         );
  TTS_EQUAL((eve::load(const_ptr  , eve::lane<T::size()>)), reference         );

  if constexpr(T::size() == eve::expected_cardinal_v<v_t>)
  {
    TTS_EQUAL(eve::load(ptr)        , reference );
    TTS_EQUAL(eve::load(const_ptr)  , reference );
  }
};
