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
#include <eve/module/core/regular/is_ordered.hpp>

namespace eve
{
  template<typename Options>
  struct is_lessgreater_t : strict_elementwise_callable<is_lessgreater_t, Options, definitely_option>
  {
    template<value T,  value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_logical_t<T,U> operator()(T a, U b) const
    {
      //      static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_lessgreater] simd tolerance requires at least one simd parameter." );
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(is_lessgreater_t, is_lessgreater_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_lessgreater
//!   @brief `elementwise callable` returning a logical true  if and only if the elements pair are not equal or unordered.
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
//!      constexpr auto is_lessgreater(value auto x, value auto y) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_lessgreater[conditional_expr auto c](value auto x, value auto y) noexcept; // 2
//!      constexpr auto is_lessgreater[logical_value auto m](value auto x, value auto y) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The call `eve::is_lessgreater(x, y)`  is semantically  equivalent to `x < y || x > y`:
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_lessgreater.cpp}
//!
//================================================================================================
  inline constexpr auto is_lessgreater = functor<is_lessgreater_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_lessgreater_(EVE_REQUIRES(cpu_),
                    O const & ,
                    logical<T> const& a, logical<U> const& b) noexcept
    {
      if constexpr( scalar_value<U> && scalar_value<T>) return common_logical_t<T,U>(a != b);
      else                                              return a != b;
    }

    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr  common_logical_t<T,U>
    is_lessgreater_(EVE_REQUIRES(cpu_),
                    O const & o,
                    T const& a, U const& b)  noexcept
    {
      return  is_not_equal[o](a, b) && is_ordered(a, b);
    }
  }
}


#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_lessgreater.hpp>
#endif
