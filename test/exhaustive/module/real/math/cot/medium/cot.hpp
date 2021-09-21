//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on cot", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto std_cot = tts::vectorize<T>( [](auto e) { return 1/std::tan(double(e)); } );
  auto l = eve::detail::Rempio2_limit(eve::medium_type(), eve::as<v_t>());

  if constexpr(eve::platform::supports_denormals)
  {
    eve::exhaustive_producer<T>  p(-l, l);
    TTS_RANGE_CHECK(p, std_cot, eve::medium(eve::cot));
  }
  else
  {
    eve::exhaustive_producer<T>  p(eve::smallestposval(eve::as<v_t>()), l);
    TTS_RANGE_CHECK(p, std_cot, eve::medium(eve::cot));
  }
}
