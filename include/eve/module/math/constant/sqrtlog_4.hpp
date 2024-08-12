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
struct sqrtlog_4_t : constant_callable<sqrtlog_4_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.2d6acp+0);
      else if constexpr(Opts::contains(downward)) return T(0x1.2d6abep+0);
      else                                         return T(0x1.2d6abep+0);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.2d6abe44afc44p+0);
      else if constexpr(Opts::contains(downward)) return T(0x1.2d6abe44afc43p+0);
      else                                         return T(0x1.2d6abe44afc43p+0);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(sqrtlog_4_t, sqrtlog_4_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var sqrtlog_4
//!   @brief Callable object computing the constant \f$\sqrt{\log4}\f$.
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
//!      T sqrtlog_4(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrtlog_4(as<T>())` returns the square root of \f$\log4\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sqrtlog_4.cpp}
//! @}
//================================================================================================
inline constexpr auto sqrtlog_4 = functor<sqrtlog_4_t>;
}
