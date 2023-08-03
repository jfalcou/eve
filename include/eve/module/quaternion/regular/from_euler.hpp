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
  //! @var from_euler
  //!
  //! @brief Callable object computing a quaternion from its euler representation.
  //!
  //!  This function build euler angles from 3 euler angles in radian. Template parameters I, J, K of type int
  //!  are used to choose the euler axis order.
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
  //!      template < int I, int J, int K > auto from_euler(auto a, auto b, auto c
  //!                                                      , axes<I> a1, axes<J> a2,  axes<K> a3
  //!                                                      , ext e
  //!                                                      ) const noexcept;
  //!      requires(I != J && J != K)
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `a`, `b`, `c` : the angles in radian
  //!  * `a1`, `a2`, `a3` the axes parameters to be chosen between _X,  _Y, _Z (two consecutive axes cannot be the same)
  //!  * `e' : allows to choos between extrinsic Extrinsic or Intrinsic representations.
  //!
  //!  **Template parameters**
  //!
  //!     * I, J, K : are on call deduced from the axes parameters
  //!
  //!
  //!   The computation method is taken from the article : "Quaternion to Euler angles conversion: A
  //!   direct, general and computationally efficient method". PLoS ONE
  //!   17(11): e0276302. https://doi.org/10.1371/journal pone 0276302.
  //!   Evandro Bernardes, and Stephane Viollet
  //!
  //! **Return value**
  //!
  //!    quaternion representing the rotation
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/quaternion/regular/from_euler.cpp}
  //!  @}
  //================================================================================================
  namespace tag { struct from_euler_; }
  template<> struct supports_conditional<tag::from_euler_> : std::false_type {};
  EVE_MAKE_CALLABLE(from_euler_, from_euler);

  namespace detail
  {
    template<floating_ordered_value V, int I,  int J,  int K, bool Extrinsic>
    EVE_FORCEINLINE auto from_euler_( EVE_SUPPORTS(cpu_)
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
