//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/compress/detail/compress_callable.hpp>

namespace eve
{
  EVE_REGISTER_CALLABLE(compress_copy_scalar_)
  EVE_DECLARE_CALLABLE(compress_copy_scalar_, compress_copy_scalar)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(compress_copy_scalar_, compress_copy_scalar);
  }

  EVE_CALLABLE_API(compress_copy_scalar_, compress_copy_scalar)
}

#include <eve/module/core/compress/detail/simd/common/compress_copy_scalar.hpp>
