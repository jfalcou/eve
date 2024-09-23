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
struct rsqrt_pi_t : constant_callable<rsqrt_pi_t, Options, lower_option, upper_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upper))        return T(0x1.20dd76p-1);
      else if constexpr(Opts::contains(lower)) return T(0x1.20dd74p-1);
      else                                         return T(0x1.20dd76p-1);
    }
    else
    {
      if constexpr(Opts::contains(upper))        return T(0x1.20dd750429b6ep-1);
      else if constexpr(Opts::contains(lower)) return T(0x1.20dd750429b6dp-1);
      else                                         return T(0x1.20dd750429b6dp-1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(rsqrt_pi_t, rsqrt_pi_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var rsqrt_pi
//!   @brief Callable object computing the constant \f$\pi^{-1/2}\f$.
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
//!      T rsqrt_pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::rsqrt_pi(as<T>())` returns the inverse of \f$\sqrt{\pi}\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/rsqrt_pi.cpp}
//! @}
//================================================================================================
inline constexpr auto rsqrt_pi = functor<rsqrt_pi_t>;
}
