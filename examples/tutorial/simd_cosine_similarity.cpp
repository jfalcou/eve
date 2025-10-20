//! [simd-function]
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <array>
#include <bit>
#include <tts/tts.hpp>

template < typename T>
struct vec3
{
  T x, y, z;
};

template<std::size_t I, typename T>
decltype(auto) get(vec3<T> const& v) noexcept
{
  if constexpr(I==0) return v.x;
  if constexpr(I==1) return v.y;
  if constexpr(I==2) return v.z;
}

template<std::size_t I, typename T>
decltype(auto) get(vec3<T>& v) noexcept
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
template<typename T>
struct kumi::is_product_type<vec3<T>> : std::true_type
{};


// Adapt as structured bindable type
template<typename T>
struct  std::tuple_size<vec3<T>>
      : std::integral_constant<std::size_t,3> {};

template<std::size_t I, typename T> struct std::tuple_element<I,vec3<T>> { using type = T; };


int main()
{

  vec3<float> a(1.0, 2.0, 3.0);
  vec3<float> b(-3.0, -4.0, -6.0);
  std::cout <<  "a " << a << std::endl;
  std::cout <<  "b " << b << std::endl;
  std::cout << "eve::cosine_similarity(a, b) = "<< eve::cosine_similarity(a, b) << std::endl;
  std::cout << "eve::cosine_similarity(a, a) = " << eve::cosine_similarity(a, a) << std::endl;
  std::cout << "eve::cosine_similarity(b, a) = " << eve::cosine_similarity(b, a) << std::endl;
  std::cout << "eve::cosine_similarity(b, b) = " << eve::cosine_similarity(b, b) << std::endl;

  using wv3_t = eve::wide<vec3<float>, eve::fixed<4>>;
  auto wa = wv3_t(a, a, b, b);
  auto wb = wv3_t(b, a, a, b);
  std::cout << "eve::cosine_similarity(wa, wb) = "<< eve::cosine_similarity(wa, wb) << std::endl;
  std::cout << "wa " << wa << std::endl;
  std::cout << "wb " << wb << std::endl;

  using w_t = eve::wide<float, eve::fixed<4>>;
  w_t vx0{1.0, 1.0, -3.0, -3.0};
  w_t vx1{2.0, 2.0, -4.0,-4.0,};
  w_t vx2{3.0, 3.0, -6.0,-6.0,};

  w_t vy0{ -3.0, 1.0, 1.0, -3.0};
  w_t vy1{ -4.0, 2.0, 2.0, -4.0};
  w_t vy2{ -6.0, 3.0, 3.0, -6.0};


  auto z1 = kumi::tuple{vx0, vx1, vx2};
  auto z2 = kumi::tuple{vy0, vy1, vy2};
  std::cout << "eve::cosine_similarity(z1, z2) = "<< eve::cosine_similarity(z1, z2) << std::endl;
  std::cout << "z1 " << z1 << std::endl;
  std::cout << "z2 " << z2 << std::endl;

}
