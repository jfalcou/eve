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
struct pi3_t : constant_callable<pi3_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.f019b6p+4);
      else if constexpr(Opts::contains(downward2)) return T(0x1.f019b4p+4);
      else                                         return T(0x1.f019b6p+4);
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.f019b59389d7dp+4);
      else if constexpr(Opts::contains(downward2)) return T(0x1.f019b59389d7cp+4);
      else                                         return T(0x1.f019b59389d7cp+4);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(pi3_t, pi3_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var pi3
//!   @brief Callable object computing the pi cubed value : \f$\pi^3\f$.
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
//!      T pi3(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::pi3(as<T>())` returns  \f$\pi^3\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pi3.cpp}
//! @}
//================================================================================================
inline constexpr auto pi3 = functor<pi3_t>;
}
