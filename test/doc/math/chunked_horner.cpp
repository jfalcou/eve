// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>


template<kumi::product_type Tuple>
void print(std::string s, Tuple const& t)
{
  kumi::apply
  (
    [s](auto const&... args)
    {
      std::cout << s << " = [";
      std::size_t n{0};
      ((std::cout << args << (++n != kumi::size<Tuple>::value ? ", " : "")), ...);
      std::cout << ']';
    }, t
  );

  std::cout << '\n';
}

template<eve::scalar_value T, eve::scalar_value ... Ts>
auto reverse_horner(T x, Ts const &... coefs) noexcept
{

  using e_t =  eve::common_value_t<T, Ts...>;
  using w_t = eve::wide<e_t>;
  auto t = kumi::make_tuple(coefs...);
//  constexpr auto siz = sizeof...(Ts);
  constexpr auto nblanes = w_t::size();
//  constexpr auto remain = siz % nblanes;
  std::cout << "nblanes " << nblanes << std::endl;
  std::cout << "x " << x << std::endl;
  auto head = eve::as_wides(eve::zero(eve::as<e_t>()), t);
  print("head", head);
  auto zz = e_t(1);
  w_t xx([&zz, x](auto ,  auto){ auto z = zz; zz *= x; return z;});
  e_t xn = eve::pow(x, nblanes);
  std::cout << "xn " << xn << std::endl;
  xx =  eve::reverse(xx);
  std::cout << "xx " << xx << std::endl;
  auto res = kumi::map([&xx, &xn](auto tt){auto fac = xx; xx*= xn; return tt*fac;  }, head);
  print("head ", head);
  print("res ", res);
  return x;

//   auto [car, cdr] = kumi::split(tup,  kumi::index<remain>);
//   auto head = eve::as_wides(eve::zero(eve::as<e_t>()), cdr);
//   auto zz =  T(1);
//   w_t xx([&zz, x](auto ,  auto ){ auto z = zz; zz *= x; return z;});
//   auto xc = zz;
//   bool domul = false;
//   auto sum = [&domul, &xx, xc](auto &s, auto v)
//   {
// //     std::cout <<  " -> i  " << i << std::endl;
// //     std::cout <<  " -> v  " << v << std::endl;
// //     std::cout <<  " -> xx " <<xx << std::endl;
// //     std::cout <<  " -> s  " << s << std::endl;
//     s = eve::fam(s, v, xx);
//     if (domul) xx*= xc; else domul = true;
// //     std::cout <<  " apres -> s  " << s << std::endl;
//     return s;
//   };
//   auto r = kumi::apply([sum](auto... m){return sum(s, m)...); }, head);
//   return r;
}


//   auto swc = scalarize(wc);
//   auto wcov1 = kumi::apply([](auto...m){return welford_covariance(m...);}, swc);
//   if constexpr(remain != 0)
//     return eve::welford_covariance(welford_covariance(car1, car2), wcov1);
//   else
//     return wcov1;
// }


int main()
{
  auto a = reverse_horner(2.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f);
  std::cout << "a " << a << std::endl;

  kumi::tuple t{1, 2, 3, 4};
  auto xx = 1;
  auto xn = 2;
  auto res = kumi::reverse(kumi::map([&xx, &xn](auto tt){auto fac = xx; xx*= xn; return tt*fac;  }, kumi::reverse(t)));
  print("t", t);
  print("res", res);

}
