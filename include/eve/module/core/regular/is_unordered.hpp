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
  struct is_unordered_t : elementwise_callable<is_unordered_t, Options>
  {
    template<value T, value U>
    constexpr EVE_FORCEINLINE common_logical_t<T,U> operator()(T a, U b) const
      requires (eve::same_lanes_or_scalar<T, U>)
    {
      return this->behavior(as<common_logical_t<T, U>>{}, eve::current_api, this->options(), a, b);
    }

    EVE_CALLABLE_OBJECT(is_unordered_t, is_unordered_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_unordered
//!   @brief `elementwise callable` returning a logical true  if and only if at least one of the
//!   parameters is `NaN`.
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
//!      // Regular overload
//!      constexpr auto is_unordered(value auto x, value auto y) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_unordered[conditional_expr auto c](value auto x, value auto y) noexcept; // 2
//!      constexpr auto is_unordered[logical_value auto m](value auto x, value auto y) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The call `eve::is_unordered(x,y)`  is semantically  equivalent to `is_nan(x) || is_nan(y)`:
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_unordered.cpp}
//================================================================================================
  inline constexpr auto is_unordered = functor<is_unordered_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, value T, value U>
    EVE_FORCEINLINE constexpr auto
    is_unordered_(EVE_REQUIRES(cpu_),
                  O const& ,
                  logical<T> const& , logical<U> const& ) noexcept
    {
      using r_t =  common_logical_t<logical<T>, logical<U>>;
      return false_(as<r_t>{});
    }


    template<callable_options O, value T, value U>
    EVE_FORCEINLINE constexpr auto
    is_unordered_(EVE_REQUIRES(cpu_),
                  O const& ,
                  T const& aa, U const& bb) noexcept
    {
      using w_t =  common_value_t<T, U>;
      {
        if constexpr(integral_value<T> )
          return false_(as<w_t>{});
        else
        {
          auto a = w_t(aa);
          auto b = w_t(bb);
          return (a != a) || (b != b);
        }
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_unordered.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/is_unordered.hpp>
#endif
