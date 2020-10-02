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
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <vector>
#include <list>

using eve::as_aligned;
using eve::logical;
using eve::fixed;

template<typename T, typename N>
auto data_block()
{
  using alloc_t = eve::aligned_allocator<logical<T>, logical<eve::wide<T, N>>::static_alignment>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - N::value;
  std::vector<logical<T>, alloc_t> ref(nb_elem);

  bool k = true;
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = (k = !k);

  return std::pair{ref,start};
}

TTS_CASE_TPL( "Check ctor from unaligned pointer for wide", EVE_TYPE )
{
  auto  [data,idx]  = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto* ref_ptr     = &data[idx];

  logical<T> simd(ref_ptr);
  logical<T> ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL(simd, ref);
}

TTS_CASE_TPL( "Check ctor from const unaligned pointer for wide", EVE_TYPE )
{
  auto        [data,idx]  = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto const* ref_ptr     = &data[idx];

  eve::logical<T> simd(ref_ptr);
  eve::logical<T> ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL( simd, ref );
}

TTS_CASE_TPL( "Check ctor from aligned pointer for wide", EVE_TYPE )
{
  auto constexpr  algt        = logical<T>::static_alignment;
  auto            [data,idx]  = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto*           ref_ptr     = &data[idx];

  eve::logical<T> simd(eve::as_aligned<algt>(ref_ptr));
  eve::logical<T> ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL( simd, ref );
}

TTS_CASE_TPL("Check ctor from const aligned pointer for wide", EVE_TYPE)
{
  auto constexpr  algt        = logical<T>::static_alignment;
  auto            [data,idx]  = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto const*     ref_ptr     = &data[idx];

  eve::logical<T> simd(eve::as_aligned<algt>(ref_ptr));
  eve::logical<T> ref;

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL( simd, ref );
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

  {
    eve::logical<T> simd(ref_ptr);
    TTS_EQUAL( simd, ref );
  }

  {
    eve::logical<T> simd(ref_ptr.begin(), ref_ptr.end());
    TTS_EQUAL( simd, ref );
  }
}
