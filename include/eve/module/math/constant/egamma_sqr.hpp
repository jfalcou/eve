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
struct egamma_sqr_t : constant_callable<egamma_sqr_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.552c98p-2);
      else if constexpr(Opts::contains(downward)) return T(0x1.552c96p-2);
      else                                         return T(0x1.552c98p-2);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.552c97fa03696p-2);
      else if constexpr(Opts::contains(downward)) return T(0x1.552c97fa03695p-2);
      else                                         return T(0x1.552c97fa03695p-2);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(egamma_sqr_t, egamma_sqr_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var egamma_sqr
//!   @brief Callable object computing the square of the [Euler-Mascheroni constant](@ref
//!   eve::egamma).
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
//!      T egamma_sqr(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::egamma_sqr(as<T>())` returns the square of the [Euler-Mascheroni constant](@ref
//!      eve::egamma).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/egamma_sqr.cpp}
//! @}
//================================================================================================
inline constexpr auto egamma_sqr = functor<egamma_sqr_t>;
}
