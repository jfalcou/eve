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
TTS_CASE_WITH( "Check load to logical wides from non-contiguous range"
        , eve::test::simd::all_types_wf16
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
TTS_CASE_WITH( "Check load to logical wides from unaligned pointer"
        , eve::test::simd::all_types_wf16
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

TTS_CASE_TPL( "Check load to logical wides from unaligned pointer to non-logical elements"
        , eve::test::simd::all_types_wf16)
<typename W>(tts::type<W>)
{
  using v_t = eve::element_type_t<W>;
  using LW = eve::logical<W>;

  auto [data  ,idx  ] = arithmetic_logical_page<v_t, eve::fixed<W::size()>>();

  auto* ptr              = &data[idx] - 1;
  auto const* const_ptr  = ptr;

  LW loaded = eve::load(ptr, eve::as<LW>{});
  LW const_loaded = eve::load(const_ptr, eve::as<LW>{});

  for (std::ptrdiff_t i = 0; i < LW::size(); ++i)
  {
    TTS_EQUAL(loaded.get(i)      , data[idx + i - 1] != 0);
    TTS_EQUAL(const_loaded.get(i), data[idx + i - 1] != 0);
  }
};
