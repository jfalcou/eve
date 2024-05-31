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
  struct sqrtsmallestposval_t : constant_callable<sqrtsmallestposval_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      using e_t = element_type_t<T>;

           if constexpr(std::integral<e_t>        ) return T(1);
      else if constexpr(std::same_as<e_t, float>  ) return T(0x1p-63);
      else if constexpr(std::same_as<e_t, double> ) return T(0x1p-511);
    }

    template<typename T>
    requires(plain_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sqrtsmallestposval_t, sqrtsmallestposval_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var sqrtsmallestposval
//!   @brief Computes the square root of the eve::smallestposval.
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
//!      T sqrtsmallestposval(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::sqrtsmallestposval(as<T>())` is semantically equivalent to
//!      `eve::sqrt (eve::smallestposval(as<T>())`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/sqrtsmallestposval.cpp}
//! @}
//================================================================================================
inline constexpr auto sqrtsmallestposval = functor<sqrtsmallestposval_t>;

}
