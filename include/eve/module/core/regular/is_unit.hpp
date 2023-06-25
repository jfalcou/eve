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
//! @addtogroup core_predicates
//! @{
//!   @var is_unit
//!   @brief Returns a logical true  if and only if the element value is zero.
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
//!      eve::as_logical<T> is_unit(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The truth value of eve;; abs(x) == 1
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_unit.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_unit[mask](x)` provides a masked version of `eve::is_unit` which is
//!     equivalent to `if_else (mask, is_unit(x), eve::false(eve::as<decltype(is_unit(x))>())`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_unit.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_unit_, is_unit);

namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, value U, value V>
  EVE_FORCEINLINE auto is_unit_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
  {
    return logical_mask_op(cond, is_unit, u);
  }
}
}

#include <eve/module/core/regular/impl/is_unit.hpp>
