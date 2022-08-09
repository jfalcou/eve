//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/decorator/roundings.hpp>
#include <eve/traits/as_integer.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var allbits
//!   @brief Computes the constant with all bits set.
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
//!      T allbits(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::allbits(as<T>())` returns a value of type T with all bits set.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/allbits.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(allbits_, allbits);

namespace detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto allbits_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t           = element_type_t<T>;
    using i_t           = as_integer_t<t_t, unsigned>;
    constexpr auto mask = ~0ULL;

    if constexpr( std::is_integral_v<t_t> ) return T(mask);
    else return T(bit_cast(i_t(mask), as<t_t>()));
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto allbits_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return allbits(as<T>());
  }
}
}
