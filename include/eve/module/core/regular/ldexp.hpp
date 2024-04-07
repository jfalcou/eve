//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/regular/is_flint.hpp>

namespace eve
{
template<typename Options>
struct ldexp_t : elementwise_callable<ldexp_t, Options, pedantic_option>
{
  template<eve::floating_ordered_value T, eve::value U>
  constexpr EVE_FORCEINLINE as_wide_as_t<T,U> operator()(T x, U n) const
  {
    return EVE_DISPATCH_CALL(x,n);
  }

  EVE_CALLABLE_OBJECT(ldexp_t, ldexp_);
};
//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var ldexp
//!   @brief Computes \f$\textstyle x 2^n\f$.
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
//!      template< eve::value T, eve::integral_value N >
//!      eve::common_value_t<T, N> ldexp(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [real argument](@ref eve::floating_value).
//!
//!     * `n` :  [integral value argument](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!    The value of \f$\textstyle x 2^n\f$ is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/ldexp.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::ldexp[mask](x, n)` computes a value equivalent to `if_else(mask, ldexp(x, n), x)`
//!
//!   * eve::pedantic
//!
//!     The call `eve::ldexp[pedantic](x,n)` computes `eve::ldexp` but takes extra care to handling limit values.
//! @}
//================================================================================================
inline constexpr auto ldexp = functor<ldexp_t>;
}

#include <eve/module/core/regular/impl/ldexp.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/ldexp.hpp>
#endif
