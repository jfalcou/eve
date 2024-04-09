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
  struct trunc_t : elementwise_callable<trunc_t, Options, tolerant_option, raw_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    {
      static_assert( valid_tolerance<T, Options>::value, "[eve::trunc] simd tolerance requires simd parameter." );
      return EVE_DISPATCH_CALL(v);
    }

    template<eve::value T, only_if<signed,unsigned>  U>
    constexpr EVE_FORCEINLINE  as_integer_t<T, U> operator()(T v,  as<U> const & target) const noexcept
    {
      static_assert( valid_tolerance<T, Options>::value, "[eve::trunc] simd tolerance requires simd parameter." );
      return EVE_DISPATCH_CALL(v, target);
    }

    EVE_CALLABLE_OBJECT(trunc_t, trunc_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var trunc
//!   @brief Computes  the integral part of `x` with the same sign as  `x`.
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
//!      T trunc(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!   **Return value**
//!
//!     The integral part of `x` with the same sign as  `x`.
//!
//!
//!     The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`,
//!     `FE_TOWARDZERO`. This function object implements the `FE_TOWARDZERO` version.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/trunc.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::trunc[mask](x)` provides a masked version of `eve::trunc` which is
//!     equivalent to `if_else (mask, trunc(x), x)`.
//!
//!   * eve::tolerant
//!
//!     The expression `trunc[tolerance = tol](x)` computes a tolerant truncated
//!     value for `x`, where `x` must be a floating value.
//!
//!        * If `tol` is a floating_value computes the truncation with
//!          a tolerance `tol` using Hagerty's FL5 function.
//!        * If `tol` is an integral_value n compute the truncation of
//!          the next or previous nth representable value in the `x` type.
//!        * the call `trunc[tolerant](x)` takes tol as  3 times
//!          the machine \f$\epsilon\f$ in the `x` type (`3*eps(as(x))`).
//!        * if t is an simd value x must be an simd value
//!
//! @}
//================================================================================================
  inline constexpr auto trunc = functor<trunc_t>;
}

#include <eve/module/core/regular/impl/trunc.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/trunc.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/trunc.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/trunc.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/trunc.hpp>
#endif
