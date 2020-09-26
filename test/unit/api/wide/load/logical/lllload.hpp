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
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <list>

using eve::as_aligned;
using eve::logical;

template<typename W> auto data_block()
{
  using alloc_t = eve::aligned_allocator<logical<EVE_VALUE>, logical<W>::static_alignment>;

  auto nb_elem  = 4096/sizeof(EVE_VALUE);
  auto start    = nb_elem - EVE_CARDINAL;
  std::vector<logical<EVE_VALUE>, alloc_t> ref(nb_elem);

  bool k = true;
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = (k = !k);

  return std::pair{ref,start};
}

TTS_CASE( "Check ctor from unaligned pointer for wide")
{
  auto  [data,idx]  = data_block<logical<T>>();
  auto* ref_ptr     = &data[idx];

  eve::logical<eve::wide<EVE_TYPE, T>> simd(ref_ptr);
  eve::logical<eve::wide<EVE_TYPE, T>> ref;

  for(std::size_t i=0;i<T::value;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL( simd, ref );
}

TTS_CASE( "Check ctor from const unaligned pointer for wide")
{
  auto        [data,idx]  = data_block<logical<T>>();
  auto const* ref_ptr     = &data[idx];

  eve::logical<eve::wide<EVE_TYPE, T>> simd(ref_ptr);
  eve::logical<eve::wide<EVE_TYPE, T>> ref;

  for(std::size_t i=0;i<T::value;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL( simd, ref );
}

TTS_CASE( "Check ctor from aligned pointer for wide")
{
  auto constexpr  algt        = logical<eve::wide<EVE_TYPE, T>>::static_alignment;
  auto            [data,idx]  = data_block<logical<T>>();
  auto*           ref_ptr     = &data[idx];

  eve::logical<eve::wide<EVE_TYPE, T>> simd(eve::as_aligned<algt>(ref_ptr));
  eve::logical<eve::wide<EVE_TYPE, T>> ref;

  for(std::size_t i=0;i<T::value;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL( simd, ref );
}

TTS_CASE("Check ctor from const aligned pointer for wide")
{
  auto constexpr  algt        = logical<eve::wide<EVE_TYPE, T>>::static_alignment;
  auto            [data,idx]  = data_block<logical<T>>();
  auto const*     ref_ptr     = &data[idx];

  eve::logical<eve::wide<EVE_TYPE, T>> simd(eve::as_aligned<algt>(ref_ptr));
  eve::logical<eve::wide<EVE_TYPE, T>> ref;

  for(std::size_t i=0;i<T::value;++i)
    ref.set(i, data[idx+i]);

  TTS_EQUAL( simd, ref );
}

TTS_CASE( "Check ctor from range for wide")
{
  std::list<eve::logical<EVE_TYPE>> ref_ptr(T::value);

  eve::logical<EVE_TYPE> k = true;
  for(auto &e : ref_ptr) e = (k = !k);

  k = true;
  eve::logical<eve::wide<EVE_TYPE, T>> ref;

  for(std::size_t i=0;i<T::value;++i)
    ref.set(i, (k = !k));

  {
    eve::logical<eve::wide<EVE_TYPE, T>> simd(ref_ptr);
    TTS_EQUAL( simd, ref );
  }

  {
    eve::logical<eve::wide<EVE_TYPE, T>> simd(ref_ptr.begin(), ref_ptr.end());
    TTS_EQUAL( simd, ref );
  }
}
