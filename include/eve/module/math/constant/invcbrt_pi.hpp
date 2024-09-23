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
struct invcbrt_pi_t : constant_callable<invcbrt_pi_t, Options, lower_option, upper_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upper))        return T(0x1.5d95ep-1);
      else if constexpr(Opts::contains(lower)) return T(0x1.5d95dep-1);
      else                                         return T(0x1.5d95ep-1);
    }
    else
    {
      if constexpr(Opts::contains(upper))        return T(0x1.5d95df6bd2aeep-1);
      else if constexpr(Opts::contains(lower)) return T(0x1.5d95df6bd2aedp-1);
      else                                         return T(0x1.5d95df6bd2aeep-1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(invcbrt_pi_t, invcbrt_pi_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var invcbrt_pi
//!   @brief Callable object computing the constant \f$\pi^{-1/3}\f$.
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
//!      T invcbrt_pi(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::invcbrt_pi(as<T>())` returns  the inverse of the cubic root of \f$\pi\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/invcbrt_pi.cpp}
//! @}
//================================================================================================
inline constexpr auto invcbrt_pi = functor<invcbrt_pi_t>;
}
