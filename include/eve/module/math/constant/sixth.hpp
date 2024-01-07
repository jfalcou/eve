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
struct sixth_t : constant_callable<sixth_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.555556p-3);
      else if constexpr(Opts::contains(downward2)) return T(0x1.555554p-3);
      else                                         return T(0x1.555556p-3);
    }
    else
    {
      if constexpr(Opts::contains(upward2))        return T(0x1.5555555555556p-3);
      else if constexpr(Opts::contains(downward2)) return T(0x1.5555555555555p-3);
      else                                         return T(0x1.5555555555555p-3);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(sixth_t, sixth_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var sixth
//!   @brief Callable object computing the constant \f$1/6\f$.
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
//!      T sixth(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sixth(as<T>())` returns  \f$1/6\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sixth.cpp}
//! @}
//================================================================================================
inline constexpr auto sixth = functor<sixth_t>;
}
