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
#include <eve/traits/bit_value.hpp>

namespace eve
{
  template<typename Options>
  struct bit_ornot_t : strict_tuple_callable<bit_ornot_t, Options>
  {
    template<eve::value T0, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, Ts...>)
    EVE_FORCEINLINE constexpr bit_value_t<T0, Ts...>
    operator()(T0 t0, Ts...ts) const noexcept
    { return EVE_DISPATCH_CALL(t0, ts...); }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::bit_value,Tup>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(bit_ornot_t, bit_ornot_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_ornot
//!   @brief  `strict_tuple_callable` object Computing the bitwise ORNOT of its arguments.
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
//!      constexpr auto bit_ornot(value auto x, value auto ... xs) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_ornot[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 2
//!      constexpr auto bit_ornot[logical_value auto m](/*any of the above overloads*/)     noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: first [argument](@ref eve::value).
//!     * `xs...`: other [arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!      1. The return value type is`bit_value` of the parameters. Each parameter
//!        is converted to this type and then:
//!           - For two parameters it computes the  bitwise ORNOT of the two parameters
//!           - For more than two parameters the call is  semantically equivalent to
//!            `bit_ornot(a0, bit_and(xs...))`
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_ornot.cpp}
//================================================================================================
  inline constexpr auto bit_ornot = functor<bit_ornot_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/bit_ornot.hpp>

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_ornot.hpp>
#endif
