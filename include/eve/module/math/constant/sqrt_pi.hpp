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
struct sqrt_pi_t : constant_callable<sqrt_pi_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.c5bf8ap+0);
      else if constexpr(Opts::contains(downward2)) return T(0x1.c5bf88p+0);
      else                                         return T(0x1.c5bf8ap+0);
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.c5bf891b4ef6bp+0);
      else if constexpr(Opts::contains(downward2)) return T(0x1.c5bf891b4ef6ap+0);
      else                                         return T(0x1.c5bf891b4ef6bp+0);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(sqrt_pi_t, sqrt_pi_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var sqrt_pi
//!   @brief Callable object computing the constant \f$\sqrt{\pi}\f$.
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
//!      T sqrt_pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrt_pi(as<T>())` returns the square root of \f$\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sqrt_pi.cpp}
//! @}
//================================================================================================
inline constexpr auto sqrt_pi = functor<sqrt_pi_t>;
}
