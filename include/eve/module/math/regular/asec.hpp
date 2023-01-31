//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
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
//!      T asec(T x) noexcept;                                    //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> acsc(eve::complex<T> z) noexcept;        //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) arc secant of the
//!      input in the range \f$[0 , \pi]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element is \f$0\f$, \f$\pi\f$ is returned.
//!      * If the element \f$|x| < 1\f$, `NaN` is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) \f$\mathop{\mathrm{acos}}(1/z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/asec.cpp}
//!  @}
//================================================================================================
namespace tag
{
  struct asec_;
}

template<> struct supports_optimized_conversion<tag::asec_> : std::true_type
{};

EVE_MAKE_CALLABLE(asec_, asec);
}

#include <eve/module/math/regular/impl/asec.hpp>
