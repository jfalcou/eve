// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <vector>

template < typename T> T dot(std::vector<T> a, std::vector<T> b)
{
  auto siz = a.size();
  if (siz == 0) return T(0);
  auto [s, e] = eve::two_prod(a[0], b[0]);
  for (std::size_t i = 1; i < siz; ++i)
  {
    auto [s1, e1] = eve::two_fma_approx(a[i], b[i], s);
    e+= e1;
    s = s1;
  }
  return s+e;
}


int main()
{
  std::vector a = {1.0, 2.0, 3.0, 4.0};
  std::vector b = {2.0, 3.0, 4.0, 5.0};
   std::cout << "-> dot(a, b) = "<< dot(a, b) << "\n";
}
