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
  struct atan_t : elementwise_callable<atan_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(atan_t, atan_);
  };


//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var atan
//!
//! @brief Callable object computing the arc tangent.
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
//!      template< eve::floating_value T >
//!      T atan(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   * `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
//!      input in the range \f$[-\frac\pi2, \frac\pi2]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\frac\pi2\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!      special cases are handled as if the operation was implemented by \f$-i \mathrm{atanh}(i z)\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/atan.cpp}
//!
//!  @}
//================================================================================================
 inline constexpr auto atan = functor<atan_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T atan_(EVE_REQUIRES(cpu_), O const& , T const& a)
    {
      T x = eve::abs(a);
      return bit_xor(atan_kernel(x, rec[pedantic2](x)), bitofsign(a));
    }
  }
}
