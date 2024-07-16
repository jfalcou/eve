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
#include <eve/module/core/regular/signnz.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/constant/mone.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve
{
  template<typename Options>
  struct sign_t : elementwise_callable<sign_t, Options>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(sign_t, sign_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sign
//!   @brief `elementwise_callable` object computing the sign of the parameter.
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
//!      constexpr auto sign(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sign[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto sign[logical_value auto m](value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1;  The [elementwise](@ref glossary_elementwise) sign of `x` computed as:
//!        - `+1` , if `x` is greater than 0
//!        - `-1` , if `x` is less than 0
//!        -  \f$\pm0\f$, if `x` is \f$\pm0\f$
//!        -  If called on `Nan`, the result is the actual sign of `Nan`.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/sign.cpp}
//! @}
//================================================================================================
  inline constexpr auto sign = functor<sign_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T sign_(EVE_REQUIRES(cpu_),
                                      O const&,
                                      T const& a) noexcept
    {
      if constexpr( unsigned_value<T> )
        return one[is_nez(a)](eve::as(a));
      else  if constexpr( floating_value<T> )
        return signnz[is_nez(a)](a);
      else
        return eve::max(eve::min(a,one(eve::as(a))), mone(eve::as(a)));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/sign.hpp>
#endif
