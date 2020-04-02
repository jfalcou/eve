.. _function-acotd:

#####
acotd
#####

**Required header** ``#include <eve/function/acotd.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ acotd = {};
   }

Function object computing the inverse sine in degrees of an :ref:`IEEEValue <concept-ieeevalue>` **v**

``acotd(x)`` returns the arc :math:`r` in the interval in degrees  :math:`[0, 180[` such that :math:`\cot(r) == x`.


********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes elementwise the mathematical value :math:`\arccot(1/v)` in degrees.
* [2] Computes the mathematical value :math:`\arccot(1/v)` in degrees.


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

.. include:: ../../../../test/doc/core/acotd.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/acotd.txt
  :literal:

