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

TTS_CASE_TPL( "Check behavior of slide_right shuffle", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = kumi::tuple<std::int8_t,T,double>;
  using w_t = eve::wide<s_t>;


  w_t x = [](auto i, auto) { return  s_t { static_cast<std::int8_t>(65+i)
                                          , static_cast<T>(i + 1)
                                          , 1.5*(1+i)
                                          };
                            };

  w_t y = [](auto i, auto) { return  s_t { static_cast<std::int8_t>(65-i)
                                          , static_cast<T>(-i + 1)
                                          , 1.5*(1+-i)
                                          };
                            };

  eve::detail::for_<0,1,w_t::size()>
  ( [&]<typename Shift>(Shift)
  {
    eve::wide<s_t> ref =  [&](auto i, auto )
                          {
                            return (i < Shift::value) ? x.get(w_t::size() + i - Shift::value) : y.get(i-Shift::value);
                          };

    TTS_EQUAL( eve::slide_right(x, y,eve::index<Shift::value>)       , ref );
  });
};
