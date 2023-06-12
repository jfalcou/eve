//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

namespace
{

TTS_CASE_TPL( "Check behavior of rotate swizzle", eve::test::scalar::all_types)
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
  ( [&]<typename M>(M)
  {
    eve::wide<s_t> ref = [&](auto i, auto)
                         {
                           std::ptrdiff_t point = w_t::size() - M{}();
                           return (i < point) ? data.get(i + M::value) : data.get(i - point);
                         };

    TTS_EQUAL( eve::rotate (data, eve::index<M{}()>)                        , ref );
    TTS_EQUAL( eve::shuffle(data, eve::rotate_pattern<M{}(), w_t::size()>) , ref );
  }
  );
};

}
