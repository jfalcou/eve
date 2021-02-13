//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE
  Copyright 2020 Denis YAROSHEVSKIY
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/detail/top_bits.hpp>
#include <eve/function/is_nez.hpp>

#include <eve/function/all.hpp>

#include <array>

# if defined(EVE_NO_SIMD)
#   define   TOP_BITS_EVE_TYPE EVE_TYPE,eve::wide<std::uint8_t, eve::fixed<128>>
# else
#   define TOP_BITS_EVE_TYPE EVE_TYPE
# endif

using eve::detail::top_bits;

template <typename T, std::size_t N>
bool expect_array(const std::array<T, N>&)
{
  return true;
}

TTS_CASE_TPL("Check top bits raw type", TOP_BITS_EVE_TYPE)
{
  using logical = eve::logical<T>;
  using storage_type = typename top_bits<logical>::storage_type;
  using ABI = typename logical::abi_type;

       if constexpr (eve::has_aggregated_abi_v<logical>) TTS_EXPECT(expect_array(storage_type{}));
  else if constexpr (!ABI::is_wide_logical)              TTS_TYPE_IS(storage_type, typename logical::storage_type);
  else if constexpr (std::same_as<ABI, eve::x86_128_>)   TTS_TYPE_IS(storage_type, std::uint16_t);
  else if constexpr (std::same_as<ABI, eve::x86_256_>)   TTS_TYPE_IS(storage_type, std::uint32_t);
  else if constexpr (eve::arm_abi<ABI>)
  {
         if constexpr ( T::static_size == 1 )                            TTS_TYPE_IS(storage_type, std::uint8_t);
    else if constexpr ( T::static_size == 2 && sizeof(EVE_VALUE) == 1 )  TTS_TYPE_IS(storage_type, std::uint16_t);
    else if constexpr ( eve::current_api == eve::asimd)                  TTS_TYPE_IS(storage_type, std::uint64_t);
    else if constexpr ( T::static_size == 16 && sizeof(EVE_VALUE) == 1 ) TTS_TYPE_IS(storage_type, std::uint64_t);
    else                                                                 TTS_TYPE_IS(storage_type, std::uint32_t);

  }
  else
  {
    if constexpr (logical::static_size < 64)             TTS_TYPE_IS(storage_type, std::uint32_t);
    else                                                 TTS_EXPECT(expect_array(storage_type{}));
  }
}

TTS_CASE_TPL("Check top bits from logical", TOP_BITS_EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical test(false);

  for (std::ptrdiff_t i = 0; i != test.static_size; ++i)
  {
    test.set(i, true);
    top_bits mmask {test};

    for (std::ptrdiff_t j = 0; j != test.static_size; ++j)
    {
      TTS_EQUAL(test.get(j), mmask.get(j));
    }

    test.set(i, false);
  }
}

TTS_CASE_TPL("top_bits, set", TOP_BITS_EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical expected(false);
  top_bits<logical> actual(eve::ignore_all);

  for (std::ptrdiff_t i = 0; i != expected.static_size; ++i)
  {
    expected.set(i, true);
    actual.set(i, true);

    TTS_EQUAL(expected, eve::detail::to_logical(actual));
  }

  for (std::ptrdiff_t i = 0; i != expected.static_size; ++i)
  {
    expected.set(i, false);
    actual.set(i, false);
    TTS_EQUAL(expected, eve::detail::to_logical(actual));
  }
}

TTS_CASE_TPL("Top bits are little endian", TOP_BITS_EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical test(false);
  test.set(0, true);

  if constexpr( top_bits<logical>::is_aggregated )
  {
    TTS_PASS("no test for aggregated");
  }
  else
  {
    top_bits test_top(test);
    TTS_EXPECT((test_top.storage & 1u));
  }
}

TTS_CASE_TPL("bit operations", TOP_BITS_EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical test_inputs[] {
    logical([](int i, int) { return i & 1; }),
    logical([](int i, int) { return i & 2; }),
    logical(false),
    logical(true)
  };

  for (auto x : test_inputs) {
    for (auto y : test_inputs) {
      TTS_EQUAL(top_bits{x && y}, (top_bits{x} & top_bits{y}));
      TTS_EQUAL(top_bits{x || y}, (top_bits{x} | top_bits{y}));

      TTS_EQUAL(top_bits{!x}, ~top_bits<logical>(x));
      // xor
      // test bits to prevent NaN shenanigans
      {
        auto expected = eve::is_nez(x.bits() ^ y.bits());

        TTS_EQUAL(top_bits{expected}, (top_bits{x} ^ top_bits{y}));
      }
    }
  }

  TTS_EQUAL(top_bits<logical>{eve::ignore_none}, ~top_bits<logical>{eve::ignore_all});

  if constexpr( !top_bits<logical>::is_aggregated )
  {
    TTS_EQUAL(0u, (~top_bits<logical>{logical{true}}).storage);
  }
}

