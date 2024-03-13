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
  struct quadrant_t : elementwise_callable<quadrant_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(quadrant_t, quadrant_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var quadrant
//!
//! @brief Callable object computing the quadrant value.
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
//!      template< eve::value T >
//!      T quadrant(T n) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`n`:   [ordered integral value](@ref eve::ordered_value). Must be of  integral type or a [flint](@ref
//!eve::is_flint) value
//!
//! **Return value**
//!
//!    return a value of the same type as `n` containing the quadrant number where `n` (supposed an
//!    integer) lies.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/quadrant.cpp}
//!  @}
//================================================================================================
  inline constexpr auto quadrant = functor<quadrant_t>;

  namespace detail
  {

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    quadrant_(EVE_REQUIRES(cpu_), O const & o, T a) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        if constexpr( floating_value<T> )
        {
          T b = a * T(0.25);
          return (b - floor(b)) * T(4);
        }
        else
          return (a & T(3));
      }
      else return apply_over(quadrant, a);
    }
  }
}
