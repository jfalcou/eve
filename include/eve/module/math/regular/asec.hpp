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

namespace eve
{
template<typename Options>
struct asec_t : elementwise_callable<asec_t, Options, raw_option>
{
  template<eve::floating_ordered_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(asec_t, asec_);
};
//================================================================================================
//! @addtogroup math_invtrig
//! @{
//! @var asec
//!
//! @brief Callable object computing the arc secant.
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
//!      T asec(T x) noexcept;
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
//!      input in the range \f$[0 , \pi]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element is \f$0\f$, \f$\pi\f$ is returned.
//!      * If the element \f$|x| < 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/asec.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::raw
//!     The call `asec[raw](x)` uses a faster implementation which can be slightly less accurate near 1.
//!  @}
//================================================================================================
inline constexpr auto asec = functor<asec_t>;

namespace detail
{
  template<typename T, callable_options O>
  constexpr EVE_FORCEINLINE T asec_(EVE_REQUIRES(cpu_), O const& o, T const& a)
  {
    return acos[o](rec[pedantic2](a));
  }
}
}
