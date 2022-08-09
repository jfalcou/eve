//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <utility>

//==================================================================================================
// arithmetic types
//==================================================================================================
TTS_CASE_WITH("Check eve::lookup behavior on arithmetic wide",
              eve::test::simd::all_types,
              tts::generate(tts::ramp(1), tts::logicals(1, 2)))
<typename T, typename L>(T data, L logical_data)
{
  using i_t = eve::as_integer_t<T>;
  using v_t = eve::element_type_t<T>;

  T   ref {[](auto i, auto c) { return static_cast<v_t>(c - i); }};
  L   lref {[=](auto i, auto c) { return logical_data.get(c - i - 1); }};
  i_t indexes {[](auto i, auto c) { return c - i - 1; }};

  TTS_EQUAL(eve::lookup(data, indexes), ref);
  TTS_EQUAL(eve::lookup(logical_data, indexes), lref);
};

template<typename T> using tuple_t = kumi::tuple<std::int8_t, T, double>;

//==================================================================================================
// product types
//==================================================================================================
TTS_CASE_TPL("Check eve::lookup behavior on product type wide", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using s_t = tuple_t<T>;
  using w_t = eve::wide<tuple_t<T>, eve::fixed<4>>;
  using i_t = eve::wide<short, eve::cardinal_t<w_t>>;

  i_t indexes {[](auto i, auto c) { return i % 2 ? i : c - i - 1; }};

  w_t data = [](auto i, auto) {
    return s_t {static_cast<std::int8_t>('a' + i), static_cast<T>(i + 1), 1.5 * (1 + i)};
  };

  w_t ref = [&data, indexes](auto i, auto) { return data.get(indexes.get(i)); };

  TTS_EQUAL(eve::lookup(data, indexes), ref);
};
