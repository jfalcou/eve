//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup functions
//! @{
//! @defgroup core Core functions
//! @brief Core functions
//!
//!  This module provides implementation for various fundamental functions
//!
//! @}
//==================================================================================================
//==================================================================================================
//! @addtogroup core
//! @{
//!
//! @defgroup core_accuracy  Accuracy helpers
//! @ingroup core
//! These functions allows performing some basic arithmetics operations with greater accuracy
//! even when a truly upgraded type is not available.
//!
//! [diff_of_prod](@ref eve::diff_of_prod), [fast_two_add](@ref eve::fast_two_add),
//! [sum_of_prod](@ref eve::sum_of_prod), [three_fma](@ref eve::three_fma), [two_add](@ref eve::two_add),
//! [two_prod](@ref eve::two_prod), .
//!
//! @defgroup core_arithmetic  Arithmetic operations
//! @ingroup core
//! Core arithmetic functions
//!
//! These functions allows performing some basic arithmetics operations with greater accuracy
//! even when and upgraded type is not available.
//!
//! @defgroup core_bitops Bitwise functions
//! @ingroup core
//! These functions are low level and acting on the bit representation of the involved datas.
//!
//! @defgroup core_constants  Constants
//! @ingroup core
//! Basic useful constants (scalar and SIMD)
//!
//! All EVE constants can be called in three ways:
//!    * ct(eve::as<T>())   where T is the wished constant type
//!    * ct(t)              where t is an instance of a type T
//!    * ct\[cond\](...)      where cond is a conditional expression.
//!
//! Here ct denotes the constant name.
//!
//! When the condition is present and evaluate to false the result element default to zero,
//! but this behavior can be changed if the condition is expressed by an `if_(...).else_(...) clause`.
//!
//! @defgroup core_decorators  Decorators
//! @ingroup core
//! Core semantic modifiers
//!
//!  Many core function semantics can be modified using decorator(s). The complete description of their effects can be found in
//!  the proper documentation page of each implied function.
//!
//!  They can be classified in the following way:
//!   * general behaviour
//!       - `raw`: indicates that the operation is performed to gain speed generally at the expanse of some accuracy
//!           or/and proper treament of limting values.
//!
//!           Concerned functions are eve::average, eve::diff_of_prod, eve::exponent, eve::frac, eve::frexp, eve::ifrexp,
//!           eve::mantissa, eve::modf, eve::next, eve::prev, eve::rec, eve::rsqrt, eve::sqrt, eve::sum_of_prod, eve::trunc,
//!       - `numeric` : indicates that the operation will aim to ignore Nans as possible.
//!
//!           Concerned functions are eve::absmax, eve::absmin, eve::is_equal, eve::is_not_equal, eve::max, eve::maxabs,
//!           eve::maxmag, eve::min, eve::minabs, eve::minmag, eve::minmax, eve::negabsmax, eve::negabsmin, eve::negmaxabs,
//!           eve::negminabs,
//!
//!       - `pedantic` : indicates that the operation will aim to follow existing **C++** standard.
//!
//!          Concerned functions are eve::absmax, eve::absmin, eve::diff_of_prod, eve::dist, eve::fam, eve::fanm,
//!          eve::fma, eve::fms, eve::fnma, eve::fnms, eve::frac, eve::frexp, eve::fsm, eve::fsnm, eve::ifrexp, eve::is_flint,
//!          eve::is_negative, eve::is_not_flint, eve::is_not_infinite, eve::is_unit, eve::ldexp, eve::lerp, eve::manhattan, eve::max,
//!          eve::maxabs, eve::maxmag, eve::min, eve::minabs, eve::minmag, eve::minmax, eve::modf, eve::negabsmax,
//!          eve::negabsmin, eve::negmaxabs, eve::negminabs, eve::next, eve::nextafter, eve::prev, eve::rec, eve::reldist,
//!          eve::rsqrt, eve::signnz, eve::sum_of_prod,
//!
//!   * integer roundings :
//!
//!     These decorators can be used with the functions
//!     eve::div, eve::rem, eve::round with floating or integral arguments
//!     to choose the rounding to integer mode
//!
//!     - `to_nearest`: troundint to nearest or even
//!     - `downward`: rounding toward \f$-\infty\f$
//!     - `upward`: rounding toward \f$+\infty\f$
//!     - `toward_zero`: rounding toward zero
//!
//!     All these decorators can be used with the functions eve::div, eve::rem, eve::round.
//!
//!    * floating point roundings;
//!
//!      - `lower`: the computed result of the floating operation is less than the mathematical exact value
//!      - `upper`: the computed result of the floating operation is greater than the mathematical exact value
//!      - `strict`: combined with lower or upper option strict ensures that the inequalities obtained are strict.
//!
//!      These decorators can be used with the functions
//!      eve::add, eve::average, eve::dec, eve::div, eve::fma,  eve::fms, eve::inc,
//!      eve::mul, eve::oneminus, eve::rec, eve::sqr, eve::sqrt, eve::sub.
//!
//!      Also `lower` and `upper` (but not `strict`) can be used with all floating point constants.
//!
//!      Except for average with integral typed inputs these decocators have no impact on integer calls.
//!
//!    * upgraded computations
//!
//!       - `widen`: the result is computed in the upgraded type corresponding to the elements parameters. Presently, this has no effect
//!          on 64 bits types as the upgrade type is the type itself.
//!          If the widen decorator is used,  it is the responsability of the user to use [convert](@ref eve::convert)
//!          if it is  needed to get back to the input type sizes.
//!
//!    * Fuzzy
//!
//!       - `almost`: allows some laxity on the predicate result or the integer rounding direction
//!       - `definitely`: impose some rigidity on the predicate result or the integer rounding direction
//!
//!       these two decorators can be used with the functions eve::ceil,  eve::floor, eve::frac, [eve::modf](@ref eve::modf), eve::trunc,
//!       `almost` with the predicates eve::is_equal, eve::is_greater_equal, eve::is_less_equal, eve::is_not_greater, eve::is_not_less,
//!       `definitely` with the predicates eve::is_not_equal, eve::is_not_greater_equal, ieve::s_not_less_equal, eve::is_greater, eve::is_less,
//!
//!    * saturation
//!
//!       - saturated: the operations are executed with saturation which avoids overflow.
//!
//!       This option can be used with eve::abs, eve::absmax, eve::absmin, eve::add, eve::bit_floor, eve::convert, eve::compare_absolute,
//!       eve::dec, eve::dist,
//!       eve::div, eve::inc, eve::manhattan, eve::maxabs, eve::maxmag, eve::minabs, eve::minmag, eve::minus, eve::mul,
//!       eve::negabsmax, eve::negabsmin, eve::negmaxabs, eve::negminabs, eve::next, eve::oneminus, eve::prev, eve::sqr, eve::sub
//!
//! @defgroup core_fma_family  Fused multiply add family
//! @ingroup core
//! These functions implements accurate versions of the operations
//! \f$\pm x \pm yz\f$ and \f$\pm xy \pm z\f$.
//!
//! The required accuracy is in two directions
//!   1. the computation is done with only one rounding
//!   2. there is no intermediate overflow
//!
//! The implementation of these two properties can always be obtained calling
//! the decorated pedantic version of these functions.
//!
//! Take care that can be very expansive if the proper hardware capabilities are not present.
//!
//! By themselves the regular version of these function acts by maping the std implementation
//! if the intrinsics are not at hand.
//!
//! [fam](@ref eve::fam), [fanm](@ref eve::fanm), [fma](@ref eve::fma), [fms](@ref eve::fms), [fnms](@ref eve::fnms),
//! [fsm](@ref eve::fsm), [fsnm](@ref eve::fsnm).
//!
//!  @defgroup core_reduction  Reductions
//!  @ingroup core
//!  Operations providing a scalar value from SIMD vectors
//!
//! @defgroup core_internal  IEEE operations
//! @ingroup core
//! Operations related to classical IEEE functions and the floating representation of real numbers
//!
//! @defgroup core_logical  Logical operations
//! @ingroup core
//! Logical operations
//!
//! @defgroup core_predicates  Predicates
//! @ingroup core
//! Operations returning logical values
//!
//! Mind that in SIMD context these functions DO NOT return boolean but logical values that is
//! an internal representation of a vector of truth values that can be handled by the function of
//! the previous section (core_logical).
//!
//! @defgroup core_conversions Conversions
//! @ingroup core
//! Type conversions
//!
//! [convert](@ref eve::convert), [simd_cast](@ref eve::simd_cast),
//!
//! @defgroup core_simd SIMD Specific Operations
//! @ingroup core
//! Proper SIMD operations as shuffling, splitting and merging SIMD vectors
//!
//! @defgroup core_named_shuffles Named Shuffles
//! @ingroup core
//! Functions that are just shuffles with a different api.
//!
//! @defgroup core_compress Compress functions
//! @ingroup core
//! Functions that in different way expose `compressing` selected elements
//! together to beginning. This is at the core of `remove_if`, `copy_if` etc.
//! Alternative search keywords: filter, remove, pack
//!
//! @}
//==================================================================================================
#include <eve/module/core/compress/core.hpp>
#include <eve/module/core/constant/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/detail/core.hpp>
#include <eve/module/core/named_shuffles/core.hpp>
#include <eve/module/core/regular/core.hpp>
#include <eve/wide.hpp>
#include <eve/arch/nofs.hpp>
#include <eve/as_element.hpp>
