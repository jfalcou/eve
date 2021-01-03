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

#if defined(SPY_ARCH_IS_AMD64) && !defined(EVE_NO_SIMD)

#include <eve/detail/top_bits.hpp>

#include <array>

using eve::detail::top_bits;

template <typename T, std::size_t N>
void expect_array(const std::array<T, N>&) {}

template <typename T>
void expect_same(T, T) {}


TTS_CASE_TPL("Check top bits raw type", EVE_TYPE)
{
  using logical = eve::logical<T>;
  using storage_type = typename top_bits<logical>::storage_type;
  using ABI = typename logical::abi_type;

       if constexpr (eve::has_aggregated_abi_v<logical>) expect_array(storage_type{});
  else if constexpr (!ABI::is_wide_logical)              expect_same(storage_type{}, typename logical::storage_type{});
  else if constexpr (std::same_as<ABI, eve::x86_128_>)   expect_same(storage_type{}, std::uint16_t{});
  else                                                   expect_same(storage_type{}, std::uint32_t{});
}

TTS_CASE_TPL("Check top bits from logical", EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical test(false);

  for (std::ptrdiff_t i = 0; i != test.static_size; ++i)
  {
    test.set(i, true);
    top_bits mmask {test};

    for (std::ptrdiff_t j = 0; j != test.static_size; ++j)
    {
      TTS_EQUAL(test[j], mmask.get(j));
    }

    test.set(i, false);
  }
}

TTS_CASE_TPL("Top bits are little endian", EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical test(false);
  test.set(0, true);

  if constexpr( eve::has_native_abi_v<logical> )
  {
    TTS_EXPECT((top_bits{test}.storage & 1u));
  }
}


TTS_CASE_TPL("bit operations", EVE_TYPE)
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

      TTS_EQUAL(top_bits{!x}, ~top_bits(x));

      // xor
      {
        auto expected = eve::is_nez(x.mask() ^ y.mask());
        TTS_EQUAL(top_bits{expected}, (top_bits{x} ^ top_bits{y}));
      }
    }
  }

  TTS_EQUAL(top_bits<logical>{eve::ignore_none}, ~top_bits<logical>{eve::ignore_all});

  if constexpr( eve::has_native_abi_v<logical> )
  {
    TTS_EQUAL(0, (~top_bits{logical{true}}).storage);
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

TTS_CASE_TPL("spread top bits", EVE_TYPE)
{
  if constexpr ((sizeof(typename T::value_type) != 2)) {
    top_bits_interesting_cases<T>([&](auto x){
      top_bits mmask{x};
      TTS_EQUAL(x, eve::detail::spread(mmask));
    });
  }
}


#endif  // defined(SPY_ARCH_IS_AMD64) && !defined(EVE_NO_SIMD)
