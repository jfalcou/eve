//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#define TTS_MAIN
#define TTS_CUSTOM_DRIVER_FUNCTION eve_entry_point
#include <tts/tts.hpp>
#include <random>
#include "measures.hpp"
#include "generator.hpp"

int main(int argc, char const **argv)
{
  std::cout << "[EVE] - Target: "
            << ::tts::cyan() << ::tts::typename_<EVE_CURRENT_API> << ::tts::reset()
            << " - Assertions: ";

#ifdef NDEBUG
  std::cout << ::tts::red() << "Disabled" << ::tts::reset() << " - ";;
#else
  std::cout << ::tts::green() << "Enabled" << ::tts::reset() << "  - ";
#endif

  ::tts::options parser{argc,argv};
  std::mt19937::result_type seed(18102008);
  seed = parser.value_or(seed, "-s", "--seed");

  std::cout << "PRNG Seed: " << ::tts::cyan() << seed << ::tts::reset() << std::endl;

  eve_entry_point(argc, argv);
  return tts::report(0,0);
}
