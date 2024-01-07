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
struct egamma_t : constant_callable<egamma_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.2788dp-1 );
      else if constexpr(Opts::contains(downward2)) return T(0x1.2788cep-1);
      else                                         return T(0x1.2788dp-1 );
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.2788cfc6fb619p-1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.2788cfc6fb618p-1);
      else                                         return T(0x1.2788cfc6fb619p-1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(egamma_t, egamma_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var egamma
//!   @brief Callable object computing the Euler-Mascheroni constant : \f$\gamma =
//!   \lim_{n\to\infty}\left( \sum_{k = 0}^n \frac1k - \log n\right )\f$.
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
//!      T egamma(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::egamma(as<T>())` returns  \f$\gamma =
//!      \lim_{n\to\infty}\left( \sum_{k = 0}^n \frac1k - \log n\right )\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/egamma.cpp}
//! @}
//================================================================================================
inline constexpr auto egamma = functor<egamma_t>;
}
