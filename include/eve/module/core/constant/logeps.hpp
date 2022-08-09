//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/module/core/constant/ieee_constant.hpp>
#include <eve/module/core/decorator/roundings.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var logeps
//!   @brief Computes the natural logarithm of the machine [epsilon](@ref eve::eps).
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
//!      T logeps(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::logeps(as<T>())` is semantically equivalent
//!      to eve::log (eve::eps (eve::as<T>())).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/logeps.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(logeps_, logeps);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto logeps_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0XC17F1402U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0XC04205966F2B4F12ULL>();
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto logeps_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    if constexpr( std::is_same_v<D, downward_type> ) return logeps(as<T>());
    else return Ieee_constant<T, 0XC17F1401U, 0XC04205966F2B4F11ULL>();
  }
}
}
