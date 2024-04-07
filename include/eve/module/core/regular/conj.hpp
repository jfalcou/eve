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
struct conj_t : elementwise_callable<conj_t, Options>
{
  template<eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(conj_t, conj_);
};

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var conj
//!   @brief Computes the the conjugate value.
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
//!      template< eve::value T >
//!      T conj(T z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `z` :  [real](@ref eve::value) argument.
//!
//!   **Return value**
//!
//!     Returns the conjugate of its argument. For real inputs the call reduces to identity.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/conj.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::conj[mask](x)` provides a masked version of `eve::conj` which is
//!     equivalent to `if_else (mask, conj(x), x)`.
//!
//! @}
//================================================================================================
  inline constexpr auto conj = functor<conj_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T  conj_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      return v;
    }
  }
}
