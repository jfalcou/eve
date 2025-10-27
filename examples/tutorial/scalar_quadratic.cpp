//! [scalar-function]
#include <iostream>
#include <array>
#include <cmath>

int main()
{
  auto print = [](std::string name, auto v){ //utility to print the results
    std::cout << name << " =  {";
    for(std::size_t i=0; i <  v.size(); ++i) std::cout << v[i] << ((i != v.size()-1) ? ", ":"}");
    std::cout << std::endl;
  };

  auto quadratic = [](auto const& a, auto const& b, auto const& c){
    if (a == 0) return std::pair(-c/b, a/a);                 // second root is nan
    auto delta = b*b-4*a*c;                                  // compute delta
    auto rmax = (-b-(b > 0 ? 1 : 0)*std::sqrt(delta))/(2*a); // compute the root with maximal absolute value
    auto rmin = (rmax == 0 ? 0 : c/(rmax*a));                // compute the other root
    if (rmin > rmax) std::swap(rmin, rmax);                  // order by increasing values
    return std::pair(rmin, rmax);                            // return properly typed values
  };

  using a_t = std::array<double, 11>;

  a_t a{5.0,  12.0,  6.0,  7.0, 1.0, 1.0,   1.0,   1.0, 1.0e-20, 0.0, 1.0};
  a_t b{3.0,   1.0,  4.0, -2.0, 2.0, 1.0,   1.0,   1.0, 1.0e20,  1.0, 2.0};
  a_t c{-1.0, -5.0, -6.0, -6.0, 5.0, 30.0, 35.0, -40.0, -1.0,   -1.0, 1.0};
  a_t rmin, rmax;

  for(std::size_t i=0; i < 11; ++i){
    auto p =  quadratic(a[i], b[i], c[i]);
    rmin[i] = p.first;
    rmax[i] = p.second;
  }
  print("a   ", a);
  print("b   ", b);
  print("c   ", c);
  print("rmin", rmin);
  print("rmax", rmax);
}
//! [scalar-function]
