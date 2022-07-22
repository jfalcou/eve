//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

#include <concepts>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var as_value
  //!   @brief Converts an eve constant or just a value to a type.
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
  //!      template< typename From, eve::value T >
  //!      T as_value(From f, as<T> const & t) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `from` :  either anything convertible to T or an eve constant.
  //!
  //!   **Return value**
  //!
  //!       T equivalent of from
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/as_value.cpp}
  //! @}
  //================================================================================================

  EVE_MAKE_CALLABLE(as_value_, as_value);

  namespace detail
  {
    template<typename From, value T>
    EVE_FORCEINLINE constexpr auto as_value_(EVE_SUPPORTS(cpu_), From from, as<T> const & t) noexcept
    {
           if constexpr ( !value<From>                               ) return from(t);
      else if constexpr ( std::integral<T> || std::floating_point<T> ) return (T)from;
      else                                                             return T{from};
    }
  }
}
