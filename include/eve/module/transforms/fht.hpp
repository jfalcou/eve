//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup transforms
//! @{
//!   @defgroup fht fast hartley discrete transform
//!   @brief Hartley transform
//!
//!   This module provides some implementation of the Hartley discrete real and complex transforms
//!
//!   **Required header:** @code{.cpp} #include <eve/module/fht.hpp> @endcode
//! @}
//==================================================================================================
#include <eve/module/transforms/fht/naive_ht.hpp>
#include <eve/module/transforms/fht/small_df_fht.hpp>
#include <eve/module/transforms/fht/small_dt_fht.hpp>
#include <eve/module/transforms/fht/large_df_fht.hpp>
#include <eve/module/transforms/fht/large_dt_fht.hpp>
