//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/concept/vectorized.hpp>

//==================================================================================================
//! @addtogroup utility
//! @{
//! @defgroup struct Structured Types Management
//!
//! **EVE** provides various elements to simplify the management of user-defined structures
//! as vectorized types.
//!
//! **Convenience header:** @code{.cpp} #include <eve/product_type.hpp> @endcode
//!
//! @}
//==================================================================================================

namespace eve
{
  // Reinject kumi concept & traits in EVE
  using kumi::product_type;
  using kumi::is_product_type;
}
