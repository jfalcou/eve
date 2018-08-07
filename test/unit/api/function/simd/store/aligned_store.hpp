//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ALIGNED_STORE_HPP
#define ALIGNED_STORE_HPP

#include <eve/pack.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/store.hpp>
#include <tts/tts.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>

using eve::fixed;
using eve::as_aligned;

TTS_CASE_TPL( "Check store behavior to aligned pointer"
            , fixed<1>, fixed<2>, fixed<4>, fixed<8>, fixed<16>, fixed<32>, fixed<64>
            )
{
  using eve::pack;

  auto filler = [](auto i, auto) { return 1 + i; };

  constexpr auto algt = pack<Type,T>::alignment();

  pack<Type,T> simd( filler );
  alignas(algt) std::array<Type,3*T::value> ref;
  alignas(algt) std::array<Type,3*T::value> target;

  for(std::size_t i=0;i<T::value;++i)
  {
    auto v = filler(i,T::value);
    ref[i] = ref[i+T::value] = ref[i+2*T::value] = v;
  }

  eve::store(simd, as_aligned<algt>(&target[0]) );
  eve::store(simd, as_aligned<algt>(&target[T::value]) );
  eve::store(simd, as_aligned<algt>(&target[2*T::value]) );

  TTS_EXPECT( std::equal(target.begin(),target.end(),ref.begin()));
}

#endif
