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
#include <eve/module/special/regular/factorial.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>

namespace eve
{
 template<typename Options>
  struct lfactorial_t : elementwise_callable<lfactorial_t, Options>
  {
    template<eve::integral_value T>
    EVE_FORCEINLINE constexpr
    as_wide_as_t<double, T >
    operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(lfactorial_t, lfactorial_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var lfactorial
//!   @brief Computes the natural logarithm of the factorial of unsigned integer values
//!   \f$\displaystyle \log n! = \sum_{i=1}^n \log i\f$.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::ordered_value N >
//!      auto lfactorial(N x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integer or flint argument](@ref eve::ordered_value).
//!
//!   **Return value**
//!
//!   The value of \f$ \log n!\f$ is returned with the following considerations:
//!     * If the entry is an [integral value](eve::integral_value), the result
//!       [element type](eve::element_type) is always double to try to avoid overflow.
//!     * If the entry is a [floating point value](eve::floating_point_value)
//!       which must be a flint,  the result is of the same type as the entry.
//!     * If `n` elements are nor integer nor flint the result is undefined.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/lfactorial.cpp}
//! @}
//================================================================================================
inline constexpr auto lfactorial = functor<lfactorial_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE decltype(eve::factorial(T()))
      lfactorial_(EVE_REQUIRES(cpu_), O const&, T n) noexcept
    {
      EVE_ASSERT(eve::all(is_flint(n)), "lfactorial : some entry elements are not flint");
      EVE_ASSERT(eve::all(is_gez(n)), "lfactorial : some entry elements are not positive");
      constexpr auto max = std::same_as<element_type_t<T>, double> ? 171 : 35;
      auto           r   = eve::log(factorial(n));

      if( eve::all(n < max) ) return r;
      else
      {
        auto np = [](auto x)
          {
            if constexpr(integral_value<T>) return float64(inc(x));
            else                            return inc(x);
          }(n);

        return if_else(n < max, r, log_abs_gamma(np));

      }
    }
  }
}
