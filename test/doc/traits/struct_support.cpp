#include <eve/product_type.hpp>
#include <eve/wide.hpp>

// vector is a product type made of 3 floats
struct vector : eve::struct_support<vector, float, float, float>
{
  // To simplify member access, we can wrap access to the product type
  // elements via a named friend accessor.
  friend decltype(auto) x(eve::like<vector> auto&& self)
  {
    return get<0>(std::forward<decltype(self)>(self));
  }

  friend decltype(auto) y(eve::like<vector> auto&& self)
  {
    return get<1>(std::forward<decltype(self)>(self));
  }

  friend decltype(auto) z(eve::like<vector> auto&& self)
  {
    return get<2>(std::forward<decltype(self)>(self));
  }

  // Defines += over vector to automatically generates +
  friend auto& operator+= ( eve::like<vector> auto& self
                          , eve::like<vector> auto const& other
                          )
  {
    x(self) += x(other);
    y(self) += y(other);
    z(self) += z(other);
    return self;
  }

  // Defines -= over vector to automatically generates -
  friend auto& operator-= ( eve::like<vector> auto& self
                          , eve::like<vector> auto const& other
                          )
  {
    x(self) -= x(other);
    y(self) -= y(other);
    z(self) -= z(other);
    return self;
  }

  // Defines stream insertion
  friend std::ostream& operator<<( std::ostream& os, eve::like<vector> auto const& self )
  {
    return os << "{" << x(self) << ", " << y(self) << ", " << z(self) << "}";
  }
};

int main()
{
  eve::wide<vector> p ( [](auto i, auto )
                          {
                            return vector{1.f+i,4.f-i,1.f/(1+i)};
                          }
                        );
  std::cout << p << "\n";

  p = p + p;
  std::cout << p << "\n";

  p -= vector{1,1,1};
  std::cout << p << "\n";
}
