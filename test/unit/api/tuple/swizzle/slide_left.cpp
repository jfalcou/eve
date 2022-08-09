//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <bit>

template<std::ptrdiff_t Shift, std::ptrdiff_t N>
inline constexpr
auto slide_left_pattern = eve::fix_pattern<N> ( [](auto i, auto c)
                                                {
                                                  return (i+Shift) < c ? i+Shift : eve::na_;
                                                }
                                              );

//==================================================================================================
// slide_left test
//==================================================================================================
TTS_CASE_TPL( "Check behavior of slide_left swizzle", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = kumi::tuple<std::int8_t,T,double>;
  using w_t = eve::wide<s_t>;

  w_t data = [](auto i, auto) { return  s_t { static_cast<std::int8_t>(65+i)
                                            , static_cast<T>(i + 1)
                                            , 1.5*(1+i)
                                            };
                              };

  eve::detail::for_<0,1,w_t::size()>
  ( [&]<typename Shift>(Shift)
  {
    eve::wide<s_t> ref =  [&](auto i, auto c)
                          {
                            return (i+Shift::value) < c ? data.get(i+Shift::value) : s_t{};
                          };

    TTS_EQUAL( eve::slide_left(data,eve::index<Shift::value>)                 , ref );
    TTS_EQUAL( eve::shuffle(data,slide_left_pattern<Shift::value,w_t::size()>), ref );
  }
  );
};
