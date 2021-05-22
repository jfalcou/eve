//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/detail/top_bits.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/all.hpp>
#include <array>

using eve::detail::top_bits;

template <typename T, typename Test> void test_over_top_bits(Test test)
{
  using logical = eve::logical<T>;
  logical x(false);

  for (int i = 0; i != logical::size(); ++i)
  {
    x.set(i, true);
    test(x);

    for (int j = i + 1; j < logical::size(); ++j)
    {
      x.set(j, true);
      test(x);
      x.set(j, false);
    }

    x.set(i, false);
  }
}

template <typename T, std::size_t N> bool expect_array(const std::array<T, N>&) { return true; }

//==================================================================================================
// Check the raw type of top_bits' storage
//==================================================================================================
EVE_TEST_TYPES( "Check top bits raw type", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using v_t         = eve::element_type_t<T>;
  using logical     = eve::logical<T>;
  using tb_storage  = typename top_bits<logical>::storage_type;
  using ABI         = typename logical::abi_type;

       if constexpr (eve::has_aggregated_abi_v<logical>) TTS_EXPECT(expect_array(tb_storage{}));
  else if constexpr (!ABI::is_wide_logical)              TTS_TYPE_IS(tb_storage, typename logical::storage_type);
  else if constexpr (std::same_as<ABI, eve::x86_128_>)   TTS_TYPE_IS(tb_storage, std::uint16_t);
  else if constexpr (std::same_as<ABI, eve::x86_256_>)   TTS_TYPE_IS(tb_storage, std::uint32_t);
  else if constexpr (eve::arm_abi<ABI>)
  {
         if constexpr(T::size() == 1)                      TTS_TYPE_IS(tb_storage, std::uint8_t);
    else if constexpr(T::size() == 2 && sizeof(v_t) == 1)  TTS_TYPE_IS(tb_storage, std::uint16_t);
    else if constexpr(T::size() * sizeof(v_t) == 4)        TTS_TYPE_IS(tb_storage, std::uint32_t);
    else if constexpr(eve::current_api == eve::asimd)           TTS_TYPE_IS(tb_storage, std::uint64_t);
    else if constexpr(T::size() == 16 && sizeof(v_t) == 1) TTS_TYPE_IS(tb_storage, std::uint64_t);
    else                                                        TTS_TYPE_IS(tb_storage, std::uint32_t);
  }
  else
  {
    if constexpr (logical::size() < 64)  TTS_TYPE_IS(tb_storage, std::uint32_t);
    else                                      TTS_EXPECT(expect_array(tb_storage{}));
  }
};

//==================================================================================================
// Check the raw type of top_bits' storage
//==================================================================================================
EVE_TEST_TYPES("Check top bits from logical", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using logical = eve::logical<T>;
  logical test(false);

  for (std::ptrdiff_t i = 0; i != test.::size(); ++i)
  {
    test.set(i, true);

    top_bits mmask {test};
    for (std::ptrdiff_t j = 0; j != test.::size(); ++j)  TTS_EQUAL(test.get(j), mmask.get(j));

    test.set(i, false);
  }
};

EVE_TEST_TYPES("Check top bits from logical+ignore", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using logical = eve::logical<T>;
  logical expected(true);
  top_bits actual(expected, eve::ignore_first(1));
  expected.set(0, false);
  TTS_EQUAL(expected, eve::detail::to_logical(actual));
};

EVE_TEST_TYPES("Check top bits to_logical", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  test_over_top_bits<T>([&](auto x)
  {
    top_bits mmask {x};
    TTS_EQUAL(x, eve::detail::to_logical(mmask));
  });
};

//==================================================================================================
// Check the raw type of top_bits' storage
//==================================================================================================
EVE_TEST_TYPES( "Check top_bits::set", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using logical = eve::logical<T>;

  logical           expected(false);
  top_bits<logical> actual(eve::ignore_all);

  for (std::ptrdiff_t i = 0; i != expected.::size(); ++i)
  {
    expected.set(i, true);
    actual.set(i, true);

    TTS_EQUAL(expected, eve::detail::to_logical(actual));
  }

  for (std::ptrdiff_t i = 0; i != expected.::size(); ++i)
  {
    expected.set(i, false);
    actual.set(i, false);
    TTS_EQUAL(expected, eve::detail::to_logical(actual));
  }
};

//==================================================================================================
// Check the raw type of top_bits' storage
//==================================================================================================
EVE_TEST_TYPES("Check top_bits endianess", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
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
};

