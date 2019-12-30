.. _function-asecpi:

######
asecpi
######

**Required header** ``#include <eve/function/asecpi.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ asecpi = {};
   }

Function object computing the inverse secant in :math:`\pi` multiples of an :ref:`IEEEValue <concept-ieeevalue>` **v**

``asecpi(x)`` returns the arc :math:`r` in the interval in :math:`\pi` multiples  :math:`[0, 180[` such that :math:`\cos(1/r) == x`.
If :math:`x` is inside :math:`]-1, 1[` the result is a Nan.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes elementwise the mathematical value :math:`\arccos(1/v)` in :math:`\pi` multiples.
* [2] Computes the mathematical value :math:`\arccos(1/s)` in :math:`\pi` multiples.


.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance

.. rubric:: Return value

* [1] A value of type **wide<T,N>**.
* [2] A value of type **T**.


*******
Example
*******

.. include:: ../../../../test/doc/core/asecpi.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/asecpi.txt
  :literal:

