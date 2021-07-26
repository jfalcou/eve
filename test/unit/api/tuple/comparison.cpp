//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/wide.hpp>
#include <utility>

template<typename T>
using tuple_t = kumi::tuple<std::int8_t,T,double>;

//==================================================================================================
// Operator==
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide<tuple>operator==", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  using s_t = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>>;

  w_t lhs = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>(i%3)
                                            , static_cast<T>(i%5)
                                            , i%2 ? -1.5 : 1.5
                                            };
                              };

  w_t rhs = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>(i%4)
                                            , static_cast<T>(i%2)
                                            , i%3 ? -1.5 : 1.5
                                            };
                              };

  eve::logical<eve::wide<std::int8_t,eve::cardinal_t<w_t>>>
  checks = [&](auto i, auto)  { return lhs.get(i) == rhs.get(i); };

  TTS_EQUAL( (lhs == rhs), checks );
};

//==================================================================================================
// Operator!=
//==================================================================================================
EVE_TEST_TYPES( "Check eve::wide<tuple>operator!=", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  using s_t = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>>;

  w_t lhs = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>(i%3)
                                            , static_cast<T>(i%5)
                                            , i%2 ? -1.5 : 1.5
                                            };
                              };

  w_t rhs = [](auto i, auto)  { return s_t  { static_cast<std::int8_t>(i%4)
                                            , static_cast<T>(i%2)
                                            , i%3 ? -1.5 : 1.5
                                            };
                              };

  eve::logical<eve::wide<std::int8_t,eve::cardinal_t<w_t>>>
  checks = [&](auto i, auto)  { return lhs.get(i) != rhs.get(i); };

  TTS_EQUAL( (lhs != rhs), checks );
};
