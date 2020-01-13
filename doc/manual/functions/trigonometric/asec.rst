.. _function-asec:

#####
asec
#####

**Required header** ``#include <eve/function/asec.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ asec = {};
   }

Function object computing  the inverse secant in radian: (:math:`\arccos(1/x)`) of an :ref:`IEEEValue <concept-ieeevalue>` **v**


********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes elementwise the mathematical value :math:`\arccos(1/v)`.
* [2] Computes the mathematical value :math:`\arccos(1/s)`.


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
    that  ``asec`` returns +0 if the argument is +1. It has less accuracy near 1 than the regular call, but is 2 times speedier .

*******
Example
*******

.. include:: ../../../../test/doc/core/asec.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/asec.txt
  :literal:

