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
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/next.hpp>

namespace eve
{
  template<typename Options>
  struct epsilon_t : elementwise_callable<epsilon_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const noexcept
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(epsilon_t, epsilon_);
  };

//================================================================================================
//! @addtogroup core_fma_internal
//! @{
//!   @var epsilon
//!   @brief Computes The distance of abs(x) to the next representable element of type T
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
//!      template< eve::value T > T epsilon(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The distance of abs(x) to the next representable element of type T
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/epsilon.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::epsilon[mask](x, ...)` provides a masked
//!     version of `epsilon` which is
//!     equivalent to `if_else(mask, epsilon(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto epsilon = functor<epsilon_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto epsilon_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      auto aa = abs(a0);
      return dist[is_not_nan(a0)](aa, next(aa));
    }
  }
}
