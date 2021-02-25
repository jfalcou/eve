//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/load.hpp>

#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/any.hpp>
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
  constexpr std::ptrdiff_t algt = eve::logical<eve::wide<T, N>>::alignment();
  using alloc_t = eve::aligned_allocator<eve::logical<T>, algt>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - std::max(algt,N::value);
  std::vector<logical<T>, alloc_t> ref(nb_elem);

  bool k = true;
  for(std::size_t i=start-1;i<nb_elem;++i) ref[i] = (k = !k);

  return std::pair{ref,start};
}

TTS_CASE_TPL("Check load for scalar", EVE_TYPE)
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<logical<T>>;

  auto [data,idx]             = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto* ref_ptr               = &data[idx];
  auto* uref_ptr              = ref_ptr - 1;
  auto const* ref_const_ptr   = ref_ptr;
  auto const* uref_const_ptr  = uref_ptr;

  TTS_EQUAL((eve::load(uref_ptr                             , eve::scalar)) , *uref_ptr       );
  TTS_EQUAL((eve::load(uref_const_ptr                       , eve::scalar)) , *uref_const_ptr );
  TTS_EQUAL((eve::load(eve::as_aligned<algt>(ref_ptr)       , eve::scalar)) , *ref_ptr        );
  TTS_EQUAL((eve::load(eve::as_aligned<algt>(ref_const_ptr) , eve::scalar)) , *ref_const_ptr  );
}

TTS_CASE_TPL("Check load from for wide", EVE_TYPE)
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<logical<T>>;
  auto [data,idx]               = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();

  TTS_WHEN("For some given relative data")
  {
    auto* ref_ptr               = &data[idx];
    auto* uref_ptr              = ref_ptr - 1;
    auto const* ref_const_ptr   = &data[idx];
    auto const* uref_const_ptr  = ref_const_ptr - 1;
    eve::logical<T> ref( [](auto i, auto) { return i%2==0; })
                  , uref( [](auto i, auto) { return (i-1)%2==0; });

    TTS_AND_THEN("we load from unaligned pointers")
    {
      TTS_EQUAL(eve::logical<T>(uref_ptr)                      , uref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(uref_ptr)                          , uref);

      TTS_EQUAL((eve::load(uref_ptr, eve::lane<EVE_CARDINAL>)) , uref);
    }

    TTS_AND_THEN("we load from unaligned pointers to constant")
    {
      TTS_EQUAL(eve::logical<T>(uref_const_ptr)                      , uref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(uref_const_ptr)                          , uref);

      TTS_EQUAL((eve::load(uref_const_ptr, eve::lane<EVE_CARDINAL>)) , uref);
    }

    TTS_AND_THEN("we load from aligned pointers")
    {
      TTS_EQUAL(eve::logical<T>(eve::as_aligned<algt>(ref_ptr))                      , ref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(eve::as_aligned<algt>(ref_ptr))                          , ref);

      TTS_EQUAL((eve::load(eve::as_aligned<algt>(ref_ptr), eve::lane<EVE_CARDINAL>)) , ref);
    }

    TTS_AND_THEN("we load from aligned pointers to constant")
    {
      TTS_EQUAL(eve::logical<T>(eve::as_aligned<algt>(ref_const_ptr))                      , ref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(eve::as_aligned<algt>(ref_const_ptr))                          , ref);

      TTS_EQUAL((eve::load(eve::as_aligned<algt>(ref_const_ptr), eve::lane<EVE_CARDINAL>)) , ref);
    }
  }
}

TTS_CASE_TPL("Check load from range for wide", EVE_TYPE )
{
  std::list<eve::logical<EVE_VALUE>> ref_ptr(EVE_CARDINAL);

  eve::logical<EVE_VALUE> k(true);
  for(auto &e : ref_ptr) e = (k = !k);

  eve::logical<T> ref( [](auto i, auto) { return i%2==1; });

  eve::logical<T> from_range(ref_ptr);
  TTS_EQUAL( from_range, ref );

  eve::logical<T> from_begin_end(ref_ptr.begin(), ref_ptr.end());
  TTS_EQUAL( from_begin_end, ref );
}

TTS_CASE_TPL("load for different alignment, logical", EVE_TYPE )
{
  using e_t = logical<EVE_VALUE>;
  std::array<e_t, 256> data;

  data.fill(false);
  for (int i = 0; i < 256; i += 2) data[i] = true;

  for (const e_t* f =  data.begin();
                  f != data.end() - EVE_CARDINAL + 1;
                  ++f)
  {
    logical<T> expected(f);

    auto test = [&]<std::ptrdiff_t A>(eve::fixed<A>) {
      if (!eve::is_aligned<A>(f)) return;
      if constexpr (A >= T::static_alignment)
      {
        eve::aligned_ptr<const e_t, static_cast<std::size_t>(A)> ptr{f};
        eve::logical<T> actual{ptr};
        TTS_EQUAL(actual, expected);

        actual = eve::unsafe(eve::load)(ptr, eve::lane<EVE_CARDINAL>);
        TTS_EQUAL(actual, expected);
      }
    };

    test(eve::lane<128>);
    test(eve::lane<64>);
    test(eve::lane<32>);
    test(eve::lane<16>);
    test(eve::lane<8>);
    test(eve::lane<4>);
  }
}
