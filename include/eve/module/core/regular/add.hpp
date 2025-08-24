//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve
{
  template<typename Options>
  struct add_t : tuple_callable<add_t, Options, saturated_option, lower_option,
                                upper_option, to_nearest_odd_option, strict_option,
                                widen_option, mod_option,
                                to_nearest_odd_option, kahan_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && !Options::contains(widen))
      EVE_FORCEINLINE common_value_t<T0, T1, Ts...> constexpr operator()(T0 t0, T1 t1, Ts...ts)
      const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && Options::contains(widen))
      EVE_FORCEINLINE common_value_t<upgrade_t<T0>, upgrade_t<T1>, upgrade_t<Ts>... >
    constexpr operator()(T0 t0, T1 t1, Ts...ts)
      const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && Options::contains(widen))
    EVE_FORCEINLINE constexpr
    upgrade_t<kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !Options::contains(widen))
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2) { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(add_t, add_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var add
//!   @brief `tuple_callable` computing the sum of its arguments.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto add(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto add(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto add[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto add[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto add[saturated](/*any of the above overloads*/)                noexcept; // 4
//!      constexpr auto add[lower](/*any of the above overloads*/)                    noexcept; // 5
//!      constexpr auto add[upper](/*any of the above overloads*/)                    noexcept; // 6
//!      constexpr auto add[lower][strict](/*any of the above overloads*/)            noexcept; // 5
//!      constexpr auto add[upper][strict](/*any of the above overloads*/)            noexcept; // 6
//!      constexpr auto add[widen](/*any of the above overloads*/)                    noexcept; // 7
//!      constexpr auto add[to_nearest_odd](/*any of the above overloads*/)           noexcept; // 8
//!      constexpr auto add[mod = p](/*any of the above overloads*/)                  noexcept; // 9
//!      constexpr auto add[kahan](/*any of the above overloads*/)                    noexcept; // 10
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `...xs`: [real](@ref eve::value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!     * `p`: modulo p operation. p must be flint less than maxflint.
//!
//!    **Return value**
//!
//!    The value of the sum of the arguments is returned.
//!    1. Take care that for floating entries, the addition is not perfectly associative due to rounding errors.
//!       This call performs additions in reverse incoming order. If you have not changed the processor rounding mode,
//!       round toward nearest mode tie to even is generally performed on standard systems.
//!    2. equivalent to the call on the elements of the tuple.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!    4. The call `add[saturated](...)` computes a saturated version of `add`.
//!       Take care that for signed integral entries this kind of addition is not associative at all.
//!       This call perform saturated additions in reverse incoming order.
//!    5. The summation is computed in a round toward \f$-\infty\f$ mode. The result is guaranted
//!       to be less or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!    6. The summation is computed in a round toward \f$\infty\f$ mode. The result is guaranted
//!       to be greater or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!    7. The summation is computed in the double sized element type (if available).
//!       This decorator has no effect on double and  64 bits integrals.
//!    8. The summation is computed in a round toward nearest mode but tie to odd (not hardware available on common systems).
//!    9. compute the result in modular arithmetic. the parameters must be floating positive
//!       and less than the modulus. The modulus itself must be less than maxflint.
//!    10. A kahan summation is performed ensuring better accuracy,  using two-add function. If the  `x`, `...xs` parameter
//!       are assumed  positive and non increasing and (or at least with non increasing exponents) adding raw option can
//!       speed a bit the summation,
//!
//!   @note
//!     * Although the infix notation with `+` is supported for two parameters, the `+` operator on
//!       standard scalar types is the original one and so can lead to automatic promotion.
//!     * add has many options. The regular user will only be interested with saturated,
//!       unless it has to deal with uncommon accuracy or order properties requirements whose enforcement can have
//!       an heavy cost even if hardware fma-like processor intrinsics are available.
//!
//!  @groupheader{External references}
//!    {kahan summation](https://en.wikipedia.org/wiki/Kahan_summation_algorithm)
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/add.cpp}
//================================================================================================
  inline constexpr auto add = functor<add_t>;
//================================================================================================
//! @}
//================================================================================================

// Required for optimisation detections
  using callable_add_ = tag_t<add>;
}

#include <eve/module/core/regular/impl/add.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/add.hpp>
#endif

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/add.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/add.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/add.hpp>
#endif
