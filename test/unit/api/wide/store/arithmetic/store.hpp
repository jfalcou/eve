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
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/store.hpp>
#include <eve/wide.hpp>

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
  constexpr auto algt = T::alignment();
  std::array<EVE_VALUE, 3 * EVE_CARDINAL> ref;
  T value([](auto i, auto) { return 1 + i * 3; });

  for(int i = 0; i < EVE_CARDINAL; ++i)
  {
    ref[ i                  ] =  1 + i * 3;
    ref[ i + EVE_CARDINAL   ] =  1 + i * 3;
    ref[ i + 2*EVE_CARDINAL ] =  1 + i * 3;
  }

  alignas(T::alignment()) std::array<EVE_VALUE, 3 * EVE_CARDINAL> target;

  eve::store(value, eve::as_aligned<algt>(&target[ 0                ]) );
  eve::store(value, eve::as_aligned<algt>(&target[ EVE_CARDINAL     ]) );
  eve::store(value, eve::as_aligned<algt>(&target[ 2 * EVE_CARDINAL ]) );

  TTS_ALL_EQUAL(target, ref);
}