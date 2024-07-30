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
#include <eve/module/core.hpp>

namespace eve
{
  template<typename Options>
  struct div_180_t : elementwise_callable<div_180_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(div_180_t, div_180_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var div_180
//!
//! @brief `elementwise_callable` object computing the product of the input by \f$1/180\f$.
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto div_180(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto div_180[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto div_180[logical_floating_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating_value](@ref value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. Returns the [elementwise](@ref glossary_elementwise) the  input divided by 180.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/div_180.cpp}
//!  @}
//================================================================================================
  inline constexpr auto div_180 = functor<div_180_t>;
//================================================================================================
//================================================================================================


  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T div_180_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      auto test = is_nez(a);
      if constexpr( scalar_value<T> )
      {
        if( !test ) return a;
      }
      using elt_t = element_type_t<T>;
      if constexpr( std::is_same_v<elt_t, double> )
      {
        const T Ch = T(5.5555555555555557675773137304986448725685477256775e-3);
        const T Cl = T(2.12021758174943082362265970771770243087787985109985e-19);
        T c  = Cl * a;
        return fma[test](a, Ch, c);
      }
      else { return convert(div_180(convert(a, as<double>())), as<float>()); }
    }
  }
}
