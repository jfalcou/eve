.. _function-bitofsign:

#########
bitofsign
#########

**Required header:** ``#include <eve/function/bitofsign.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ bitofsign = {};
   }

Function object computing the bit of sign of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Returns the element-wise masking of all bits of the parameter except the highest one.
* [2] Returns the masking of all bits of the parameter except the highest one. .

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Example
*******

.. include:: ../../../../test/doc/core/bitofsign.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/bitofsign.txt
  :literal:
