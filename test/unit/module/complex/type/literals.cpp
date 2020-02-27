//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <eve/wide.hpp>
#include <eve/literals.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Generate a complex using double literals")
{
  using namespace eve::literal;

  eve::complex<eve::wide<float>> z = eve::wide<float>{3.f} + 1._if;
  std::cout << z.real << " + " << z.imag << "i" << std::endl;
}
