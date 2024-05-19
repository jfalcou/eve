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
  struct fms_t : strict_elementwise_callable<fms_t, Options, pedantic_option, promote_option>
  {
    template<eve::value T,eve::value U,eve::value V>
    requires(Options::contains(promote))
    constexpr EVE_FORCEINLINE auto operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

    template<eve::value T,eve::value U,eve::value V>
    requires(!Options::contains(promote))
    constexpr EVE_FORCEINLINE
    common_value_t<T,U,V> operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

    EVE_CALLABLE_OBJECT(fms_t, fms_);
  };

  //================================================================================================
  //! @addtogroup core_fma_family
  //! @{
  //!   @var fms
  //!   @brief Computes the fused  multiply substract of its three parameters.
  //!
  //!   The call `fms(x, y, z)` is similar to `x*y-z` as if calculated to infinite precision
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
  //!      eve::common_value_t fms(T x, U y,  V z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`, `z` :  [real arguments](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!    The value of `x*y-z` as if calculated to infinite precision
  //!    and rounded once is returned,  but only if the hardware is in capacity
  //!    to do it at reasonable cost.
  //!
  //!    @note
  //!       This `fms` implementation provides those properties for all
  //!       [integral real value](@ref eve::integral_value)
  //!       and when possible for [floating real value](@ref eve::floating_value).
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/fms.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::fms[mask](x, ...)` provides a masked
  //!     version of `fms` which is
  //!     equivalent to `if_else(mask, fms(x, ...), x)`
  //!
  //!   * eve::pedantic, eve::numeric
  //!
  //!       * The call `fms[pedantic](x,y,z)` ensures the full compliance to fms properties.
  //!       This can be very expensive if the system has no hardware capability.
  //!
  //!   * eve::promote
  //!
  //!     * The call `fms[promote](x,y,z)`promotes all arguments to their common value type
  //!       before computing fma.
  //!
  //! @}
  //================================================================================================
    inline constexpr auto fms = functor<fms_t>;
}

#include <eve/module/core/regular/impl/fms.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fms.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fms.hpp>
#endif
