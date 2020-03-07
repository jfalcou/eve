.. _function-sqrt:

####
sqrt
####

**Required header:** ``#include <eve/function/sqrt.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ sqrt = {};
   }

Function object computing the square root value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise square root value of the :ref:`wide <type-wide>`.
* [2] Computes the square root value of the scalar.

Parameters
**********

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

Return value
**************

* [1,2] A value with the same type as the parameter.

Notes
*******

 For postive Integral typed entries the return is the truncation of the real result

Options
*******

  - With :ref:`raw_ <feature-decorator>` decorator: if any fast and dirty intrinsic exists it will be returned by the  call

Example
*******

.. include:: ../../../../test/doc/core/sqrt.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/sqrt.txt
  :literal:
