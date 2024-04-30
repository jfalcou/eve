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
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve
{
 template<typename Options>
  struct reldist_t : elementwise_callable<reldist_t, Options, saturated_option,  pedantic_option>
  {
    template<value T,  value U>
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T a, U b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(reldist_t, reldist_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var reldist
//!   @brief Computes the relative distance of its arguments.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T, eve::value U >
//!      eve::common_value_t<T, U> reldist(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :   [real](@ref eve::floating_value) arguments.
//!
//!    **Return value**
//!
//!    The value of the relative distance of the arguments is returned,  i.e. `eve::abs (x-y)/max(abs(x), abs(y), 1)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/reldist.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto reldist = functor<reldist_t>;

  namespace detail
  {
    template<value T, callable_options O>
    constexpr T reldist_(EVE_REQUIRES(cpu_), O const&, T a, T b)
    {
      return dist(a, b)/max(abs(a), abs(b), one(as(a)));
    }
  }
}
