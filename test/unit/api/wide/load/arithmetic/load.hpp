//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIEVE_TYPE License <http://opensource.org/licenses/MIT>.
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
  auto [data,idx] = data_block<EVE_TYPE>();
  auto* ref_ptr   = &data[idx];

  EVE_TYPE simd(ref_ptr);
  EVE_TYPE ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE("Check ctor from const unaligned pointer for wide")
{
  auto [data,idx]     = data_block<EVE_TYPE>();
  auto const* ref_ptr = &data[idx];

  EVE_TYPE simd(ref_ptr);
  EVE_TYPE ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE("Check ctor from aligned pointer for wide")
{
  auto constexpr algt = EVE_TYPE::static_alignment;
  auto [data,idx]     = data_block<EVE_TYPE>();
  auto* ref_ptr       = &data[idx];

  EVE_TYPE simd(eve::as_aligned<algt>(ref_ptr));
  EVE_TYPE ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE("Check ctor from const aligned pointer for wide")
{
  auto constexpr algt = EVE_TYPE::static_alignment;
  auto [data,idx]     = data_block<EVE_TYPE>();
  auto const* ref_ptr = &data[idx];

  EVE_TYPE simd(eve::as_aligned<algt>(ref_ptr));
  EVE_TYPE ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE("Check ctor from range for wide")
{
  std::list<EVE_VALUE> ref_ptr(EVE_CARDINAL);

  EVE_VALUE k = {};
  for(auto &e : ref_ptr) e = k++;

  EVE_TYPE ref;

  k = {};

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, k++);

  {
    EVE_TYPE simd(ref_ptr);
    TTS_EQUAL(simd, ref);
  }

  {
    EVE_TYPE simd(ref_ptr.begin(), ref_ptr.end());
    TTS_EQUAL(simd, ref);
  }
}
