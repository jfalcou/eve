//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <concepts>
#include <type_traits>

#include <eve/as.hpp>
#include <eve/detail/kumi.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!
  //! @struct common_type
  //!
  //! @brief Computes a type that can represent all values in a list of types.
  //!
  //! **Required header:** `#include <eve/traits/common_type.hpp>`
  //!
  //! Similar to std::common_type.
  //!
  //! We cannot use std::common_type because it tends to return a bigger type:
  //!   For example: `std::int16_t`, `std::int8_t` will return `std::int32_t`: https://godbolt.org/z/vjf9c45E5
  //!
  //! We also do not follow standard promotion rules:
  //!      std::common_type_t<std::int16_t, std::uint16_t> is std::int32_t
  //! BUT: std::common_type_t<std::int32_t, std::uint32_t> is std::uint32_t
  //! We always do like 32 bit one: - eve::common_type_t<std::int16_t, std::uint16_t> is std::uint16_t
  //!
  //! *NOTE:* for signed unsigned of the same size we return unsigned of this size (same as std).
  //!
  //! For product types will compute the common type by field.
  //! If the result matches one of the specified types, we will return that one.
  //! Otherwise we'll return a `kumi::tuple` of the result.
  //!
  //! @}
  //================================================================================================
  template<typename T, typename ...Ts> struct common_type;

  template<typename ...Ts>
  using common_type_t = typename common_type<Ts...>::type;

  // We don't care for not default constructible types.
  template <typename ...Ts>
  concept have_common_type = requires (Ts...) {
    { common_type_t<Ts...>{} };
  };
}

namespace eve::detail
{
  struct no_common_type
  {
    template <typename U>
    friend constexpr auto operator+(no_common_type, U) { return no_common_type{}; }
  };

  template <typename T>
  struct common_type_reduction;

  template <typename, typename>
  struct common_kumi_tuple
  {
    using type = no_common_type;
  };

  template <typename ...Ts, typename ...Us>
  struct common_kumi_tuple<kumi::tuple<Ts...>, kumi::tuple<Us...>>
  {
    using type = common_type_reduction<kumi::tuple<eve::common_type_t<Ts, Us> ...>>;
  };


  template <typename T>
  struct common_type_reduction
  {
    using type = T;

    template <typename U>
    friend constexpr auto operator+(common_type_reduction<T> self, as<U>) {
      common_type_reduction<U> other{};

           if constexpr ( std::same_as<T, U>                                 ) return self;
      else if constexpr ( std::is_arithmetic_v<T> && std::is_arithmetic_v<U> )
      {
             if constexpr ( sizeof(U) < sizeof(T)                             ) return other + as<T>{};
        else if constexpr ( std::floating_point<T> && !std::floating_point<U> ) return self;
        else if constexpr ( std::floating_point<U> || sizeof(T) < sizeof(U)   ) return other;
        else if constexpr ( std::unsigned_integral<U>                         ) return other;
        else                                                                    return self;
      }
      else if constexpr ( kumi::product_type<T> && kumi::product_type<U> )
      {
        using t_as_tuple = typename kumi::as_tuple<T>::type;
        using u_as_tuple = typename kumi::as_tuple<U>::type;
        using tuple_res = typename common_kumi_tuple<t_as_tuple, u_as_tuple>::type;

        if constexpr ( std::same_as<no_common_type, tuple_res> ) return tuple_res{};
        else
        {
          using type = typename tuple_res::type;
               if constexpr ( std::same_as<type, t_as_tuple> ) return self;
          else if constexpr ( std::same_as<type, u_as_tuple> ) return other;
          else                                                 return tuple_res{};
        }
      }
      else return no_common_type{};
    }
  };
}

namespace eve
{
  template<typename T, typename ...Ts> struct common_type
  {
    using type = typename decltype(
                    (detail::common_type_reduction<T>{} + ... + as<Ts>{}))
                  ::type;
  };
}
