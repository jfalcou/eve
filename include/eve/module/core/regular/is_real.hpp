//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core/constant/true.hpp>

namespace eve
{
  template<typename Options>
  struct is_real_t : elementwise_callable<is_real_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_real_t, is_real_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_real
//!   @brief Returns a logical true.
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
//!      eve::as_logical<T> is_real(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns [elementwise](@ref glossary_elementwise) true.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_real.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_real[mask](x)` provides a masked version of `eve::is_real` which is
//!     equivalent to `if_else (mask, is_real(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_real.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto is_real = functor<is_real_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_real_(EVE_REQUIRES(cpu_), O const &, T const&) noexcept
    {
      return true_(as<T>());
    }
  }
}
