//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup eve_functions
//! @{
//! @defgroup eve_core Core functions
//! @brief Core functions
//!
//!  This module provides implementation for various fundamental functions
//!
//! @}
//==================================================================================================
//==================================================================================================
//! @addtogroup eve_core
//! @{
//!
//! @defgroup eve_core_accuracy  Accuracy helpers
//! @ingroup eve_core
//! These functions allows performing some basic arithmetic operations with greater accuracy
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
//! @defgroup eve_core_arithmetic  Arithmetic operations
//! @ingroup eve_core
//! Core arithmetic functions
//!
//! These functions allows performing some basic arithmetic operations and some less basic.
//!
//! [abs](@ref eve::abs), [absmax](@ref eve::absmax), [absmin](@ref eve::absmin),
//! [add](@ref eve::add), [agm](@ref eve::agm), [average](@ref eve::average),
//! [ceil](@ref eve::ceil), [chi](@ref eve::chi), [clamp](@ref eve::clamp),
//! [copysign](@ref eve::copysign), [cosine_similarity](@ref eve::cosine_similarity),
//! [covariance](@ref eve::covariance),
//! [dec](@ref eve::dec), [dist](@ref eve::dist), [div](@ref eve::div), [dot](@ref eve::dot),
//! [fdim](@ref eve::fdim), [floor](@ref eve::floor), [fmod](@ref eve::fmod), [frac](@ref eve::frac),
//! [fracscale](@ref eve::fracscale), [heaviside](@ref eve::heaviside),
//! [inc](@ref eve::inc), [lerp](@ref eve::lerp), [manhattan](@ref eve::manhattan), [max](@ref eve::max),
//! [maxabs](@ref eve::maxabs), [maxmag](@ref eve::maxmag), [min](@ref eve::min),
//! [minabs](@ref eve::minabs), [minmag](@ref eve::minmag), [minmax](@ref eve::minmax), [minus](@ref eve::minus),
//! [modf](@ref eve::modf), [mul](@ref eve::mul), [nearest](@ref eve::nearest), [negabsmax](@ref eve::negabsmax),
//! [negabsmin](@ref eve::negabsmin), [negate](@ref eve::negate),[negatenz](@ref eve::negatenz),
//! [negmaxabs](@ref eve::negmaxabs), [negminabs](@ref eve::negminabs), [oneminus](@ref eve::oneminus),
//! [rat](@ref eve::rat), [rec](@ref eve::rec), [reldist](@ref eve::reldist), [rem](@ref eve::rem),
//! [remainder](@ref eve::remainder), [round](@ref eve::round), [roundscale](@ref eve::roundscale),
//! [rsqrt](@ref eve::rsqrt), [saturate](@ref eve::saturate), [sign](@ref eve::sign), [sign_alternate](@ref eve::sign_alternate)
//! [signnz](@ref eve::signnz), [sqr](@ref eve::sqr), [sqrt](@ref eve::sqrt), [sub](@ref eve::sub),
//! [sum_of_squares](@ref eve::sum_of_squares),
//! [trunc](@ref eve::trunc), [variance](@ref eve::variance), [welford_average](@ref eve::welford_average),
//! [welford_covariance](@ref eve::welford_covariance), [welford_variance](@ref eve::welford_variance).
//!
//! @defgroup eve_core_bitops Bitwise functions
//! @ingroup eve_core
//! These functions are low level and acting on the bit or byte representation of the involved data independently of their type.
//!
//! [bit_and](@ref eve::bit_and), [bit_andnot](@ref eve::bit_andnot), [bit_cast](@ref eve::bit_cast), [bit_ceil](@ref eve::bit_ceil),
//! [bit_flip](@ref eve::bit_flip),[bit_floor](@ref eve::bit_floor),  [bit_mask](@ref eve::bit_mask),
//! [bit_not](@ref eve::bit_not), [bit_notand](@ref eve::bit_notand), [bit_notor](@ref eve::bit_notor), [bit_or](@ref eve::bit_or).
//! [bit_ornot](@ref eve::bit_ornot), [bit_reverse](@ref eve::bit_reverse), [bit_select](@ref eve::bit_select),
//! [bit_set](@ref eve::bit_set), [shl](@ref eve::shl),
//! [bit_shr](@ref eve::bit_shr), [bit_swap_adjacent](@ref eve::bit_swap_adjacent), [bit_swap_pairs](@ref eve::bit_swap_pairs),
//! [bit_ternary](@ref eve::bit_ternary), [bit_unset](@ref eve::bit_unset), [bit_width](@ref eve::bit_width), [bit_xor](@ref eve::bit_xor).
//! [byte_reverse](@ref eve::byte_reverse), [byte_swap_adjacent](@ref eve::byte_swap_adjacent), [byte_swap_pairs](@ref eve::byte_swap_pairs),
//! [countl_one](@ref eve::countl_one), [countl_zero](@ref eve::countl_zero), [countr_one](@ref eve::countr_one), [countr_zero](@ref eve::countr_zero).
//!
//! @defgroup eve_core_constants  Constants
//! @ingroup eve_core
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
//!       `lower` can be used to provide values guaranteed to be greater or equal (respectively less or equal) to
//!       the real mathematical value. For instance the regular nearest values of \f$\pi\f$ for float and double are
//!       greater (resp. less) than the mathematical value.
//!
//! @defgroup eve_core_decorators  Decorators
//! @ingroup eve_core
//! Core semantic modifiers
//!
//!  Many core functions accept one or more of these options to change what they compute or how.
//!  Each is documented below; which functions accept which is stated on the page of every
//!  function that does.
//!
//! @defgroup eve_core_fma_family  Fused multiply add family
//! @ingroup eve_core
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
//! and if there is no possibility of  mapping the std implementation
//!
//! [fam](@ref eve::fam), [fanm](@ref eve::fanm), [fma](@ref eve::fma), [fms](@ref eve::fms), [fnma](@ref eve::fnma),
//! [fnms](@ref eve::fnms)[fsm](@ref eve::fsm), [fsnm](@ref eve::fsnm).
//!
//!  @defgroup eve_core_reduction  Reductions
//!  @ingroup eve_core
//!  Operations providing a scalar value from SIMD vectors
//!
//! @defgroup eve_core_internal  IEEE operations
//! @ingroup eve_core
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
//! @defgroup eve_core_logical  Logical operations
//! @ingroup eve_core
//! Logical operations
//!
//! [swap_if](@ref eve::swap_if), [logical_and](@ref eve::logical_and), [logical_andnot](@ref eve::logical_andnot),
//! [logical_not](@ref eve::logical_not), [logical_notand](@ref eve::logical_notand), [logical_notor](@ref eve::logical_notor),
//! [logical_or](@ref eve::logical_or), [logical_ornot](@ref eve::logical_ornot),
//! [replace_ignored](@ref eve::replace_ignored).
//!
//! @defgroup eve_core_predicates  Predicates
//! @ingroup eve_core
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
//! *  [almost](@ref eve::almost) and [definitely](@ref eve::definitely) allow a fuzzy treatment of comparisons.
//!
//! Supplementary comparisons functions take the bit of sign of zero into account,  namely
//! [is_eqpz](@ref eve::is_eqpz), [is_eqmz](@ref eve::is_eqmz), [is_negative](@ref eve::is_negative), [is_positive](@ref eve::is_positive)
//!
//! @defgroup eve_core_conversions Conversions
//! @ingroup eve_core
//! Type conversions
//!
//! [convert](@ref eve::convert), [simd_cast](@ref eve::simd_cast),
//!
//! * conversion functions take two arguments a value and a scalar type to convert each lane of the value (the value itself, if it is scalar value)
//! * The conversion can use the decorator  [eve::saturated](@ref eve::saturated) in which case (sic) the result is saturated in the target type.
//!
//! @defgroup eve_core_simd SIMD Specific Operations
//! @ingroup eve_core
//! Proper SIMD operations as shuffling, splitting and merging SIMD vectors
//!
//! @defgroup eve_core_named_shuffles Named Shuffles
//! @ingroup eve_core
//! Functions that are just shuffles with a different api.
//!
//! @defgroup eve_core_compress Compress functions
//! @ingroup eve_core
//! Functions that in different way expose `compressing` selected elements
//! together to beginning. This is at the core of `remove_if`, `copy_if` etc.
//! Alternative search keywords: filter, remove, pack
//!
//! @}
//==================================================================================================
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/compress/core.hpp>
#include <eve/module/core/constant/core.hpp>
#include <eve/module/core/detail/core.hpp>
#include <eve/module/core/named_shuffles/core.hpp>
#include <eve/module/core/regular/core.hpp>
#include <eve/wide.hpp>
#include <eve/arch/nofs.hpp>
#include <eve/as_element.hpp>
