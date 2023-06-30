//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

//==================================================================================================
//! @addtogroup simd_types
//! @{
//! @defgroup quaternion Quaternion Numbers
//! @brief Quaternion Numbers
//!
//!  This module provides types and functions to handle quaternion numbers.
//!
//!
//! In mathematics, the quaternion number system extends the complex numbers. The set of quaternions
//! is generally denoted by \f$\mathbb{H}\f$ as for first described by the Irish mathematician
//! William Rowan Hamilton in 1843
//!
//! Quaternions are generally represented in the form
//!
//! \f${\displaystyle a+b\ \mathbf {i} +c\ \mathbf {j} +d\ \mathbf {k} ,}\f$
//!
//! where a, b, c, and d are real numbers; and 1, i, j, and k are the basis vectors or basis elements.
//!
//! Quaternions are used in pure mathematics, but also have practical uses in applied mathematics,
//! particularly for calculations involving three-dimensional rotations.
//!
//! As complex number can algebraize rotations in f$\mathbb{R}^2\f$, quanternion number can to
//!  it in f$\mathbb{R}^3\f$
//!
//! Quaternions form a four-dimensional non-commutative but associative normed division algebra
//! over the real numbers,
//!
//! Given the associativity of the multiplication,  the general rule can be divised from
//! the following table
//!
//!  | *  |  1  |  i  |  j  |  k |
//!  | -- | --- | --- | --- | -- |
//!  | 1  |  1  |  i  |  j  |  k |
//!  | i  |  i  | -1  |  k  | -j |
//!  | j  |  j  | -k  | -1  |  i |
//!  | k  |  k  |  j  | -i  | -1 |
//!
//! The implementation is largely inspired by the Boost::math::quaternion one of Hubert Holin,
//!  with some adds and name changes to fit **EVE**
//!
//! # Operators implementation
//!
//!  addition, substraction, multiplication and division can be done mixing simd and scalar values
//!  of floating points, eve::complex and eve::quaternions of same underlying type. Infix notations
//!  can be used.
//!
//!  @warning multiplication is not commutative exept if one of the two argument satifies to the is_real
//!            predicate
//!
//!  For a quaternion q the calls to real(q), ipart(q), jpart(q) or kpart(q)  allows accessing the
//!  quaternion basis coefficients
//!
//!  # Constructors
//!
//!  Quaternions can be created from quadruplet of floating point values or pair of complex values
//!  using the call to eve::to_quaternions or eve::as_quaternion_t<T>. We refer to the product tpe
//!  documentation to see why it is generally advisable not to use the direct constructors.
//!
//!  the functions `semipolar`, `cylindrical`,`cylindrospherical` and `spherical`can also be used
//!  to generate quaternions  from various  \f$\mathbb{R}^4\f$ element representations, quite as
//!  creating complex numbers using polar representation.
//!
//!  #arithmetic fonctions
//!
//!  Some but not all arithmetic function are at hand :
//!
//!  |          |          |         |           |           |          |          |
//!  | -------- | -------- | ------- | --------- | --------- | -------- | -------- |
//!  |  abs     | add      | average | ceil      | conj      | dec      | dist     |
//!  |  div     | floor    | frac    | inc       | lerp      | maxabs   | minabs   |
//!  |  minus   | mul      | nearest | negmaxabs | negminabs | oneminus | plus     |
//!  |  pure    | rec      | reldist | sign      | slerp     | sqr      | sqr_abs  |
//!  |  sub     | to_euler | trunc   |           |           |          |          |
//!
//!    * `sqr_abs` computes the so called Cayley norm of a quaternion,  which is the square
//!       of the Euclidian norm (given by `abs`) and so is not a norm at all but a quadratic form
//!
//!    * `pure` return a quaternion with zeroed real part (sometimes denoted as  "unreal").
//!
//!    * `slerp`,  (the spherical interpolation) interpolates betwween two quaternions
//!        considered as elements of the unit \$f\mathbb{R]^4\$f hypersphere and
//!        is a common operation in keyframe animation.
//!
//!    * `to_euler` takes a quaternion three axes and a boolean (extrinsic/intrinsic), to computes three angle
//!       in radian which are the Euler or Bryan-Taits angles according to the axes given.
//!
//!  #Mathematical fonctions
//!
//!  Some but not all math function are at hand :
//!
//!  |          |             |         |           |           |          |          |
//!  | -------- | ----------- | ------- | --------- | --------- | -------- | -------- |
//!  |  cos     | cosh        | cot     | coth      | exp       |  expm1   | hypot    |
//!  |  lpnorm  | manhattan   | pow     | powm1     | sin       | sincos   | sinh     |
//!  | sinhcosh | sqrt        | tan     | tanh      |           |          |          |
//!
//!  @note `sqrt` on quaternions can have two square roots (general case) or infinitely many ones
//!         is the quaternion "is real" and the real part is negative. We always return
//!         the root with positive or null real part and the complex i*sqrt(abs(q)) in the second
//!         case.
//!
//!
//!  #Predicate fonctions
//!
//!  There is no order on the quaternions  compatible with the algebra operators.
//!  What remains are equality or inequality, ieee relative properties and `is_pure` (resp. `is_not_pure`),
//!  that return true (resp. false) for quaternion with 0 real part (resp. non 0 real part).
//!
//!  |                  |               |                |                 |             |             |             |
//!  | ---------------- | ------------- | -------------- | --------------- | ----------- | ----------- | ----------- |
//!  | is_denormal      | is_equal      | is_eqz         | is_finite       | is_infinite | is_nan      | is_nez      |
//!  | is_not_denormal  | is_not_equal  | is_not_finite  | is_not_infinite | is_not_nan  | is_not_pure | is_not_real |
//!  | is_ordered       | is_pure       | is_real        | is_unordered    |             |             |             |
//!
//! @}
//==================================================================================================
#include <eve/wide.hpp>
#include <eve/module/quaternion/regular/quaternion.hpp>
#include <eve/module/quaternion/quaternion.hpp>
