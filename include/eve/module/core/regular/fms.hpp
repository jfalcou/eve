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
  struct fms_t : strict_elementwise_callable<fms_t, Options, pedantic_option, promote_option,
                                             upper_option, lower_option, strict_option>
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
//!   @brief `strict_elementwise_callable` computing the fused  multiply substract of its three parameters.
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto fms(value auto x, value auto y, value auto z)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto fms[conditional_expr auto c](value auto x, value auto y, value auto z) noexcept; // 2
//!      constexpr auto fms[logical_value auto m](value auto x, value auto y, value auto z)    noexcept; // 2
//!
//!      // Semantic option
//!      constexpr auto fms[pedantic](value auto x, value auto y, value auto z)                noexcept; // 3
//!      constexpr auto fms[promote](value auto x, value auto y, value auto z)                 noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z` : [values](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of `x*y-z` as if calculated to infinite precision
//!         and rounded once is returned,  but only if the hardware is in capacity
//!         to do it at reasonable cost.
//!      2. [The operation is performed conditionnaly](@ref conditional)
//!      3. `pedantic` option always ensures the full compliance to fam properties. This can be very expensive if the system
//!         has no hardware capability.
//!      4. The operation is performed as if the parameters where promoted to the common type of the three parameters.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/special_functions/fma)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/fma.cpp}
//================================================================================================
  inline constexpr auto fms = functor<fms_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/fms.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fms.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/fms.hpp>
#endif


#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/fms.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fms.hpp>
#endif
