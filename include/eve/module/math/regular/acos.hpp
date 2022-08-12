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
//! @var acos
//!
//! @brief Callable object computing acos.
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
//!      T acos(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_real_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) arc cosine of the
//! input in the range \f$[0 , \pi]\f$.
//!
//! In particular:
//!
//!   * If the element is \f$1\f$, \f$+0\f$ is returned.
//!   * If the element \f$|x| > 1\f$, `NaN` is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/acos.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::raw
//!     The call `raw(acos)(x)`, call a faster implementation which can be slightly less accurate
//!     near 1.
//!  @}
//================================================================================================

namespace tag
{
  struct acos_;
}
template<> struct supports_conditional<tag::acos_> : std::false_type
{};

EVE_MAKE_CALLABLE(acos_, acos);
}

#include <eve/module/math/regular/impl/acos.hpp>
