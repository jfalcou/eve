//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/load.hpp>

#include <eve/function/any.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/wide.hpp>

#include <array>
#include <numeric>
#include <vector>
#include <list>

template<typename T, typename N>
auto data_block()
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<eve::wide<T, N>>;
  using alloc_t = eve::aligned_allocator<T, algt>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - std::max(algt,N::value);
  std::vector<T, alloc_t> ref(nb_elem);

  T k = {1};
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = k++;

  return std::pair{ref,start};
}

TTS_CASE_TPL("Check load for scalar", EVE_TYPE)
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<T>;

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
  constexpr std::ptrdiff_t algt = eve::alignment_v<T>;
  auto [data,idx]               = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();

  TTS_WHEN("For some given relative data")
  {
    auto* ref_ptr               = &data[idx];
    auto* uref_ptr              = ref_ptr - 1;
    auto const* ref_const_ptr   = &data[idx];
    auto const* uref_const_ptr  = ref_const_ptr - 1;
    T ref, uref;

    for(std::size_t i=0;i<EVE_CARDINAL;++i)
    {
      ref.set (i, ref_ptr[i]);
      uref.set(i, uref_ptr[i]);
    }

    TTS_AND_THEN("we load from unaligned pointers")
    {
      TTS_EQUAL(T(uref_ptr)                                    , uref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(uref_ptr)                          , uref);

      TTS_EQUAL((eve::load(uref_ptr, eve::lane<EVE_CARDINAL>)) , uref);
    }

    TTS_AND_THEN("we load from unaligned pointers to constant")
    {
      TTS_EQUAL(T(uref_const_ptr)                                    , uref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(uref_const_ptr)                          , uref);

      TTS_EQUAL((eve::load(uref_const_ptr, eve::lane<EVE_CARDINAL>)) , uref);
    }

    TTS_AND_THEN("we load from aligned pointers")
    {
      TTS_EQUAL(T(eve::as_aligned<algt>(ref_ptr))                                    , ref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(eve::as_aligned<algt>(ref_ptr))                          , ref);

      TTS_EQUAL((eve::load(eve::as_aligned<algt>(ref_ptr), eve::lane<EVE_CARDINAL>)) , ref);
    }

    TTS_AND_THEN("we load from aligned pointers to constant")
    {
      TTS_EQUAL(T(eve::as_aligned<algt>(ref_const_ptr))                                    , ref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(eve::as_aligned<algt>(ref_const_ptr))                          , ref);

      TTS_EQUAL((eve::load(eve::as_aligned<algt>(ref_const_ptr), eve::lane<EVE_CARDINAL>)) , ref);
    }
  }
}

TTS_CASE_TPL("Check load from range for wide", EVE_TYPE )
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

TTS_CASE_TPL("load for different alignment, wide", EVE_TYPE )
{
  using e_t = EVE_VALUE;
  std::array<e_t, 256> data;

  std::iota(data.begin(), data.end(), 0);

  for (const e_t* f =  data.begin();
                  f != data.end() - EVE_CARDINAL + 1;
                  ++f)
  {
    T expected(f);

    auto test = [&]<std::ptrdiff_t A>(eve::fixed<A>) {
      if (!eve::is_aligned<A>(f)) return;
      if constexpr (A >= T::static_alignment)
      {
        eve::aligned_ptr<const e_t, static_cast<std::size_t>(A)> ptr{f};
        T actual{ptr};
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
