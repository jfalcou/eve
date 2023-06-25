//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BS!L-1.0
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
  //! @var is_not_pure
  //!
  //! @brief Callable object computing is_not_pureinary part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | is x a not a not_pure quaternion (i.e. with 0 real part)             |
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
  //! true  if `x` the real  part of `x` if not zero,  false otherwise
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/is_not_pure.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct is_not_pure_; }
  template<> struct supports_conditional<tag::is_not_pure_> : std::false_type {};

  EVE_MAKE_CALLABLE(is_not_pure_, is_not_pure);

  namespace detail
  {
    template<value V>
    EVE_FORCEINLINE auto is_not_pure_( EVE_SUPPORTS(cpu_), V const & a) noexcept
    {
      return is_nez(a); ;
    }

    template<value V>
    EVE_FORCEINLINE V is_not_pure_( EVE_SUPPORTS(cpu_), eve::complex<V> const & z) noexcept
    {
      return is_nez(real(z));
    }
  }
}
