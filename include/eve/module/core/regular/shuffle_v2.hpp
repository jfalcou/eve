//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>
#if defined(SPY_COMPILER_IS_GCC) || defined(SPY_COMPILER_IS_CLANG)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#endif

//TODO DOC here
#include <eve/detail/shuffle_v2/shuffle_v2_fwd.hpp>
#include <eve/detail/shuffle_v2/native_shuffle_lookup.hpp>
#include <eve/detail/shuffle_v2/shuffle_v2_driver.hpp>

#if defined(SPY_COMPILER_IS_GCC) || defined(SPY_COMPILER_IS_CLANG)
#pragma GCC diagnostic pop
#endif
