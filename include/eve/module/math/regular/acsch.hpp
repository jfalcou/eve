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
#include <eve/module/math/regular/asinh.hpp>

namespace eve
{
  template<typename Options>
  struct acsch_t : elementwise_callable<acsch_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(acsch_t, acsch_);
};


//================================================================================================
//! @addtogroup math_invhyper
//! @{
//! @var acsch
//! @brief `elementwise_callable` object computing the inverse hyperbolic cosecant, \f$\log(1/x+\sqrt{1/x^2+1})\f$.
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
//!      constexpr auto acsch(floating_value auto x)      noexcept; // 1
//!      constexpr auto acsch[raw](floating_value auto x) noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto acsch[conditional_expr auto c](value auto x) noexcept;  // 3.1
//!      constexpr auto acsch[logical_value auto m](value auto x)    noexcept;  // 3.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) maskin. The operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosecant of the input.
//!      For values in the domain `x>1`, the inverse hyperbolic cosecant is semantically equivalent to
//!      \f$\log(1/x+\sqrt{1/x^2+1})\f$.
//!      In particular:
//!      * If the element is \f$\pm\infty\f$, \f$\pm0\f$ returned.
//!      * If the element is \f$\pm1\f$, \f$\pm\infty\f$ is returned.
//!      * If the element does not belong \f$]0,1[\f$, `NaN` is returned.
//!    2. [The operation is performed conditionnaly.](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/regular/acsch.cpp}
//!
//!  @}
//================================================================================================

//================================================================================================
//! @addtogroup math_invhyper
//! @{
//! @var acsch
//!
//! @brief Callable object computing \f$\log(1/x+\sqrt{1/x^2+1})\f$.
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
//!      T acsch(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosecant of the input.
//!      The inverse hyperbolic sine is semantically equivalent to  \f$\log(1/x+\sqrt{1/x^2+1})\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm\infty\f$, \f$\pm0\f$ returned.
//!      * If the element is \f$\pm1\f$, \f$\pm\infty\f$ is returned.
//!      * If the element does not belong \f$]0,1[\f$, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acsch.cpp}
//!  @}
//================================================================================================
  inline constexpr auto acsch = functor<acsch_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acsch_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      return asinh(rec[pedantic2](a));
    }
  }
}
