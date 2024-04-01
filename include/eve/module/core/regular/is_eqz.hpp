//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/is_equal.hpp>
#include <eve/module/core/regular/logical_not.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_eqz_t : elementwise_callable<is_eqz_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_eqz_t, is_eqz_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_eqz
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
//!      eve::as_logical<T> is_eqz(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The truth value of x == 0
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_eqz.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_eqz[mask](x)` provides a masked version of `eve::is_eqz` which is
//!     equivalent to `if_else (mask, is_eqz(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_eqz.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto is_eqz = functor<is_eqz_t>;
  
  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_eqz_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( scalar_value<T> || is_logical_v<T> )
        return !a;
      else
        return (a == zero(eve::as(a)));
    }
  }
}
