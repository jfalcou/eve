//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
// The benchmark in main.cpp says how fast the SIMD filter is. This says it computes the same thing
// as the scalar one - on every architecture we emulate.
//==================================================================================================
#include "bilateral.hpp"

#include <cmath>
#include <random>
#include <vector>

#include "test.hpp"

TTS_CASE("Bilateral filter, SIMD against scalar")
{
  auto size = ::tts::arguments().value(512, "--size");

  std::vector<float> input(size);
  std::vector<float> out_scalar(size, 0.0f);
  std::vector<float> out_eve(size, 0.0f);
  std::vector<float> out_raw(size, 0.0f);

  std::mt19937                          gen(42);
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);
  for(float& f : input) f = dist(gen);

  bilateral::filter_scalar(input, out_scalar, [](float x) { return std::exp(x); });
  bilateral::filter_simd  (input, out_eve   , eve::exp                          );
  bilateral::filter_simd  (input, out_raw   , eve::exp[eve::raw]                );

  TTS_ALL_ULP_EQUAL(out_scalar, out_eve, 3);
  TTS_ALL_RELATIVE_EQUAL(out_scalar, out_raw, 1.0);
};
