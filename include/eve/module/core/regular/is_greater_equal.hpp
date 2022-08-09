//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_greater_equal
//!   @brief Returns a logical true  if and only if the element value of the first parameter is
//!          greater or equal to the second one.
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
//!      template< eve::value T, eve::value U >
//!      eve::as_logical<T> is_greater_equal(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_greater_equal(x,y)`  is semantically  equivalent to `x >= y`:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_greater_equal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_greater_equal[mask](x,y)` provides a masked version of
//!     `eve::is_greater_equal` which is equivalent to `if_else (mask, is_greater_equal(x),
//!     eve::false( eve::as(x,y)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_greater_equal.cpp}
//!
//!  * `almost`
//!
//!     The expression `definitely(is_greater_equal)(x, y, t)` where `x` and `y` must be
//!      floating point values, evals to true if and only if `x` is almost greater than `y`.
//!      This means that:
//!
//!      - if `t` is a floating_value then  \f$x > y - t \max(|x|, |y|)\f$
//!      - if `t` is a positive integral_value then \f$x > \mbox{prev}(y, t)\f$;
//!      - if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
//!
//!      **Example**
//!
//!         @godbolt{doc/core/fuzzy/is_greater_equal.cpp}
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(is_greater_equal_, is_greater_equal);

namespace detail
{
  template<value T, value U>
  EVE_FORCEINLINE auto is_greater_equal_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
  {
    if constexpr( scalar_value<T> && scalar_value<U> ) return as_logical_t<T>(a >= b);
    else return a >= b;
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, value U, value V>
  EVE_FORCEINLINE auto
  is_greater_equal_(EVE_SUPPORTS(cpu_), C const& cond, U const& u, V const& v) noexcept
  {
    return logical_mask_op(cond, is_greater_equal, u, v);
  }
}
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_greater_equal.hpp>
#endif
