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
  struct add_t : tuple_callable<add_t, Options, saturated_option, lower_option, upper_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
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
//!      constexpr auto add[lower](/*any of the above overloads*/)                 noexcept; // 5
//!      constexpr auto add[upper](/*any of the above overloads*/)                   noexcept; // 6
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `...xs`: [real](@ref value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!    The value of the sum of the arguments is returned.
//!    1. Take care that for floating entries, the addition is not perfectly associative due to rounding errors.
//!       This call performs additions in reverse incoming order.
//!    2. equivalent to the call on the elements of the tuple.
//!    3. [The operation is performed conditionnaly](@ref conditional)
//!    4. The call `add[saturated](...)` computes a saturated version of `add`.
//!       Take care that for signed integral entries this kind of addition is not associative at all.
//!       This call perform saturated additions in reverse incoming order.
//!    5. The summation is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!       to be less or equal to the exact one (except for Nans).
//!    6. The summation is computed in a 'round toward \f$\infty\f$ mode. The result is guaranted
//!       to be greater or equal to the exact one (except for Nans).
//!
//!   @note
//!      Although the infix notation with `+` is supported for two parameters, the `+` operator on
//!      standard scalar types is the original one and so can lead to automatic promotion.
//!
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

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/add.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/add.hpp>
#endif
