//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var bit_cast
//!   @brief Computes the saturation of a value in a type.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!   {   template<value From, scalar_value To>
//!       To bit_cast operator()(From x, as<To> t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `t` :  [Type wrapper](@ref eve::as) instance embedding the type of the result.
//!
//!  **Template parameters**
//!
//!     * To: scalar type to which each element of `x` is saturated
//!
//!    **Return value**
//!
//!      For an  `x` of [real value](@ref eve::value) `Target`, the expression:
//!      @code
//!        To  r = saturate(x, as_<Target>{});
//!      @endcode
//!
//!      is semantically equivalent to:
//!
//!      @code
//!       To vmin=static_cast<T>(Valmin<To>());
//!       To vmax=static_cast<T>(Valmax<To>());
//!       To r = convert(clamp(x,vmi,vmax),as(x));
//!      @endcode
//!
//!   @note
//!      Saturation operated by [eve::saturate](#eve::saturate) may lead to
//!      Undefined Behaviors if it implies conversions that are themselves U.B.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/saturate.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(saturate_, saturate);
}

#include <eve/module/core/regular/impl/saturate.hpp>
