/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/traits/bit_value.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_denormal_t : elementwise_callable<is_not_denormal_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_not_denormal_t, is_not_denormal_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_denormal
//!   @brief Returns a logical true if and only if the element value is not denormal.
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
//!      eve::as_logical<T> is_not_denormal(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `is_not_denormal(x)` is semantically  equivalent to:
//!     `(eve::abs(x) >=  eve::smallestposval(eve::as(x))) || eve::is_eqz(x)`,
//!     in particular this is always true for integral types.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_not_denormal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_denormal[mask](x)` provides a masked version
//!     of `eve::is_not_denormal` which is
//!     equivalent to `if_else (mask, is_not_denormal(x), eve::false( eve::as(x)))`.
//!
//!
//! @}
//================================================================================================
  inline constexpr auto is_not_denormal = functor<is_not_denormal_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_not_denormal_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( !floating_value<T> || !eve::platform::supports_denormals )
        return true_(eve::as<T>());
      else
        return is_eqz(a) || is_not_less(eve::abs(a), smallestposval(eve::as<T>()));
    }
  }
}