//==================================================================================================
// Check the behavior of top_bits all()/any()
//==================================================================================================
EVE_TEST_TYPES("Check all(top_bits)", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using logical = eve::logical<T>;

  logical x(true);

  TTS_EXPECT(eve::detail::all(top_bits(x)));

  for (int i = 0; i != x.::size(); ++i)
  {
    x.set(i, false);
    TTS_EXPECT_NOT(eve::detail::all(top_bits(x)));
    x.set(i, true);
  }
};

EVE_TEST_TYPES("Check any(top_bits)", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using logical = eve::logical<T>;

  logical x(false);

  TTS_EXPECT_NOT(eve::detail::any(top_bits(x)));

  for (int i = 0; i != x.::size(); ++i)
  {
    x.set(i, true);
    TTS_EXPECT(eve::detail::any(top_bits(x)));
    x.set(i, false);
  }
};

//==================================================================================================
// Check the behavior of top_bits first_true/count_true
//==================================================================================================
EVE_TEST_TYPES("Check first_true(top_bits)", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  using logical = eve::logical<T>;
  logical x(true);

  TTS_EQUAL(0, eve::detail::first_true(top_bits(x)));

  for (int i = 0; i != x.::size() - 1; ++i)
  {
    x.set(i, false);

    std::optional res = eve::detail::first_true(top_bits(x));

    TTS_EXPECT(res);

    int expected = i + 1;
    TTS_EQUAL(expected, *res);
  }

  x = false;

  TTS_EXPECT_NOT(eve::detail::first_true(top_bits(x)));
};

EVE_TEST_TYPES("Check count_true(top_bits)", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
{
  test_over_top_bits<T>([&](auto x) {
    std::ptrdiff_t expected = 0;
    for (int i = 0; i != x.::size(); ++i) expected += x.get(i);

    top_bits mmask{x};
    TTS_EQUAL(expected, eve::detail::count_true(mmask));
  });
};

//==================================================================================================
// Check the behavior of top_bits over ignore masks
//==================================================================================================
EVE_TEST_TYPES("Check top_bits from ignore_*", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
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

  // ignore_extrema / keep_between
  {
    for (int i = 0; i < logical::size() + 1; ++i)
    {
      for (int j = logical::size() - i; j ; --j)
      {
        logical expected([&](int k, int) { return (k >= i) && (logical::size() - k) > j; });
        top_bits<logical> actual(eve::ignore_extrema(i, j));
        TTS_EQUAL(expected, eve::detail::to_logical(actual));

        actual = top_bits<logical>(eve::keep_between(i, logical::size() - j));
        TTS_EQUAL(expected, eve::detail::to_logical(actual));
      }
    }
  }

  // ignore first / keep_last
  {
    for (int i = 0; i < logical::size() + 1; ++i)
    {
      logical expected([&](int j, int) { return j >= i; });
      top_bits<logical> actual(eve::ignore_first{i});
      TTS_EQUAL(expected, eve::detail::to_logical(actual));

      actual = top_bits<logical>(eve::keep_last(logical::size() - i));
      TTS_EQUAL(expected, eve::detail::to_logical(actual));
    }
  }

  // ignore last / keep_first
  {
    for (int i = 0; i < logical::size() + 1; ++i)
    {
      logical expected([&](int j, int) { return (logical::size() - j) > i; });
      top_bits<logical> actual(eve::ignore_last{i});
      TTS_EQUAL(expected, eve::detail::to_logical(actual));

      actual = top_bits<logical>(eve::keep_first(logical::size() - i));
      TTS_EQUAL(expected, eve::detail::to_logical(actual));
    }
  }
};

//==================================================================================================
// Check the behavior of top_bits bitwise operators
//==================================================================================================
EVE_TEST_TYPES("Check top_bits bitwise operators", eve::test::simd::all_types)
<typename T>(eve::as_<T>)
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
      TTS_EQUAL(top_bits{x != y}, (top_bits{x} ^ top_bits{y}));

      TTS_EQUAL(top_bits{!x}, ~top_bits<logical>(x));
    }
  }

  TTS_EQUAL(top_bits<logical>{eve::ignore_none}, ~top_bits<logical>{eve::ignore_all});

  if constexpr( !top_bits<logical>::is_aggregated )
  {
    TTS_EQUAL(0u, (~top_bits<logical>{logical{true}}).storage);
  }
};
