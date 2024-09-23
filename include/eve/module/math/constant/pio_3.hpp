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
struct pio_3_t : constant_callable<pio_3_t, Options, lower_option, upper_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upper))        return T(0x1.0c1524p+0);
      else if constexpr(Opts::contains(lower)) return T(0x1.0c1522p+0);
      else                                         return T(0x1.0c1524p+0);
    }
    else
    {
      if constexpr(Opts::contains(upper))        return T(0x1.0c152382d7366p+0);
      else if constexpr(Opts::contains(lower)) return T(0x1.0c152382d7365p+0);
      else                                         return T(0x1.0c152382d7366p+0);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(pio_3_t, pio_3_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var pio_3
//!   @brief Callable object computing the constant \f$\pi/3\f$.
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
//!      T pio_3(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::pio_3(as<T>())` returns \f$\pi/3\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pio_3.cpp}
//! @}
//================================================================================================
inline constexpr auto pio_3 = functor<pio_3_t>;
}
