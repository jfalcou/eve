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
struct sqrt_2pi_t : constant_callable<sqrt_2pi_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.40d932p+1);
      else if constexpr(Opts::contains(downward)) return T(0x1.40d93p+1);
      else                                         return T(0x1.40d932p+1);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.40d931ff62706p+1);
      else if constexpr(Opts::contains(downward)) return T(0x1.40d931ff62705p+1);
      else                                         return T(0x1.40d931ff62706p+1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(sqrt_2pi_t, sqrt_2pi_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var sqrt_2pi
//!   @brief Callable object computing the constant \f$\sqrt{2\pi}\f$.
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
//!      T sqrt_2pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrt_2pi(as<T>())` returns athe square root of \f$2\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sqrt_2pi.cpp}
//! @}
//================================================================================================
inline constexpr auto sqrt_2pi = functor<sqrt_2pi_t>;
}
