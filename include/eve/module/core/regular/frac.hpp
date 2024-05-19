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
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/trunc.hpp>

namespace eve
{

  template<typename Options>
  struct frac_t : elementwise_callable<frac_t, Options, raw_option, almost_option, pedantic_option>
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
//!   * raw Call
//!
//!     The call `eve;::frac[raw](x)` does not guaranties the bit of sign
//!     conservation when the input is \f$\pm0\f$.
//!
//!   * pedantic Call
//!
//!     The call `eve;::frac[pedantic](x)` return zero if x is infinite, and preserves the sign bit.
//!
//!   * almost Call
//!
//!     If the The call `eve;::frac[almost { = tolerance }](x)` computes `x-trunc[almost { = tolerance }(x)`
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
    frac_(EVE_REQUIRES(cpu_), O const& o, T const& a) noexcept
    {
      if constexpr( floating_value<T> )
      {
        if constexpr(O::contains(raw2))      return a-trunc[o](a);
        else
        {
          auto f = if_else(is_eqz(a), a, a - trunc[o](a));
          if constexpr(platform::supports_infinites && O::contains(pedantic2))
            return if_else(is_infinite(a), bit_and(a, signmask(as(a))), f);
          else
            return f;
        }
      }
      else
        return zero(eve::as(a));
    }
  }
}
