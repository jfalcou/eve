//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

//================================================================================================
//! @defgroup arithmetic Arithmetic functions
//!
//! These functions provide scalar and SIMD version of basic arithmetic functions.
//!
//! To keep the results homogeneous and coherent between SIMD and scalar mode, the types usable
//! in those functions are required to satisfy `eve::compatible_values`
//!
//! **Convenience header:** @code{.cpp} #include <eve/function/arithmetic.hpp> @endcode
//!
//================================================================================================
#include <eve/function/abs.hpp>
#include <eve/function/arg.hpp>
#include <eve/function/average.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/cbrt.hpp>
#include <eve/function/clamp.hpp>
#include <eve/function/conj.hpp>
#include <eve/function/copysign.hpp>
#include <eve/function/dist.hpp>
#include <eve/function/fdim.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/fnms.hpp>
#include <eve/function/frac.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/manhattan.hpp>
#include <eve/function/max.hpp>
#include <eve/function/maxmag.hpp>
#include <eve/function/min.hpp>
#include <eve/function/minmag.hpp>
#include <eve/function/modf.hpp>
#include <eve/function/negate.hpp>
#include <eve/function/negatenz.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/plus.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/sqr_abs.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
