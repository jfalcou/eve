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
  struct logeps_t : constant_callable<logeps_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
    {
      if      constexpr(std::same_as<T, float> ) return T(-0x1.fe2804p+3);
      else if constexpr(std::same_as<T, double>) return T(-0x1.205966f2b4f12p+5);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(logeps_t, logeps_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var logeps
//!   @brief Computes the natural logarithm of the machine [epsilon](@ref eve::eps).
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
//!     template<eve::floating_value T> constexpr T logeps(as<T> x);
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::logeps(as<T>())` is semantically equivalent
//!      to eve::log (eve::eps (eve::as<T>())).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/logeps.cpp}
//! @}
//================================================================================================
  inline constexpr auto logeps = functor<logeps_t>;

}
