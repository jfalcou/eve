//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <array>
#include <limits>

//==================================================================================================
// tts::comparison decides what TTS_EQUAL and TTS_BIT_EQUAL mean on a wide and a logical: every
// lane agreeing, and nothing outside the lanes.
//==================================================================================================

namespace
{
  template<typename L, typename R = L> using c = tts::comparison<L, R>;
}

//==================================================================================================
TTS_CASE("tts::comparison<eve::wide> is every lane agreeing, not the first")
{
  using w_t = eve::wide<std::int32_t, 4>;

  w_t const a {1, 2, 3, 4};

  TTS_EXPECT(c<w_t>::equal(a, a));
  TTS_EXPECT(c<w_t>::equal(a, w_t{1, 2, 3, 4}));

  TTS_EXPECT_NOT(c<w_t>::equal(a, w_t{1, 2, 3, 9}));
  TTS_EXPECT_NOT(c<w_t>::equal(a, w_t{1, 2, 9, 4}));
  TTS_EXPECT_NOT(c<w_t>::equal(a, w_t{1, 9, 3, 4}));
};

//==================================================================================================
//==================================================================================================
TTS_CASE("tts::comparison<eve::wide> answers no on a NaN lane")
{
  using w_t = eve::wide<double, 2>;

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
  using w_t = eve::wide<std::int32_t, 4>;
  using l_t = eve::logical<w_t>;

  l_t const t {true, true, true, true};

  TTS_EXPECT    (c<l_t>::equal(t, t));
  TTS_EXPECT_NOT(c<l_t>::equal(t, l_t{true, true, false, true}));
  TTS_EXPECT_NOT(c<l_t>::equal(l_t{false, false, false, false}, t));
};

//==================================================================================================
//==================================================================================================
TTS_CASE("tts::_::eq routes the EVE shapes through the trait")
{
  using w_t = eve::wide<float, 4>;
  using l_t = eve::logical<w_t>;

  TTS_EXPECT    (tts::_::eq(w_t{1.0f, 2.0f, 3.0f, 4.0f}, w_t{1.0f, 2.0f, 3.0f, 4.0f}));
  TTS_EXPECT_NOT(tts::_::eq(w_t{1.0f, 2.0f, 3.0f, 4.0f}, w_t{1.0f, 2.0f, 3.0f, 5.0f}));

  TTS_EXPECT_NOT(tts::_::eq(l_t{true, true, true, true}, l_t{true, false, true, true}));

  TTS_EXPECT    (tts::_::eq(1, 1.0));
  TTS_EXPECT_NOT(tts::_::eq(1, 2.0));
};

//==================================================================================================
TTS_CASE_TPL("tts::comparison<eve::logical>::bit_equal reads the lanes, not the storage",
             eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using l_t = eve::logical<T>;

  auto const lanes_agree = [](l_t const& a, l_t const& b)
  {
    for(std::size_t i = 0; i < static_cast<std::size_t>(l_t::size()); ++i)
      if(a.get(i) != b.get(i)) return false;

    return true;
  };

  std::array<l_t, 5> masks {l_t {true}, l_t {false}, l_t {false}, l_t {false}, l_t {false}};

  masks[2].set(0, true);
  masks[3].set(static_cast<std::size_t>(l_t::size() / 2), true);
  masks[4].set(static_cast<std::size_t>(l_t::size() - 1), true);

  for(auto const& a : masks)
    for(auto const& b : masks) TTS_EQUAL(tts::_::bit_eq(a, b), lanes_agree(a, b));
};

//==================================================================================================
TTS_CASE_TPL("TTS_BIT_EQUAL reaches the trait on a scalar logical", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using l_t = eve::logical<T>;

  TTS_BIT_EQUAL(l_t {true}, l_t {true});
  TTS_BIT_EQUAL(l_t {false}, l_t {false});
  TTS_BIT_NOT_EQUAL(l_t {true}, l_t {false});
};

//==================================================================================================
TTS_CASE("TTS_BIT_EQUAL reaches the trait on a logical wide")
{
  using w_t = eve::wide<std::int32_t, 4>;
  using l_t = eve::logical<w_t>;

  l_t const t {true, true, true, true};

  TTS_BIT_EQUAL(t, (l_t {true, true, true, true}));
  TTS_BIT_NOT_EQUAL(t, (l_t {true, true, false, true}));
};

//==================================================================================================
TTS_CASE("TTS_BIT_EQUAL leaves out what a partial logical does not carry")
{
  using l4_t = eve::logical<eve::wide<std::int32_t, 4>>;
  using l2_t = eve::logical<eve::wide<std::int32_t, 2>>;

  // The lower half keeps the upper lanes in the register, ff*16, where the same two lanes built
  // on their own give ff*8 then 00*8.
  auto const [lo, hi] = l4_t {true, true, true, true}.slice();

  TTS_EQUAL(lo.get(0), true);
  TTS_EQUAL(lo.get(1), true);

  TTS_BIT_EQUAL(lo, (l2_t {true, true}));
  TTS_BIT_NOT_EQUAL(lo, (l2_t {true, false}));
};
