//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_equal
//!   @brief Returns a logical true  if and only if the element value are not equal.
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
//!      auto is_not_equal(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  arguments
//!
//!   **Return value**
//!
//!     Returns the logical value containing the [elementwise](@ref glossary_elementwise) equality
//!     test result between `x` and `y`. The infix notation `x != y` can also be used.
//!
//!   @note
//!
//!      Although the infix notation with `==` is supported, the `!=` operator on
//!      standard scalar types is the original one and so returns bool result, not `eve::logical`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_not_equal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::is_not_equal[mask](x)` provides a masked version of `eve::is_not_equal` which
//!     is equivalent to `if_else (mask, is_not_equal(x, y), false_
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_not_equal.cpp}
//!
//!  * eve::numeric
//!
//!     The expression `numeric(is_not_equal)(x,y)` considers that Nan values are not equal.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/pedantic/is_not_equal.cpp}
//!
//!  * `definitely`
//!
//!     The expression `definitely(is_not_equal)(x, y, t)` where `x` and `y` must be floating point
//!     values, evals to
//!      true if and only if `x` is almost equal to `y`.
//!      This means that:
//!
//!      * if `t` is a floating_value then the relative error of not confusing is `x` and `y` is
//!      greater than `t` \f$(|x-y| \ge t \max(|x|, |y|))\f$.
//!      * if `t` is a positive integral_value then there are more than `t` values of the type of
//!      `x` representable in the interval \f$[x,y[\f$.
//!      * if `t` is omitted then the tolerance `t` is taken to 3 times the machine \f$\epsilon\f$
//!      in the `x` type (`3*eps(as(x))`).
//!
//!      **Example**
//!
//!        @godbolt{doc/core/fuzzy/is_not_equal.cpp}
//! @}
//================================================================================================
EVE_IMPLEMENT_CALLABLE(is_not_equal_, is_not_equal);

namespace detail
{
  template<value T, value U>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
  {
    if constexpr( scalar_value<T> && scalar_value<U> ) return as_logical_t<T>(a != b);
    else return a != b;
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, value U, value V>
  EVE_FORCEINLINE auto
  is_not_equal_(EVE_SUPPORTS(cpu_), C const& cond, U const& u, V const& v) noexcept
  {
    return logical_mask_op(cond, is_not_equal, u, v);
  }
}
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_not_equal.hpp>
#endif
