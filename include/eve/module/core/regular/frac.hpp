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
  struct frac_t : elementwise_callable<frac_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(frac_t, frac_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var frac
//!   @brief Computes the fractional part of the input.
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
//!      T frac(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!   **Return value**
//!
//!     Returns a value with the same type as `x`  containing the
//!     [elementwise](@ref glossary_elementwise) fractional part of `x`
//!     with the same sign as `x`.
//!
//!     In particular:
//!       * If an [element](@ref glossary_elementwise) of `x` is \f$\pm0\f$,  \f$\pm0\f$ is
//!         returned.
//!       * If an [element](@ref glossary_elementwise) of `x` is \f$\pm\infty\f$ or `Nan`, a
//!        `Nan` is returned.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/frac.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::frac[mask](x)` provides a masked version of `eve::frac` which is
//!     equivalent to `if_else (mask, frac(x), x)`.
//!
//! @}
//================================================================================================
  inline constexpr auto frac = functor<frac_t>;

  namespace detail
  {
   template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    frac_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
   {
     if constexpr( floating_value<T> )
     {
       if constexpr( scalar_value<T> ) return !a ? a : a - trunc(a);
       else                            return if_else(is_eqz(a), a, a - trunc(a));
     }
     else                              return zero(eve::as(a));
   }
  }
}
