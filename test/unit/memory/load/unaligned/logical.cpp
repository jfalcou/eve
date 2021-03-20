//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "unit/memory/page.hpp"

#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/load.hpp>
#include <array>
#include <list>

//==================================================================================================
// Load into scalars
//==================================================================================================
auto scalar_tests = []<typename T>(T)
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<eve::logical<T>>;

  auto [data,idx]        = logical_page<T, eve::scalar_cardinal>();
  auto* ptr               = &data[idx];
  auto* uptr              = ptr - 1;
  auto const* const_ptr   = ptr;
  auto const* uconst_ptr  = uptr;

  TTS_EQUAL((eve::load(uptr                             , eve::scalar)) , *uptr       );
  TTS_EQUAL((eve::load(uconst_ptr                       , eve::scalar)) , *uconst_ptr );
  TTS_EQUAL((eve::load(eve::as_aligned<algt>(ptr)       , eve::scalar)) , *ptr        );
  TTS_EQUAL((eve::load(eve::as_aligned<algt>(const_ptr) , eve::scalar)) , *const_ptr  );
};

EVE_TEST_BED( "Check load to scalar values"
            , eve::test::scalar::all_types
            , eve::test::generate(eve::test::no_data)
            , scalar_tests
            );

//==================================================================================================
// Load into wide from a (non-contiguous) range
//==================================================================================================
auto range_tests = []<typename T>(T reference)
{
  std::list<eve::element_type_t<T>> ref_range(T::size());

  std::ptrdiff_t i = 0;
  for(auto &e : ref_range) e = reference.get(i++);

  T from_range(ref_range);
  T from_begin_end(ref_range.begin(), ref_range.end());

  TTS_EQUAL(from_range, reference);
  TTS_EQUAL(from_begin_end, reference);
};

EVE_TEST_BED( "Check load to wides from non-contiguous range"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::logicals(1,2))
            , range_tests
            );

//==================================================================================================
// Load into wide from an unaligned pointer
//==================================================================================================
auto unaligned_tests = []<typename T>(T reference)
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

EVE_TEST_BED( "Check load to wides from unaligned pointer"
            , eve::test::simd::all_types
            , eve::test::generate(eve::test::logicals(1,2))
            , unaligned_tests
            );
