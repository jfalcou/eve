//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/acos.hpp>
#include <eve/module/math/regular/radinpi.hpp>

namespace eve
{
  template<typename Options>
  struct asecpi_t : elementwise_callable<asecpi_t, Options, raw_option>
  {
      template<floating_value T>
      constexpr EVE_FORCEINLINE T operator()(T v) const
      {
        return EVE_DISPATCH_CALL_PT(T, v);
      }

    EVE_CALLABLE_OBJECT(asecpi_t, asecpi_);
  };

  //================================================================================================
  //! @addtogroup math_invtrig
  //! @{
  //! @var asecpi
  //!
  //! @brief Callable object computing the arc secant in \f$\pi\f$ multiples.
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
  //!      constexpr auto asecpi(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Semantic option
  //!      constexpr auto asecpi[raw](floating_value auto x)                     noexcept; // 2
  //!
  //!      // Lanes masking
  //!      constexpr auto asecpi[conditional_expr auto c](floating_value auto x) noexcept; // 3
  //!      constexpr auto asecpi[logical_value auto m](floating_value auto x)    noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: [floating value](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!    **Return value**
  //!
  //!   1. Returns the [elementwise](@ref glossary_elementwise) arc secant of the
  //!     input in \f$\pi\f$ multiples in the range \f$[0, 1]\f$.
  //!     In particular:
  //!     * If the element is \f$1\f$, \f$+0\f$ is returned.
  //!     * If the element is \f$0\f$, \f$1\f$ is returned.
  //!     * If the element \f$|x| < 1\f$, `NaN` is returned.
  //!     * If the element is a `Nan`, `NaN` is returned.
  //!    2. Same as 1 but uses a faster implementation which can be slightly less accurate near 'x = 1'
  //!    3. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Inverse Hyperbolic Secant](https://mathworld.wolfram.com/InverseHyperbolicSecant.html)
  //!   *  [Wikipedia: Inverse hyperbolic functions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
  //!   *  [DLMF: Inverse hyperbolic functions](https://dlmf.nist.gov/4.37)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/asecpi.cpp}
  //================================================================================================
  inline constexpr auto asecpi = functor<asecpi_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE T asecpi_(EVE_REQUIRES(cpu_), O const& o, T const& a)
    {
      return radinpi(asec[o](a));
    }
  }
}
