//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/wide.hpp>
#include <eve/function/shuffle.hpp>
#include <bit>
#include <cstdint>

template<int I, int N>
inline constexpr auto broadcast = eve::fix_pattern<N>( [](int, int){ return I; } );

//==================================================================================================
// Identity test
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of broadcast swizzle", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  using s_t = kumi::tuple<std::int8_t,T,double>;

  eve::wide<s_t> data = [](auto i, auto){ return s_t{ static_cast<std::int8_t>(65+i)
                                                    , static_cast<T>(i + 1)
                                                    , 1.5*i
                                                    };
                                            };

  auto f  = [&]<std::size_t N, typename S>(S simd, std::integral_constant<std::size_t,N>)
            {
              [&]<std::size_t... V>(std::index_sequence<V...>)
              {
                ([&]()
                {
                  typename S::template rescale<typename S::cardinal_type> ref(simd.get(V));
                  TTS_EQUAL(eve::shuffle(simd,broadcast<V,S::size()>) , ref);
                  TTS_EQUAL((eve::broadcast(simd, eve::index<V>))     , ref);
                }(), ...);

              }( std::make_index_sequence<S::size()>{} );
            };
  f(data    , std::integral_constant<std::size_t,eve::wide<s_t>::size()>{});
};
