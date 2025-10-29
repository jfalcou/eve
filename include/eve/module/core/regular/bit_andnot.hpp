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
  struct bit_andnot_t : bit_callable<bit_andnot_t, Options>
  {
    template<value T0, value... Ts>
    EVE_FORCEINLINE constexpr bit_value_t<T0, Ts...> operator()(T0 t0, Ts...ts) const noexcept
    {
      if constexpr (!match_option<condition_key, decltype(this->options()), ignore_none_>)
      {
        static_assert(same_lanes_or_scalar<T0, Ts...>,
          "[eve::bit_andnot] - Masking is not supported for inputs of different lane count");
      }

      return EVE_DISPATCH_CALL(t0, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    EVE_FORCEINLINE constexpr kumi::apply_traits_t<bit_value, Tup> operator()(Tup const& t) const noexcept
    {
      if constexpr (!match_option<condition_key, decltype(this->options()), ignore_none_>)
      {
        static_assert(same_lanes_or_scalar_tuple<Tup>,
          "[eve::bit_andnot] - Masking is not supported for inputs of different lane count");
      }

      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(bit_andnot_t, bit_andnot_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_andnot
//!   @brief `bit_callable` object computing the bitwise ANDNOT of its arguments.
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
//!      constexpr auto bit_andnot[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto bit_andnot[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
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
//!      1. The return value type is  to the common `bit_value` of the parameters. Each parameter
//!         is converted to this type and then:
//!            - For two parameters it computes the  bitwise ANDNOT of the two parameters
//!            - For more than two parameters the call is  semantically equivalent to
//!              `bit_andnot(a0, bit_and(xs...))`
//!      2. equivalent to the call on the elements of the tuple.
//!      3. [The operation is performed conditionnaly](@ref conditional). This is only supported when all parameters
//!         share the same number of lanes or are scalars.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Bitwise_operation)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_andnot.cpp}
//================================================================================================
  inline constexpr auto bit_andnot = functor<bit_andnot_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/bit_andnot.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/bit_andnot.hpp>
#endif
