//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <list>

template<typename W> auto data_block()
{
  using alloc_t = eve::aligned_allocator<EVE_VALUE, W::static_alignment>;

  auto nb_elem  = 4096/sizeof(EVE_VALUE);
  auto start    = nb_elem - EVE_CARDINAL;
  std::vector<EVE_VALUE, alloc_t> ref(nb_elem);

  EVE_VALUE k = {};
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = k++;

  return std::pair{ref,start};
}

TTS_CASE("Check ctor from unaligned pointer for wide")
{
  auto [data,idx] = data_block<T>();
  auto* ref_ptr   = &data[idx];

  T simd(ref_ptr);
  T ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE("Check ctor from const unaligned pointer for wide")
{
  auto [data,idx]     = data_block<T>();
  auto const* ref_ptr = &data[idx];

  T simd(ref_ptr);
  T ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE("Check ctor from aligned pointer for wide")
{
  auto constexpr algt = T::static_alignment;
  auto [data,idx]     = data_block<T>();
  auto* ref_ptr       = &data[idx];

  T simd(eve::as_aligned<algt>(ref_ptr));
  T ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE("Check ctor from const aligned pointer for wide")
{
  auto constexpr algt = T::static_alignment;
  auto [data,idx]     = data_block<T>();
  auto const* ref_ptr = &data[idx];

  T simd(eve::as_aligned<algt>(ref_ptr));
  T ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE("Check ctor from range for wide")
{
  std::list<EVE_VALUE> ref_ptr(EVE_CARDINAL);

  EVE_VALUE k = {};
  for(auto &e : ref_ptr) e = k++;

  T ref;

  k = {};

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, k++);

  {
    T simd(ref_ptr);
    TTS_EQUAL(simd, ref);
  }

  {
    T simd(ref_ptr.begin(), ref_ptr.end());
    TTS_EQUAL(simd, ref);
  }
}
