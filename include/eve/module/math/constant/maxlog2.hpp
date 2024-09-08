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
struct maxlog2_t : constant_callable<maxlog2_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      return T(0x1.fcp+6);
    }
    else
    {
      return T(0x1.ff8p+9);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(maxlog2_t, maxlog2_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var maxlog2
//!   @brief Callable object computing the greatest positive value for which eve::exp2 is finite.
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
//!      T maxlog2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::maxlog2(as<T>())` returns the greatest positive value for which
//!      eve::exp2 is finite.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/maxlog2.cpp}
//! @}
//================================================================================================
inline constexpr auto maxlog2 = functor<maxlog2_t>;
}
