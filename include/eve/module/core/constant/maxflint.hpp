//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/roundings.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var maxflint
  //!   @brief Computes the the greatest floating point representing an integer and
  //!   such that n != n+1.
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
  //!      T maxflint(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::maxflint(as<T>())` is semantically equivalent to:
  //!        * T(16777216.0f) if eve::element_type_t<T> is float.
  //!        * T(9007199254740992.0) if eve::element_type_t<T> is double.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/maxflint.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(maxflint_, maxflint);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto maxflint_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x4b800000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x4340000000000000LL>();
    }

    template<floating_value T, typename D>
    EVE_FORCEINLINE constexpr auto maxflint_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return maxflint(as<T>());
    }
  }
}
