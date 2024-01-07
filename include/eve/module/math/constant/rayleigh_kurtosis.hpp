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
struct rayleigh_kurtosis_t : constant_callable<rayleigh_kurtosis_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.9f5f18p+1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.9f5f16p+1);
      else                                         return T(0x1.9f5f16p+1);
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.9f5f161186c6p+1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.9f5f161186c5fp+1);
      else                                         return T(0x1.9f5f161186c5fp+1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(rayleigh_kurtosis_t, rayleigh_kurtosis_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var rayleigh_kurtosis
//!   @brief Callable object computing the Rayleigh kurtosis value :
//!   \f$3+(6\pi^2-24\pi+16)/(4-\pi^2)\f$.
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
//!      T rayleigh_kurtosis(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::rayleigh_kurtosis(as<T>())` returns the Rayleigh kurtosis value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/rayleigh_kurtosis.cpp}
//! @}
//================================================================================================
inline constexpr auto rayleigh_kurtosis = functor<rayleigh_kurtosis_t>;
}
