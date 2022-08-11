/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/is_not_equal.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_nez
//!   @brief Returns a logical true  if and only if the element value is not zero.
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
//!      template< eve::value T >
//!      eve::as_logical<T> is_nez(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The truth value of x != 0
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_nez.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_nez[mask](x)` provides a masked version of `eve::is_nez` which is
//!     equivalent to `if_else (mask, is_nez(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_nez.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_nez_, is_nez);
}

namespace eve::detail
{
template<value T>
EVE_FORCEINLINE constexpr auto
is_nez_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  return detail::to_logical(a);
}

// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
is_nez_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
{
  return is_not_equal[cond](u, zero(as(u)));
}
}
