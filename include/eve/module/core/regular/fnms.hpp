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
#include <eve/module/core/regular/minus.hpp>

namespace eve
{
  template<typename Options>
  struct fnms_t : strict_elementwise_callable<fnms_t, Options, pedantic_option, promote_option>
  {
    template<eve::value T,eve::value U,eve::value V>
    requires(Options::contains(promote))
      constexpr EVE_FORCEINLINE auto operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

    template<eve::value T,eve::value U,eve::value V>
    requires(!Options::contains(promote))
      constexpr EVE_FORCEINLINE
    common_value_t<T,U,V> operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

    EVE_CALLABLE_OBJECT(fnms_t, fnms_);
  };

//================================================================================================
//! @addtogroup core_fma_family
//! @{
//!   @var fnms
//!   @brief Computes the fused  negate multiply substract of its three parameters.
//!
//!   The call `fnms(x, y, z)` is similar to `-x*y-z` as if calculated to infinite precision
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
//!      eve::common_value_t fnms(T x, U y,  V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z` :  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of `-x*y-z` as if calculated to infinite precision
//!    and rounded once is returned,  but only if the hardware is in capacity
//!    to do it at reasonable cost.
//!
//!    @note
//!       This `fnms` implementation provides those properties for all
//!       [integral real value](@ref eve::integral_value)
//!       and when possible for [floating real value](@ref eve::floating_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/fnms.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::fnms[mask](x, ...)` provides a masked
//!     version of `fnms` which is
//!     equivalent to `if_else(mask, fnms(x, ...), x)`
//!
//!   * eve::pedantic
//!
//!       * The call `fnms[pedantic](x,y,z)` ensures  the full compliance to fms properties.
//!       This can be very expensive if the system has no hardware capability.
//!
//! @}
//================================================================================================
 inline constexpr auto fnms = functor<fnms_t>;

  namespace detail
  {

    template<typename T, typename U, typename V, callable_options O>
    EVE_FORCEINLINE constexpr auto fnms_(EVE_REQUIRES(cpu_), O const& o, T const& a, U const& b, V const& c)
    {
      return minus(fma[o](a, b, c));
    }

  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fnms.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fnms.hpp>
#endif
