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
  //! @var to_rotation_matrix
  //!
  //! @brief Callable object computing a quaternion from its to_rotation_matrix representation.
  //!
  //!  This function build rotation_matrix angles from a quaternion. Template parameters I, J, K of type int
  //!  are used to choose the rotation_matrix order.
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
  //!       auto to_rotation_matrix(auto q) const noexcept;
  //!       auto to_rotation_matrix(auto q, Assume_normalized) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `q`  quaternion representing the rotation
  //!  * `Asume_normalized``: implies that q is already normalized
  //!
  //!
  //!
  //! **Return value**
  //!
  //!   compute the rotation matrix associated to the quaternion.
  //!
  //!   if T is the element type of q,  returns an std::array<std::array<T, 3>, 3> containing
  //!   the 9 coefficients of the rotation matrix
  //!
  //! @note use this function if you really need the rotation matrix,  but to rotate vectors
  //!       prefer the function rot_vec that directly uses the quaternion.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/quaternion/regular/to_rotation_matrix.cpp}
  //!  @}
  //================================================================================================
  namespace tag { struct to_rotation_matrix_; }
  template<> struct supports_conditional<tag::to_rotation_matrix_> : std::false_type {};
  EVE_MAKE_CALLABLE(to_rotation_matrix_, to_rotation_matrix);

  namespace detail
  {
    template<floating_ordered_value V, bool normalize>
    EVE_FORCEINLINE auto to_rotation_matrix_( EVE_SUPPORTS(cpu_)
                                            , [[maybe_unused]] V const & q, nor<normalize> ) noexcept

    {
      if constexpr (!normalize) EVE_ASSERT(eve::all(abs(q) == V(1)), "some quaternions are not unitary");
      using m_t = std::array< std::array<V, 3>, 3>;
      return m_t{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}} ;
    }

    template<floating_ordered_value V>
    EVE_FORCEINLINE auto to_rotation_matrix_( EVE_SUPPORTS(cpu_)
                                            , V const & ) noexcept

    {
      using m_t = std::array< std::array<V, 3>, 3>;
      return m_t{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}} ;
    }

    template<value Z, bool normalize>
    EVE_FORCEINLINE auto to_rotation_matrix_( EVE_SUPPORTS(cpu_)
                                            , Z const & q, nor<normalize>) noexcept
    requires(is_complex_v<Z>)
    {
      if constexpr (!normalize)
      {
        EVE_ASSERT(eve::all(sqr_abs(q) == decltype(sqr_abs(q))(1)), "some quaternions are not unitary");
      }
      auto q0 = real(q);
      auto q1 = imag(q);
      auto q02 = 2*sqr(q0)-1;
      auto q0q1= 2*q0*q1;
      using m_t = std::array< std::array<Z, 3>, 3>;
      return m_t{{1, 0, 0}, {0, q02, -q0q1}, {0, q0q1, q02}};
    }

    template<value Z>
    EVE_FORCEINLINE auto to_rotation_matrix_( EVE_SUPPORTS(cpu_)
                                            , Z const & q) noexcept
    requires(is_complex_v<Z>)
    {
      return to_rotation_matrix(q, Normalize);
    }

  }
}
