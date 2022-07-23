//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
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
  //!     * `x` :  argument.
  //!
  //!    **Return value**
  //!
  //!     The call `eve::mindenormal(as<T>())` is semantically equivalent to:
  //!       * T(1.4013e-45f) if eve::element_type_t<T> is float
  //!       * T(4.94066e-324) if eve::element_type_t<T> is double
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/mindenormal.cpp}
  //! @}
  //================================================================================================

  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var mindenormal
  //!
  //! @brief Callable object computing the least denormal positive value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the mindenormal constant                          |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::mindenormal(as<T>())` is semantically equivalent to:
  //!   - T(1.4013e-45f) if eve::element_type_t<T> is float
  //!   - T(4.94066e-324) if eve::element_type_t<T> is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/mindenormal.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(mindenormal_, mindenormal);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto mindenormal_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x1U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x1ULL>();
    }

    template<floating_value T, typename D>
    EVE_FORCEINLINE constexpr auto mindenormal_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return mindenormal(as<T>());
    }
  }
}
