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
struct log_2_t : constant_callable<log_2_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.62e43p-1 );
      else if constexpr(Opts::contains(downward)) return T(0x1.62e42ep-1);
      else                                         return T(0x1.62e43p-1 );
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.62e42fefa39fp-1 );
      else if constexpr(Opts::contains(downward)) return T(0x1.62e42fefa39efp-1);
      else                                         return T(0x1.62e42fefa39efp-1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(log_2_t, log_2_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var log_2
//!   @brief Callable object computing the constant \f$\log 2\f$.
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
//!      T log_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::log_2(as<T>())` returns \f$\log 2\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/log_2.cpp}
//! @}
//================================================================================================
inline constexpr auto log_2 = functor<log_2_t>;
}
