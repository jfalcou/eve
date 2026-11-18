//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/traits/iterator_width.hpp>

#include <eve/memory/aligned_ptr.hpp>

#include <vector>

struct no_iterator_width
{
  using value_type = int;
};

struct has_iterator_width
{
  using value_type = int;

  static constexpr eve::width_type iterator_width() { return 2; }
};

TTS_CASE( "Check for iterator_width")
{
  using half_aligned  = eve::aligned_ptr<int, eve::expected_width_v<int> / 2>;
  using twice_aligned = eve::aligned_ptr<int, eve::expected_width_v<int> * 2>;

  TTS_CONSTEXPR_EQUAL(eve::iterator_width_v<int*>,                        eve::expected_width_v<int>);
  TTS_CONSTEXPR_EQUAL(eve::iterator_width_v<int const*>,                  eve::expected_width_v<int>);
  TTS_CONSTEXPR_EQUAL(eve::iterator_width_v<half_aligned>,                eve::expected_width_v<int>);
  TTS_CONSTEXPR_EQUAL(eve::iterator_width_v<twice_aligned>,               eve::expected_width_v<int>);
  TTS_CONSTEXPR_EQUAL(eve::iterator_width_v<std::vector<int>::iterator>,  eve::expected_width_v<int>);
  TTS_CONSTEXPR_EQUAL(eve::iterator_width_v<no_iterator_width>,           eve::expected_width_v<int>);
  TTS_CONSTEXPR_EQUAL(eve::iterator_width_v<has_iterator_width>,          2);
};
