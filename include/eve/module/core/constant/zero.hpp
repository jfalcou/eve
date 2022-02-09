//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/as.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var zero
  //!
  //! @brief Callable object computing the O value.
  //!
  //! **Required header:** #include <eve/module/core.hpp>
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the zero constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::zero(as<T>())` is semantically equivalent to  `T(0)`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/zero.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(zero_, zero);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE T zero_(EVE_SUPPORTS(cpu_), eve::as<T> const &) noexcept
    {
      if constexpr ( kumi::product_type<T> )
      {
        // Can't just T{kumi::map} because that does not work for scalar product types
        T res;
        // This better inline.
        kumi::for_each([](auto& m) { m = zero(as(m)); }, res);

        return res;
      }
      else return T(0);
    }
  }
}
