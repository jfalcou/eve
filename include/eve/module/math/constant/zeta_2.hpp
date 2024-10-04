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
struct zeta_2_t : constant_callable<zeta_2_t, Options, lower_option, upper_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upper))        return T{0x1.a51a68p+0};
      else if constexpr(Opts::contains(lower)) return T{0x1.a51a66p+0};
      else                                         return T{0x1.a51a66p+0};
    }
    else
    {
      if constexpr(Opts::contains(upper))        return T{0x1.a51a6625307d4p+0};
      else if constexpr(Opts::contains(lower)) return T{0x1.a51a6625307d3p+0};
      else                                         return T{0x1.a51a6625307d3p+0};
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(zeta_2_t, zeta_2_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var zeta_2
//!   @brief Callable object computing the constant \f$\zeta(2)\f$.
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
//!      T zeta_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::zeta_2(as<T>())` returns  \f$\zeta(2)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/zeta_2.cpp}
//! @}
//================================================================================================
inline constexpr auto zeta_2 = functor<zeta_2_t>;
}
