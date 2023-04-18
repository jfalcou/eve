//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup simd
//! @{
//!   @defgroup fft fast fourier transform
//!   @brief fourier transform
//!
//!   This module provides some implementation ofthe fourier transform
//!
//!   **Required header:** @code{.cpp} #include <eve/module/fft.hpp> @endcode
//! @}
//==================================================================================================

#include <eve/module/fft/detail/combined_ops.hpp>
#include <eve/module/fft/utils.hpp>
#include <eve/module/fft/regular/naive_fft.hpp>
#include <eve/module/fft/regular/fft_df_dif2.hpp>
#include <eve/module/fft/regular/fft_df_dit2.hpp>
#include <eve/module/fft/regular/fft_usual_dif2.hpp>
#include <eve/module/fft/regular/fft_usual_dit2.hpp>
#include <eve/module/fft/regular/fft_no_dif4.hpp>
#include <eve/module/fft/regular/fft_dif4.hpp>
#include <eve/module/fft/regular/fft_dit4.hpp>
#include <eve/module/fft/regular/fft_split.hpp>


// #include <eve/module/fft/regular/fft_000.hpp>
