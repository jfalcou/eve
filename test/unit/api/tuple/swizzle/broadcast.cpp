//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <bit>
#include <cstdint>

template<int I, int N>
inline constexpr auto broadcast = eve::fix_pattern<N>( [](int, int){ return I; } );

template<std::size_t... V, typename S>
auto bcast_test(S d, std::index_sequence<V...>)
{
  auto check = [&]<typename I>(S simd, I idx)
  {
    constexpr auto i = I::value;
    typename S::template rescale<typename S::cardinal_type> ref(simd.get(i));
    TTS_EQUAL(eve::shuffle(simd,broadcast<i,S::size()>) , ref);
    TTS_EQUAL((eve::broadcast(simd, idx))     , ref);
  };

  (check(d,eve::index<V>), ...);
};

//==================================================================================================
// Identity test
//==================================================================================================
TTS_CASE_TPL( "Check behavior of broadcast swizzle", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = kumi::tuple<std::int8_t,T,double>;

  eve::wide<s_t> data = [](auto i, auto){ return s_t{ static_cast<std::int8_t>(65+i)
                                                    , static_cast<T>(i + 1)
                                                    , 1.5*i
                                                    };
                                            };

  bcast_test(data, std::make_index_sequence<eve::wide<s_t>::size()>{} );
};
