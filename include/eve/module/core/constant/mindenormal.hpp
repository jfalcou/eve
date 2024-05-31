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
  struct mindenormal_t : constant_callable<mindenormal_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static constexpr EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      using e_t = element_type_t<T>;

      if      constexpr(std::integral<e_t>        ) return T(1);
      else if constexpr(std::same_as<e_t, float>  ) return T( 0x1p-149);
      else if constexpr(std::same_as<e_t, double> ) return T(0x0.0000000000001p-1022);
    }

    template<typename T>
    requires(plain_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(mindenormal_t, mindenormal_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var mindenormal
//!   @brief Computes the smallest denormal positive value.
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
//!      template< eve::floating_value T >
//!      T mindenormal(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!     The call `eve::mindenormal(as<T>())` is semantically equivalent to:
//!       * `T(1)'            if eve::element_type_t<T> is integral
//!       * `T(1.4013e-45f)`  if eve::element_type_t<T> is float
//!       * `T(4.94066e-324)` if eve::element_type_t<T> is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/mindenormal.cpp}
//! @}
//================================================================================================
  inline constexpr auto mindenormal = functor<mindenormal_t>;
}
