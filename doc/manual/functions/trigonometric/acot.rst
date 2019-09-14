.. _function-acot:

#####
acot
#####

**Required header** ``#include <eve/function/acot.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ acot = {};
   }

Function object computing the inverse cotangent of an :ref:`IEEEValue <concept-ieeevalue>` **v**

``acot(x)`` returns the arc :math:`r` in the interval   :math:`[0, \pi[` such that :math:`\cot(r) == x`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes the mathematical value :math:`\arctan(1/v)` .
* [2] Computes the mathematical value :math:`\arctan(1/s)`.
  

.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance

.. rubric:: Return value

* [1] A value of type **wide<T,N>**.
* [2] A value of type **T**.


*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/acot.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/acot.txt
  :literal:

