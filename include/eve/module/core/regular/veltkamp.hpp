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
#include <eve/module/core/regular/fsm.hpp>

namespace eve
{
  template<typename Options>
  struct veltkamp_t : callable<veltkamp_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE kumi::tuple<T, T>
    operator()(T t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(veltkamp_t, veltkamp_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var veltkamp
//!   @brief split a loating-point number with radix 2 and p mantissa bits
//!   x into two floating-point numbers xh and xl such that, the
//!   significand of xh fits in p-floor(p/2), the significand of xl fits in floor(p/2) digits, and
//!   `x = xh + xl` exactly. Where p is the number of mantissa bits of the floating type element.
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
//!      template<eve::floating_value T, eve::floating_value U  >
//!      constexpr eve::zipped<T, T> veltkamp(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[xh, xl]` such that:
//!
//!     * 'xh+xl' is 'x',  but each has much less significant digits.
//!
//!  @groupheader{External references}
//!   *  [HAL: On various ways to split a floating-point number]( https://members.loria.fr/PZimmermann/papers/split.pdf)
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/veltkamp.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto veltkamp = functor<veltkamp_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr auto
    veltkamp_(EVE_REQUIRES(cpu_), O const&, T a) noexcept
    {
      constexpr auto C = ieee_constant<0x1.0p+13f, 0x1.0p+27>(as<eve::element_type_t<T>>());
      constexpr auto Cp1 = C+1;
      T const c  = Cp1 * a;
      if constexpr( spy::supports::fma_)
      {
        T const ah = fnma(C, a, c);
        T       al = fms(Cp1, a, c);
        return  eve::zip(ah, al);
      }
      else
      {
        T const c1 = c - a;
        T       r0 = c - c1;
        return eve::zip(r0, a - r0);
      }
    }
  }
}
