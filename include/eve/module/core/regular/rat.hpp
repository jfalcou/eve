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
//! @addtogroup core_arithmetic
//! @{
//!   @var rat
//!   @brief Computes a rational approximation.
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
//!      template< eve::real_value T>
//!      kumi::tuple<T, T> rat(T x, T tol = T(1.0e-6)*eve::abs(x)) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `tol`: [floating_value](@ref eve::value). By  default `tol`
//!       is equal to `T(1.0e-6)*``eve::abs``(x)`.
//!
//!   **Return value**
//!
//!     A pair of values  with the same type as `x` containing the
//!     [elementwise](@ref glossary_elementwise)
//!     numerator and denominator of the rational number approximating `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/rat.cpp}
//! @}
//================================================================================================

namespace tag
{
  struct rat_;
}
template<> struct supports_conditional<tag::rat_> : std::false_type
{};

EVE_MAKE_CALLABLE(rat_, rat);
}

#include <eve/module/core/regular/impl/rat.hpp>
