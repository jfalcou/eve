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
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_unit_t : elementwise_callable<is_unit_t, Options, pedantic_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_unit_t, is_unit_);
  };

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
//!  @godbolt{doc/core/is_unit.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_unit[mask](x)` provides a masked version of `eve::is_unit` which is
//!     equivalent to `if_else (mask, is_unit(x), eve::false(eve::as<decltype(is_unit(x))>())`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_unit = functor<is_unit_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE as_logical_t<T>
    is_unit_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      return is_equal[almost](sqr(a), one(as<T>()));
    }
  }
}
