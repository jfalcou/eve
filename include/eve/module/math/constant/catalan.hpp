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
struct catalan_t : constant_callable<catalan_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.d4f972p-1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.d4f97p-1);
      else                                         return T(0x1.d4f972p-1);
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.d4f9713e8135ep-1);
      else if constexpr(Opts::contains(downward2)) return T(0x1.d4f9713e8135dp-1);
      else                                         return T(0x1.d4f9713e8135dp-1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(catalan_t, catalan_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var catalan
//!   @brief Callable object computing the catalan constant \f$\beta(2) = \sum_0^\infty
//!   \frac{(-1)^n}{(2n+1)^2}\f$.
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
//!      T catalan(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::catalan(as<T>())` returns  the catalan constant \f$\beta(2) = \sum_0^\infty
//!      \frac{(-1)^n}{(2n+1)^2}\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/catalan.cpp}
//! @}
//================================================================================================
inline constexpr auto catalan = functor<catalan_t>;
}
