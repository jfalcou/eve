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
#include <eve/module/core.hpp>
#include <eve/module/math/detail/generic/atan_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct acot_t : elementwise_callable<acot_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acot_t, acot_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var acot
//!
//! @brief Callable object computing the arc cotangent.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template< eve::floating_value T > T acot(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *   Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
//!       input in the range \f$[-\frac\pi2, \frac\pi2]\f$.
//!
//!       In particular:
//!
//!       * If the element is \f$\pm0\f$, \f$\pm\frac\pi2\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!       * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acot.cpp}
//!  @}
//================================================================================================
  inline constexpr auto acot = functor<acot_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acot_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto x = eve::abs(a);
        return bit_xor(atan_kernel(rec[pedantic2](x), x), bitofsign(a));
      }
      else
        return apply_over(acot, a);
    }
  }
}
