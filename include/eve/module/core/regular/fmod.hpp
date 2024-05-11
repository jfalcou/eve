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
#include <eve/module/core/regular/is_not_infinite.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/fanm.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/constant/allbits.hpp>

namespace eve
{
  template<typename Options>
  struct fmod_t : elementwise_callable<fmod_t, Options>
  {
    template<value T,  value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(fmod_t, fmod_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fmod
//!   @brief Computes the  remainder after division for floating entries similarly to std::fmod
//!   for floating entries.
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
//!      template< eve::value T,  eve::value U>
//!      eve::common_value_t<T, U> fmod(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:   [real](@ref eve::value) arguments.
//!
//!   **Return value**
//!
//!      Return the remainder after division division of `x` by `y` and is
//!      semantically equivalent to  `x- eve::trunc ( eve:div(x, y) )*y`.
//!
//!        For floating point entries this call is similar to std::fmod. In particular:
//!
//!        * If `x` is  \f$\pm0\f$ and y is not zero,  \f$\pm0\f$ is returned.
//!        * If `x` is \f$\pm\infty\f$, and y is not NaN, NaN is returned.
//!        * If `y` is  \f$\pm0\f$, NaN is returned.
//!        * If `y` is  \f$\pm\infty\f$ and `x` is finite, `x` is returned.
//!        * If either argument is a Nan, NaN is returned.
//!
//!        For integral entries this call is similar to rem. but if y is zero returns a:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/fmod.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fmod[mask](x, ...)` provides a masked
//!     version of `fmod` which is
//!     equivalent to `if_else(mask, fmod(x, ...), x)`
//!
//! @}
//================================================================================================
 inline constexpr auto fmod = functor<fmod_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T fmod_(EVE_REQUIRES(cpu_), O const&, T a, T b) noexcept
    {
      auto bb = if_else(is_nez(b), b, one);
      if constexpr( floating_value<T> )
      {
        return if_else(is_eqz(b) || is_infinite(a) || is_unordered(a, b),
                       allbits,
                       fanm[pedantic2][is_nez(a) && is_not_infinite(b)](a, trunc(a/b), b));
      }
      else
      {
        return if_else(is_nez(b), rem(a, bb), a);
      }
    }
  }
}
