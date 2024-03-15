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
  struct deginrad_t : elementwise_callable<deginrad_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(deginrad_t, deginrad_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var deginrad
//!
//! @brief Callable object multiplying the input by \f$\pi/180\f$.
//!
//!   **Defined in Header**
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
//!      template< eve::floating_value T >
//!      T deginrad(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) the degree input converted in radian.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/deginrad.cpp}
//!  @}
//================================================================================================
  inline constexpr auto deginrad = functor<deginrad_t>;

  namespace detail
  {
    template<floating_ordered_value T, callable_options O>
    EVE_FORCEINLINE constexpr T
    deginrad_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto ridh = ieee_constant<0x1.1de0000p-6f, 0x1.1df46a0000000p-6>(eve::as<T>{});
        auto ridl = ieee_constant<0x1.46a2520p-18f, 0x1.294e9c8ae0ec6p-33>(eve::as<T>{});
        return fma(a, ridl, a * ridh);
      }
      else return apply_over(deginrad, a);
    }
  }
}
