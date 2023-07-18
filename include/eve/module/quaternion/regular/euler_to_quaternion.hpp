//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/math.hpp>
#include <eve/module/quaternion/regular/axes.hpp>
namespace eve
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var euler_to_quaternion
  //!
  //! @brief Callable object computing a quaternion from its euler_to_quaternion representation.
  //!
  //!  This function build euler angles from a quaternion. Template parameters I, J, K of type int
  //!  are used to choose the euler order.
  //!
  //!  for instance I = 3, J = 2, K = 3 choose the ZYZ sequence.
  //!  the values of I, J, and K must be in {1, 2, 3} ans satisfy I != J && J != K.
  //!
  //! **Defined in header**
  //!
  //!   @code
  //!   #include eve/module/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template < int I, int J, int K > auto euler_to_quaternion(auto q) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `q` the rotation quaternion (not necesseraly normalized)
  //!
  //!  **Template parameters**
  //!
  //!     * I, J, K
  //!
  //!
  //!   The computation method is taken from the article : "Quaternion to Euler angles conversion: A
  //!   direct, general and computationally efficient method". PLoS ONE
  //!   17(11): e0276302. https://doi.org/10.1371/journal pone 0276302.
  //!   Evandro Bernardes, and Stephane Viollet
  //!
  //! **Return value**
  //!
  //!    kumi tuple of the three euler angles in radian.
  //!    In case of singularity the first angle is 0.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/quaternion/regular/euler_to_quaternion.cpp}
  //!  @}
  //================================================================================================
  namespace tag { struct euler_to_quaternion_; }
  template<> struct supports_conditional<tag::euler_to_quaternion_> : std::false_type {};
  EVE_MAKE_CALLABLE(euler_to_quaternion_, euler_to_quaternion);

  namespace detail
  {
    template<floating_ordered_value V, int I,  int J,  int K, bool Extrinsic>
    EVE_FORCEINLINE auto euler_to_quaternion_( EVE_SUPPORTS(cpu_)
                                             , V const & v1
                                             , V const & v2
                                             , V const & v3
                                             , axes<I>
                                             , axes<J>
                                             , axes<K>
                                             , ext<Extrinsic>
                                             ) noexcept

    requires(I != J && J != K)
    {
      std::array<as_quaternion_t<V>, 3> qs;
      auto [sa, ca] = sincos(v3/2);
      auto [sb, cb] = sincos(v2/2);
      auto [sc, cc] = sincos(v1/2);
      get<0>(qs[0]) = ca;
      get<0>(qs[1]) = cb;
      get<J>(qs[1]) = sb;
      get<0>(qs[2]) = cc;
      if constexpr(!Extrinsic)
      {
        get<K>(qs[0]) = sa;
        get<I>(qs[2]) = sc;
        as_quaternion_t<V> q = qs[2]*qs[1]*qs[0];
        return q;
      }
      else
      {
        get<I>(qs[0]) = sa;
        get<K>(qs[2]) = sc;
        as_quaternion_t<V> q = qs[0]*qs[1]*qs[2];
        return q;
      }

    }
  }
}
