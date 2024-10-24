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
//! even when and upgraded type is not available.
//!
//! @defgroup core_arithmetic  Arithmetic operations
//! @ingroup core
//! Core arithmetic functions
//!
//! These functions allows performing some basic arithmetics operations with greater accuracy
//! even when and upgraded type is not available.
//!
//![absmin](@ref absmin), [add](@ref add), [agm](@ref agm), [average](@ref average), [ceil](@ref ceil),
//![chi](@ref chi), [clamp](@ref clamp), [copysign](@ref copysign), [dec](@ref dec), [dist](@ref dist),
//![div](@ref div), [dot](@ref dot), [fdim](@ref fdim), [floor](@ref floor),
//![flush_denormal](@ref flush_denormal), [fmod](@ref fmod), [frac](@ref frac),
//![fracscale](@ref fracscale), [heaviside](@ref heaviside), [inc](@ref inc), [lerp](@ref lerp),
//![manhattan](@ref manhattan), [max](@ref max), [maxabs](@ref maxabs), [maxmag](@ref maxmag),
//![min](@ref min), [minabs](@ref minabs), [minmag](@ref minmag), [minmax](@ref minmax),
//![minus](@ref minus), [modf](@ref modf), [mul](@ref mul), [nearest](@ref nearest),
//![negabsmax](@ref negabsmax), [negabsmin](@ref negabsmin), [negate](@ref negate),
//![negatenz](@ref negatenz), [negmaxabs](@ref negmaxabs), [negminabs](@ref negminabs),
//![of_class](@ref of_class), [oneminus](@ref oneminus), [rat](@ref rat), [rec](@ref rec),
//![reldist](@ref reldist), [rem](@ref rem), [remainder](@ref remainder), [round](@ref round),
//![roundscale](@ref roundscale), [rsqrt](@ref rsqrt), [saturate](@ref saturate), [shl](@ref shl),
//![sign](@ref sign), [sign_alternate](@ref sign_alternate), [signnz](@ref signnz), [sqr](@ref sqr),
//![sqrt](@ref sqrt), [sub](@ref sub), [trunc](@ref trunc).

