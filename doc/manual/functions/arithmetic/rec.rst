.. _function-rec:

###
rec
###

**Required header:** ``#include <eve/function/rec.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ rec = {};
   }

Function object computing the inverse of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  inverse of the :ref:`wide <type-wide>`.
* [2] Computes the inverse of the scalar.

Parameters
**********

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

Return value
**************

* [1,2] A value with the same type as the parameter. *TODO*


Options
*******

  - with :ref:`raw_ <feature-decorator>` decorator: if a proper intrinsic exist it is called with possibly poor accuracy in return
  - with no decorator an accurate inverse is provided
  - with :ref:`pedantic_ <feature-decorator>` decorator: with integral inputs the inverse 0 is :ref:`Valmax <constant-Valmax>` of the type


.. seealso::  :ref:`div <function-div>`

Example
*******

.. include:: ../../../../test/doc/core/rec.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/rec.txt
  :literal:
