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
struct pi_pow_e_t : constant_callable<pi_pow_e_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.6758b6p+4);
      else if constexpr(Opts::contains(downward2)) return T(0x1.6758b4p+4);
      else                                         return T(0x1.6758b6p+4);
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.6758b5c381112p+4);
      else if constexpr(Opts::contains(downward2)) return T(0x1.6758b5c381111p+4);
      else                                         return T(0x1.6758b5c381111p+4);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(pi_pow_e_t, pi_pow_e_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var pi_pow_e
//!   @brief Callable object computing the constant \f$\pi^e\f$.
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
//!      T pi_pow_e(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::pi_pow_e(as<T>())` returns  \f$\pi^e\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pi_pow_e.cpp}
//! @}
//================================================================================================
inline constexpr auto pi_pow_e = functor<pi_pow_e_t>;
}
