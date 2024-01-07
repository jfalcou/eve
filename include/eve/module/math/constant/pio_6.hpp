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
struct pio_6_t : constant_callable<pio_6_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.0c1524p-1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.0c1522p-1);
      else                                         return T(0x1.0c1524p-1);
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.0c152382d7366p-1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.0c152382d7365p-1);
      else                                         return T(0x1.0c152382d7366p-1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(pio_6_t, pio_6_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var pio_6
//!   @brief Callable object computing the constant \f$\pi/6\f$.
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
//!      T pio_6(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::pio_6(as<T>())` returns  \f$\pi/6\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pio_6.cpp}
//! @}
//================================================================================================
inline constexpr auto pio_6 = functor<pio_6_t>;
}
