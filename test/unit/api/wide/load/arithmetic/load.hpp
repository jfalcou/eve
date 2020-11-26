//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIEVE_TYPE License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/load.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <list>

template<typename T, typename N>
auto data_block()
{
  using alloc_t = eve::aligned_allocator<T, alignof(eve::wide<T, N>)>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - N::value;
  std::vector<T, alloc_t> ref(nb_elem);

  T k = {};
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = k++;

  return std::pair{ref,start};
}

TTS_CASE_TPL("Check ctor from unaligned pointer for wide", EVE_TYPE)
{
  auto [data,idx] = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto* ref_ptr   = &data[idx];

  T ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  T constructed(ref_ptr);
  TTS_EQUAL(constructed, ref);

  T loaded = eve::load(ref_ptr, eve::as_<T>());
  TTS_EQUAL(loaded, ref);
}

TTS_CASE_TPL("Check ctor from const unaligned pointer for wide", EVE_TYPE )
{
  auto [data,idx]     = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto const* ref_ptr = &data[idx];

  T ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  T constructed(ref_ptr);
  TTS_EQUAL(constructed, ref);

  T loaded = eve::load(ref_ptr, eve::as_<T>());
  TTS_EQUAL(loaded, ref);
}

TTS_CASE_TPL("Check ctor from aligned pointer for wide", EVE_TYPE )
{
  auto constexpr algt = alignof(T);
  auto [data,idx]     = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto* ref_ptr       = &data[idx];

  T ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  T constructed(eve::as_aligned<algt>(ref_ptr));
  TTS_EQUAL(constructed, ref);

  T loaded = eve::load(eve::as_aligned<algt>(ref_ptr), eve::as_<T>());
  TTS_EQUAL(loaded, ref);
}

TTS_CASE_TPL("Check ctor from const aligned pointer for wide", EVE_TYPE )
{
  auto constexpr algt = alignof(T);
  auto [data,idx]     = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto const* ref_ptr = &data[idx];

  T ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  T constructed(eve::as_aligned<algt>(ref_ptr));
  TTS_EQUAL(constructed, ref);

  T loaded = eve::load(eve::as_aligned<algt>(ref_ptr), eve::as_<T>());
  TTS_EQUAL(loaded, ref);
}

TTS_CASE_TPL("Check ctor from range for wide", EVE_TYPE )
{
  std::list<EVE_VALUE> ref_ptr(EVE_CARDINAL);

  EVE_VALUE k = {};
  for(auto &e : ref_ptr) e = k++;

  T ref;

  k = {};

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, k++);

  T from_range(ref_ptr);
  TTS_EQUAL(from_range, ref);

  T from_begin_end(ref_ptr.begin(), ref_ptr.end());
  TTS_EQUAL(from_begin_end, ref);
}
