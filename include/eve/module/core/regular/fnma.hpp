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
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/detail/fmx_utils.hpp>


namespace eve
{
  template<typename Options>
  struct fnma_t : strict_elementwise_callable<fnma_t, Options, pedantic_option, promote_option,
                                             lower_option, upper_option, strict_option>
  {
    template<eve::value T, eve::value U, eve::value V>
    constexpr EVE_FORCEINLINE detail::fmx_promote_rt<T, U, V> operator()(T a, U b, V c) const noexcept
      requires (Options::contains(promote))
    {
      return this->behavior(as<detail::fmx_promote_rt<T, U, V>>{}, eve::current_api, this->options(), a, b, c);
    }

    template<eve::value T, eve::value U, eve::value V>
    constexpr EVE_FORCEINLINE common_value_t<T, U, V> operator()(T a, U b, V c) const noexcept
      requires (!Options::contains(promote))
    {
      return this->behavior(as<common_value_t<T, U, V>>{}, eve::current_api, this->options(), a, b, c);
    }

    EVE_CALLABLE_OBJECT(fnma_t, fnma_);
  };


//================================================================================================
//! @addtogroup core_fnma_family
//! @{
//!   @var fnma
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
//!      constexpr auto fnma(value auto x, value auto y, value auto z)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto fnma[conditional_expr auto c](value auto x, value auto y, value auto z) noexcept; // 2
//!      constexpr auto fnma[logical_value auto m](value auto x, value auto y, value auto z)    noexcept; // 2
//!
//!      // Semantic option
//!      constexpr auto fnma[pedantic](value auto x, value auto y, value auto z)                noexcept; // 3
//!      constexpr auto fnma[promote](value auto x, value auto y, value auto z)                 noexcept; // 4
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
//!      1. The value of `-x*y+z` as if calculated to infinite precision
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
//!  @godbolt{doc/core/fnma.cpp}
//================================================================================================
  inline constexpr auto fnma = functor<fnma_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, typename U, typename V, callable_options O>
    EVE_FORCEINLINE constexpr auto fnma_(EVE_REQUIRES(cpu_), O const& o, T const& a, U const& b, V const& c)
    {
      if constexpr(O::contains(promote))
      {
        using er_t = common_type_t<element_type_t<T>, element_type_t<U>, element_type_t<V>>;
        constexpr auto tgt = as{as<er_t>{}};
        return fma[o.drop(promote)](minus(convert(a, tgt)), convert(b, tgt), convert(c,tgt));
      }
      else
      {
        using r_t = common_value_t<T, U, V>;
        return fma[o](minus(r_t(a)), r_t(b), r_t(c));
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fnma.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/fnma.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fnma.hpp>
#endif
