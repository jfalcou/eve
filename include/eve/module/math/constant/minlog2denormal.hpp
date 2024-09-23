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
struct minlog2denormal_t : constant_callable<minlog2denormal_t, Options, lower_option, upper_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
      return T(-0x1.2cp+7);
    else
      return T(-0x1.0cbffffffffffp+10);
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(minlog2denormal_t, minlog2denormal_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var minlog2denormal
//!   @brief Callable object computing the least value for which eve::exp2 is not denormal.
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
//!      T minlog2denormal(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::minlog2denormal(as<T>())` returns  the least value for which eve::exp2
//!      is not zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/minlog2denormal.cpp}
//! @}
//================================================================================================
inline constexpr auto minlog2denormal = functor<minlog2denormal_t>;
}
