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
  //! @var slerp
  //!
  //! @brief Callable object computing slerpinary part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of slerp part                         |
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
  //! @godbolt{doc/quaternion/regular/slerp.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct slerp_; }
  template<> struct supports_conditional<tag::slerp_> : std::false_type {};

  EVE_MAKE_CALLABLE(slerp_, slerp);

  namespace detail
  {
    template<ordered_value V1, ordered_value V2, ordered_value T>
    EVE_FORCEINLINE auto slerp_( EVE_SUPPORTS(cpu_), V1 const & v1, V2 const & v2) noexcept
    -> decltype(v1+v2)
    {
      using r_t = decltype(v1+v2);
      EVE_ASSERT(eve::all(v1 == v2), "some angles between parameters are not acute");
      EVE_ASSERT(eve::all(is_unit(v1) && is_unit(v2)), "a parameter is not unitary");
      return as_quaternion<r_t>(r_t(v1));
    }

    template<value V1, value V2>
    EVE_FORCEINLINE auto slerp_( EVE_SUPPORTS(cpu_), eve::complex<V1> const & z1, eve::complex<V2> const & z2) noexcept
    {
      EVE_ASSERT(eve::all(is_unit(z1)&&is_unit(z2)), "some parameter is not unitary");
      return slerp(quaternion<V1>(real(z1), imag(z2), 0, 0), quaternion<V2>(real(z1), imag(z2), 0, 0));
    }
  }
}
