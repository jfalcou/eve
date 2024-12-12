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
#include <eve/module/core/regular/logical_and.hpp>

namespace eve
{
  template<typename Options>
  struct logical_andnot_t : logical_elementwise_callable<logical_andnot_t, Options>
  {
    template<typename T, typename U>
    constexpr EVE_FORCEINLINE common_logical_t<T, U> operator()(T a, U b) const noexcept
      requires (same_lanes_or_scalar<T, U> && !arithmetic_simd_value<T> && !arithmetic_simd_value<U>)
    {
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(logical_andnot_t, logical_andnot_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_andnot
//!   @brief Computes the logical ANDNOT of its arguments.
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
//!      constexpr auto logical_andnot(auto logical_value x, auto logical_value y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [logical arguments](@ref eve::logical_value).
//!
//!    **Return value**
//!
//!     Returns the logical ANDNOT of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_andnot(x, y)` is semantically equivalent to `x && !y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and  does not shortcut.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/logical_andnot.cpp}
//================================================================================================
  inline constexpr auto logical_andnot = functor<logical_andnot_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T, typename U>
    EVE_FORCEINLINE constexpr common_logical_t<T, U> logical_andnot_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
      requires (bool_or_scalar<T> && bool_or_scalar<U>) || (std::same_as<T, U>)
    {
      if  constexpr (bool_or_scalar<T>) return a && !b;
      else                              return bit_cast(a.bits() & (!b).bits(), as<T>{});
    }
  }
}
