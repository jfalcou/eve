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
  struct bit_notand_t : strict_tuple_callable<bit_notand_t, Options>
  {
    template<value T0, value T1, value... Ts>
    EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
      requires(same_lanes_or_scalar<T0, T1, Ts...>)
    {
      return EVE_DISPATCH_CALL_PT((bit_value_t<T0, T1, Ts...>), t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<bit_value, Tup> operator()(Tup const& t) const noexcept
      requires (same_lanes_or_scalar_tuple<Tup> && (kumi::size_v<Tup> >= 2))
    {
      return EVE_DISPATCH_CALL_PT((kumi::apply_traits_t<bit_value, Tup>), t);
    }

    EVE_CALLABLE_OBJECT(bit_notand_t, bit_notand_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_notand
//!   @brief  `strict_tuple_callable` object computing the bitwise NOTAND of its arguments.
//!
//!   **Defined in Header**
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
//!      constexpr auto bit_notand(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto bit_notand(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto bit_notand[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto bit_notand[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: first [argument](@ref eve::value).
//!     * `xs...`: other [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!     1. The return value type is the common `bit_value` of the parameters. Each parameter
//!        is converted to this type and then:
//!         - For two parameters it computes the  bitwise NOTAND of the two parameters
//!         - For more than two parameters the call is  semantically equivalent to
//!           `bit_notand(a0, bit_and(xs...))`
//!     2. equivalent to the call on the elements of the tuple.
//!     3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_notand.cpp}
//================================================================================================
  inline constexpr auto bit_notand = functor<bit_notand_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/bit_notand.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_notand.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_notand.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_notand.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/bit_notand.hpp>
#endif
