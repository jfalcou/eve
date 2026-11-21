//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//==================================================================================================
// The header precompiled for the unit tests: all of test.hpp but its main(), which each test then
// gets from its own #include "test.hpp".
//
// A precompiled header made with clang-cl's /Yc puts the definitions it contains in its object, which
// CMake links into every test reusing it, but every test still emits them too. cl.exe emits them in
// the former only. main() can't be inline, so it has to stay out of the precompiled header.
//==================================================================================================
#define EVE_TEST_BUILDING_PCH
#include "test.hpp"
#undef EVE_TEST_BUILDING_PCH
