.. _function-maxmag:

#########
minnummag
#########

**Required header:** ``#include <eve/function/minnummag.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ minnummag = {};
   }

Function object computing the value of minimal magnitude between two :ref:`Values <concept-value>`, excluding nan value.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T> constexpr               T         operator()( T a, T b ) noexcept;

* [1] Computes the element-wise value of minimal magnitude between both :ref:`wides <type-wide>` excluding nan value.
* [2,3] Computes the value of minimal magnitude between the scalar and each element of the :ref:`type-wide` instance excluding nan value.
* [4] Computes the value of minimal magnitude between both scalars excluding nan value.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide`.
* **s**, **t**: Scalar values of type **U** which must be convertible to **T**.
* **a**, **b**: Scalar values of type **T**

.. rubric:: Return value

* [1-3] A value with the same type as the :ref:`type-wide` parameter.
* [4] A value of type **T**.

Notes
*****

 - For floating point entries, this object function returns a nan value if and only if both entries are a nan value.
 
Example
*******

.. include:: ../../../../test/doc/minnummag.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/minnummag.txt
  :literal:
