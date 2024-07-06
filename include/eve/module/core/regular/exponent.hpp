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

#include <eve/module/core/constant/mantissamask.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_not_finite.hpp>
#include <eve/module/core/regular/logical_not.hpp>
#include <eve/module/core/regular/logical_or.hpp>
#include <eve/arch/platform.hpp>

namespace eve
{

  template<typename Options>
  struct exponent_t : elementwise_callable<exponent_t, Options, raw_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE as_integer_t<T> operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(exponent_t, exponent_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var exponent
//!   @brief `elementwise_callable` object computing the integral IEEE exponent of the floating value.
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      constexpr auto exponent(floating_value auto x)       noexcept; // 1
//!
//!      // Semantic options
//!      constexpr auto exponent[raw](floating_value auto x)  noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!      1. The value of the IEEE exponent is returned. In particular:
//!        *  `inf`,  `minf` and `nan` return `maxexponent` plus 1
//!        *  zero returns zero
//!      2 identical except that results for zero, nan and infinite  inputs are unspecified
//!
//! @note
//!    *  The exponent \f$e\f$ and mantissa \f$m\f$ of a floating point entry \f$x\f$ are related by
//!       \f$x =  m\times 2^e\f$, with  \f$|m| \in \{0\} \cup [1, 2[\f$.
//!  @groupheader{Example}
//!  @godbolt{doc/core/exponent.cpp}
//! @}
//================================================================================================
  inline constexpr auto exponent = functor<exponent_t>;

  namespace detail
  {
    template<floating_value T, callable_options O>
    constexpr as_integer_t<T>  exponent_(EVE_REQUIRES(cpu_), O const&, T const& a) noexcept
    {
      auto z = bit_and(exponentmask(as<T>()), a);
      auto x = (z >> nbmantissabits(eve::as<T>()));
      return sub[is_nez(a)](x, maxexponent(eve::as<T>()));
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/exponent.hpp>
#endif
