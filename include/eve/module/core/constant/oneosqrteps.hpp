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
  struct oneosqrteps_t : constant_callable<oneosqrteps_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&,  Opts const&)
    {
      if constexpr(std::same_as<T, float>)
      {
        if constexpr(Opts::contains(upper))        return T(0x1.6a09e8p+11f);
        else                                        return T(0x1.6a09e6p+11f);
      }
      else if constexpr(std::same_as<T, double> ) return T(0x1p+26);
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(oneosqrteps_t, oneosqrteps_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var oneosqrteps
//!   @brief Computes the  the inverse of the square root of the machine epsilon.
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
//!     template<eve::floating_value T> constexpr T oneosqrteps(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::oneosqrteps(as<T>())`  is semantically equivalent to
//!      `eve::rec (eve::sqrt (eve::eps (as<T>())))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/oneosqrteps.cpp}
//!
//================================================================================================
  inline constexpr auto oneosqrteps = functor<oneosqrteps_t>;
//================================================================================================
//! @}
//================================================================================================
}
//
