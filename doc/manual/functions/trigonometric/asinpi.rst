.. _function-asinpi:

#####
asinpi
#####

**Required header** ``#include <eve/function/asinpi.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ asinpi = {};
   }

Function object computing the inverse sine in :math:`\pi` multiples of an :ref:`IEEEValue <concept-ieeevalue>` **v**

``asinpi(x)`` returns the arc :math:`r` in the interval :math:`[-0.5, 0.5[`, in :math:`\pi` multiples such that :math:`\sin(\pi r) == x`.
If :math:`x` is outside :math:`[-1, 1[` the result is a Nan.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes elementwise the mathematical value :math:`\arcsin(v)` in :math:`\pi` multiples.
* [2] Computes the mathematical value :math:`\arcsin(s)` in :math:`\pi` multiples.


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

.. include:: ../../../../test/doc/core/asinpi.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/asinpi.txt
  :literal:

