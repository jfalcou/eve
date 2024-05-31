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

namespace eve
{
  template<typename Options>
  struct sqrteps_t : constant_callable<sqrteps_t, Options, downward_option, upward_option>
  {
    template<typename T, typename Opts>
    static constexpr EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
    {
      using e_t = element_type_t<T>;

      if constexpr(std::same_as<e_t, float>  )
      {
        if constexpr(Opts::contains(upward2))
          return T(0x1.6a09e8p-12f);
        else
          return T(0x1.6a09e6p-12f);
      }
      else if constexpr(std::same_as<e_t, double> ) return T(0x1p-26);
    }

    template<floating_value T>
    requires(plain_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sqrteps_t, sqrteps_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var sqrteps
//!   @brief Computes the square root of the machine epsilon.
//!
//!   **Defined in Header**
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
//!      template< eve::value T >
//!      T sqrteps(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrteps(as<T>())` is semantically equivalent to
//!      `eve::sqrt (eve::eps (as<T>()))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/sqrteps.cpp}
//! @}
//================================================================================================
  inline constexpr auto sqrteps = functor<sqrteps_t>;
}
