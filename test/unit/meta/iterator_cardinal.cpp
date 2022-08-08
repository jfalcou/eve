//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/traits/iterator_cardinal.hpp>

#include <eve/memory/aligned_ptr.hpp>

#include <vector>

struct no_iterator_cardinal
{
  using value_type = int;
};

struct has_iterator_cardinal
{
  using value_type = int;

  static constexpr eve::fixed<2> iterator_cardinal() { return {}; }
};

TTS_CASE( "Check for iterator_cardinal")
{
  using half_aligned  = eve::aligned_ptr<int, eve::fixed<eve::expected_cardinal_v<int> / 2>>;
  using twice_aligned = eve::aligned_ptr<int, eve::fixed<eve::expected_cardinal_v<int> * 2>>;

  TTS_TYPE_IS(eve::iterator_cardinal_t<int*>,                       eve::expected_cardinal_t<int>);
  TTS_TYPE_IS(eve::iterator_cardinal_t<int const*>,                 eve::expected_cardinal_t<int>);
  TTS_TYPE_IS(eve::iterator_cardinal_t<half_aligned>,               eve::expected_cardinal_t<int>);
  TTS_TYPE_IS(eve::iterator_cardinal_t<twice_aligned>,              eve::expected_cardinal_t<int>);
  TTS_TYPE_IS(eve::iterator_cardinal_t<std::vector<int>::iterator>, eve::expected_cardinal_t<int>);
  TTS_TYPE_IS(eve::iterator_cardinal_t<no_iterator_cardinal>,       eve::expected_cardinal_t<int>);
  TTS_TYPE_IS(eve::iterator_cardinal_t<has_iterator_cardinal>,      eve::fixed<2>);
};
