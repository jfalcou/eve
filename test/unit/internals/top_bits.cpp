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
<typename T>(eve::as<T>)
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
<typename T>(eve::as<T>)
{
  using logical = eve::logical<T>;
  for (std::ptrdiff_t i = 0; i != T::size(); ++i)
  {
    logical test = [=](auto e, auto) { return e == i;};
    top_bits mmask {test};
    for (std::ptrdiff_t j = 0; j != T::size(); ++j)  TTS_EQUAL(test.get(j), mmask.get(j));
  }
};

EVE_TEST_TYPES("Check top bits from logical+ignore", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using logical = eve::logical<T>;
  logical expected(true);
  top_bits actual(expected, eve::ignore_first(1));
  expected.set(0, false);
  TTS_EQUAL(expected, eve::detail::to_logical(actual));
};

EVE_TEST_TYPES("Check top bits to_logical", eve::test::simd::all_types)
<typename T>(eve::as<T>)
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
<typename T>(eve::as<T>)
{
  using logical = eve::logical<T>;

  top_bits<logical> actual(eve::ignore_all);

  for (std::ptrdiff_t i = 0; i != T::size(); ++i)
  {
    logical expected = [=](auto e, auto) { return e <= i; };
    actual.set(i, true);

    TTS_EQUAL(expected, eve::detail::to_logical(actual));
  }

  for (std::ptrdiff_t i = 0; i != T::size(); ++i)
  {
    logical expected = [=](auto e, auto) { return e > i; };
    actual.set(i, false);
    TTS_EQUAL(expected, eve::detail::to_logical(actual));
  }
};

//==================================================================================================
// Check the raw type of top_bits' storage
//==================================================================================================
EVE_TEST_TYPES("Check top_bits endianess", eve::test::simd::all_types)
<typename T>(eve::as<T>)
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
<typename T>(eve::as<T>)
{
  using logical = eve::logical<T>;
  TTS_EXPECT(eve::detail::all(top_bits(logical(true))));

  for (int i = 0; i != T::size(); ++i)
  {
    logical v([=](auto e, auto) { return e != i; } );
    TTS_EXPECT_NOT(eve::detail::all(top_bits(v)));
  }
};

//==================================================================================================
// Check the behavior of top_bits over ignore masks
//==================================================================================================
EVE_TEST_TYPES("Check top_bits from ignore_*", eve::test::simd::all_types)
<typename T>(eve::as<T>)
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
<typename T>(eve::as<T>)
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

//==================================================================================================
// Check the behavior of top_bits slicing
//==================================================================================================
EVE_TEST_TYPES("Check top_bits slicing", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using logical = eve::logical<T>;

  if constexpr( T::size() == 1 )
  {
    TTS_PASS("Can't slice 1");
  }
  else
  {
    using half_logical = typename top_bits<logical>::half_logical;

    if constexpr ( eve::current_api == eve::avx2 )
    {
      static_assert(top_bits<half_logical>::bits_per_element == top_bits<logical>::bits_per_element);
    }

    if constexpr (top_bits<half_logical>::bits_per_element != top_bits<logical>::bits_per_element)
    {
      TTS_PASS("FIX-1209: slice top bits");
    }
    else
    {
      for( int i = 0; i != T::size() - 1; ++i )
      {
        logical v([=](auto e, auto) { return e > i; });
        auto [vl, vh] = v.slice();

        top_bits together {v};

        top_bits lo {vl};
        top_bits hi {vh};

        TTS_EQUAL(together, (top_bits<logical> {lo, hi}));
        TTS_EQUAL(together.slice(), (kumi::tuple{lo, hi}));
        TTS_EQUAL(together.slice(eve::lower_), lo);
        TTS_EQUAL(together.slice(eve::upper_), hi);
      }
    }
  }
};
