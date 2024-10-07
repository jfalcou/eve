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
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/acos.hpp>
#include <eve/module/math/regular/radinpi.hpp>

namespace eve
{
template<typename Options>
struct acospi_t : elementwise_callable<acospi_t, Options, raw_option>
{
  template<floating_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const
  {
    return EVE_DISPATCH_CALL_PT(T, v);
  }

  EVE_CALLABLE_OBJECT(acospi_t, acospi_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var acospi
//!   @brief  `elementwise_callable` object computing the arc cosine in \f$\pi\f$ multiples.
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
//!      constexpr auto acospi(floating_value auto x)                          noexcept; // 1
//!
//!      // Semantic option
//!      constexpr auto acospi[raw](floating_value auto x)                     noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto acospi[conditional_expr auto c](floating_value auto x) noexcept; // 3
//!      constexpr auto acospi[logical_value auto m](floating_value auto x)    noexcept; // 3
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) arc cosine of the
//!      input in \f$\pi\f$ multiples, in the range \f$[0 , 1]\f$.
//!      In particular:
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element \f$|x| > 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!    2. Same as 1 but uses a faster implementation which can be slightly less accurate near `x = 1`
//!    3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: acos](https://en.cppreference.com/w/cpp/numeric/math/acos)
//!   *  [Wolfram MathWorld: Inverse Cosine](https://mathworld.wolfram.com/InverseCosine.html)
//!   *  [DLMF: Error Functions](https://dlmf.nist.gov/7.2#i)
//!   *  [Wikipedia: Arc cosinus](https://fr.wikipedia.org/wiki/Arc_cosinus)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/acospi.cpp}
//================================================================================================
  inline constexpr auto acospi = functor<acospi_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE T acospi_(EVE_REQUIRES(cpu_), O const& o, T const& a0)
    {
      if constexpr( has_native_abi_v<T> ) return radinpi(acos[o](a0));
      else                                return apply_over(acospi[o], a0);
    }
  }
}
