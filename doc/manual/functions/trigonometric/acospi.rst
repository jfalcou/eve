.. _function-acospi:

######
acospi
######

**Required header** ``#include <eve/function/acospi.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ acospi = {};
   }

Function object computing the inverse cosine in :math:`\pi` multiples of an :ref:`IEEEValue <concept-ieeevalue>` **v**

``acospi(x)`` returns the arc :math:`r` in :math:`\pi` multiples in the interval :math:`[0, 1[` such that :math:`\cos(\pi r) == x`.
If :math:`x` is outside :math:`[-1, 1[` the result is a Nan.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes elementwise the mathematical value :math:`\arccos(v)` in :math:`\pi` multiples.
* [2] Computes the mathematical value :math:`\arccos(s)` in :math:`\pi` multiples.


.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance

.. rubric:: Return value

* [1] A value of type **wide<T,N>**.
* [2] A value of type **T**.



*******
Options
*******

   regular (no_option) and raw_ are available.

  - raw_ call ensures the IEEE requisites that the call returns a Nan.If :math:`x` is outside :math:`[-1, 1]` and
    that  ``acospi`` returns +0 if the argument is +1. It has less accuracy near 1 than the regular call, but is 2 times speedier .

*******
Example
*******

.. include:: ../../../../test/doc/core/acospi.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/acospi.txt
  :literal:

