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
#include <eve/module/quaternion/regular/traits.hpp>
namespace eve
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_rotation_matrix
  //!
  //! @brief Callable object computing a quaternion from its rotation_matrix representation.
  //!
  //!  This function returns a quaternion associated to the input rotation matrix m.
  //!  If m is not a proper rotation 3x3 rotation matrix (i.e an orthogonal matrix with determinant 1)
  //!  the result is undefined.
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
  //!      template < typename M >
  //!      auto from_rotation_matrix(auto m) const noexcept
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `m` the rotation matrix. The actual implementation assumes that m[i][j] will return
  //!        the ith line and jth column element of the matrix (indices starting from 0).
  //!
  //!
  //!   The computation method is inspired from the article : "Accurate Computation of
  //!   Quaternions from Rotation Matrices",  by   Soheil Sarabandi and Federico Thomas
  //!   Institut de Robotica i Informatica Industrial (CSIC-UPC)
  //!   Llorens Artigas 4-6, 08028 Barcelona, Spain.
  //!
  //! **Return value**
  //!
  //!    an unitary quaternion representing the rotation
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/quaternion/regular/from_rotation_matrix.cpp}
  //!  @}
  //================================================================================================
  namespace tag { struct from_rotation_matrix_; }
  template<> struct supports_conditional<tag::from_rotation_matrix_> : std::false_type {};
  EVE_MAKE_CALLABLE(from_rotation_matrix_, from_rotation_matrix);

  namespace detail
  {
    template<typename M>
    EVE_FORCEINLINE auto from_rotation_matrix_( EVE_SUPPORTS(cpu_)
                                  , M const & r ) noexcept

    {
      auto r11pr22 =  r[1][1] + r[2][2];
      auto qq0m1   =  r[0][0] + r11pr22;
      auto qq1m1   =  r[0][0] - r11pr22;
      auto r11mr22 =  r[1][1] - r[2][2];
      auto qq2m1   = -r[0][0] + r11mr22;
      auto qq3m1   = -r[0][0] - r11mr22;

      auto r21mr12 = r[2][1] - r[1][2];
      auto r02mr20 = r[0][2] - r[2][0];
      auto r10mr01 = r[1][0] - r[0][1];
      auto r01pr10 = r[1][0] + r[0][1];
      auto r20pr02 = r[2][0] + r[0][2];
      auto r12pr21 = r[1][2] + r[2][1];

      auto h = half(as(r11pr22));
      auto q0 =  sqrt(if_else(is_gtz(qq0m1), inc(qq0m1), (sqr(r21mr12)+sqr(r02mr20)+sqr(r10mr01))/(3-qq0m1)))*h;
      auto q1 =  sqrt(if_else(is_gtz(qq1m1), inc(qq1m1), (sqr(r21mr12)+sqr(r01pr10)+sqr(r20pr02))/(3-qq1m1)))*h;
      auto q2 =  sqrt(if_else(is_gtz(qq2m1), inc(qq2m1), (sqr(r02mr20)+sqr(r01pr10)+sqr(r12pr21))/(3-qq2m1)))*h;
      auto q3 =  sqrt(if_else(is_gtz(qq3m1), inc(qq3m1), (sqr(r10mr01)+sqr(r20pr02)+sqr(r12pr21))/(3-qq3m1)))*h;
      using e_t = decltype(r11pr22);
      return as_quaternion_t<e_t>(q0, q1, q2, q3);
    }
  }
}
