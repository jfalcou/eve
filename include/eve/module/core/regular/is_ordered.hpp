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
#include <eve/module/core/constant/true.hpp>


namespace eve
{
  template<typename Options>
  struct is_ordered_t : elementwise_callable<is_ordered_t, Options>
  {
    template<value T,  value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_logical_t<T,U>  operator()(T a, U b) const
    {
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(is_ordered_t, is_ordered_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_ordered
//!   @brief `elementwise callable` returning a logical true  if and only no parameter is NaN.
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
//!      template< eve::value T, eve::value U >
//!      constexpr auto is_ordered(value auto x, value auto y) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_ordered[conditional_expr auto c](value auto x, value auto y) noexcept; // 2
//!      constexpr auto is_ordered[logical_value auto m](value auto x, value auto y) noexcept;    // 2
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
//!     1. The call `eve::is_ordered(x,y)`  is semantically  equivalent to `is_not_nan(x) && is_not_nan(y)`:
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_ordered.cpp}
//! @}
//================================================================================================
  inline constexpr auto is_ordered = functor<is_ordered_t>;

  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    is_ordered_(EVE_REQUIRES(cpu_),
                  O const & ,
                  logical<T> const& , logical<U> const& ) noexcept
    {
      using r_t =   common_logical_t<logical<T>, logical<U>>;
      return true_(as<r_t>());
    }


    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    is_ordered_(EVE_REQUIRES(cpu_),
                  O const & ,
                  T const& aa, U const& bb) noexcept
    {
      using w_t =  common_value_t<T, U>;
      {
        if constexpr(integral_value<T> )
          return true_(as<w_t>());
        else
        {
          auto a = w_t(aa);
          auto b = w_t(bb);
          return (a == a) && (b == b);
        }
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_ordered.hpp>
#endif
