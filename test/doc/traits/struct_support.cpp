#include <eve/product_type.hpp>
#include <eve/wide.hpp>

// position is a product type made of 3 floats
struct position : eve::struct_support<position, float, float, float>
{
  // To simplify member access, we can wrap access to the product type
  // elements via a named friend accessor.
  friend decltype(auto) x(eve::like<position> auto&& self)
  {
    return get<0>(std::forward<decltype(self)>(self));
  }

  friend decltype(auto) y(eve::like<position> auto&& self)
  {
    return get<1>(std::forward<decltype(self)>(self));
  }

  friend decltype(auto) z(eve::like<position> auto&& self)
  {
    return get<2>(std::forward<decltype(self)>(self));
  }

  // Defines += over position to automatically generates +
  friend auto& operator+= ( eve::like<position> auto& self
                          , eve::like<position> auto const& other
                          )
  {
    x(self) += x(other);
    y(self) += y(other);
    z(self) += z(other);
    return self;
  }

  // Defines -= over position to automatically generates -
  friend auto& operator-= ( eve::like<position> auto& self
                          , eve::like<position> auto const& other
                          )
  {
    x(self) -= x(other);
    y(self) -= y(other);
    z(self) -= z(other);
    return self;
  }

  // Defines stream insertion
  friend std::ostream& operator<<( std::ostream& os, eve::like<position> auto const& self )
  {
    return os << "{" << x(self) << ", " << y(self) << ", " << z(self) << "}";
  }
};

int main()
{
  eve::wide<position> p ( [](auto i, auto )
                          {
                            return position{1.f+i,4.f-i,1.f/(1+i)};
                          }
                        );
  std::cout << p << "\n";

  p = p + p;
  std::cout << p << "\n";

  p -= position{1,1,1};
  std::cout << p << "\n";
}