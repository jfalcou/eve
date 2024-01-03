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
struct pio_4_t : constant_callable<pio_4_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.921fb6p-1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.921fb4p-1);
      else                                         return T(0x1.921fb6p-1);
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.921fb54442d19p-1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.921fb54442d18p-1);
      else                                         return T(0x1.921fb54442d18p-1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(pio_4_t, pio_4_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var pio_4
//!   @brief Callable object computing the constant \f$\pi/4\f$.
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
//!      T pio_4(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::pio_4(as<T>())` returns \f$\pi/4\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pio_4.cpp}
//! @}
//================================================================================================
inline constexpr auto pio_4 = functor<pio_4_t>;
}
