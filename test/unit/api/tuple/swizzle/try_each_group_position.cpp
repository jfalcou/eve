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

TTS_CASE_TPL( "Check behavior of try_each_group_position", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = kumi::tuple<std::int8_t,T,double>;
  using w_t = eve::wide<s_t>;

  w_t data = [](auto i, auto) { return  s_t { static_cast<std::int8_t>(65+i)
                                            , static_cast<T>(i + 1)
                                            , 1.5*(1+i)
                                            };
                              };
  auto r = eve::try_each_group_position(data, eve::lane<1>);

  eve::detail::for_<0,1,w_t::size()>([&]<typename I>(I ) {
    auto perm = get<I{}()>(r);
    for (int i = 0; i != w_t::size(); ++i) {
      TTS_EXPECT(eve::any(perm == data.get(i))) << data.get(i);
    }
  });
};

}
