//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup functions
//! @{
//! @defgroup decorator Decorators
//!
//! Decorators are higher-order functions that modify the behavior of other functions.
//! Every decorators returns a new callable object that will behave as the callable passed as
//! parameters but with different computation scheme (e.g more precision, more speed, etc...).
//!
//! **Convenience header:** @code{.cpp} #include <eve/function/decorator.hpp> @endcode
//! @}
//==================================================================================================

#include <eve/function/numeric.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/roundings.hpp>
