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

namespace eve
{
  template<typename Options>
  struct mul_t : strict_tuple_callable<mul_t, Options, saturated_option, lower_option,
                                       upper_option, strict_option, widen_option, mod_option>
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
      EVE_FORCEINLINE common_value_t<upgrade_t<T0>, upgrade_t<T1>, upgrade_t<Ts>... > //typename result<T0, T1, Ts...>::type
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
    EVE_CALLABLE_OBJECT(mul_t, mul_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var mul
//!   @brief tuple_callable` computing the product of its arguments.
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
//!      constexpr auto mul(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto mul(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto mul[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto mul[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto mul[saturated](/*any of the above overloads*/)                noexcept; // 4
//!      constexpr auto mul[lower](/*any of the above overloads*/)                    noexcept; // 5
//!      constexpr auto mul[upper](/*any of the above overloads*/)                    noexcept; // 6
//!      constexpr auto mul[lower][strict](/*any of the above overloads*/)            noexcept; // 5
//!      constexpr auto mul[upper][strict](/*any of the above overloads*/)            noexcept; // 6
//!      constexpr auto mul[widen](/*any of the above overloads*/)                    noexcept; // 7
//!      constexpr auto mul[mod = p](/*any of the above overloads*/)                  noexcept; // 8
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `... xs` : [real](@ref eve::value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      The value of the product of the arguments is returned.
//!    1. Take care that for floating entries, the multiplication is not perfectly associative due to rounding errors.
//!       This call performs multiplications in reverse incoming order.
//!    2. equivalent to the call on the elements of the tuple.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!    4. The call `mul[saturated](...)` computes a saturated version of `mul`.
//!       Take care that for signed integral entries this kind of multiplication is not associative at all.
//!       This call perform saturated multiplications in reverse incoming order.
//!    5. The product is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!       to be less or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!    6. The product is computed in a 'round toward \f$\infty\f$ mode. The result is guaranted
//!       to be greater or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!    7. The operation is computed in the double sized element type (if available).
//!       This decorator has no effect on double and 64 bits integrals.
//!    8. compute the result in modular arithmetic. the parameters must be flint positive
//!       and less than the modulus. The modulus itself must be less than maxflint.
//!
//!   @note
//!      Although the infix notation with `*` is supported for two parameters, the `*` operator on
//!      standard scalar types is the original one and so can lead to automatic promotion.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/mul.cpp}
//================================================================================================
  inline constexpr auto mul = functor<mul_t>;
//================================================================================================
//! @}
//================================================================================================

// Required for optimisation detections
  using callable_mul_ = tag_t<mul>;
}

#include <eve/module/core/regular/impl/mul.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/mul.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/mul.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/mul.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/mul.hpp>
#endif
