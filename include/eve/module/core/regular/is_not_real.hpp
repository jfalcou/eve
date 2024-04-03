//==================================================================================================
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
#include <eve/module/core/constant/false.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_real_t : elementwise_callable<is_not_real_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_not_real_t, is_not_real_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_real
//!   @brief Returns a logical true  if and only if the element value is not real (never).
//!
//!   Always return false.
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
//!      template< eve::floating_value T >
//!      eve::as_logical<T> is_not_real(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns false for all floating entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_not_real.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_real[mask](x)` provides a masked version of `eve::is_not_real` which
//!     is equivalent to `if_else (mask, is_not_real(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
 inline constexpr auto is_not_real = functor<is_not_real_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_not_real_(EVE_REQUIRES(cpu_), O const &, T const&) noexcept
    {
      return false_(as<T>());
    }
  }
}
