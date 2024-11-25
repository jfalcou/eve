//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{
  template<typename Options>
  struct mantissa_t : elementwise_callable<mantissa_t, Options, raw_option>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(mantissa_t, mantissa_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var mantissa
//!   @brief  `elementwise_callable` object computing the IEEE mantissa of the floating value.
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
//!      constexpr auto mantissa(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto mantissa[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto mantissa[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto mantissa[raw](floating_value auto x)                     noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [real argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the IEEE mantissa is returned. In particular:
//!        *  `nan` returns nan
//!        *  zero returns zero
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. The results for zero and nan are unspecified.
//!
//!
//! @note The `exponent` \f$e\f$ and `mantissa` \f$m\f$ of a floating point entry \f$x\f$
//!       are related by \f$x =  m\times 2^e\f$, with  \f$|m| \in \{0, nan\} \cup [1, 2[\f$.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/mantissa.cpp}
//================================================================================================
  inline constexpr auto mantissa = functor<mantissa_t>;
//================================================================================================
//! @}
//================================================================================================


  namespace detail
  {
    template<floating_value T, callable_options O>
    constexpr T  mantissa_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr (O::contains(raw))
        return  bit_or(bit_and(a, mantissamask(as<T>{})), one(as<T>{}));
      else
        return if_else(is_nan(a), allbits,  bit_or(bit_and(a, mantissamask(as<T>{})), one[is_nez(a)](as<T>{})));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/mantissa.hpp>
#endif
