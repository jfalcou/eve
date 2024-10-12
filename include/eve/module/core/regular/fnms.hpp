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
  struct fnms_t : strict_elementwise_callable<fnms_t, Options, pedantic_option, promote_option,
                                             lower_option, upper_option, strict_option>
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
//!      constexpr auto fnms(value auto x, value auto y, value auto z)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto fnms[conditional_expr auto c](value auto x, value auto y, value auto z) noexcept; // 2
//!      constexpr auto fnms[logical_value auto m](value auto x, value auto y, value auto z)    noexcept; // 2
//!
//!      // Semantic option
//!      constexpr auto fnms[pedantic](value auto x, value auto y, value auto z)                noexcept; // 3
//!      constexpr auto fnms[promote](value auto x, value auto y, value auto z)                 noexcept; // 4
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
//!      1. The value of `-x*y-z` as if calculated to infinite precision
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
//!  @godbolt{doc/core/fnms.cpp}
//================================================================================================
  inline constexpr auto fnms = functor<fnms_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<typename T, typename U, typename V, callable_options O>
    EVE_FORCEINLINE constexpr auto fnms_(EVE_REQUIRES(cpu_), O const& o, T const& a, U const& b, V const& c)
    {
      if constexpr(O::contains(upper) || O::contains(lower))
      {
        return fma[o](a, minus(b), minus(c));
      }
      else return minus(fma[o](a, b, c));
    }

  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fnms.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fnms.hpp>
#endif
