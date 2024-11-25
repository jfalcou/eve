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
  struct bit_xor_t : strict_tuple_callable<bit_xor_t, Options>
  {
    template<value T0, value T1>
    EVE_FORCEINLINE constexpr bit_value_t<T0, T1> operator()(T0 t0, T1 t1) const noexcept
    {
      return this->behavior(as<bit_value_t<T0, T1>>{}, eve::current_api, this->options(), t0, t1);
    }

    template<value T0, value T1, value... Ts>
    EVE_FORCEINLINE constexpr bit_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return this->behavior(as<bit_value_t<T0, T1, Ts...>>{}, eve::current_api, this->options(), t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<bit_value, Tup> operator()(Tup const& t) const noexcept 
      requires (kumi::size_v<Tup> >= 2)
    {
      return this->behavior(as<kumi::apply_traits_t<bit_value, Tup>>{}, eve::current_api, this->options(), t);
    }

    EVE_CALLABLE_OBJECT(bit_xor_t, bit_xor_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_xor
//!   @brief `strict_tuple_callable` object computing the bitwise XOR of its arguments.
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
//!      constexpr auto bit_xor(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto bit_xor(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto bit_xor[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto bit_xor[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: first [argument](@ref eve::value).
//!     * `xs...` : other [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the bitwise XOR of its arguments converted to their  common `bit_value`
//!        is returned.
//!      2. equivalent to the call on the elements of the tuple.
//!      3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_xor.cpp}
//================================================================================================
  inline constexpr auto bit_xor = functor<bit_xor_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/bit_xor.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_xor.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_xor.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_xor.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/bit_xor.hpp>
#endif
