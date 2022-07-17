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
#include <eve/concept/value.hpp>
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
  //! Similar to `std::common_type`.
  //!
  //! We cannot use `std::common_type` because it tends to return a bigger type:
  //!   For example: `std::int16_t`, `std::int8_t` will return `std::int32_t`: https://godbolt.org/z/vjf9c45E5
  //!
  //! We also do not follow standard promotion rules:
  //!      `std::common_type_t<std::int16_t, std::uint16_t>` is `std::int32_t`
  //! BUT: `std::common_type_t<std::int32_t, std::uint32_t>` is `std::uint32_t`
  //! We always do like 32 bit one: - `eve::common_type_t<std::int16_t, std::uint16_t>` is `std::uint16_t`
  //!
  //! For functors from eve/constant support is incomplete: FIX-#941.
  //! For now, we just skip them.
  //!
  //! *NOTE:* for signed unsigned of the same size we return unsigned of this size (same as std).
  //!
  //! For product types TODO: FIX-#905
  //! Right now we have some simplified logic.
  //!
  //! @}
  //================================================================================================
  template<typename ...Ts> struct common_type;

  template<typename ...Ts>
  using common_type_t = typename common_type<Ts...>::type;

  // We don't care for not default constructible types.
  template <typename ...Ts>
  concept have_common_type = requires (Ts...) {
    { typename common_type<Ts...>::type{} };
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
  struct is_kumi_tuple : std::false_type {};

  template <typename ...Ts>
  struct is_kumi_tuple<kumi::tuple<Ts...>> : std::true_type {};

  template <typename T>
  concept is_kumi_tuple_v = is_kumi_tuple<T>::value;

  template <typename T>
  struct common_type_reduction;

  template <typename, typename>
  struct common_kumi_tuple
  {
    using type = no_common_type;
  };

  template <typename ...Ts, typename ...Us>
    requires (sizeof...(Ts) == sizeof...(Us))
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
      else if constexpr ( !value<T>                                      ) return other;
      else if constexpr ( !value<U>                                      ) return self;
      else if constexpr ( kumi::product_type<T> && kumi::product_type<U> )
      {
        using t_as_tuple = kumi::as_tuple_t<T>;
        using u_as_tuple = kumi::as_tuple_t<U>;
        using tuple_res  = typename common_kumi_tuple<t_as_tuple, u_as_tuple>::type;

        if constexpr ( !std::same_as<no_common_type, tuple_res> )
        {
          using type = typename tuple_res::type;

               if constexpr ( std::same_as<type, t_as_tuple> && !is_kumi_tuple_v<T> ) return self;
          else if constexpr ( std::same_as<type, u_as_tuple> && !is_kumi_tuple_v<U> ) return other;
          else                                                                        return tuple_res{};
        }
        else
        {
          using t_flat = kumi::result::flatten_all_t<T>;
          using u_flat = kumi::result::flatten_all_t<U>;
          using flat_res = typename common_kumi_tuple<t_flat, u_flat>::type;

          if constexpr ( std::same_as<no_common_type, flat_res> ) return flat_res{};
          else
          {
            using type = typename flat_res::type;

                 if constexpr ( std::same_as<type, t_flat> && !is_kumi_tuple_v<T> ) return self;
            else if constexpr ( std::same_as<type, u_flat> && !is_kumi_tuple_v<U> ) return other;
            else if constexpr ( std::same_as<type, t_flat>                        ) return self;
            else if constexpr ( std::same_as<type, u_flat>                        ) return other;
            else                                                                    return flat_res{};
          }
        }
      }
      else return no_common_type{};
    }
  };
}

namespace eve
{
  template <> struct common_type<>
  {
  };

  template<typename T, typename ...Ts> struct common_type<T, Ts...> :
    decltype((detail::common_type_reduction<T>{} + ... + as<Ts>{}))
  {
  };
}
