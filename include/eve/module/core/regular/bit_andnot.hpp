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
  struct bit_andnot_t : strict_tuple_callable<bit_andnot_t, Options>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...>
    operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::bit_value,Tup>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2)
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(bit_andnot_t, bit_andnot_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_andnot
//!   @brief `strict_tuple_callable` object computing the bitwise ANDNOT of its arguments.
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
//!      constexpr auto bit_andnot(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto bit_andnot(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto bit_andnot[conditional_expr auto c](value auto x, value auto ... xs) noexcept; // 3
//!      constexpr auto bit_andnot[logical_value auto m](value auto x, value auto ... xs)    noexcept; // 3
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
//!      1. The return value type is bit_value<T,  Ts...> Each parameter is converted
//!         to this type and then:
//!            - For two parameters it computes the  bitwise ANDNOT of the two parameters
//!            - For more than two parameters the call is  semantically equivalent to
//!              `bit_andnot(a0, bit_and(xs...))`
//!      2. equivalent to the call on the elements of the tuple.
//!      3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operation)
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/bit_andnot.cpp}
//!  @groupheader{Semantic Modifiers}
//! @}
//================================================================================================
  inline constexpr auto bit_andnot = functor<bit_andnot_t>;
}

#include <eve/module/core/regular/impl/bit_andnot.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/bit_andnot.hpp>
#endif
