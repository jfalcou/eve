//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/conditional.hpp>
#include <eve/concept/value.hpp>

#include <concepts>
#include <type_traits>
#include <utility>
#include <ostream>

#define EVE_DISPATCH() delay_t{}, EVE_CURRENT_API{}

#define EVE_BIND_TO_CALLABLE(TAG)                                                           \
template<typename... Tn> static EVE_FORCEINLINE constexpr auto evaluate(Tn... an) noexcept  \
{                                                                                           \
  return TAG(EVE_DISPATCH(), an...);                                                        \
}                                                                                           \
/**/

namespace eve::detail
{
  template<typename Tag, typename Caller> struct basic_callable
  {
    using tag_type    = Tag;
    using caller_type = Caller;

    template<typename... Args>
    static EVE_FORCEINLINE constexpr auto dispatch(Args &&... args) noexcept
    {
      if constexpr( tag_dispatchable<tag_type,Args...> )
      {
        return tagged_dispatch(tag_type{}, std::forward<Args>(args)...);
      }
      else
      {
        return Caller::evaluate(std::forward<Args>(args)...);
      }
    }

    template<typename... Args>
    static EVE_FORCEINLINE constexpr auto redispatch( basic_callable const&
                                                    , Args &&... args
                                                    ) noexcept
    {
      return dispatch(args...);
    }
  };

  template<typename Condition, typename Caller>
  struct conditional_callable
  {
    using tag_type        = typename Caller::tag_type;
    using caller_type     = typename Caller::caller_type;
    using is_conditional  = void;

    template<typename... Args>
    EVE_FORCEINLINE constexpr auto operator()(Args &&... args) noexcept
    -> decltype( std::declval<caller_type>()(std::forward<Args>(args)...) )
    {
      return caller_type::dispatch(condition, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static EVE_FORCEINLINE constexpr auto redispatch( conditional_callable const& func
                                                    , Args &&... args
                                                    ) noexcept
    {
      using internal_type = typename Caller::caller_type;
      return internal_type::dispatch(func.condition, args...);
    }

    Condition condition;
  };

  template<typename Caller> struct supports_conditional
  {
    template<value Condition>
    EVE_FORCEINLINE constexpr auto operator[](Condition const &c) const noexcept
    {
      auto cond = if_(to_logical(c));
      return conditional_callable<decltype(cond),Caller>{cond};
    }

    template<conditional_expr Condition>
    EVE_FORCEINLINE constexpr auto operator[](Condition const &c) const noexcept
    {
      return conditional_callable<Condition,Caller>{c};
    }
  };

  template<typename Tag, typename Caller>
  struct callable : basic_callable<Tag,Caller>, supports_conditional<Caller>
  {
  };
}

#define EVE_BUILD_CALLABLE(TAG, NAME)                                                              \
inline std::ostream& operator<<(std::ostream& os, detail::callable_##TAG const&)                   \
{                                                                                                  \
  return os << #NAME;                                                                              \
}                                                                                                  \
inline detail::callable_##TAG const NAME = {}                                                      \
/**/
