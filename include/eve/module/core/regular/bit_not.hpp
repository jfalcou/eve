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
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve
{

  template<typename Options>
  struct bit_not_t : elementwise_callable<bit_not_t, Options, saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(bit_not_t, bit_not_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_not
//!   @brief  `elementwise_callable` object computing the one complement of the parameter.
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
//!      constexpr auto bit_not(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_not[conditional_expr auto c](value auto x) noexcept; // 2.1
//!      constexpr auto bit_not[logical_value auto m](value auto x)    noexcept; // 2.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the bitwise NOT of the parameter is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_not.cpp}
//! @}
//================================================================================================
  inline constexpr auto bit_not = functor<bit_not_t>;

  namespace detail
  {
    template<value T, callable_options O>
    constexpr T  bit_not_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      if constexpr( floating_scalar_value<T> )
        return bit_cast(~bit_cast(v, as<as_integer_t<T>> {}), as(v));
      else
        return T(~v);
    }
  }
}
