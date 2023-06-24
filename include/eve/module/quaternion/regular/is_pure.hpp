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
  //! @var is_pure
  //!
  //! @brief Callable object computing is_pureinary part of values.
  //!
  //! **Required header:** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of is_pure part                         |
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
  //! @godbolt{doc/quaternion/regular/is_pure.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct is_pure_; }
  template<> struct supports_conditional<tag::is_pure_> : std::false_type {};

  EVE_MAKE_CALLABLE(is_pure_, is_pure);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE auto is_pure_( EVE_SUPPORTS(cpu_), V const &) noexcept
    {
      return True(as<V>()); ;
    }

    template<value V>
    EVE_FORCEINLINE V is_pure_( EVE_SUPPORTS(cpu_), eve::complex<V> const & z) noexcept
    {
      return is_imag(z); ;
    }
  }
}
