//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve
{
  template<typename Options>
  struct logical_xor_t : elementwise_callable<logical_xor_t, Options>
  {
    template<typename T, typename U>
    constexpr EVE_FORCEINLINE common_logical_t<T, U> operator()(T a, U b) const noexcept
      requires (same_lanes_or_scalar<T, U> && relaxed_logical_value<T> && relaxed_logical_value<U>)
    {
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(logical_xor_t, logical_xor_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_xor
//!   @brief Computes the logical XOR of its arguments.
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
//!      constexpr auto logical_xor(auto logical_value x, auto logical_value y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::logical_value).
//!
//!    **Return value**
//!
//!      Returns the logical XOR of the two parameters following the
//!      [logical operations semantic](@ref glossary_logical).
//!
//!      The call `logical_xor(x, y)` is semantically equivalent to `(x && !y) || (!x && y)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/logical_or.cpp}
//================================================================================================
  inline constexpr auto logical_xor = functor<logical_xor_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T, typename U>
    EVE_FORCEINLINE constexpr common_logical_t<T, U> logical_xor_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
      requires (relaxed_logical_scalar_value<T> && relaxed_logical_scalar_value<U>) || (std::same_as<T, U>)
    {
      // case 1: both are scalar/bool, possibly different.
      if  constexpr (relaxed_logical_scalar_value<T>) return a != b;
      // case 2: both are logical<wide> of the same type. This is required for most archs as they can only perform
      // bitswise operations and convert.
      else                                            return bit_cast(a.bits() != b.bits(), as<T>{});
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/logical_xor.hpp>
#endif
