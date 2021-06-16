//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/memory/aligned_ptr.hpp>
#include <eve/detail/kumi.hpp>

#include <concepts>

namespace eve
{
  template<typename T, typename Enable=void>
  struct pointer_traits
  {
    using value_type = void;
  };

  template<typename T> struct pointer_traits<T*>        { using value_type = T; };
  template<typename T> struct pointer_traits<T const*>  { using value_type = T; };

  template<typename T>
  struct pointer_traits<T, std::void_t<typename T::value_type>>
  {
    using value_type = typename T::value_type;
  };

  template<typename... Ptrs>
  struct pointer_traits<kumi::tuple<Ptrs...>>
  {
    using value_type = kumi::tuple<typename pointer_traits<Ptrs>::value_type...>;
  };
}

namespace eve::detail
{
  template<typename Ptr>
  concept behaves_as_ptr = !std::same_as<typename pointer_traits<Ptr>::value_type,void>
  && requires(Ptr p)
  {
    { *p };
  };

  template<typename Ptr>
  struct is_data_source : std::bool_constant<behaves_as_ptr<Ptr>>
  {};

  template<typename... Ptrs>
  struct is_data_source<kumi::tuple<Ptrs...>> : std::bool_constant<(behaves_as_ptr<Ptrs> && ...)>
  {};

  template<typename Ptr>
  concept data_source = is_data_source<Ptr>::value;

  template<typename T, typename Ptr> struct dereference_as;

  template<typename T, typename Ptr>
  requires( !kumi::product_type<Ptr> )
  struct dereference_as<T,Ptr>
  {
    using base = typename pointer_traits<Ptr>::value_type;
    static constexpr bool value = std::same_as<T,base>;
  };

  template<typename T, typename... Ptrs>
  struct dereference_as<T, kumi::tuple<Ptrs...>>
  {
    using base = kumi::tuple<typename pointer_traits<Ptrs>::value_type...>;
    static constexpr bool value = std::same_as<T,base>;
  };

  template <typename T>
  EVE_FORCEINLINE auto as_raw_pointer(T p)
  {
    if constexpr ( !std::is_pointer_v<T> ) return p.get();
    else                                   return p;
  }

  template <typename U, typename T, typename Lanes>
  EVE_FORCEINLINE auto ptr_cast(eve::aligned_ptr<T, Lanes> p)
  {
    return aligned_ptr<U, eve::fixed<Lanes() * sizeof(T) / sizeof(U)>>{(U*)(p.get())};
  }

  template <typename U, typename T>
  EVE_FORCEINLINE auto ptr_cast(T* p)
  {
    return (U*)p;
  }
}
