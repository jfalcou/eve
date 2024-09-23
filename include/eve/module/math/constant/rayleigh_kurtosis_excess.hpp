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
struct rayleigh_kurtosis_excess_t : constant_callable<rayleigh_kurtosis_excess_t, Options, lower_option, upper_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upper))        return T(0x1.f5f162p-3);
      else if constexpr(Opts::contains(lower)) return T(0x1.f5f16p-3);
      else                                         return T(0x1.f5f162p-3);
    }
    else
    {
      if constexpr(Opts::contains(upper))        return T(0x1.f5f161186c5f2p-3);
      else if constexpr(Opts::contains(lower)) return T(0x1.f5f161186c5f1p-3);
      else                                         return T(0x1.f5f161186c5f2p-3);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(rayleigh_kurtosis_excess_t, rayleigh_kurtosis_excess_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var rayleigh_kurtosis_excess
//!   @brief Callable object computing the Rayleigh kurtosis excess value :
//!   \f$-(6\pi^2-24\pi+16)/(4-\pi^2)\f$.
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
//!      T rayleigh_kurtosis_excess(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::rayleigh_kurtosis_excess(as<T>())` returns the Rayleigh kurtosis excess value?
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/rayleigh_kurtosis_excess.cpp}
//! @}
//================================================================================================
inline constexpr auto rayleigh_kurtosis_excess = functor<rayleigh_kurtosis_excess_t>;
}
