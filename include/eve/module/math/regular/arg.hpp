//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>


namespace eve
{

  template<typename Options>
  struct arg_t : elementwise_callable<arg_t, Options, pedantic_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(arg_t, arg_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var arg
//!
//! @brief Callable object computing the phase angle (in radians).
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
//!      template< eve::floating_value T > T arg(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    `x`:   [real](@ref eve::floating_value) argument.
//!
//! **Return value**
//!
//!   Returns the [elementwise](@ref glossary_elementwise)
//!   the phase angle (in radians) of the input (0 or\f$\pi\f$).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/arg.cpp}
//!
//!  @}
//================================================================================================
inline constexpr auto arg = functor<arg_t>;
}


namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T
  arg_(EVE_REQUIRES(cpu_), O const & o, T a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto z = if_else(is_negative(a), pi(eve::as(a)), eve::zero);
      if constexpr( platform::supports_nans && O::contains(pedantic2))
        return if_else(is_nan(a), eve::allbits, z);
      else
        return z;
    }
    else
      return apply_over(arg[o], a);
  }
}