template <typename T, typename Test>
void top_bits_interesting_cases(Test test)
{
  using logical = eve::logical<T>;

  logical x(false);

  for (int i = 0; i != logical::static_size; ++i) {
    x.set(i, true);
    test(x);

    for (int j = i + 1; j < logical::static_size; ++j) {
      x.set(j, true);
      test(x);
      x.set(j, false);
    }

    x.set(i, false);
  }
}

TTS_CASE_TPL("to_logical", TOP_BITS_EVE_TYPE)
{
    top_bits_interesting_cases<T>([&](auto x) {
      top_bits mmask {x};
      TTS_EQUAL(x, eve::detail::to_logical(mmask));
    });
}

TTS_CASE_TPL("top_bits from ignore", TOP_BITS_EVE_TYPE)
{
  using logical = eve::logical<T>;

  // ignore all
  {
    top_bits<logical> mmask(eve::ignore_all);
    TTS_EQUAL(logical(false), eve::detail::to_logical(mmask));
  }

  // ignore none
  {
    top_bits<logical> mmask(eve::ignore_none);
    TTS_EQUAL(logical(true), eve::detail::to_logical(mmask));
  }

  // ignore_extrema_ / keep_between
  {
    for (int i = 0; i < logical::static_size + 1; ++i)
    {
      for (int j = logical::static_size - i; j ; --j)
      {
        logical expected([&](int k, int) { return (k >= i) && (logical::static_size - k) > j; });
        top_bits<logical> actual(eve::ignore_extrema_(i, j));
        TTS_EQUAL(expected, eve::detail::to_logical(actual));

        actual = top_bits<logical>(eve::keep_between(i, logical::static_size - j));
        TTS_EQUAL(expected, eve::detail::to_logical(actual));
      }
    }
  }

  // ignore first / keep_last
  {
    for (int i = 0; i < logical::static_size + 1; ++i)
    {
      logical expected([&](int j, int) { return j >= i; });
      top_bits<logical> actual(eve::ignore_first(i));
      TTS_EQUAL(expected, eve::detail::to_logical(actual));

      actual = top_bits<logical>(eve::keep_last(logical::static_size - i));
      TTS_EQUAL(expected, eve::detail::to_logical(actual));
    }
  }

  // ignore last / keep_first
  {
    for (int i = 0; i < logical::static_size + 1; ++i)
    {
      logical expected([&](int j, int) { return (logical::static_size - j) > i; });
      top_bits<logical> actual(eve::ignore_last(i));
      TTS_EQUAL(expected, eve::detail::to_logical(actual));

      actual = top_bits<logical>(eve::keep_first(logical::static_size - i));
      TTS_EQUAL(expected, eve::detail::to_logical(actual));
    }
  }
}

TTS_CASE_TPL("top_bits from logical + ignore", TOP_BITS_EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical expected(true);

  top_bits actual(expected, eve::ignore_first(1));

  expected.set(0, false);

  TTS_EQUAL(expected, eve::detail::to_logical(actual));
}

TTS_CASE_TPL("top_bits all", TOP_BITS_EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical x(true);

  TTS_EXPECT(eve::detail::all(top_bits(x)));

  for (int i = 0; i != x.static_size; ++i)
  {
    x.set(i, false);
    TTS_EXPECT_NOT(eve::detail::all(top_bits(x)));
    x.set(i, true);
  }
}

TTS_CASE_TPL("top_bits any", TOP_BITS_EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical x(false);

  TTS_EXPECT_NOT(eve::detail::any(top_bits(x)));

  for (int i = 0; i != x.static_size; ++i)
  {
    x.set(i, true);
    TTS_EXPECT(eve::detail::any(top_bits(x)));
    x.set(i, false);
  }
}

TTS_CASE_TPL("top_bits first_true", TOP_BITS_EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical x(true);

  TTS_EQUAL(0, eve::detail::first_true(top_bits(x)));

  for (int i = 0; i != x.static_size - 1; ++i)
  {
    x.set(i, false);

    std::optional res = eve::detail::first_true(top_bits(x));

    TTS_EXPECT(res);

    int expected = i + 1;
    TTS_EQUAL(expected, *res);
  }

  x = false;

  TTS_EXPECT_NOT(eve::detail::first_true(top_bits(x)));
}

TTS_CASE_TPL("top_bits count_true", TOP_BITS_EVE_TYPE)
{
  top_bits_interesting_cases<T>([&](auto x) {
    std::ptrdiff_t expected = 0;
    for (int i = 0; i != x.static_size; ++i) expected += x.get(i);

    top_bits mmask{x};
    TTS_EQUAL(expected, eve::detail::count_true(mmask));
  });
}
