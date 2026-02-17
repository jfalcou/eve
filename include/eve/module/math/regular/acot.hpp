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
  struct acot_t : elementwise_callable<acot_t, Options,
                                       rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acot_t, acot_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var acot
//!   @brief `elementwise_callable` object computing the arc cotangent.
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      constexpr auto acot(floating_value auto x)                          noexcept; // 1
//!
//!      // Semantic option
//!      constexpr auto acos[raw](floating_value auto x)                     noexcept; // 2
//!      constexpr auto acos[rad](floating_value auto x)                     noexcept; // 1
//!      constexpr auto acos[deg](floating_value auto x)                     noexcept; // 3
//!      constexpr auto acos[pirad](floating_value auto x)                   noexcept; // 4
//!
//!      // Lanes masking
//!      constexpr auto acot[conditional_expr auto c](floating_value auto x) noexcept; // 5
//!      constexpr auto acot[logical_value auto m](floating_value auto x)    noexcept; // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`: [floating value](@ref eve::floating_value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) arc cotangent in radians of the
//!      input in the range  \f$[-\frac\pi2, \frac\pi2]\f$.
//!      In particular:
//!       * If the element is \f$\pm0\f$, \f$\pm\frac\pi2\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!       * If the element is a `Nan`, `NaN` is returned.
//!    3. Result in degrees
//!    4. Result in \f$\pi\f$ multiples
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Cotangent](https://mathworld.wolfram.com/InverseCotangent.html)
//!   *  [DLMF: ](https://dlmf.nist.gov/4.23)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/acot.cpp}
//================================================================================================
  inline constexpr auto acot = functor<acot_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acot_(EVE_REQUIRES(cpu_), O const& o, T const& a)
    {
     if constexpr(O::contains(rad))
        return acot[o.drop(rad)](a);
      else if constexpr(O::contains(deg))
        return radindeg(acot[o.drop(deg)](a));
      else if constexpr(O::contains(radpi))
        return radinpi(acot[o.drop(radpi)](a));
      else if constexpr(std::same_as<eve::element_type_t<T>, eve::float16_t>)
        return eve::detail::apply_fp16_as_fp32(eve::acot[o], a);
      else
      {
        auto x = eve::abs(a);
        return bit_xor(atan_kernel(rec[pedantic](x), x), bitofsign(a));
      }
    }
  }
  constexpr auto acotd = eve::acot[eve::deg];
  constexpr auto acotpi= eve::acot[eve::radpi];

}
