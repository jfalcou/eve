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
  //!      template < int I, int J, int K > auto to_rotation_matrix(auto q) const noexcept;
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
  //!   The computation method is taken from the article : "Quaternion to Rotation_Matrix angles conversion: A
  //!   direct, general and computationally efficient method". PLoS ONE
  //!   17(11): e0276302. https://doi.org/10.1371/journal pone 0276302.
  //!   Evandro Bernardes, and Stephane Viollet
  //!
  //! **Return value**
  //!
  //!    kumi tuple of the three rotation_matrix angles in radian.
  //!    In case of singularity the first angle is 0.
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
                                            , V const & , nor<normalize> ) noexcept

    {
      if constexpr (!normalize) EVE_ASSERT(eve::all(abs(q) == V(1)), "some quaternions are not unitary");
      using m_t = std::array< std::array<V, 3>, 3>;
      return m_t{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}} ;
    }

    template<value Z, bool normalize>
    EVE_FORCEINLINE auto to_rotation_matrix_( EVE_SUPPORTS(cpu_)
                                            , Z const & q, nor<normalize> const &) noexcept
    requires(is_complex_v<Z>)
    {
//      using e_t = element_type_t<Z>;
      if constexpr (!normalize) EVE_ASSERT(eve::all(sqr_abs(q) == e_t(1)), "some quaternions are not unitary");
      auto q0 = real(q);
      auto q1 = imag(q);
      auto q02 = 2*sqr(q0)-1;
      auto q0q1= 2*q0*q1;
      using m_t = std::array< std::array<Z, 3>, 3>;
      return m_t{{1, 0, 0}, {0, q02, -q0q1}, {0, q0q1, q02}};
    }
  }
}
