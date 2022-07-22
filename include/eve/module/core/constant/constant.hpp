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
#include <eve/detail/meta.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var constant
  //!   @brief Computes a floating constant from its scalar hexadecimal integral representation.
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
  //!      template< eve::floating_value T, auto BitsPattern >
  //!      T constant(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::constant<Bitpattern>(as<T>())` returns a value of type T
  //!      from the bits found in Bitpattern.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/constant.cpp}
  //! @}
  //================================================================================================

  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var Constant
  //!
  //! @brief Callable object computing a floating constant from its scalar hexadecimal integral representation |
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | generates a floating constant from its scalar hexadecimal integral representation |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_real_value T, auto BitsPattern > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! @tparam
  //! `T`:   type of the output constant
  //! `BitsPattern': hexadecimal integral representation of the floating scalar constant
  //!
  //! **Return value**
  //!
  //! the call `eve::Constant<T, Bitpattern>()` is semantically equivalent to
  //! T(eve::bit_cast(Bitpattern, `as<element_type_t<T>>()))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/constant.cpp}
  //!
  //! @}
  //================================================================================================

  template<typename T, auto BitsPattern>
  EVE_FORCEINLINE auto Constant(eve::as<T> const & = {})
  {
    using t_t = element_type_t<T>;

    if constexpr(std::is_integral_v<t_t>)
    {
      return static_cast<T>(BitsPattern);
    }
    else
    {
      if constexpr(sizeof(t_t) != sizeof(BitsPattern))
      {
        static_assert ( sizeof(t_t) == sizeof(BitsPattern),
                        "[eve::constant] floating_point case - BitsPattern has not the correct size"
                      );
        return T{};
      }
      else
      {
        return static_cast<T>(bit_cast(BitsPattern,as<t_t>{}));
      }
    }
  }
}
