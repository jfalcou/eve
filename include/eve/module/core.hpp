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
//![absmin](@ref eve::absmin), [add](@ref eve::add), [agm](@ref eve::agm), [average](@ref eve::average), [ceil](@ref eve::ceil),
//![chi](@ref eve::chi), [clamp](@ref eve::clamp), [copysign](@ref eve::copysign), [dec](@ref eve::dec), [dist](@ref eve::dist),
//![div](@ref eve::div), [dot](@ref eve::dot), [fdim](@ref eve::fdim), [floor](@ref eve::floor),
//![flush_denormal](@ref eve::flush_denormal), [fmod](@ref eve::fmod), [frac](@ref eve::frac),
//![fracscale](@ref eve::fracscale), [heaviside](@ref eve::heaviside), [inc](@ref eve::inc), [lerp](@ref eve::lerp),
//![manhattan](@ref eve::manhattan), [max](@ref eve::max), [maxabs](@ref eve::maxabs), [maxmag](@ref eve::maxmag),
//![min](@ref eve::min), [minabs](@ref eve::minabs), [minmag](@ref eve::minmag), [minmax](@ref eve::minmax),
//![minus](@ref eve::minus), [modf](@ref eve::modf), [mul](@ref eve::mul), [nearest](@ref eve::nearest),
//![negabsmax](@ref eve::negabsmax), [negabsmin](@ref eve::negabsmin), [negate](@ref eve::negate),
//![negatenz](@ref eve::negatenz), [negmaxabs](@ref eve::negmaxabs), [negminabs](@ref eve::negminabs),
//![of_class](@ref eve::of_class), [oneminus](@ref eve::oneminus), [rat](@ref eve::rat), [rec](@ref eve::rec),
//![reldist](@ref eve::reldist), [rem](@ref eve::rem), [remainder](@ref eve::remainder), [round](@ref eve::round),
//![roundscale](@ref eve::roundscale), [rsqrt](@ref eve::rsqrt), [saturate](@ref eve::saturate), [shl](@ref eve::shl),
//![sign](@ref eve::sign), [sign_alternate](@ref eve::sign_alternate), [signnz](@ref eve::signnz), [sqr](@ref eve::sqr),
//![sqrt](@ref eve::sqrt), [sub](@ref eve::sub), [trunc](@ref eve::trunc).

