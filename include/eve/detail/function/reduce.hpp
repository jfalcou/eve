//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

namespace eve
{
  EVE_DECLARE_CALLABLE(basic_reduce_)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(basic_reduce_, basic_reduce);
  }

  EVE_CALLABLE_API(basic_reduce_, basic_reduce)
}

#include <eve/detail/function/simd/common/reduce.hpp>
