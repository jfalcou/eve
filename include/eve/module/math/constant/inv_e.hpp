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
struct inv_e_t : constant_callable<inv_e_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.78b564p-2);
      else if constexpr(Opts::contains(downward2)) return T(0x1.78b562p-2);
      else                                         return T(0x1.78b564p-2);
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.78b56362cef38p-2);
      else if constexpr(Opts::contains(downward2)) return T(0x1.78b56362cef37p-2);
      else                                         return T(0x1.78b56362cef38p-2);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(inv_e_t, inv_e_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var inv_e
//!   @brief Callable object computing the constant \f$e^{-1}\f$.
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
//!      T inv_e(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::inv_e(as<T>())` returns athe inverse of the basis of the natural logarithms.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/inv_e.cpp}
//! @}
//================================================================================================
inline constexpr auto inv_e = functor<inv_e_t>;
}
