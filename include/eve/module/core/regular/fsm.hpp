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
#include <eve/module/core/regular/fma.hpp>

namespace eve
{
template<typename Options>
struct fsm_t : strict_elementwise_callable<fsm_t, Options, pedantic_option, promote_option>
{
  template<eve::value T,eve::value U,eve::value V>
  requires(Options::contains(promote))
  constexpr EVE_FORCEINLINE auto operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

  template<eve::value T,eve::value U,eve::value V>
  requires(!Options::contains(promote))
  constexpr EVE_FORCEINLINE
  common_value_t<T,U,V> operator()(T a, U b, V c) const noexcept { return EVE_DISPATCH_CALL(a,b,c); }

  EVE_CALLABLE_OBJECT(fsm_t, fsm_);
};

//================================================================================================
//! @addtogroup core_fma_family
//! @{
//!   @var fsm
//!   @brief `strict_elementwise_callable` computing the fused add multiply of its three parameters.
//!
//!   @groupheader{Callable Signatures}
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
//!      constexpr auto fsm(value auto x, value auto y, value auto z)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto fsm[conditional_expr auto c](value auto x, value auto y, value auto z) noexcept; // 2
//!      constexpr auto fsm[logical_value auto m](value auto x, value auto y, value auto z)    noexcept; // 2
//!
//!      // Semantic option
//!      constexpr auto fsm[pedantic](value auto x, value auto y, value auto z)                noexcept; // 3
//!      constexpr auto fsm[promote](value auto x, value auto y, value auto z)                 noexcept; // 4
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
//!    1. The value of `-x+y*z` as if calculated to infinite precision
//!       and rounded once is returned,  but only if the hardware is in capacity
//!       to do it at reasonable cost.
//!    2. [The operation is performed conditionnaly](@ref conditional)
//!    3. `pedantic` option always ensures the full compliance to fsm properties. This can be very expensive if the system
//!       has no hardware capability.
//!    4. TO DO : DESCRIBE
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/special_functions/fma)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/fsm.cpp}
//================================================================================================
  inline constexpr auto fsm = functor<fsm_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, typename U, typename V, callable_options O>
    EVE_FORCEINLINE constexpr auto fsm_(EVE_REQUIRES(cpu_), O const& o, T const& a, U const& b, V const& c)
    {
      return fms[o](b, c, a);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fsm.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fsm.hpp>
#endif
