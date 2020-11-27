//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/load.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <list>

using eve::as_aligned;
using eve::logical;
using eve::fixed;

template<typename T, typename N>
auto data_block()
{
  constexpr std::ptrdiff_t algt = alignof(eve::wide<T, N>);
  using alloc_t = eve::aligned_allocator<T, algt>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - std::max(algt,N::value);
  std::vector<logical<T>, alloc_t> ref(nb_elem);

  bool k = true;
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = (k = !k);

  return std::pair{ref,start};
}

TTS_CASE_TPL( "Check ctor from unaligned pointer for wide", EVE_TYPE )
{
  auto  [data,idx]  = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto* ref_ptr     = &data[idx];

  logical<T> ref;
  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  logical<T> constructed(ref_ptr);
  TTS_EQUAL(constructed, ref);

  logical<T> loaded = eve::load(ref_ptr, eve::as_<logical<T>>());
  TTS_EQUAL(loaded, ref);
}

TTS_CASE_TPL( "Check ctor from const unaligned pointer for wide", EVE_TYPE )
{
  auto        [data,idx]  = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto const* ref_ptr     = &data[idx];

  logical<T> ref;
  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  logical<T> constructed(ref_ptr);
  TTS_EQUAL( constructed, ref );

  logical<T> loaded = eve::load(ref_ptr, eve::as_<logical<T>>());
  TTS_EQUAL(loaded, ref);
}

TTS_CASE_TPL( "Check ctor from aligned pointer for wide", EVE_TYPE )
{
  auto constexpr  algt        = alignof(logical<T>);
  auto            [data,idx]  = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto*           ref_ptr     = &data[idx];

  logical<T> ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  logical<T> constructed(eve::as_aligned<algt>(ref_ptr));
  TTS_EQUAL( constructed, ref );

  logical<T> loaded = eve::load(eve::as_aligned<algt>(ref_ptr), eve::as_<logical<T>>());
  TTS_EQUAL(loaded, ref);
}

TTS_CASE_TPL("Check ctor from const aligned pointer for wide", EVE_TYPE)
{
  auto constexpr  algt        = alignof(logical<T>);
  auto            [data,idx]  = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto const*     ref_ptr     = &data[idx];

  logical<T> ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  logical<T> constructed(eve::as_aligned<algt>(ref_ptr));
  TTS_EQUAL( constructed, ref );

  logical<T> loaded = eve::load(eve::as_aligned<algt>(ref_ptr), eve::as_<logical<T>>());
  TTS_EQUAL(loaded, ref);
}

TTS_CASE_TPL( "Check ctor from range for wide", EVE_TYPE )
{
  std::list<eve::logical<EVE_VALUE>> ref_ptr(EVE_CARDINAL);

  eve::logical<EVE_VALUE> k(true);
  for(auto &e : ref_ptr) e = (k = !k);

  k = true;
  eve::logical<T> ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, (k = !k));

  eve::logical<T> from_range(ref_ptr);
  TTS_EQUAL( from_range, ref );

  eve::logical<T> from_begin_end(ref_ptr.begin(), ref_ptr.end());
  TTS_EQUAL( from_begin_end, ref );
}
