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
  struct bit_and_t : bit_callable<bit_and_t, Options>
  {
    template<value T0, value... Ts>
    EVE_FORCEINLINE constexpr bit_value_t<T0, Ts...> operator()(T0 t0, Ts...ts) const noexcept
    {
      if constexpr (!match_option<condition_key, decltype(this->options()), ignore_none_>)
      {
        static_assert(same_lanes_or_scalar<T0, Ts...>,
          "[eve::bit_and] - Masking is not supported for inputs of different lane count");
      }

      return EVE_DISPATCH_CALL(t0, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<bit_value, Tup> operator()(Tup const& t) const noexcept
    {
      if constexpr (!match_option<condition_key, decltype(this->options()), ignore_none_>)
      {
        static_assert(same_lanes_or_scalar_tuple<Tup>,
          "[eve::bit_and] - Masking is not supported for inputs of different lane count");
      }

      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(bit_and_t, bit_and_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_and
//!   @brief `bit_callable` object computing the bitwise AND of its arguments.
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
//!      constexpr auto bit_and(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto bit_and(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto bit_and[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto bit_and[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: first [argument](@ref eve::value).
//!     * `xs...`: other [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the bitwise AND of its arguments converted to the common `bit_value` of the arguments
//!     2. equivalent to the call on the elements of the tuple.
//!     3. [The operation is performed conditionnaly](@ref conditional). This is only supported when all parameters
//!         share the same number of lanes or are scalars.
//!
//!    @note
//!      Although the infix notation with `&` is supported for two parameters, the `&` operator on
//!      standard scalar types is the original one and so can lead to automatic promotion.
//!      Moreover, and due to C++ limitations is not available for floating point scalar entries.
//!
//!  @groupheader{External reference}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operation)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_and.cpp}
//================================================================================================
  inline constexpr auto bit_and = functor<bit_and_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/bit_and.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_and.hpp>
#endif

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_and.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_and.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/bit_and.hpp>
#endif
