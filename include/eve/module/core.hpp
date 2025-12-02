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
//! [diff_of_prod](@ref eve::diff_of_prod), [safe_scale](@ref eve::safe_scale), [sufp](@ref eve::sufp),
//! [sulp](@ref eve::sulp), [sum_of_prod](@ref eve::sum_of_prod), [three_fma](@ref eve::three_fma),
//! [two_add](@ref eve::two_add), [two_prod](@ref eve::two_prod), [two_sub](@ref eve::two_sub),
//! [veltkamp](@ref eve::veltkamp).
//!
//! @note Many functions can also use a `widen` decorators. This make the whole computation and result
//!       made in the upgraded type if available. Currently types with 64 bits elements cannot be upgraded and
//!       for then  `widen` has no effect.
//!
//! @defgroup core_arithmetic  Arithmetic operations
//! @ingroup core
//! Core arithmetic functions
//!
//! These functions allows performing some basic arithmetics operations and some less basic.
//!
//! [abs](@ref eve::abs), [absmax](@ref eve::absmax), [absmi](@ref eve::absmin),
//! [add](@ref eve::add), [agm](@ref eve::agm), [average](@ref eve::average),
//! [ceil](@ref eve::ceil), [chi](@ref eve::chi), [clamp](@ref eve::clamp),
//! [copysign](@ref eve::copysign), [](@ref eve::), [cosine_similarity_](@ref eve::cosine_similarity_),
//! [covariance](@ref eve::covariance),
//! [dec](@ref eve::dec), [dist](@ref eve::dist), [div](@ref eve::div), [dot](@ref eve::dot),
//! [fdim](@ref eve::fdim)], [floor](@ref eve::floor), [fmod](@ref eve::fmod), [frac](@ref eve::frac),
//! [fracscale](@ref eve:fracscale), [heaviside](@ref eve::heaviside),
//! [inc](@ref eve::inc), [lerp](@ref eve::lerp), [manhattan](@ref eve::manhattan), [max](@ref eve::max),
//! [maxabs](@ref eve::maxabs), [maxmag](@ref eve::maxmag), [min](@ref eve::min),
//! [minabs](@ref eve::minabs), [minmag](@ref eve::minmag), [minmax](@ref eve::minmax), [minus](@ref eve::minus),
//! [modf](@ref eve::modf), [mul](@ref eve::mul), [nearest](@ref eve::nearest), [negabsmax](@ref eve::negabsmax),
//! [negabsmin](@ref eve::negabsmin), [negate](@ref eve::negate),[negatenz](@ref eve::negatenz),
//! [negmaxabs](@ref eve::negmaxabs), [negminabs](@ref eve::negminabs), [oneminus](@ref eve::oneminus),
//! [rat](@ref eve::rat), [rec](@ref eve::rec), [reldist](@ref eve::reldist), [rem](@ref eve::rem),
//! [remainder](@ref eve::remainder), [round](@ref eve::round), [roundscale](@ref eve::roundscale)],
//! [rsqrt](@ref eve::rsqrt), [saturate](@ref eve::saturate), [sign](@ref eve::sign), [sign_alternate](@ref eve::sign_alternate)
//! [signnz](@ref eve::signnz), [sqr](@ref eve::sqr), [sqrt](@ref eve::sqrt), [sub](@ref eve::sub),
//! [sum_of_squares](@ref eve::sum_of_squares),
//! [trunc](@ref eve::trunc), [variance](@ref eve::variance), [welford_average](@ref eve::welford_average),
//! [welford_covariance](@ref eve::welford_covariance), [welford_variance](@ref eve::welford_variance).
//!
//! @defgroup core_bitops Bitwise functions
//! @ingroup core
//! These functions are low level and acting on the bit or byte representation of the involved datas independantly of their type.
//!
//! [bit_and](@ref eve::bit_and), [bit_andnot](@ref eve::bit_andnot), [bit_cast](@ref eve::bit_cast), [bit_ceil](@ref eve::bit_ceil),
//! [bit_flip](@ref eve::bit_flip),[bit_floor](@ref eve::bit_floor),  [bit_mask](@ref eve::bit_mask),
//! [bit_not](@ref eve::bit_not), [bit_notand](@ref eve::bit_notand), [bit_notor](@ref eve::bit_notor), [bit_or](@ref eve::bit_or).
//! [bit_ornot](@ref eve::bit_ornot), [bit_reverse](@ref eve::bit_reverse), [bit_select](@ref eve::bit_select),
//! [bit_set](@ref eve::bit_set), [shl](@ref eve::shl),
//! [bit_shr](@ref eve::bit_shr), [bit_swap_adjacent](@ref eve::bit_swap_adjacent), [bit_swap_pairs](@ref eve::bit_swap_pairs),
//! [bit_ternary](@ref eve::bit_ternary), [bit_unset](@ref eve::bit_unset), [bit_width](@ref eve::bit_width), [bit_xor](@ref eve::bit_xor).
//! [byte_reverse](@ref eve::byte_reverse), [byte_swap_adjacent](@ref eve::byte_swap_adjacent), [byte_swap_pairs](@ref eve::byte_swap_pairs),
//! [countl](@ref eve::countl), [countl_zero](@ref eve::countl_zero), [countr_one](@ref eve::countr_one), [countr_zero](@ref eve::countr_zero).
//!
//! @defgroup core_constants  Constants
//! @ingroup core
//! Basic useful constants (scalar and SIMD)
//!
//! All EVE constants can be called in four ways:
//!    * ct(eve::as<T>())     where T is the wished constant type
//!    * ct(eve::as(t))       where t is an instance of a type T
//!    * ct\[cond\](...)      where cond is a conditional expression.
//!    * `upper`, `lower`      decorators can also been used (see the note  below).
//!
//! Here ct denotes the constant name.
//!
//! When the condition is present and evaluate to false the result element default to zero,
//! but this behavior can be changed if the condition is expressed by an `if_(...).else_(...) clause`.
//!
//! @note For mathematic constants whose value is (perhaps) not exactly represented in the floating point type used,
//!       the regular call provides the value rounded to nearest even, but the semantic modifiyers `upper` and
//!       `lower` can be used to provide values guaranted to be greater or equal (respectively less or equal) to
//!       the real mathematical value. For instance the regular nearest values of \f$\pi\f$ for float and double are
//!       greater (resp. less) than the mathematical value.
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
//!       -  `upper`, `lower`  : when available enforce that the operation will lead to a result that will be guaranted less or
//!                 equal (resp. greater or equal) that the perfect not rounded result. (with nan exception).
//!
//!   * integer roundings :
//!
//!     These decorators can be used with the functions
//!     eve::div, eve::rem, eve::round with floating or integral arguments
//!     to choose the rounding to integer mode
//!
//!     - `to_nearest`: rounding to nearest or even
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
//!           (so in general worse approximation but speedier).
//!
//!      These decorators can be used with the functions
//!      eve::add, eve::average, eve::dec, eve::div, eve::fma,  eve::fms, eve::inc,
//!      eve::mul, eve::oneminus, eve::rec, eve::sqr, eve::sqrt, eve::sub.
//!
//!      Experimentaly eve::add can accept an expansive `to_nearest_odd` decorator.
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
//! the decorated pedantic version of these functions. (or the lower or upper versions, that must guarantee on ordering
//! against the mathematical correct result)
//!
//! Take care that can be very expensive if the proper hardware capabilities are not present.
//!
//! By themselves the regular version of these function acts with mere operators * + and minus if the intrinsics are not at hand
//! and if there is no possibility of  maping the std implementation
//!
//! [fam](@ref eve::fam), [fanm](@ref eve::fanm), [fma](@ref eve::fma), [fms](@ref eve::fms), [fnma](@ref eve::fnma),
//! [fnms](@ref eve::fnms)[fsm](@ref eve::fsm), [fsnm](@ref eve::fsnm).
//!
//!  @defgroup core_reduction  Reductions
//!  @ingroup core
//!  Operations providing a scalar value from SIMD vectors
//!
//! @defgroup core_internal  IEEE operations
//! @ingroup core
//! Operations related to classical IEEE functions and the floating representation of real numbers
//!
//! most of the standard function are present,  but their names and calls can slightly change.
//!
//!  * [ifrexp](@ref eve::ifrexp) and  [frexp](@ref eve::frexp) are similar to `std:frexp`,  but return a kumi::tuple of two values mantissa and exponent.
//!        For [ifrexp](@ref eve::ifrexp) the exponent is and integral value,  but for [frexp](@ref eve::frexp) it is a floating value.
//!  *  [mantissa](@ref eve::mantissa) and  [exponent](@ref eve::exponent) also exists individually but **TAKE CARE** they are not equal to
//!     the pair returned by `ifrexp`
//!  * [nextafter](@ref eve::nextafter) comes along  [next](@ref eve::next) and  [prev](@ref eve::prev) that can take a second scalar integral parameter say `n`
//!    which indicates one want the nth representable value that follows (resp. precedes) the first parameter.
//!
//! @defgroup core_logical  Logical operations
//! @ingroup core
//! Logical operations
//!
//! [swap_if](@ref eve::swap_if), [logical_and](@ref eve::logical_and), [logical_andnot](@ref eve::logical_andnot),
//! [logical_not](@ref eve::logical_not), [logical_notand](@ref eve::logical_notand), [logical_notor](@ref eve::logical_notor),
//! [logical_or](@ref eve::logical_or). [logical_ornot](@ref eve::logical_ornot),
//! [logical_select](@ref eve::logical_select), [replace_ignored](@ref eve::replace_ignored).
//!
//! @defgroup core_predicates  Predicates
//! @ingroup core
//! Operations returning logical values
//!
//! Mind that in SIMD context these functions DO NOT return boolean but logical values that is
//! an internal representation of a vector of truth values that can be handled by the function of
//! the previous section logical operations).
//!
//! The set of functions is quite exhaustive. Peculiarly all comparison are treated with their negations and decorations as
//! sometime architectures provide specific intrinsics and also because floating Nan values must be taken into
//! account more easily.
//!
//! *  With [numeric](@ref eve::numeric) decorator, Nan never wins against a definite value in a comparison.
//! *  [pedantic](@ref eve::pedantic) try to mimic the corresponding standard function behaviour.
//! *  [almost](@ref eve::almost) and [definitely](@ref eve::almost) allow a fuzzy treatment of comparisons.
//!
//! Supplementary comparisons functions take the bit of sign of zero into account,  namely
//! [is_eqpz](@ref eve::is_eqpz), [is_eqmz](@ref eve::is_eqmz), [is_negative](@ref eve::is_negative), [is_positive](@ref eve::is_positive)
//!
//! @defgroup core_conversions Conversions
//! @ingroup core
//! Type conversions
//!
//! [convert](@ref eve::convert), [simd_cast](@ref eve::simd_cast),
//!
//! * conversion functions take two arguments a value and a scalar type to convert each lane of the value (the value itself, if it is scalar value)
//! * The conversion can use the decorator  [eve::saturated](@ref eve::saturated) in which case (sic) the result is saturated in the target type.
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
