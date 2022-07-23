//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

 #include <eve/module/core/decorator/roundings.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <limits>

namespace eve
{
 //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var valmax
  //!   @brief Computes the  the greatest representable value.
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
  //!      T valmax(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::valmax(as<T>())` is semantically equivalent to
  //!      `T(std::numeric_limits<element_type_t<T>>::max())`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/valmax.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(valmax_, valmax);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE auto valmax_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = element_type_t<T>;
      return T(std::numeric_limits<t_t>::max());
    }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto valmax_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return valmax(as<T>());
  }
  }
}
