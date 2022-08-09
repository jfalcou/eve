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
//!   @var bitincrement
//!   @brief Computes the constant of type T in which the only bit set is the least significant
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
//!      T bitincrement(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::bitincrement(as<T>())` returns a value of type T in which the only bit
//!      set is the least significant
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/bitincrement.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bitincrement_, bitincrement);

namespace detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto bitincrement_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;

    if constexpr( std::is_integral_v<t_t> ) return T(1);
    else if constexpr( std::is_same_v<t_t, float> ) return Constant<T, 0X1U>();
    else if constexpr( std::is_same_v<t_t, double> ) return Constant<T, 0x1ULL>();
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto bitincrement_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return bitincrement(as<T>());
  }
}
}
