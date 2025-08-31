// revision 1
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <iomanip>

template<typename T, std::invocable<std::span<T>> F>
decltype(auto) with_alloca(auto size, F f)
{
  T* p = (T*)(__builtin_alloca_with_align(size*sizeof(T), 8*alignof(T)));
  auto s = std::span(p, size);
  return f(s);
}

template<typename T, std::invocable<std::span<T>, std::span<T>> F>
decltype(auto) with_alloca(auto size, F f)
{
  T* p1 = (T*)(__builtin_alloca_with_align(size*sizeof(T), 8*alignof(T)));
  T* p2 = (T*)(__builtin_alloca_with_align(size*sizeof(T), 8*alignof(T)));
  auto s1 = std::span(p1, size);
  auto s2 = std::span(p2, size);
  return f(s1, s2);
}



auto efthorner = [](auto x,  auto a){
  constexpr auto N = 4;
  using r_t = float;
  std::array<r_t, N> err, s;
  s[0] = a[0];
  err[0] = 0;
  for(int i=1; i < N; ++i)
  {
    auto [pi, epi] = eve::two_prod(s[i-1], x);
    auto [si, esi] = eve::two_add(pi, a[i]);
    s[i] = si;
    err[i] = epi+esi;
  };
  std::cout << "err " << eve::horner(x, err) << std::endl;
  return s[N-1]+ eve::horner(x, err);
};

auto efthorner2 = []<typename T, typename C,  typename ...Cs>(T x,  C a0, Cs ... a){
  using r_t = eve::common_value_t<T, C, Cs...>;
  constexpr auto N =  sizeof...(Cs)+1;
  std::array<r_t, N> err;
  err[0] = 0;
  auto i = 1;
  auto s = a0;
  auto step = [&s, &err, x, &i]( auto a)
  {
    auto [pi, epi] = eve::two_prod(s, x);
    auto [si, esi] = eve::two_add(pi, a);
    s = si;
    err[i] = epi+esi;
    ++i;
    return s;
  };
  ((s = step(a)), ...);
  std::cout << "err " << eve::horner(x, err) << std::endl;
  return s+ eve::horner(x, err);
};


int main()
{
  std::array<float, 4> a ={1.234f, -2.234f, 3.234f, -4.234f};
  std::cout << std::setprecision(15) << efthorner(2.234f, a) << std::endl;
//   std::cout <<    eve::horner(2.234f, a) << std::endl;
//   std::cout <<    eve::horner(2.234f, a)-efthorner(2.234f, a) << std::endl;
  std::cout << std::endl;
  std::cout <<  efthorner2(2.234f, 1.234f, -2.234f, 3.234f, -4.234f) << std::endl;
};
