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
//!   @defgroup transforms
//!   @brief dicrete transforms
//!
//!   This module provides some implementations of transform algorithms,
//!   The most well known being fast fourier transform.
//!
//!   Providing data to the algorithms
//!
//!   Input Datas are supposed to be contiguous ranges of real or complex floating values.
//!
//!     - Real values datas must simply satisfy the eve relaxed_range concept
//!     - Complex datas can be passed in three forms
//!        - Two real datas ranges providing real (resp. imaginary) parts of the inputs.
//!        - eve::algo::soa_vector of complex (roughly the same thing as the previous one in encapsulated form).
//!        - ordinary range of "scalar" eve::complex (aos rang of complex).
//!
//!   Output data of the algorithms
//!
//!   No permanent storage is claimed inside the algorithms!
//!
//!   In place algorithm are provided if the output is storage compatible with the output
//!   For instance real datas support in place fht but not in place fft whose results are complex.
//!
//!   Out of place algorithm must pass their output storage during the call
//!
//!   Transforms implemented
//!
//!   - discrete Fourier transform
//!   - discrete Hartley transform
//!
//!   Caveat
//!
//!   - Up to now fft and fht are provided for range having a power of 2 length.
//!
//!   **Required header:** @code{.cpp} #include <eve/module/transforms.hpp> @endcode
//! @}
//==================================================================================================

#include <eve/module/transforms/detail/pr.hpp>
#include <eve/module/transforms/detail/combined_ops.hpp>
#include <eve/module/transforms/utils.hpp>
#include <eve/module/transforms/permute.hpp>
#include <eve/module/transforms/fft.hpp>
#include <eve/module/transforms/fht.hpp>
// #include <eve/module/transforms/regular/naive_transforms.hpp>
// #include <eve/module/transforms/regular/transforms_df_dif2.hpp>
// #include <eve/module/transforms/regular/transforms_df_dit2.hpp>
// #include <eve/module/transforms/regular/transforms_usual_dif2.hpp>
// #include <eve/module/transforms/regular/transforms_usual_dit2.hpp>
// #include <eve/module/transforms/regular/transforms_no_dif4.hpp>
// #include <eve/module/transforms/regular/transforms_dif4.hpp>
// #include <eve/module/transforms/regular/transforms_dit4.hpp>
// #include <eve/module/transforms/regular/transforms_split.hpp>


// #include <eve/module/transforms/regular/transforms_000.hpp>