//!
//! @defgroup core_bitops Bitwise functions
//! @ingroup core
//! These functions are low level and acting on the bit representation of the involved datas.
//!
//! [bit_and](@ref eve::bit_and), [bit_andnot](@ref eve::bit_andnot), [bit_cast](@ref eve::bit_cast),
//! [bit_ceil](@ref eve::bit_ceil), [bit_flip](@ref eve::bit_flip), [bit_floor](@ref eve::bit_floor),
//! [bit_mask](@ref eve::bit_mask), [bit_not](@ref eve::bit_not), [bit_notand](@ref eve::bit_notand),
//! [bit_notor](@ref eve::bit_notor), [bit_or](@ref eve::bit_or), [bit_ornot](@ref eve::bit_ornot),
//! [bit_reverse](@ref eve::bit_reverse), [bit_select](@ref eve::bit_select), [bit_set](@ref eve::bit_set),
//! [bit_shl](@ref eve::bit_shl), [bit_shr](@ref eve::bit_shr), [bit_swap_adjacent](@ref eve::bit_swap_adjacent),
//! [bit_swap_pairs](@ref eve::bit_swap_pairs), [bit_ternary](@ref eve::bit_ternary),
//! [bit_unset](@ref eve::bit_unset), [bit_width](@ref eve::bit_width), [bit_xor](@ref eve::bit_xor),
//! [byte_reverse](@ref eve::byte_reverse), [byte_swap_adjacent](@ref eve::byte_swap_adjacent),
//! [byte_swap_pairs](@ref eve::byte_swap_pairs), [countl_one](@ref eve::countl_one),
//! [countl_zero](@ref eve::countl_zero), [countr_one](@ref eve::countr_one),
//! [countr_zero](@ref eve::countr_zero), [firstbitset](@ref eve::firstbitset),
//! [firstbitunset](@ref eve::firstbitunset), [hi](@ref eve::hi), [lo](@ref eve::lo), [lohi](@ref eve::lohi),
//! [popcount](@ref eve::popcount), [rotl](@ref eve::rotl), [rotr](@ref eve::rotr), [rshl](@ref eve::rshl),
//! [rshr](@ref eve::rshr), [shl](@ref eve::shl), [shr](@ref eve::shr), [swap_pairs](@ref eve::swap_pairs).
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
//! [allbits](@ref eve::allbits), [as_value](@ref eve::as_value), [bitincrement](@ref eve::bitincrement),
//! [constant](@ref eve::constant), [eps](@ref eve::eps), [exponentmask](@ref eve::exponentmask),
//! [false_](@ref eve::false_), [half](@ref eve::half), [ieee_constant](@ref eve::ieee_constant),
//! [inf](@ref eve::inf), [iota](@ref eve::iota), [logeps](@ref eve::logeps), [mantissamask](@ref eve::mantissamask),
//! [maxexponent](@ref eve::maxexponent), [maxexponentm1](@ref eve::maxexponentm1),
//! [maxexponentp1](@ref eve::maxexponentp1), [maxflint](@ref eve::maxflint),
//! [mhalf](@ref eve::mhalf), [mindenormal](@ref eve::mindenormal), [minexponent](@ref eve::minexponent),
//! [minf](@ref eve::minf), [mone](@ref eve::mone), [mzero](@ref eve::mzero), [nan](@ref eve::nan),
//! [nbmantissabits](@ref eve::nbmantissabits), [one](@ref eve::one), [oneosqrteps](@ref eve::oneosqrteps),
//! [signmask](@ref eve::signmask), [smallestposval](@ref eve::smallestposval), [sqrteps](@ref eve::sqrteps),
//! [sqrtsmallestposval](@ref eve::sqrtsmallestposval), [sqrtvalmax](@ref eve::sqrtvalmax), [true_](@ref eve::true_),
//! [twotonmb](@ref eve::twotonmb), [valmax](@ref eve::valmax), [valmin](@ref eve::valmin), [zero](@ref eve::zero).
//!
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
//!  [all](@ref eve::all), [any](@ref eve::any), [count_true](@ref eve::count_true), [first_true](@ref eve::first_true),
//!  [maximum](@ref eve::maximum), [minimum](@ref eve::minimum), [none](@ref eve::none), [reduce](@ref eve::reduce).
//!
//!
//! @defgroup core_internal  IEEE operations
//! @ingroup core
//! Operations related to classical IEEE functions and the floating representation of real numbers
//!
//!  [bitofsign](@ref eve::bitofsign), [exponent](@ref eve::exponent), [frexp](@ref eve::frexp), [ifrexp](@ref eve::ifrexp),
//!  [ilogb](@ref eve::ilogb), [ldexp](@ref eve::ldexp), [mantissa](@ref eve::mantissa), [nb_values](@ref eve::nb_values), [next](@ref eve::next),
//!  [nextafter](@ref eve::nextafter), [prev](@ref eve::prev), [ulpdist](@ref eve::ulpdist).
//!
//! @defgroup core_logical  Logical operations
//! @ingroup core
//! Logical operations
//!
//! [if_else](@ref eve::if_else), [logical_and](@ref eve::logical_and), [logical_andnot](@ref eve::logical_andnot),
//! [logical_not](@ref eve::logical_not), [logical_notand](@ref eve::logical_notand), [logical_notor](@ref eve::logical_notor),
//! [logical_or](@ref eve::logical_or), [logical_ornot](@ref eve::logical_ornot), [logical_xor](@ref eve::logical_xor),
//! [replace](@ref eve::replace), [swap_if](@ref eve::swap_if).
//!
//! @defgroup core_predicates  Predicates
//! @ingroup core
//! Operations returning logical values
//!
//! Mind that in SIMD context these functions DO NOT return boolean but logical values that is
//! an internal representation of a vector of truth values that can be handled by the function of
//! the previous section (core_logical).
//!
//! [is_bit_equal](@ref eve::is_bit_equal), [is_denormal](@ref eve::is_denormal), [is_eqmz](@ref eve::is_eqmz), [is_eqpz](@ref eve::is_eqpz),
//! [is_equal](@ref eve::is_equal), [is_eqz](@ref eve::is_eqz), [is_even](@ref eve::is_even), [is_finite](@ref eve::is_finite),
//! [is_flint](@ref eve::is_flint), [is_gez](@ref eve::is_gez), [is_greater](@ref eve::is_greater), [is_greater_equal](@ref eve::is_greater_equal),
//! [is_gtz](@ref eve::is_gtz), [is_infinite](@ref eve::is_infinite), [is_less](@ref eve::is_less), [is_less_equal](@ref eve::is_less_equal),
//! [is_lessgreater](@ref eve::is_lessgreater), [is_lez](@ref eve::is_lez), [is_ltz](@ref eve::is_ltz), [is_minf](@ref eve::is_minf),
//! [is_nan](@ref eve::is_nan), [is_negative](@ref eve::is_negative), [is_nemz](@ref eve::is_nemz), [is_nepz](@ref eve::is_nepz),
//! [is_nez](@ref eve::is_nez), [is_ngez](@ref eve::is_ngez), [is_ngtz](@ref eve::is_ngtz), [is_nlez](@ref eve::is_nlez), [is_nltz](@ref eve::is_nltz),
//! [is_normal](@ref eve::is_normal), [is_not_denormal](@ref eve::is_not_denormal), [is_not_equal](@ref eve::is_not_equal),
//! [is_not_finite](@ref eve::is_not_finite), [is_not_flint](@ref eve::is_not_flint), [is_not_greater](@ref eve::is_not_greater),
//! [is_not_greater_equal](@ref eve::is_not_greater_equal), [is_not_infinite](@ref eve::is_not_infinite), [is_not_less](@ref eve::is_not_less),
//! [is_not_less_equal](@ref eve::is_not_less_equal), [is_not_nan](@ref eve::is_not_nan), [is_odd](@ref eve::is_odd), [is_ordered](@ref eve::is_ordered),
//! [is_pinf](@ref eve::is_pinf), [is_positive](@ref eve::is_positive), [is_pow2](@ref eve::is_pow2), [is_unit](@ref eve::is_unit),
//! [is_unordered](@ref eve::is_unordered).
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
//! [broadcast](@ref eve::broadcast), [broadcast_group](@ref eve::broadcast_group), [combine](@ref eve::combine),
//! [deinterleave_groups_shuffle](@ref eve::deinterleave_groups_shuffle), [gather](@ref eve::gather),
//! [has_equal_in](@ref eve::has_equal_in), [iterate_selected](@ref eve::iterate_selected),
//! [scan](@ref eve::scan), [scatter](@ref eve::scatter), [sort](@ref eve::sort), [splat](@ref eve::splat), [zip](@ref eve::zip), .
//!
//! @defgroup core_named_shuffles Named Shuffles
//! @ingroup core
//! Functions that are just shuffles with a different api.
//!
//! [blend](@ref eve::blend), [broadcast_lane](@ref eve::broadcast_lane), [reverse](@ref eve::reverse),
//! [reverse_in_subgroups](@ref eve::reverse_in_subgroups), [slide](@ref eve::slide), [swap_adjacent](@ref eve::swap_adjacent).
//!
//! @defgroup core_compress Compress functions
//! @ingroup core
//! Functions that in different way expose `compressing` selected elements
//! together to beginning. This is at the core of `remove_if`, `copy_if` etc.
//! Alternative search keywords: filter, remove, pack
//!
//! [compress](@ref eve::compress), [compress_copy](@ref eve::compress_copy), [compress_copy_scalar](@ref eve::compress_copy_scalar),
//! [compress_copy_simd](@ref eve::compress_copy_simd), [compress_store](@ref eve::compress_store).
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
