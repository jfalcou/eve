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
#include <eve/module/core/detail/fmx_utils.hpp>

namespace eve
{
  template<typename Options>
  struct fsnm_t : strict_elementwise_callable<fsnm_t, Options, pedantic_option, promote_option,
                                             lower_option, upper_option, strict_option>
  {
    template<value T, value U, value V>
    constexpr EVE_FORCEINLINE detail::fmx_promote_rt<T, U, V> operator()(T a, U b, V c) const
      requires (Options::contains(promote))
    {
      return EVE_DISPATCH_CALL_PT((detail::fmx_promote_rt<T, U, V>), a, b, c);
    }

    template<value T, value U, value V>
    constexpr EVE_FORCEINLINE common_value_t<T, U, V> operator()(T a, U b, V c) const noexcept
      requires (!Options::contains(promote))
    {
      return EVE_DISPATCH_CALL_PT((common_value_t<T, U, V>), a, b, c);
    }

    EVE_CALLABLE_OBJECT(fsnm_t, fsnm_);
  };

  //================================================================================================
  //! @addtogroup core_fma_family
  //! @{
  //!   @var fsnm
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
  //!      constexpr auto fsnm(value auto x, value auto y, value auto z)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto fsnm[conditional_expr auto c](value auto x, value auto y, value auto z) noexcept; // 2
  //!      constexpr auto fsnm[logical_value auto m](value auto x, value auto y, value auto z)    noexcept; // 2
  //!
  //!      // Semantic option
  //!      constexpr auto fsnm[pedantic](value auto x, value auto y, value auto z)                noexcept; // 3
  //!      constexpr auto fsnm[promote](value auto x, value auto y, value auto z)                 noexcept; // 4
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
  //!    1. The value of `-x-y*z` as if calculated to infinite precision
  //!       and rounded once is returned,  but only if the hardware is in capacity
  //!       to do it at reasonable cost.
  //!    2. [The operation is performed conditionnaly](@ref conditional)
  //!    3. `pedantic` option always ensures the full compliance to fsnm properties. This can be very expensive if the system
  //!       has no hardware capability.
  //!    4. The operation is performed as if the parameters where promoted to the common type of the three parameters.
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/special_functions/fma)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/fsnm.cpp}
  //================================================================================================
  inline constexpr auto fsnm = functor<fsnm_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T, typename U, typename V>
    EVE_FORCEINLINE constexpr auto fsnm_(EVE_REQUIRES(cpu_), O const& o, T const& a, U const& b, V const& c)
    {
      return fnms[o](b, c, a);
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/fsnm.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/fsnm.hpp>
#endif
