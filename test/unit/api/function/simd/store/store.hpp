//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef STORE_HPP
#define STORE_HPP

#include <eve/pack.hpp>
#include <eve/logical.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/store.hpp>
#include <tts/tts.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>

using eve::fixed;
using eve::as_aligned;

TTS_CASE_TPL( "Check store behavior to unaligned pointer"
            , fixed<1>, fixed<2>, fixed<4>, fixed<8>, fixed<16>, fixed<32>, fixed<64>
            )
{
  using eve::pack;

  auto filler = [](auto i, auto) { return 1 + i; };

  pack<Type,T> simd( filler );
  std::array<Type,3*T::value> ref;
  std::array<Type,3*T::value> target;

  for(int i=0;i<T::value;++i)
  {
    auto v = filler(i,T::value);
    ref[i] = ref[i+T::value] = ref[i+2*T::value] = static_cast<Type>(v);
  }

  eve::store(simd, &target[0] );
  eve::store(simd, &target[T::value] );
  eve::store(simd, &target[2*T::value] );

  TTS_EXPECT( std::equal(target.begin(),target.end(),ref.begin()));
}

TTS_CASE_TPL( "Check store behavior to unaligned logical pointer"
            , fixed<1>, fixed<2>, fixed<4>, fixed<8>, fixed<16>, fixed<32>, fixed<64>
            )
{
  using eve::pack;
  using eve::logical;

  auto filler = [](auto i, auto) { return i % 3 == 0; };

  pack<logical<Type>,T> simd( filler );
  std::array<logical<Type>,3*T::value> ref;
  std::array<logical<Type>,3*T::value> target;

  for(std::size_t i=0;i<T::value;++i)
  {
    auto v = filler(i,T::value);
    ref[i] = ref[i+T::value] = ref[i+2*T::value] = static_cast<Type>(v);
  }

  eve::store(simd, &target[0] );
  eve::store(simd, &target[T::value] );
  eve::store(simd, &target[2*T::value] );

  TTS_EXPECT( std::equal(target.begin(),target.end(),ref.begin()));
}

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
    ref[i] = ref[i+T::value] = ref[i+2*T::value] = static_cast<Type>(v);
  }

  eve::store(simd, as_aligned<algt>(&target[0]) );
  eve::store(simd, as_aligned<algt>(&target[T::value]) );
  eve::store(simd, as_aligned<algt>(&target[2*T::value]) );

  TTS_EXPECT( std::equal(target.begin(),target.end(),ref.begin()));
}

TTS_CASE_TPL( "Check store behavior to aligned pointer of logical"
            , fixed<1>, fixed<2>, fixed<4>, fixed<8>, fixed<16>, fixed<32>, fixed<64>
            )
{
  using eve::pack;
  using eve::logical;

  auto filler = [](auto i, auto) { return i%3 == 0; };

  constexpr auto algt = pack<logical<Type>,T>::alignment();

  pack<logical<Type>,T> simd( filler );
  alignas(algt) std::array<logical<Type>,3*T::value> ref;
  alignas(algt) std::array<logical<Type>,3*T::value> target;

  for(std::size_t i=0;i<T::value;++i)
  {
    auto v = filler(i,T::value);
    ref[i] = ref[i+T::value] = ref[i+2*T::value] = static_cast<Type>(v);
  }

  eve::store(simd, as_aligned<algt>(&target[0]) );
  eve::store(simd, as_aligned<algt>(&target[T::value]) );
  eve::store(simd, as_aligned<algt>(&target[2*T::value]) );

  TTS_EXPECT( std::equal(target.begin(),target.end(),ref.begin()));
}

#endif
