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
  struct smallestposval_t : constant_callable<smallestposval_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      using e_t = element_type_t<T>;

           if constexpr(std::integral<e_t>        ) return T(1);
      else if constexpr(std::same_as<e_t, float>  ) return T(0x1p-126);
      else if constexpr(std::same_as<e_t, double> ) return T(0x1p-1022);
    }

    template<typename T>
    requires(plain_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(smallestposval_t, smallestposval_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var smallestposval
//!   @brief Computes the smallest normal positive value.
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
//!      T smallestposval(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::smallestposval(as<T>())` is semantically equivalent to:
//!        * `T(1)` if `eve::element_type_t<T>` is integral
//!        * `T(1.1754944e-38f)` if `eve::element_type_t<T>` is float
//!        * `T(2.225073858507201e-308)` if `eve::element_type_t<T>` is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/smallestposval.cpp}
//! @}
//================================================================================================
  inline constexpr auto smallestposval = functor<smallestposval_t>;
}
