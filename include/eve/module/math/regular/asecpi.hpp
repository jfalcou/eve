//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
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
  template<eve::floating_ordered_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(asecpi_t, asecpi_);
};
//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var asecpi
//!
//! @brief Callable object computing the arc secant in \f$\pi\f$ multiples.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T asecpi(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) arc secant of the
//!      input in \f$\pi\f$ multiples in the range \f$[0, 1]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element is \f$0\f$, \f$1\f$ is returned.
//!      * If the element \f$|x| < 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/asecpi.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::raw
//!     The call `asecpi[raw](x)` uses a faster implementation which can be slightly less accurate near 1.
//!
//!  @}
//================================================================================================
inline constexpr auto asecpi = functor<asecpi_t>;

namespace detail
{
  template<typename T, callable_options O>
  constexpr EVE_FORCEINLINE T asecpi_(EVE_REQUIRES(cpu_), O const& o, T const& a)
  {
    return radinpi(asec[o](a));
  }
}
}
