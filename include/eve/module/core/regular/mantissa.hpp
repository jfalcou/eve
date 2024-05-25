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
  struct mantissa_t : elementwise_callable<mantissa_t, Options, pedantic_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(mantissa_t, mantissa_);
  };


//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var mantissa
//!   @brief Computes the IEEE mantissa of the floating value.
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
//!      T mantissa(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of the IEEE mantissa.
//!    is returned.
//!
//! @note
//!    *  The exponent \f$e\f$ and mantissa \f$m\f$ of a floating point entry \f$x\f$
//!       are related by \f$x =  m\times 2^e\f$, with  \f$|m| \in [1, 2[\f$.
//!
//!    *  The exception is when \f$x = \pm0, \pm\infty\f$ or is a Nan, where \f$m=x\f$ and \f$e=0\f$).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/mantissa.cpp}
//! @}
//================================================================================================

 inline constexpr auto mantissa = functor<mantissa_t>;

  namespace detail
  {
    template<floating_value T, callable_options O>
    constexpr T  mantissa_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      if constexpr(O::contains(pedantic2))
      {
        if constexpr( scalar_value<T> )
        {
          if( !a ) return a;
          if constexpr( eve::platform::supports_invalids )
          {
            if( is_not_finite(a) ) return a;
          }
          return bit_or(bit_and(a, mantissamask(eve::as<T>())), one(eve::as(a)));
        }
        else if constexpr( simd_value<T> )
        {
          auto test = is_eqz(a);
          if constexpr( eve::platform::supports_invalids ) { test = test || is_not_finite(a); }
          return if_else(test, a, bit_or(bit_and(a, mantissamask(eve::as<T>())), one(eve::as<T>())));
        }
      }
      else
      {
        return if_else(is_eqz(a), a, bit_or(bit_and(a, mantissamask(eve::as<T>())), one(eve::as<T>())));
      }
    }
  }
}
// #if defined(EVE_INCLUDE_X86_HEADER)
// #  include <eve/module/core/regular/impl/simd/x86/mantissa.hpp>
// #endif
