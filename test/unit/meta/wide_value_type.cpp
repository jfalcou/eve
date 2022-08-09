//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/traits/wide_value_type.hpp>

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

TTS_CASE( "Check for wide_value_type")
{
  using half_aligned  = eve::aligned_ptr<int, eve::fixed<eve::expected_cardinal_v<int> / 2>>;
  using twice_aligned = eve::aligned_ptr<int, eve::fixed<eve::expected_cardinal_v<int> * 2>>;

  TTS_TYPE_IS(eve::wide_value_type_t<int*>,                       eve::wide<int>);
  TTS_TYPE_IS(eve::wide_value_type_t<int const*>,                 eve::wide<int>);
  TTS_TYPE_IS(eve::wide_value_type_t<half_aligned>,               eve::wide<int>);
  TTS_TYPE_IS(eve::wide_value_type_t<twice_aligned>,              eve::wide<int>);
  TTS_TYPE_IS(eve::wide_value_type_t<std::vector<int>::iterator>, eve::wide<int>);
  TTS_TYPE_IS(eve::wide_value_type_t<no_iterator_cardinal>,       eve::wide<int>);
  TTS_TYPE_IS(eve::wide_value_type_t<has_iterator_cardinal>,      (eve::wide<int, eve::fixed<2>>));
  TTS_TYPE_IS(eve::wide_value_type_t<eve::logical<int>*>,         (eve::logical<eve::wide<int>>));

};
