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
struct two_o_sqrt_pi_t : constant_callable<two_o_sqrt_pi_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.20dd76p+0);
      else if constexpr(Opts::contains(downward)) return T(0x1.20dd74p+0);
      else                                         return T(0x1.20dd76p+0);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.20dd750429b6ep+0);
      else if constexpr(Opts::contains(downward)) return T(0x1.20dd750429b6dp+0);
      else                                         return T(0x1.20dd750429b6dp+0);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(two_o_sqrt_pi_t, two_o_sqrt_pi_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var two_o_sqrt_pi
//!   @brief Callable object computing the constant \f$2/\sqrt\pi\f$.
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
//!      template< eve::value T >
//!      T two_o_sqrt_pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::two_o_sqrt_pi(as<T>())` returns  \f$2/\sqrt\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/two_o_sqrt_pi.cpp}
//! @}
//================================================================================================
inline constexpr auto two_o_sqrt_pi = functor<two_o_sqrt_pi_t>;
}
