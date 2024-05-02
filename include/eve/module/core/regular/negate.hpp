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
  struct negate_t : elementwise_callable<negate_t, Options, raw_option>
  {
    template<value T,  value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(negate_t, negate_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var negate
//!   @brief Computes the [elementwise](@ref glossary_elementwise) product of the first parameter
//!   by the sign of the second.
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
//!      eve::common_value_t<T, U> negate(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!   **Return value**
//!
//!      The [elementwise](@ref glossary_elementwise) product of the first parameter
//!      by the sign of the second is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/negate.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::negate[mask](x, ...)` provides a masked
//!     version of `negate` which is equivalent to `if_else(mask, negate(x, ...), x)`
//!
//! @}
//================================================================================================
 inline constexpr auto negate = functor<negate_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    negate_(EVE_REQUIRES(cpu_), O const &, T const &a,  T const &b) noexcept
    {
      if constexpr( signed_value<T> )
        return a * sign(b);
      else
        return if_else(is_nez(b), a, eve::zero);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/negate.hpp>
#endif
