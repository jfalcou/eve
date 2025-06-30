//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/detail/fmx_utils.hpp>

namespace eve
{
  template<typename Options>
  struct fma_t : strict_elementwise_callable<fma_t, Options, pedantic_option, promote_option,
                                             raw_option, lower_option, upper_option, strict_option>
  {
    template<eve::value T,eve::value U,eve::value V>
    requires(Options::contains(promote))
    constexpr EVE_FORCEINLINE
    detail::fmx_common_promote_t<T, U, V> operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

    template<eve::value T,eve::value U,eve::value V>
    requires(!Options::contains(promote))
    constexpr EVE_FORCEINLINE
    common_value_t<T,U,V> operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

    EVE_CALLABLE_OBJECT(fma_t, fma_);
  };

//================================================================================================
//! @addtogroup core_fma_family
//! @{
//!   @var fma
//!   @brief `strict_elementwise_callable` computing the fused multiply add of its three parameters.
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
//!      constexpr auto fma(value auto x, value auto y, value auto z)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto fma[conditional_expr auto c](value auto x, value auto y, value auto z) noexcept; // 2
//!      constexpr auto fma[logical_value auto m](value auto x, value auto y, value auto z)    noexcept; // 2
//!
//!      // Semantic option
//!      constexpr auto fma[pedantic](value auto x, value auto y, value auto z)                noexcept; // 3
//!      constexpr auto fma[promote](value auto x, value auto y, value auto z)                 noexcept; // 4
//!      constexpr auto add[lower](value auto x, value auto y, value auto z)                   noexcept; // 5
//!      constexpr auto add[upper](value auto x, value auto y, value auto z)                   noexcept; // 6
//!      constexpr auto fma[lower][srict](value auto x, value auto y, value auto z)            noexcept; // 5
//!      constexpr auto fma[upper][srict](value auto x, value auto y, value auto z)            noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z` : [values](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of `x*y+z` as if calculated to infinite precision
//!         and rounded once is returned,  but only if the hardware is in capacity
//!         to do it at reasonable cost.
//!      2. [The operation is performed conditionnaly](@ref conditional)
//!      3. `pedantic` option always ensures the full compliance to fam properties. This can be very expensive if the system
//!         has no hardware capability.
//!      4. The operation is performed as if the parameters where promoted to the common type of the three parameters.
//!      5. The operation is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!         to be less or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!      6. The operation is computed in a 'round toward \f$\infty\f$ mode. The result is guaranted
//!         to be greater or equal to the exact one (except for Nans). Combined with `strict` the option
//!       ensures generally faster computation, but strict inequality.
//!
//!  @note
//!    *  `lower`and `upper` can be associated with raw to provide a correct,
//!       faster but less accurate version
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/special_functions/fma)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/fma.cpp}
//================================================================================================
  inline constexpr auto fma = functor<fma_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/fma.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fma.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/fma.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/fma.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fma.hpp>
#endif
