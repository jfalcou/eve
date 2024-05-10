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
#include <eve/module/core/regular/div.hpp>
#include <eve/module/core/regular/is_not_infinite.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/fanm.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/constant/allbits.hpp>

namespace eve
{
  template<typename Options>
  struct remainder_t : elementwise_callable<remainder_t, Options>
  {
    template<value T,  value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    //      requires(signed_value<common_value_t<T, U>>)
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(remainder_t, remainder_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var remainder
//!   @brief Computes the  remainder after division for floating entries similarly to std::remainder
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
//!      template< eve::signed_value T,  eve::signed_value U>
//!      eve::common_value_t<T, U> rem(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:   [real](@ref eve::value) arguments.
//!
//!   **Return value**
//!
//!      The common_value_t<T, U> is required to be a signed type,  as the call
//!      returns the remainder after division division of `x` by `y` and is
//!      semantically equivalent to  `x- eve::nearest ( eve:div(x, y) )*y`, which can be negative.
//!
//!        For floating point entries this call is similar to std::remainder. In particular:
//!
//!        * If `x` is \f$\pm\infty\f$, NaN is returned
//!        * If `y` is \f$\pm0\f$, NaN is returned
//!        * If either argument is a Nan, NaN is returned
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/remainder.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::remainder[mask](x, ...)` provides a masked
//!     version of `remainder` which is
//!     equivalent to `if_else(mask, remainder(x, ...), x)`
//!
//! @}
//================================================================================================
 inline constexpr auto remainder = functor<remainder_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T remainder_(EVE_REQUIRES(cpu_), O const&, T a, T b) noexcept
    {
      auto bb = if_else(is_nez(b), b, one);
      if constexpr( floating_value<T> )
      {
        return if_else(is_eqz(b) || is_infinite(a) || is_unordered(a, b),
                       allbits,
                       fanm[pedantic2][is_nez(a) && is_not_infinite(b)](a, nearest(a/b), b));
      }
      else
      {
        return fnma(b, eve::div[to_nearest2](a, b), a);
      }
    }
  }
}
