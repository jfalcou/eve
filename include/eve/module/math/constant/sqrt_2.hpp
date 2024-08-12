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
struct sqrt_2_t : constant_callable<sqrt_2_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.6a09e8p+0);
      else if constexpr(Opts::contains(downward)) return T(0x1.6a09e6p+0);
      else                                         return T(0x1.6a09e6p+0);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.6a09e667f3bcdp+0);
      else if constexpr(Opts::contains(downward)) return T(0x1.6a09e667f3bccp+0);
      else                                         return T(0x1.6a09e667f3bcdp+0);
    }
  }


  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(sqrt_2_t, sqrt_2_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var sqrt_2
//!   @brief Callable object computing the constant \f$\sqrt2\f$.
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
//!      T sqrt_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrt_2(as<T>())` returns the square root of 2.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sqrt_2.cpp}
//! @}
//================================================================================================
inline constexpr auto sqrt_2 = functor<sqrt_2_t>;
}
