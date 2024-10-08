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
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/allbits.hpp>
#include <eve/module/core/regular/bitofsign.hpp>
#include <eve/module/core/regular/is_nan.hpp>

namespace eve
{
  template<typename Options>
  struct signnz_t : elementwise_callable<signnz_t, Options, pedantic_option>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    { return this->behavior(as<T>{}, eve::current_api, this->options(), a); }

    EVE_CALLABLE_OBJECT(signnz_t, signnz_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var signnz
//!   @brief `elementwise_callable` object computing the never zero sign of the parameter.
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
//!      constexpr auto signnz(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto signnz[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto signnz[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto abs[pedantic](value auto x)                   noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. Computes  [elementwise](@ref glossary_elementwise) the never zero sign of `x`.
//!          - If x is [positive](@ref eve::is_positive), 1 is returned.
//!          - If x is [negative](@ref eve::is_negative), -1 is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. same as 1. but returns NaN for NaN input
//!
//!      @note `is_negative` and `is_positive` only look at the sign bit and a NaN has
//!        generally unpredicable sign bit.
//!
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/signnz.cpp}
//================================================================================================
 inline constexpr auto signnz = functor<signnz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr T
    signnz_(EVE_REQUIRES(cpu_), O const &, T const &a) noexcept
    {
      if constexpr( unsigned_value<T> )
      {
        return one(eve::as(a));
      }
      else if constexpr( floating_value<T> )
      {
        auto r = bit_or(one(eve::as(a)), bitofsign(a));
        if constexpr( eve::platform::supports_nans && O::contains(pedantic))
        {
          if constexpr( scalar_value<T> )
            return is_nan(a) ? a : r;
          else
            return if_else(is_nan(a), eve::allbits, r);
        }
        else
          return r;
      }
      else if constexpr( integral_value<T> )
      {
        using elt_t = element_type_t<T>;
        return (a >> (sizeof(elt_t) * 8 - 2)) | T(1);
      }
    }
  }
}
