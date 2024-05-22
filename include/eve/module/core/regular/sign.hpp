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
//!   @brief Computes the sign of the parameter.
//!
//!   **Defined in Header**
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
//!      template< eve::value T >
//!      T sign(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!   The [elementwise](@ref glossary_elementwise) sign of `x` computed as:
//!     - `+1` , if `x` is greater than 0
//!     - `-1` , if `x` is less than 0
//!     -  `0` , if `x` is equal to 0
//!     - `-0.`, if `x` is equal -0
//!
//!   If called on `Nan`, the result is the actual sign of `Nan`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/sign.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::sign[mask](x)` provides a masked version of `eve::sign` which is
//!     equivalent to `if_else (mask, sign(x), x)`.
//!
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