//!
//! @defgroup core_bitops Bitwise functions
//! @ingroup core
//! These functions are low level and acting on the bit representation of the involved datas.
//!
//! [bit_and](@ref bit_and), [bit_andnot](@ref bit_andnot), [bit_cast](@ref bit_cast),
//! [bit_ceil](@ref bit_ceil), [bit_flip](@ref bit_flip), [bit_floor](@ref bit_floor),
//! [bit_mask](@ref bit_mask), [bit_not](@ref bit_not), [bit_notand](@ref bit_notand),
//! [bit_notor](@ref bit_notor), [bit_or](@ref bit_or), [bit_ornot](@ref bit_ornot),
//! [bit_reverse](@ref bit_reverse), [bit_select](@ref bit_select), [bit_set](@ref bit_set),
//! [bit_shl](@ref bit_shl), [bit_shr](@ref bit_shr), [bit_swap_adjacent](@ref bit_swap_adjacent),
//! [bit_swap_pairs](@ref bit_swap_pairs), [bit_ternary](@ref bit_ternary),
//! [bit_unset](@ref bit_unset), [bit_width](@ref bit_width), [bit_xor](@ref bit_xor),
//! [byte_reverse](@ref byte_reverse), [byte_swap_adjacent](@ref byte_swap_adjacent),
//! [byte_swap_pairs](@ref byte_swap_pairs), [countl_one](@ref countl_one),
//! [countl_zero](@ref countl_zero), [countr_one](@ref countr_one),
//! [countr_zero](@ref countr_zero), [firstbitset](@ref firstbitset),
//! [firstbitunset](@ref firstbitunset), [hi](@ref hi), [lo](@ref lo), [lohi](@ref lohi),
//! [popcount](@ref popcount), [rotl](@ref rotl), [rotr](@ref rotr), [rshl](@ref rshl),
//! [rshr](@ref rshr), [shl](@ref shl), [shr](@ref shr), [swap_pairs](@ref swap_pairs).
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
//! [allbits](@ref allbits), [as_value](@ref as_value), [bitincrement](@ref bitincrement),
//! [constant](@ref constant), [core](@ref core), [eps](@ref eps), [exponentmask](@ref exponentmask),
//! [false_](@ref false_), [half](@ref half), [ieee_constant](@ref ieee_constant),
//! [inf](@ref inf), [iota](@ref iota), [logeps](@ref logeps), [mantissamask](@ref mantissamask),
//! [maxexponent](@ref maxexponent), [maxexponentm1](@ref maxexponentm1),
//! [maxexponentp1](@ref maxexponentp1), [maxflint](@ref maxflint),
//! [mhalf](@ref mhalf), [mindenormal](@ref mindenormal), [minexponent](@ref minexponent),
//! [minf](@ref minf), [mone](@ref mone), [mzero](@ref mzero), [nan](@ref nan),
//! [nbmantissabits](@ref nbmantissabits), [one](@ref one), [oneosqrteps](@ref oneosqrteps),
//! [signmask](@ref signmask), [smallestposval](@ref smallestposval), [sqrteps](@ref sqrteps),
//! [sqrtsmallestposval](@ref sqrtsmallestposval), [sqrtvalmax](@ref sqrtvalmax), [true_](@ref true_),
//! [twotonmb](@ref twotonmb), [valmax](@ref valmax), [valmin](@ref valmin), [zero](@ref zero).
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
//!          eve::negabsmin, eve::negmaxabs, eve::negminabs, eve::next, eve::nextafter, eve::prev, eve::rec, eve::reldist, eve::rsqrt, eve::signnz, eve::sum_of_prod,
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
//!       - `widen`: the result is computes in the upgraded type corresding to the elements parameters. Presently, this has no effect
//!          on 64 bits types as the upgrade type is currently the type itself.
//!          If the widen decorator is used,  it is the responsability of the user to use `convert` if he needs to get back to the input
//!          type sizes.
//!
//!    * Fuzzy
//!
//!       - `almost`: allows some laxity on the predicate result or the integer rounding direction
//!       - `definitely`: impose some rigidity on the predicate result or the integer rounding direction
//!
//!       these two decorators can be used with the functions eve::ceil,  eve::floor, eve::frac, eve::modf, eve::trunc,
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
//! [fam](@ref fam), [fanm](@ref fanm), [fma](@ref fma), [fms](@ref fms), [fnms](@ref fnms),
//! [fsm](@ref fsm), [fsnm](@ref fsnm).
//!
//!  @defgroup core_reduction  Reductions
//!  @ingroup core
//!  Operations providing a scalar value from SIMD vectors
//!
//!  [all](@ref all), [any](@ref any), [count_true](@ref count_true), [first_true](@ref first_true),
//!  [maximum](@ref maximum), [minimum](@ref minimum), [none](@ref none), [reduce](@ref reduce).
//!
//!
//! @defgroup core_internal  IEEE operations
//! @ingroup core
//! Operations related to classical IEEE functions and the floating representation of real numbers
//!
//!  [bitofsign](@ref bitofsign), [exponent](@ref exponent), [frexp](@ref frexp), [ifrexp](@ref ifrexp),
//!  [ilogb](@ref ilogb), [ldexp](@ref ldexp), [mantissa](@ref mantissa), [nb_values](@ref nb_values), [next](@ref next),
//!  [nextafter](@ref nextafter), [prev](@ref prev), [ulpdist](@ref ulpdist).
//!
//! @defgroup core_logical  Logical operations
//! @ingroup core
//! Logical operations
//!
//! [if_else](@ref if_else), [logical_and](@ref logical_and), [logical_andnot](@ref logical_andnot),
//! [logical_not](@ref logical_not), [logical_notand](@ref logical_notand), [logical_notor](@ref logical_notor),
//! [logical_or](@ref logical_or), [logical_ornot](@ref logical_ornot), [logical_xor](@ref logical_xor),
//! [replace](@ref replace), [swap_if](@ref swap_if).
//!
//! @defgroup core_predicates  Predicates
//! @ingroup core
//! Operations returning logical values
//!
//! Mind that in SIMD context these functions DO NOT return boolean but logical values that is
//! an internal representation of a vector of truth values that can be handled by the function of
//! the previous section (core_logical).
//!
//! [is_bit_equal](@ref is_bit_equal), [is_denormal](@ref is_denormal), [is_eqmz](@ref is_eqmz), [is_eqpz](@ref is_eqpz),
//! [is_equal](@ref is_equal), [is_eqz](@ref is_eqz), [is_even](@ref is_even), [is_finite](@ref is_finite),
//! [is_flint](@ref is_flint), [is_gez](@ref is_gez), [is_greater](@ref is_greater), [is_greater_equal](@ref is_greater_equal),
//! [is_gtz](@ref is_gtz), [is_infinite](@ref is_infinite), [is_less](@ref is_less), [is_less_equal](@ref is_less_equal),
//! [is_lessgreater](@ref is_lessgreater), [is_lez](@ref is_lez), [is_ltz](@ref is_ltz), [is_minf](@ref is_minf),
//! [is_nan](@ref is_nan), [is_negative](@ref is_negative), [is_nemz](@ref is_nemz), [is_nepz](@ref is_nepz),
//! [is_nez](@ref is_nez), [is_ngez](@ref is_ngez), [is_ngtz](@ref is_ngtz), [is_nlez](@ref is_nlez), [is_nltz](@ref is_nltz),
//! [is_normal](@ref is_normal), [is_not_denormal](@ref is_not_denormal), [is_not_equal](@ref is_not_equal),
//! [is_not_finite](@ref is_not_finite), [is_not_flint](@ref is_not_flint), [is_not_greater](@ref is_not_greater),
//! [is_not_greater_equal](@ref is_not_greater_equal), [is_not_infinite](@ref is_not_infinite), [is_not_less](@ref is_not_less),
//! [is_not_less_equal](@ref is_not_less_equal), [is_not_nan](@ref is_not_nan), [is_odd](@ref is_odd), [is_ordered](@ref is_ordered),
//! [is_pinf](@ref is_pinf), [is_positive](@ref is_positive), [is_pow2](@ref is_pow2), [is_unit](@ref is_unit),
//! [is_unordered](@ref is_unordered).
//!
//! @defgroup core_conversions Conversions
//! @ingroup core
//! Type conversions
//!
//! [as_value](@ref as_value), [convert](@ref convert), [simd_cast](@ref simd_cast),
//!
//! @defgroup core_simd SIMD Specific Operations
//! @ingroup core
//! Proper SIMD operations as shuffling, splitting and merging SIMD vectors
//!
//! [broadcast](@ref broadcast), [broadcast_group](@ref broadcast_group), [combine](@ref combine),
//! [deinterleave_groups_shuffle](@ref deinterleave_groups_shuffle), [gather](@ref gather),
//! [has_equal_in](@ref has_equal_in), [iterate_selected](@ref iterate_selected),
//! [scan](@ref scan), [scatter](@ref scatter), [sort](@ref sort), [splat](@ref splat), [zip](@ref zip), .
//!
//! @defgroup core_named_shuffles Named Shuffles
//! @ingroup core
//! Functions that are just shuffles with a different api.
//!
//! [blend](@ref blend), [broadcast_lane](@ref broadcast_lane), [reverse](@ref reverse),
//! [reverse_in_subgroups](@ref reverse_in_subgroups), [slide](@ref slide), [swap_adjacent](@ref swap_adjacent).
//!
//! @defgroup core_compress Compress functions
//! @ingroup core
//! Functions that in different way expose `compressing` selected elements
//! together to beginning. This is at the core of `remove_if`, `copy_if` etc.
//! Alternative search keywords: filter, remove, pack
//!
//! [compress](@ref compress), [compress_copy](@ref compress_copy), [compress_copy_scalar](@ref compress_copy_scalar),
//! [compress_copy_simd](@ref compress_copy_simd), [compress_store](@ref compress_store).
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
