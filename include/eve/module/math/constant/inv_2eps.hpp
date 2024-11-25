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

namespace eve
{
  template<typename Options>
  struct inv_2eps_t : constant_callable<inv_2eps_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>) return T{0x1p+22};
      else                                  return T{0x1p+51};
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(inv_2eps_t, inv_2eps_);
  };

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var inv_2eps
//!   @brief Callable object computing half the inverse of the machine epsilon.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T inv_2eps(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::inv_2eps(as<T>())` returns  half the inverse of the machine epsilon.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/inv_2eps.cpp}
//! @}
//================================================================================================
inline constexpr auto inv_2eps = functor<inv_2eps_t>;
}
