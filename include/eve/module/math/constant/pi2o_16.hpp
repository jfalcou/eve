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
struct pi2o_16_t : constant_callable<pi2o_16_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.3bd3cep-1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.3bd3ccp-1);
      else                                         return T(0x1.3bd3ccp-1);
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.3bd3cc9be45dfp-1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.3bd3cc9be45dep-1);
      else                                         return T(0x1.3bd3cc9be45dep-1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(pi2o_16_t, pi2o_16_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var pi2o_16
//!   @brief Callable object computing the constant \f$\pi^2/16\f$.
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
//!      T pi2o_16(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::pi2o_16(as<T>())` returns  \f$\pi^2/16\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pi2o_16.cpp}
//! @}
//================================================================================================
inline constexpr auto pi2o_16 = functor<pi2o_16_t>;
}
