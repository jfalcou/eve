//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/pattern.hpp>
#include <eve/detail/function/canonical_shuffle_adapter.hpp>

namespace eve
{
  EVE_REGISTER_CALLABLE(shuffle_l0_impl_)
  EVE_DECLARE_CALLABLE(shuffle_l0_impl_, shuffle_l0_impl)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(shuffle_l0_impl_, shuffle_l0_impl);
  } // namespace detail

  EVE_CALLABLE_API(shuffle_l0_impl_, shuffle_l0_impl)
}

namespace eve
{

//================================================================================================
//! @addtogroup core
//! @{
//!    @var shuffle_l0
//!    @brief Work in Progress. Most likely you were looking for `eve::shuffle`.
//!    A shuffle building block that is responsible for best shuffles on the platfrom.
//!    Only works if shuffle is doable in 1 instruction with no mask registers required.
//! @}
//================================================================================================
constexpr auto shuffle_l0 = eve::detail::as_canonical_shuffle(detail::shuffle_l0_impl);

}

#include <eve/module/core/regular/impl/shuffle_l0.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/shuffle_l0.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/shuffle_l0.hpp>
#endif
