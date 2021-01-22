//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#define TTS_MAIN
#define TTS_CUSTOM_DRIVER_FUNCTION eve_entry_point
#include <tts/tts.hpp>
#include "measures.hpp"

int main(int argc, char const **argv)
{
  std::cout << "[EVE] - Target: " << ::tts::typename_<EVE_CURRENT_API> << " - Assertions: ";
#ifdef NDEBUG
  std::cout << "Disabled\n";
#else
  std::cout << "Enabled\n";
#endif

  eve_entry_point(argc, argv);
  return tts::report(0,0);
}
