//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/vectorized.hpp>

namespace eve {

  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief The cheapest to get bitset for simd logical.
  //!
  //! One value in top bits can be represented by multiple bits (bits_per_element member constant).
  //!
  //! NOTE: this is a generalization of `movemask` instructions from x86
  //!
  //! Typical usage: created with CTAD: `top_bits{logical}`.
  //!
  //! @tparam Logical simd value.
  //================================================================================================
  template <logical_simd_value Logical>
  struct top_bits;
}

#include <eve/arch/cpu/top_bits.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/arch/x86/top_bits.hpp>
#endif
