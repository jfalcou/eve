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
  //! @var to_euler
  //!
  //! @brief Callable object computing euler angles  from a quaternion.
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
  //!      template < int I, int J, int K >
  //!      auto to_euler(auto q
  //!                  , axes<I> const & a1, axes<J> const & a2, axes<K> const & a3) const noexcept
  //!        requires(I != J && J != K)
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `q` the rotation quaternion (not necesseraly normalized)
  //!  * `a1`, `a2`, `a3` : the axes parameters to be chosen between _X,  _Y, _Z (two consecutive axes cannot be the same)
  //!  *                    depending of the euler order
  //!
  //!  **Template parameters**
  //!
  //!     * I, J, K : actual parameters can be chosen between axes values _X,  _Y,  _Z from
  //!                 which I, J and K are deduced
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
  //! @godbolt{doc/quaternion/regular/to_euler.cpp}
  //!  @}
  //================================================================================================
  namespace tag { struct to_euler_; }
  template<> struct supports_conditional<tag::to_euler_> : std::false_type {};
  EVE_MAKE_CALLABLE(to_euler_, to_euler);

  namespace detail
  {
    template<auto I, auto J, auto K, floating_ordered_value V, bool Extrinsic>
    EVE_FORCEINLINE auto to_euler_( EVE_SUPPORTS(cpu_)
                                  , V const &
                                  , axes<I> const &
                                  , axes<J> const &
                                  , axes<K> const &
                                  , ext<Extrinsic>  const &) noexcept

    {
      return  kumi::tuple{zero(as<V>()), zero(as<V>()), zero(as<V>())};
    }

    template<auto I, auto J, auto K, value Z, bool Extrinsic>
    EVE_FORCEINLINE auto to_euler_( EVE_SUPPORTS(cpu_)
                                  , Z const & c
                                  , axes<I> const & a1
                                  , axes<J> const & a2
                                  , axes<K> const & a3
                                  , ext<Extrinsic> const & e) noexcept
    requires(is_complex_v<Z>)
    {
      return to_euler(eve::as_quaternion_t<Z>(c), a1, a2, a3, e);
    }
  }
}
