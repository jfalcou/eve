//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// adapting a vec3 structure for tests purposes

template < typename T> struct vec3 {  T x = 0, y = 0, z = 0;};

template<std::size_t I, typename T>
decltype(auto) get(vec3<T> & v) noexcept
{
  if constexpr(I==0) return v.x;
  if constexpr(I==1) return v.y;
  if constexpr(I==2) return v.z;
}

template<std::size_t I, typename T>
auto get(vec3<T> const & v) noexcept
{
  if constexpr(I==0) return v.x;
  if constexpr(I==1) return v.y;
  if constexpr(I==2) return v.z;
}

template < typename T>
std::ostream& operator << (std::ostream& os, vec3<T> const & v){
  os << '[' << v.x << ",  " << v.y << ", " << v.z << "]";
  return os;
}

// Opt-in for Product Type semantic
template<typename T> struct kumi::is_product_type<vec3<T>> : std::true_type{};

// Adapt as structured bindable type
template<typename T>
struct  std::tuple_size<vec3<T>> : std::integral_constant<std::size_t,3> {};

template<std::size_t I, typename T> struct std::tuple_element<I,vec3<T>> { using type = T; };
