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

namespace eve
{
  template<typename Options>
  struct is_nez_t : elementwise_callable<is_nez_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_nez_t, is_nez_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_nez
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is not zero.
//!
//!   @groupheader{Header file}
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
//!  @godbolt{doc/core/is_nez.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_nez[mask](x)` provides a masked version of `eve::is_nez` which is
//!     equivalent to `if_else (mask, is_nez(x), eve::false( eve::as(x)))`.
//! @}
//================================================================================================
  inline constexpr auto is_nez = functor<is_nez_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_nez_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      return detail::to_logical(a);
    }
  }
}
