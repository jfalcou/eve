//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
TTS_CASE_WITH( "Check load to wides from non-contiguous range"
        , eve::test::simd::all_types
        , tts::generate(tts::logicals(1,2))
        )
<typename T>(T reference)
{
  std::list<eve::element_type_t<T>> ref_range(T::size());

  std::ptrdiff_t i = 0;
  for(auto &e : ref_range) e = reference.get(i++);

  T from_range(ref_range);

  TTS_EQUAL(from_range, reference);
};

//==================================================================================================
// Load into wide from an unaligned pointer
//==================================================================================================
TTS_CASE_WITH( "Check load to wides from unaligned pointer"
        , eve::test::simd::all_types
        , tts::generate(tts::logicals(1,2))
        )
<typename T>(T reference)
{
  using v_t = eve::element_type_t<typename T::mask_type>;

  auto [data  ,idx  ] = logical_page<v_t, eve::fixed<T::size()>>();

  auto* ptr              = &data[idx] - 1;
  auto const* const_ptr  = ptr;

  TTS_EQUAL(T(ptr)                                        , reference         );
  TTS_EQUAL(T(const_ptr)                                  , reference         );
  TTS_EQUAL((eve::load(ptr        , eve::lane<T::size()>)), reference         );
  TTS_EQUAL((eve::load(const_ptr  , eve::lane<T::size()>)), reference         );

  if constexpr(T::size() == eve::expected_cardinal_v<v_t>)
  {
    TTS_EQUAL(eve::load(ptr)        , reference         );
    TTS_EQUAL(eve::load(const_ptr)  , reference         );
  }
};
