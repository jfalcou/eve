//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/store.hpp>
#include <eve/wide.hpp>

#include <array>
#include <numeric>

TTS_CASE_TPL("Check store behavior to unaligned arithmetic pointer", EVE_TYPE)
{
  std::array<EVE_VALUE, 3 * EVE_CARDINAL> ref;
  T value([](auto i, auto) { return 1 + i * 3; });

  for(int i = 0; i < EVE_CARDINAL; ++i)
  {
    ref[ i                  ] =  1 + i * 3;
    ref[ i + EVE_CARDINAL   ] =  1 + i * 3;
    ref[ i + 2*EVE_CARDINAL ] =  1 + i * 3;
  }

  std::array<EVE_VALUE, 3 * EVE_CARDINAL> target;

  eve::store(value, &target[ 0                ]);
  eve::store(value, &target[ EVE_CARDINAL     ]);
  eve::store(value, &target[ 2 * EVE_CARDINAL ]);

  TTS_ALL_EQUAL(target, ref);
}

TTS_CASE_TPL("Check store behavior to aligned arithmetic pointer", EVE_TYPE)
{
  constexpr auto algt = eve::alignment_v<T>;

  std::array<EVE_VALUE, 3 * EVE_CARDINAL> ref;
  T value([](auto i, auto) { return 1 + i * 3; });

  for(int i = 0; i < EVE_CARDINAL; ++i)
  {
    ref[ i                  ] =  1 + i * 3;
    ref[ i + EVE_CARDINAL   ] =  1 + i * 3;
    ref[ i + 2*EVE_CARDINAL ] =  1 + i * 3;
  }

  alignas(algt) std::array<EVE_VALUE, 3 * EVE_CARDINAL> target;

  eve::store(value, eve::as_aligned<algt>(&target[ 0                ]) );
  eve::store(value, eve::as_aligned<algt>(&target[ EVE_CARDINAL     ]) );
  eve::store(value, eve::as_aligned<algt>(&target[ 2 * EVE_CARDINAL ]) );

  TTS_ALL_EQUAL(target, ref);
}

TTS_CASE_TPL("store for different alignment", EVE_TYPE )
{
  using e_t = EVE_VALUE;
  std::array<e_t, 256> data;

  const T what{[](int i, int) { return i; }};

  for (e_t* f =  data.begin();
            f != data.end() - EVE_CARDINAL + 1;
          ++f)
  {
    auto test = [&]<std::ptrdiff_t A>(eve::fixed<A>) {
      if (!eve::is_aligned<A>(f)) return;
      if constexpr (A >= T::static_alignment)
      {
        eve::aligned_ptr<e_t, static_cast<std::size_t>(A)> ptr{f};
        eve::store(what, ptr);
        TTS_EQUAL(T{f}, what);
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
