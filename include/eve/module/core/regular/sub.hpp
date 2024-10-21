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
  struct sub_t : tuple_callable<sub_t, Options, saturated_option, lower_option,
                                upper_option, strict_option, widen_option>
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

    EVE_CALLABLE_OBJECT(sub_t, sub_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sub
//!   @brief `tuple_callable` computing the difference of its first argument with the sum of the others.
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
//!      constexpr auto sub(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto sub(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto sub[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto sub[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto sub[saturated](/*any of the above overloads*/)                noexcept; // 4
//!      constexpr auto sub[lower](/*any of the above overloads*/)                    noexcept; // 5
//!      constexpr auto sub[upper](/*any of the above overloads*/)                    noexcept; // 6
//!      constexpr auto sub[widen](/*any of the above overloads*/)                    noexcept; // 7
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `... xs` :  [real](@ref eve::value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!    The value of the difference of its first argument with the sum of the others
//!    1. Take care that for floating entries, the addition is not perfectly associative due to rounding errors.
//!       This call performs additions in reverse incoming order.
//!    2. equivalent to the call on the elements of the tuple.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!    4. The call `sub[saturated](...)` computes a saturated version of `add`.
//!       Take care that for signed integral entries this kind of a is highly order dependant.
//!       This call perform saturated additions in reverse incoming order.
//!        We do not advise to use it for more than 2 parameters.
//!    5. The substraction is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!       to be less or equal to the exact one (except for Nans).
//!    6. The substraction is computed in a 'round toward \f$\infty\f$ mode. The result is guaranted
//!       to be greater or equal to the exact one (except for Nans).
//!    7. The operation is computed in the double sized element type (if available).
//!       This decorator has no effect on double and 64 bits integrals.
//!
//!
//!   @note
//!      Although the infix notation with `-` is supported for two parameters, the `-` operator on
//!      standard scalar types is the original one and so can lead to automatic promotion.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sub.cpp}
//================================================================================================
  inline constexpr auto sub = functor<sub_t>;
//================================================================================================
//! @}
//================================================================================================

}

#include <eve/module/core/regular/impl/sub.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/sub.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/sub.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/sub.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/sub.hpp>
#endif
