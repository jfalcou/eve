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
struct pio_2_t : constant_callable<pio_2_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.921fb6p+0);
      else if constexpr(Opts::contains(downward)) return T(0x1.921fb4p+0);
      else                                         return T(0x1.921fb6p+0);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.921fb54442d19p+0);
      else if constexpr(Opts::contains(downward)) return T(0x1.921fb54442d18p+0);
      else                                         return T(0x1.921fb54442d18p+0);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(pio_2_t, pio_2_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var pio_2
//!   @brief Callable object computing the constant \f$\pi/2\f$.
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
//!      T pio_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::pio_2(as<T>())` returns  \f$\pi/2\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pio_2.cpp}
//! @}
//================================================================================================
inline constexpr auto pio_2 = functor<pio_2_t>;
}
