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
#include <eve/module/core/regular/fnms.hpp>

namespace eve
{
  template<typename Options>
  struct fsnm_t : strict_elementwise_callable<fsnm_t, Options, pedantic_option, promote_option>
  {
    template<value T,  value U,  value V>
    requires(Options::contains(promote))
      constexpr EVE_FORCEINLINE auto operator()(T a, U b, V c) const
    { return EVE_DISPATCH_CALL(a, b, c); }

    template<eve::value T,eve::value U,eve::value V>
    requires(!Options::contains(promote))
    constexpr EVE_FORCEINLINE
    common_value_t<T,U,V> operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

    EVE_CALLABLE_OBJECT(fsnm_t, fsnm_);
  };

//================================================================================================
//! @addtogroup core_fma_family
//! @{
//!   @var fsnm
//!   @brief Computes the fused negate substact multiply of its three parameters.
//!
//!   The call `fsnm(x, y, z)` is similar to `-x-y*z` as if calculated to infinite precision
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
//!      eve::common_value_t fsnm(T x, U y,  V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z` :  [real arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of `-x-y*z` as if calculated to infinite precision
//!    and rounded once is returned,  but only if the hardware is in capacity
//!    to do it at reasonnable cost.
//!
//!    @note
//!       This `fsnm` implementation provides those properties for all
//!       [integral real value](@ref eve::integral_value)
//!       and when possible for [floating real value](@ref eve::floating_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/fsnm.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fsnm[mask](x, ...)` provides a masked
//!     version of `fsnm` which is
//!     equivalent to `if_else(mask, fsnm(x, ...), x)`
//!
//!   * eve::pedantic, eve::numeric
//!
//!       * The call `pedantic(fsnm)(x,y,z)` ensures the one rounding property.
//!       This can be very expensive if the system has no hardware capability.
//!
//! @}
//================================================================================================
  inline constexpr auto fsnm = functor<fsnm_t>;

  namespace detail
  {
    template<typename T, typename U, typename V, callable_options O>
    EVE_FORCEINLINE constexpr auto fsnm_(EVE_REQUIRES(cpu_), O const& o, T const& a, U const& b, V const& c)
    {
      return fnms[o](b, c, a);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fsnm.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fsnm.hpp>
#endif
