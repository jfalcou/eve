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
  struct minlog_t : constant_callable<minlog_t, Options, downward_option, upward_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
    {
      if constexpr(std::same_as<T, float>)
      {
        return T(-0x1.5d814ap+6);
      }
      else
      {
        return T(-0x1.6232bdd7abcd3p+9);
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(minlog_t, minlog_);
  };

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var minlog
//!   @brief Callable object computing the least value for which eve::exp is not zero
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
//!      T minlog(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::minlog(as<T>())` returns the least value for which eve::exp is not zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/minlog.cpp}
//! @}
//================================================================================================
inline constexpr auto minlog = functor<minlog_t>;
}
