//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <eve/function/slide_right.hpp>
#include <bit>

template<std::ptrdiff_t Shift, std::ptrdiff_t N>
inline constexpr
auto slide_right_pattern  = eve::fix_pattern<N>([](auto i, auto )
                                                {
                                                  return i<Shift ? eve::na_ : i-Shift;
                                                });

//==================================================================================================
// slide_right test
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of slide_right swizzle", eve::test::scalar::all_types)
<typename T>(eve::as_<T>)
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
    eve::wide<s_t> ref =  [&](auto i, auto )
                          {
                            return (i < Shift::value) ? s_t{} : data.get(i-Shift::value);
                          };

    TTS_EQUAL( eve::slide_right(data,eve::index<Shift::value>)       , ref );
    TTS_EQUAL( (data[slide_right_pattern<Shift::value,w_t::size()>]) , ref );
  }
  );
};
