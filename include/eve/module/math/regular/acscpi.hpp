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
#include <eve/module/math/regular/radinpi.hpp>
#include <eve/module/math/regular/acsc.hpp>

namespace eve
{
  template<typename Options>
  struct acscpi_t : elementwise_callable<acscpi_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acscpi_t, acscpi_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var acscpi
//!   @brief  `elementwise_callable` object computing the arc cosecant in \f$\pi\f$ multiples.
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
//!      // Regular overloads
//!      constexpr auto acscpi(floating_value auto x)                         noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto acscpi[conditional_expr auto c](floatingvalue auto x) noexcept; // 2.1
//!      constexpr auto acscpi[logical_value auto m](floatingvalue auto x)    noexcept; // 2.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) arc cosecant of the
//!      input in \f$\pi\f$ multiples, in the range \f$[-\frac12, \frac12]\f$.
//!      In particular:
//!      * If the element is \f$\pm1\f$, \f$\pm\frac12\f$ is returned.
//!      * If the element \f$|x| < 1\f$, `NaN` is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/regular/acscpi.cpp}
//!  @}
//================================================================================================

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var acscpi
//!
//! @brief Callable object computing he arc cosecant in \f$\pi\f$ multiples.
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
//!      T acscpi(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *   Returns the [elementwise](@ref glossary_elementwise) arc cosecant of the
//!       input in the range \f$[-\frac12, \frac12]\f$.
//!
//!       In particular:
//!
//!        * If the element is \f$\pm1\f$, \f$\pm\frac12\f$ is returned.
//!        * If the element \f$|x| < 1\f$, `NaN` is returned.
//!        * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!        * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acscpi.cpp}
//!  @}
//================================================================================================
  inline constexpr auto acscpi = functor<acscpi_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acscpi_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      return radinpi(acsc(a));
    }
  }
}
