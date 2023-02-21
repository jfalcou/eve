//====================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//====================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

#include <ostream>
#include <utility>
#include <type_traits>

//====================================================================================================
//  This part is a indirect implementation of P1895R0
//  See https://www.open-std.org/jtc1/sc22/WG21/docs/papers/2019/p1895r0.pdf for details and
//  rationale.
//====================================================================================================
namespace eve::func_ns
{
struct invoker
{
  template<typename Tag, typename... Args>
  requires requires(Tag tag, Args&&...args) { tag_invoke(tag, EVE_FWD(args)...); }
  EVE_FORCEINLINE constexpr auto operator()(Tag tag, Args&&...args) const
      noexcept(noexcept(tag_invoke(tag, EVE_FWD(args)...)))
          -> decltype(tag_invoke(tag, EVE_FWD(args)...))
  {
    return tag_invoke(tag, EVE_FWD(args)...);
  }
};
}

namespace eve
{
//==================================================================================================
//! @addtogroup traits
//! @{
//! @defgroup invoke Generalized Tag Invoke Protocol
//! @brief This module defines all the **EVE** generalized tag_invoke protocol infrastructure.
//! @}
//==================================================================================================

inline namespace callable_ns
{
  inline constexpr func_ns::invoker tag_invoke = {};
}

//==================================================================================================
//! @addtogroup invoke
//! @{
//==================================================================================================

//==================================================================================================
//! @concept tag_invocable
//! @brief Type supporting the tag_invoke protocol
//!
//! A type `Tag` satisfies eve::tag_invocable<Args...> if and only if it can be used in a call to
//! eve::tag_invoke.
//!
//! @tparam Tag  Tag type for the @callable to check
//! @tparam Args Arguments used in the call.
//==================================================================================================
template<typename Tag, typename... Args>
concept tag_invocable =
    requires(Tag&& tag, Args&&...args) { eve::tag_invoke(EVE_FWD(tag), EVE_FWD(args)...); };

//! @brief Compute the return type of a eve::tag_invoke call.
template<typename Tag, typename... Args>
using tag_invoke_result = std::invoke_result_t<decltype(eve::tag_invoke), Tag, Args...>;

//! @brief Compute the type of an instance of an **EVE** @callable.
template<auto& Func> using tag_of = std::decay_t<decltype(Func)>;

//==================================================================================================
//! @}
//==================================================================================================

}
