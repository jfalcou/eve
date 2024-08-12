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
struct log_10_t : constant_callable<log_10_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.26bb1cp+1);
      else if constexpr(Opts::contains(downward)) return T(0x1.26bb1ap+1);
      else                                         return T(0x1.26bb1cp+1);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.26bb1bbb55516p+1);
      else if constexpr(Opts::contains(downward)) return T(0x1.26bb1bbb55515p+1);
      else                                         return T(0x1.26bb1bbb55516p+1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(log_10_t, log_10_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var log_10
//!   @brief Callable object computing the constant \f$\log 10\f$.
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
//!      T log_10(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::log_10(as<T>())` returns \f$\log 10\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/log_10.cpp}
//! @}
//================================================================================================
inline constexpr auto log_10 = functor<log_10_t>;
}
