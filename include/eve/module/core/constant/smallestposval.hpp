//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/module/core/decorator/roundings.hpp>

#include <type_traits>

namespace eve
{
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
EVE_MAKE_CALLABLE(smallestposval_, smallestposval);

namespace detail
{
  template<typename T>
  requires(plain_scalar_value<element_type_t<T>>)
  EVE_FORCEINLINE auto smallestposval_(EVE_SUPPORTS(cpu_), eve::as<T> const& = {}) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) { return Constant<T, 0X00800000U>(); }
    else if constexpr( std::is_same_v<t_t, double> )
    {
      return Constant<T, 0X0010000000000000ULL>();
    }
    else if constexpr( std::is_integral_v<t_t> ) { return T(1); }
  }

  template<typename T, typename D>
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  EVE_FORCEINLINE constexpr auto smallestposval_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
  -> decltype(smallestposval(as<T>()))
  {
    return smallestposval(as<T>());
  }
}
}
