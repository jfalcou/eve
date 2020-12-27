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
  else if constexpr (!ABI::is_wide_logical) expect_same(storage_type{}, typename logical::storage_type{});
  else                                      expect_same(storage_type{}, std::uint32_t{});
}

TTS_CASE_TPL("Check top bits movemask", EVE_TYPE)
{
  using logical = eve::logical<T>;

  logical test(false);

  for (std::ptrdiff_t i = 0; i != test.static_size; ++i)
  {
    test.set(i, true);
    top_bits<logical> mmask = eve::detail::movemask(test);

    for (std::ptrdiff_t j = 0; j != test.static_size; ++j)
    {
      TTS_EQUAL(test[j], mmask.get(j));
    }

    test.set(i, false);
  }
}

#endif  // defined(SPY_ARCH_IS_AMD64) && !defined(EVE_NO_SIMD)
