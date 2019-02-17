#ifndef EVE_DETAIL_IS_BITWISE_LOGICAL_HPP_INCLUDED
#define EVE_DETAIL_IS_BITWISE_LOGICAL_HPP_INCLUDED

#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  
// is_bitwise_logical
  template<typename T>
  struct  is_bitwise_logical
        : std::bool_constant<sizeof(T) == sizeof(as_logical_t<T>)>
  {};

  template<typename T> inline constexpr bool
  is_bitwise_logical_v = is_bitwise_logical<T>::value_type;
}

#endif
