//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/quaternion/regular/traits.hpp>
#include <eve/module/quaternion/regular/pure.hpp>
#include <eve/module/quaternion/regular/from_euler.hpp>
#include <eve/module/quaternion/regular/from_rotation_matrix.hpp>
#include <eve/module/quaternion/regular/from_spherical.hpp>
#include <eve/module/quaternion/regular/from_semipolar.hpp>
#include <eve/module/quaternion/regular/from_multipolar.hpp>
#include <eve/module/quaternion/regular/from_cylindrospherical.hpp>
#include <eve/module/quaternion/regular/from_cylindrical.hpp>
#include <eve/module/quaternion/regular/ipart.hpp>
#include <eve/module/quaternion/regular/jpart.hpp>
#include <eve/module/quaternion/regular/kpart.hpp>
#include <eve/module/quaternion/regular/purepart.hpp>
#include <eve/module/quaternion/regular/is_not_pure.hpp>
#include <eve/module/quaternion/regular/is_pure.hpp>
#include <eve/module/quaternion/regular/to_euler.hpp>
#include <eve/module/quaternion/regular/slerp.hpp>
#include <eve/module/quaternion/regular/squad.hpp>
#include <eve/module/quaternion/regular/rot_vec.hpp>
#include <eve/module/quaternion/regular/axis.hpp>
#include <eve/module/quaternion/regular/angle.hpp>
#include <eve/module/quaternion/regular/to_rotation_matrix.hpp>
#include <eve/module/quaternion/regular/decorator.hpp>
#include <eve/module/quaternion/detail/horner.hpp>
