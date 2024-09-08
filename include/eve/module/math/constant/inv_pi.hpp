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
struct inv_pi_t : constant_callable<inv_pi_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.45f308p-2);
      else if constexpr(Opts::contains(downward)) return T(0x1.45f306p-2);
      else                                         return T(0x1.45f306p-2);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.45f306dc9c883p-2);
      else if constexpr(Opts::contains(downward)) return T(0x1.45f306dc9c882p-2);
      else                                         return T(0x1.45f306dc9c883p-2);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(inv_pi_t, inv_pi_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var inv_pi
//!   @brief Callable object computing the constant \f$\frac{1}{\pi}\f$.
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
//!      T inv_pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::inv_pi(as<T>())` returns the inverse of \f$\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/inv_pi.cpp}
//! @}
//================================================================================================
inline constexpr auto inv_pi = functor<inv_pi_t>;
}
