//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
// **=======================================================

//================================================================================================
//! @addtogroup functions
//! @{
//! @defgroup operators Operators
//!
//! These functions provide scalar and SIMD version of operators functions.
//! In general these functions are not needed for direct call but can be used if the parameters are
//! scalar as the operator will be the original **C++** one and could lead to unexpected promotions.
//! Moreover they are mandatory if the operator has to be decorated (saturated(add)` is an example).
//!
//! **Convenience header:** @code{.cpp} #include <eve/function/operator.hpp> @endcode
//!
//!@}
//================================================================================================

#include <eve/function/add.hpp>
#include <eve/function/plus.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/div.hpp>
#include <eve/function/rem.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/rshl.hpp>
#include <eve/function/rshr.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/shr.hpp>
