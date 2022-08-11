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
//!   @var $name$
//!   @brief Computes the the machine epsilon.
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
//!      T $name$(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      the call `eve::eps(as<T>())` returns [elementwise](@ref glossary_elementwise), the smallest
//!      positive value `x` of the type such that `1+x !=  x`.
//!
//!      * If T is an [integral value](@ref eve::integral_value) the elements returned are equal to
//!      one
//!      * If T is a  [floating value](@ref eve::floating_value) the elements returned are equal to
//!           * 2.220446049250313e-16 if the [elements type](@ref eve::element_type) is float
//!           * 1.1920929e-07f        if the [elements type](@ref eve::element_type) is double
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/$name$.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(eps_, eps);

namespace detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto eps_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_integral_v<t_t> ) return T(1);
    else if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0X34000000U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0x3CB0000000000000ULL>();
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto eps_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return eps(as<T>());
  }
}
}
