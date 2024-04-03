//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once


#include "eve/traits/common_type.hpp"
#include "eve/traits/common_value.hpp"
#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
template<typename Options>
struct fma_t : elementwise_callable<fma_t, Options, pedantic_option, promote_option, regular_option>
{
  template<eve::value T,eve::value U,eve::value V>
  requires(Options::contains(promote2))
  constexpr EVE_FORCEINLINE auto operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

  template<eve::value T,eve::value U,eve::value V>
  requires(!Options::contains(promote2))
  constexpr EVE_FORCEINLINE
  common_value_t<T,U,V> operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

  EVE_CALLABLE_OBJECT(fma_t, fma_);
};

//======================================================================================================================
//! @addtogroup core_fma_family
//! @{
//!   @var fma
//!   @brief Computes the fused multiply add of its three parameters.
//!
//!   The call `fma(x, y, z)` is similar to `x*y+z` as if calculated to infinite precision
//!   and rounded once to fit the result as much as supported by the hardware.
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
//!      eve::common_value_t fma(T x, U y,  V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z` :  [real arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of `x*y+z` as if calculated to infinite precision
//!    and rounded once is returned,  but only if the hardware is in capacity
//!    to do it at reasonable cost.
//!
//!    @note
//!       This `fma` implementation provides those properties for all
//!       [integral real value](@ref eve::integral_value)
//!       and when possible for [floating real value](@ref eve::floating_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/fma.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fma[mask](x, ...)` provides a masked
//!     version of `fma` which is
//!     equivalent to `if_else(mask, fma(x, ...), x)`
//!
//!   * eve::pedantic, eve::numeric
//!
//!     * The call `pedantic(fma)(x,y,z)` ensures the one rounding property.
//!       This can be very expensive if the system has no hardware capability.
//!
//!     * The call `numeric(fma)(x,y,z)` ensures the full compliance to fma properties.
//!       This can be very expensive if the system has no hardware capability.
//! @}
//======================================================================================================================
inline constexpr auto fma = functor<fma_t>;
}

#include <eve/module/core/regular/impl/fma.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fma.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/fma.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/fma.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fma.hpp>
#endif
