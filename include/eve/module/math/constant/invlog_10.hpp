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
struct invlog_10_t : constant_callable<invlog_10_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.bcb7b2p-2);
      else if constexpr(Opts::contains(downward)) return T(0x1.bcb7bp-2 );
      else                                         return T(0x1.bcb7b2p-2);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.bcb7b1526e50fp-2);
      else if constexpr(Opts::contains(downward)) return T(0x1.bcb7b1526e50ep-2);
      else                                         return T(0x1.bcb7b1526e50ep-2);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(invlog_10_t, invlog_10_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var invlog_10
//!   @brief Callable object computing \f$1/\log10\f$.
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
//!      T invlog_10(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::invlog_10(as<T>())` returns the inverse of \f$\log10\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/invlog_10.cpp}
//! @}
//================================================================================================
inline constexpr auto invlog_10 = functor<invlog_10_t>;
}
