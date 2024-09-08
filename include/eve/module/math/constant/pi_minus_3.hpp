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
struct pi_minus_3_t : constant_callable<pi_minus_3_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.21fb56p-3);
      else if constexpr(Opts::contains(downward)) return T(0x1.21fb54p-3);
      else                                         return T(0x1.21fb54p-3);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.21fb54442d185p-3);
      else if constexpr(Opts::contains(downward)) return T(0x1.21fb54442d184p-3);
      else                                         return T(0x1.21fb54442d184p-3);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(pi_minus_3_t, pi_minus_3_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var pi_minus_3
//!   @brief Callable object computing the constant \f$\pi-3\f$.
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
//!      T pi_minus_3(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::pi_minus_3(as<T>())` returns  \f$\pi-3\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pi_minus_3.cpp}
//! @}
//================================================================================================
inline constexpr auto pi_minus_3 = functor<pi_minus_3_t>;
}
