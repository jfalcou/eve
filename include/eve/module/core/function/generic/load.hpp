//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <type_traits>

namespace eve
{
  template<typename T> concept scalar_pointer = requires(T a)
  {
    { *a };
    requires scalar_value<std::remove_cvref_t<decltype(*a)>>;
  };
}

namespace eve::detail
{
  //================================================================================================
  // SIMD
  //================================================================================================
  template<scalar_pointer Ptr>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), Ptr ptr) noexcept
                  -> as_wide_t<std::remove_cvref_t<decltype(*std::declval<Ptr>())>>
  {
    return as_wide_t<std::remove_cvref_t<decltype(*ptr)>>(ptr);
  }

  template<scalar_pointer Ptr, typename Cardinal>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), Ptr ptr, Cardinal const &) noexcept
                  -> as_wide_t<std::remove_cvref_t< decltype(*std::declval<Ptr>())>
                                                  , typename Cardinal::type
                                                  >
  {
    return as_wide_t<std::remove_cvref_t<decltype(*ptr)>, typename Cardinal::type>(ptr);
  }

  template<relative_conditional_expr C, scalar_pointer Ptr>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), C const &cond, Ptr ptr) noexcept
                  -> as_wide_t<std::remove_cvref_t<decltype(*std::declval<Ptr>())>>
  {
    using e_t = std::remove_cvref_t<decltype(*ptr)>;
    using r_t = as_wide_t< e_t >;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      return eve::load[cond](ptr.get());
    }
    else
    {
      // If the ignore/keep is complete we can jump over if_else
      if constexpr( C::is_complete )
      {
        if constexpr(C::is_inverted)  { return eve::load(ptr);  }
        else
        {
          if constexpr(C::has_alternative)  return r_t{cond.alternative};
          else                              return r_t{};
        }
      }
      else
      {
        auto offset = cond.offset( as_<r_t>{} );

        if constexpr(C::has_alternative)
        {
          [[maybe_unused]] r_t that(cond.alternative);
          auto* dst   = (e_t*)(&that.storage());
          std::memcpy( dst + offset, ptr + offset, cond.count( as_<r_t>{} ) );
          return that;
        }
        else
        {
          [[maybe_unused]] r_t that;
          auto* dst   = (e_t*)(&that.storage());
          std::memcpy( dst + offset, ptr + offset, cond.count( as_<r_t>{} ) );
          return that;
        }
      }
    }
  }

  template<relative_conditional_expr C, scalar_pointer Ptr, typename Cardinal>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), C const &cond, Ptr ptr, Cardinal const&) noexcept
                  -> as_wide_t<std::remove_cvref_t< decltype(*std::declval<Ptr>())>
                                                  , typename Cardinal::type
                                                  >
  {
    using e_t = std::remove_cvref_t<decltype(*ptr)>;
    using r_t = as_wide_t< e_t, typename Cardinal::type >;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      return eve::load[cond](ptr.get(), Cardinal{});
    }
    else
    {
      // If the ignore/keep is complete we can jump over if_else
      if constexpr( C::is_complete )
      {
        if constexpr(C::is_inverted)  { return eve::load(ptr);  }
        else
        {
          if constexpr(C::has_alternative)  return r_t{cond.alternative};
          else                              return r_t{};
        }
      }
      else
      {
        auto offset = cond.offset( as_<r_t>{} );

        if constexpr(C::has_alternative)
        {
          [[maybe_unused]] r_t that(cond.alternative);
          auto* dst   = (e_t*)(&that.storage());
          std::memcpy( dst + offset, ptr + offset, cond.count( as_<r_t>{} ) );
          return that;
        }
        else
        {
          [[maybe_unused]] r_t that;
          auto* dst   = (e_t*)(&that.storage());
          std::memcpy( dst + offset, ptr + offset, cond.count( as_<r_t>{} ) );
          return that;
        }
      }
    }
  }

  //================================================================================================
  // Scalar support
  //================================================================================================
  template<scalar_pointer Ptr>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), Ptr p, scalar_cardinal const&) noexcept
  {
    return *p;
  }

  template<scalar_pointer Ptr, scalar_value T>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_)
                            , converter_type<T> const&, Ptr p, scalar_cardinal const&
                            ) noexcept
  {
    return static_cast<T>(*p);
  }
}
