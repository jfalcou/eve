//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <limits>

//==================================================================================================
// tts::comparison decides what TTS_EQUAL means on the shapes EVE adds. A register answers `==`
// lane by lane, so the operator hands back another register rather than a bool, and the whole
// suite depends on that being read as "every lane agrees".
//
// Seven hundred files exercise the hook without ever naming it, and none of them would notice a
// specialization that stopped being selected: the built-in path would fail to convert the register
// to a bool, or, worse, succeed on a shape where it happens to be convertible and report the first
// lane as the verdict. These cases name the hook and pin what it answers.
//
// The negative case, that a stale `compare_equal` overload is refused, is deliberately absent: it
// is a static_assert in a function body, which no requires-expression can observe. Writing it
// would break this file rather than report a failure.
//==================================================================================================

namespace
{
  template<typename L, typename R = L> using c = tts::comparison<L, R>;
}

//==================================================================================================
TTS_CASE("tts::comparison<eve::wide> is every lane agreeing, not the first")
{
  using w_t = eve::wide<std::int32_t, eve::fixed<4>>;

  w_t const a {1, 2, 3, 4};

  TTS_EXPECT(c<w_t>::equal(a, a));
  TTS_EXPECT(c<w_t>::equal(a, w_t{1, 2, 3, 4}));

  // One lane is enough to lose it, wherever it sits. The first lane matching in all three is what
  // separates this hook from a built-in path that read the register's leading value.
  TTS_EXPECT_NOT(c<w_t>::equal(a, w_t{1, 2, 3, 9}));
  TTS_EXPECT_NOT(c<w_t>::equal(a, w_t{1, 2, 9, 4}));
  TTS_EXPECT_NOT(c<w_t>::equal(a, w_t{1, 9, 3, 4}));
};

//==================================================================================================
// A NaN lane is unequal to itself, and this hook is the one that keeps it that way. The lane-wise
// maximum in tts::precision has the opposite job, its `ieee` member being where NaN meets NaN.
//==================================================================================================
TTS_CASE("tts::comparison<eve::wide> answers no on a NaN lane")
{
  using w_t = eve::wide<double, eve::fixed<2>>;

  auto const nan = std::numeric_limits<double>::quiet_NaN();

  TTS_EXPECT    (c<w_t>::equal(w_t{1.0, 2.0}, w_t{1.0, 2.0}));
  TTS_EXPECT_NOT(c<w_t>::equal(w_t{1.0, nan}, w_t{1.0, nan}));

  TTS_EXPECT(tts::precision<w_t>::ieee(w_t{1.0, nan}, w_t{1.0, nan}));
};

//==================================================================================================
TTS_CASE_TPL("tts::comparison<eve::logical> holds for a scalar logical", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using l_t = eve::logical<T>;

  TTS_EXPECT    (c<l_t>::equal(l_t{true},  l_t{true}));
  TTS_EXPECT    (c<l_t>::equal(l_t{false}, l_t{false}));
  TTS_EXPECT_NOT(c<l_t>::equal(l_t{true},  l_t{false}));
  TTS_EXPECT_NOT(c<l_t>::equal(l_t{false}, l_t{true}));
};

//==================================================================================================
TTS_CASE("tts::comparison<eve::logical<wide>> takes the same lane by lane reading")
{
  using w_t = eve::wide<std::int32_t, eve::fixed<4>>;
  using l_t = eve::logical<w_t>;

  l_t const t {true, true, true, true};

  TTS_EXPECT    (c<l_t>::equal(t, t));
  TTS_EXPECT_NOT(c<l_t>::equal(t, l_t{true, true, false, true}));
  TTS_EXPECT_NOT(c<l_t>::equal(l_t{false, false, false, false}, t));
};

//==================================================================================================
// The trait is what TTS_EQUAL reaches, through tts::_::eq. Going through the dispatcher rather than
// the members proves the routing, which is the half a direct call cannot see.
//==================================================================================================
TTS_CASE("tts::_::eq routes the EVE shapes through the trait")
{
  using w_t = eve::wide<float, eve::fixed<4>>;
  using l_t = eve::logical<w_t>;

  TTS_EXPECT    (tts::_::eq(w_t{1.0f, 2.0f, 3.0f, 4.0f}, w_t{1.0f, 2.0f, 3.0f, 4.0f}));
  TTS_EXPECT_NOT(tts::_::eq(w_t{1.0f, 2.0f, 3.0f, 4.0f}, w_t{1.0f, 2.0f, 3.0f, 5.0f}));

  TTS_EXPECT_NOT(tts::_::eq(l_t{true, true, true, true}, l_t{true, false, true, true}));

  // Two scalars of different types keep the built-in path, which is the whole point of the trait
  // taking both operand types: only the pairs EVE names are diverted.
  TTS_EXPECT    (tts::_::eq(1, 1.0));
  TTS_EXPECT_NOT(tts::_::eq(1, 2.0));
};
