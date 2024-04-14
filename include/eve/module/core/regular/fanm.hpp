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
#include <eve/module/core/regular/fnma.hpp>


namespace eve
{
  template<typename Options>
  struct fanm_t : elementwise_callable<fanm_t, Options, pedantic_option, promote_option>
  {
    template<value T,  value U,  value V>
    constexpr EVE_FORCEINLINE common_value_t<T, U, V> operator()(T a, U b, V c) const
    { return EVE_DISPATCH_CALL(a, b, c); }

    EVE_CALLABLE_OBJECT(fanm_t, fanm_);
  };

//================================================================================================
//! @addtogroup core_fma_family
//! @{
//!   @var fanm
//!   @brief Computes the fused add negate multiply of its three parameters.
//!
//!   The call `fanm(x, y, z)` is similar to `x-y*z` as if calculated to infinite precision
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
//!      eve::common_value_t fanm(T x, U y,  V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z` :  [real arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of `x-y*z` as if calculated to infinite precision
//!    and rounded once is returned,  but only if the hardware is in capacity
//!    to do it at reasonable cost.
//!
//!    @note
//!       This `fanm` implementation provides those properties for all
//!       [integral real value](@ref eve::integral_value)
//!       and when possible for [floating real value](@ref eve::floating_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/fanm.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fanm[mask](x, ...)` provides a masked
//!     version of `fanm` which is
//!     equivalent to `if_else(mask, fanm(x, ...), x)`
//!
//!   * eve::pedantic, eve::numeric
//!
//!       * The call `pedantic(fanm)(x,y,z)` ensures the one rounding property.
//!       This can be very expensive if the system has no hardware capability.
//! @}
//================================================================================================
  inline constexpr auto fanm = functor<fanm_t>;

  namespace detail
  {
    template<typename T, typename U, typename V, callable_options O>
    EVE_FORCEINLINE constexpr auto fanm_(EVE_REQUIRES(cpu_), O const& o, T const& a, U const& b, V const& c)
    {
      return fnma[o](b, c, a);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fanm.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fanm.hpp>
#endif
