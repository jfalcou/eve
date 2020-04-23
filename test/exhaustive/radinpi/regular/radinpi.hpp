//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/invpi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/radinpi.hpp>

#include "measures.hpp"
#include "producers.hpp"
#include <cmath>
#include <tts/tests/range.hpp>

<<<<<<< HEAD:test/exhaustive/radinpi/regular/radinpi.hpp
TTS_CASE("wide random check on radinpi")
{
  auto std_radinpi = tts::vectorize<EVE_TYPE>([](auto e) { return eve::Invpi<EVE_VALUE>() * e; });

  eve::exhaustive_producer<EVE_TYPE> p(eve::Valmin<EVE_VALUE>(), eve::Valmax<EVE_VALUE>());
  TTS_RANGE_CHECK(p, std_radinpi, eve::radinpi);
=======
TTS_CASE_TPL("wide exhaustive check on inpi", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto std_inpi = tts::vectorize<T>( [](auto e) { return eve::Invpi<v_t>()*e; } );

  eve::exhaustive_producer<T> p(eve::Valmin<v_t>(), eve::Valmax<v_t>());
  TTS_RANGE_CHECK(p, std_inpi, eve::inpi);
>>>>>>> 4e3087f65... WIP: Adapt tests for proper dependant type checking for constants:test/exhaustive/inpi/regular/inpi.hpp
}
