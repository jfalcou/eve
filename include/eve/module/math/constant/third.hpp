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
struct third_t : constant_callable<third_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.555556p-2);
      else if constexpr(Opts::contains(downward)) return T(0x1.555554p-2);
      else                                         return T(0x1.555556p-2);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.5555555555556p-2);
      else if constexpr(Opts::contains(downward)) return T(0x1.5555555555555p-2);
      else                                         return T(0x1.5555555555555p-2);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(third_t, third_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var third
//!   @brief Callable object computing the constant \f$1/3\f$.
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
//!      T third(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::third(as<T>())` returns one third.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/third.cpp}
//! @}
//================================================================================================
inline constexpr auto third = functor<third_t>;
}
