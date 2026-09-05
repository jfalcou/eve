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

  static constexpr eve::fixed<2> iterator_width() { return {}; }
};

TTS_CASE( "Check for iterator_width")
{
  using half_aligned  = eve::aligned_ptr<int, eve::expected_width_v<int> / 2>;
  using twice_aligned = eve::aligned_ptr<int, eve::expected_width_v<int> * 2>;

  TTS_TYPE_IS(eve::iterator_width_t<int*>,                       eve::expected_width_t<int>);
  TTS_TYPE_IS(eve::iterator_width_t<int const*>,                 eve::expected_width_t<int>);
  TTS_TYPE_IS(eve::iterator_width_t<half_aligned>,               eve::expected_width_t<int>);
  TTS_TYPE_IS(eve::iterator_width_t<twice_aligned>,              eve::expected_width_t<int>);
  TTS_TYPE_IS(eve::iterator_width_t<std::vector<int>::iterator>, eve::expected_width_t<int>);
  TTS_TYPE_IS(eve::iterator_width_t<no_iterator_width>,       eve::expected_width_t<int>);
  TTS_TYPE_IS(eve::iterator_width_t<has_iterator_width>,      eve::fixed<2>);
};
