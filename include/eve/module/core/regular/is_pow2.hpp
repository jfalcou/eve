/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_finite.hpp>
#include <eve/module/core/regular/is_greater_equal.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_pow2_t : elementwise_callable<is_pow2_t, Options>
  {
    template<eve::integral_value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }
    
    EVE_CALLABLE_OBJECT(is_pow2_t, is_pow2_);
  };
  
//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_pow2
//!   @brief Returns a logical true  if and only if the element value is a power of 2.
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
//!      template< eve::integral_value T >
//!      eve::as_logical<T> is_pow2(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Checks [elementwise](@ref glossary_elementwise) if `x` is an integral power of two.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_pow2.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_pow2[mask](x)` provides a masked version of `eve::is_pow2` which is
//!     equivalent to `if_else (mask, is_pow2(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_pow2.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto is_pow2 = functor<is_pow2_t>;
  
  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_pow2_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      return is_gtz(a) && is_eqz(a & dec(a));
    }
  }
}
