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
struct invlog_phi_t : constant_callable<invlog_phi_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.09fec2p+1);
      else if constexpr(Opts::contains(downward)) return T(0x1.09fecp+1);
      else                                         return T(0x1.09fecp+1);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.09fec09279922p+1);
      else if constexpr(Opts::contains(downward)) return T(0x1.09fec09279921p+1);
      else                                         return T(0x1.09fec09279922p+1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(invlog_phi_t, invlog_phi_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var invlog_phi
//!   @brief Callable object computing the inverse of the logarithm of the golden ratio :
//!   \f$1/\log((1+\sqrt5)/2)\f$.
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
//!      T invlog_phi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::invlog_phi(as<T>())` returns the inverse of the logarithm of the golden ratio?
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/invlog_phi.cpp}
//! @}
//================================================================================================
inline constexpr auto invlog_phi = functor<invlog_phi_t>;
}
