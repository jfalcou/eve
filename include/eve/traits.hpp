//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup simd_types
//! @{
//! @defgroup traits Type traits
//! @brief  Type traits for SIMD related types and functions
//!
//! Using **EVE** types and functions may require informations about some properties of the processed
//! types that are accessible through the following traits.
//!
//! **Convenience header:** @code{.cpp} #include <eve/traits.hpp> @endcode
//! @}
//==================================================================================================
#include <eve/traits/alignment.hpp>
#include <eve/traits/as_arithmetic.hpp>
#include <eve/traits/as_floating_point.hpp>
#include <eve/traits/as_integer.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/traits/common_compatible.hpp>
#include <eve/traits/common_type.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/traits/iterator_cardinal.hpp>
#include <eve/traits/max_scalar_size.hpp>
#include <eve/traits/value_type.hpp>
#include <eve/traits/wide_value_type.hpp>
