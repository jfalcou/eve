//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/complex.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var pure
  //!
  //! @brief Callable object computing pureinary part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of pure part                         |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //! 0 if `x` is real or the unreal part of `x` if x is an instance of eve::quaternion or eve::complex
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/pure.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct pure_; }
  template<> struct supports_conditional<tag::pure_> : std::false_type {};

  EVE_MAKE_CALLABLE(pure_, pure);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE auto pure_( EVE_SUPPORTS(cpu_), V const &) noexcept
    {
      return quaternion<V>();
    }

    template<value V>
    EVE_FORCEINLINE V pure_( EVE_SUPPORTS(cpu_), eve::complex<V> const & z) noexcept
    {
      return quaternion<V>(0, imag(z), 0, 0);
    }
  }
}
