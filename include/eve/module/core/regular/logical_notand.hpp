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
#include <eve/detail/overload.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/regular/logical_and.hpp>

namespace eve
{
  template<typename Options>
  struct logical_notand_t : elementwise_callable<logical_notand_t, Options>
  {
    template<typename T, typename U>
    constexpr EVE_FORCEINLINE common_logical_t<T, U> operator()(T a, U b) const noexcept
      requires (same_lanes_or_scalar<T, U> && relaxed_logical_value<T> && relaxed_logical_value<U>)
    {
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(logical_notand_t, logical_notand_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_notand
//!   @brief Computes the logical NOTAND of its arguments.
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
//!      constexpr auto logical_notand(auto logical_value x, auto logical_value y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [logical arguments](@ref eve::logical_value).
//!
//!    **Return value**
//!
//!     Returns the logical NOTAND of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_notand(x, y)` is semantically equivalent to `!x && y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and  does not shortcut.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/logical_notand.cpp}
//================================================================================================
  inline constexpr auto logical_notand = functor<logical_notand_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/logical_notand.hpp>
