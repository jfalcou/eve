.. _function-min:

###
min
###

**Required header:** ``#include <eve/function/min.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ min = {};
   }

Function object computing the minimum of two :ref:`Values <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T> constexpr               T         operator()( T a, T b ) noexcept;

* [1] Computes the element-wise minimum of both :ref:`wides <type-wide>`.
* [2,3] Computes the minimum of the scalar with each element of the :ref:`type-wide` instance.
* [4] Computes the minimum of both scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide`.
* **s**, **t**: Scalar values of type **U** which must be convertible to **T**.
* **a**, **b**: Scalar values of type **T**

.. rubric:: Return value

* [1-3] A value with the same type as the :ref:`type-wide` parameter.
* [4] A value of type **T**.

Notes
*****

    For any given value `x` and `y` of type  `T`:

    Using `min(x, y)` is similar to `(x < y) ? x : y` which is the standard behaviour.

    With this definition with floating point entries min(`Nan(as(y))`,`y`) should return `y`...

    On some systems the intrinsic used returns a nan value as soon `x` or `y` is a nan value.
    So the real definition of our `min` function must add: but if `x` is a nan value the result is system dependent.

    This can be corrected using the pedantic_ options that ensures the standard behaviour at a cost.

Options
*******

Example
*******

.. include:: ../../../../test/doc/min.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/min.txt
  :literal:
