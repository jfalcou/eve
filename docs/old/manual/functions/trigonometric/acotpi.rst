.. _function-acotpi:

######
acotpi
######

**Required header** ``#include <eve/function/acotpi.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ acotpi = {};
   }

Function object computing the inverse sine in :math:`\pi` multiples of an :ref:`IEEEValue <concept-ieeevalue>` **v**

``acotpi(x)`` returns the arc :math:`r` in the interval  :math:`[0, 1[`  in :math:`\pi` multiplessuch that :math:`\cot(r) == x`.


********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes elementwise the mathematical value :math:`\arccot(1/v)` in :math:`\pi` multiples.
* [2] Computes the mathematical value :math:`\arccot(1/v)` in :math:`\pi` multiples.


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

.. include:: ../../../../test/doc/core/acotpi.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/acotpi.txt
  :literal:

