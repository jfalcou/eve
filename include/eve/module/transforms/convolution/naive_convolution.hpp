//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(naive_cyclic_convolution_,  naive_cyclic_convolution);
  EVE_MAKE_CALLABLE(naive_linear_convolution_,  naive_linear_convolution);
}

#include <eve/module/transforms/convolution/impl/naive_convolution.hpp>
