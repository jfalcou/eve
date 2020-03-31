.. _function-cosh:

####
cosh
####

**Required header:** ``#include <eve/function/cosh.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ cosh = {};
   }

Function object computing the hyperbolic cosine  of a :ref:`Value <concept-value>`,
that is :math:`(e^x+e^{-x})/2`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  hyperbolic cosine of the :ref:`wide <type-wide>`.
* [2] Computes the hyperbolic cosine of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 


.. seealso::  :ref:`exp <function-exp>`,  :ref:`sinh <function-sinh>`,  :ref:`tanh <function-tanh>`, 
 :ref:`coth <function-coth>`,  :ref:`sech <function-sech>`,  :ref:`csch <function-csch>`

Example
*******

.. include:: ../../../../test/doc/core/cosh.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/cosh.txt
  :literal:
