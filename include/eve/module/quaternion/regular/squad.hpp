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
  //! @var squad
  //!
  //! @brief Callable object computing squadinary part of values.
  //!
  //! **Defined in header** `#include <eve/module/quaternion.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of squad part                         |
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
  //! @godbolt{doc/quaternion/regular/squad.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct squad_; }
  template<> struct supports_conditional<tag::squad_> : std::false_type {};

  EVE_MAKE_CALLABLE(squad_, squad);

  namespace detail
  {
    template<ordered_value V1, ordered_value V2, ordered_value V3, ordered_value V4, ordered_value T>
    EVE_FORCEINLINE auto squad_( EVE_SUPPORTS(cpu_), V1 const & v1, V2 const & v2
                               , V3 const & v3, V4 const & v4, T const &) noexcept
    -> decltype(v1+v2+v3+v4+T())
    {
      using r_t = decltype(v1+v2+v3+v4);
      EVE_ASSERT(eve::all(v1 == v2 && v2 == v3 && v3 == v4), "some angles between parameters are not acute");
      EVE_ASSERT(eve::all(is_unit(v1)), "a parameter is not unitary");
      return as_quaternion<r_t>(r_t(v1));
    }

    template<value V1, value V2, value V3, value V4, ordered_value T>
    EVE_FORCEINLINE auto squad_( EVE_SUPPORTS(cpu_), eve::complex<V1> const & z1, eve::complex<V2> const & z2
                               , eve::complex<V3> const & z3, eve::complex<V4> const & z4, T const & t) noexcept
    {
      EVE_ASSERT(eve::all(is_unit(z1)&&is_unit(z2)), "some parameter is not unitary");
      return squad(quaternion<V1>(real(z1), imag(z2), 0, 0), quaternion<V2>(real(z1), imag(z2), 0, 0)
                  , quaternion<V3>(real(z3), imag(z3), 0, 0), quaternion<V4>(real(z4), imag(z4), 0, 0), t);
    }
  }
}
