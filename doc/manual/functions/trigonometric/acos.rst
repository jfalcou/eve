.. _function-acos:

#####
acos
#####

**Required header** ``#include <eve/function/acos.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ acos = {};
   }

Function object computing the inverse cosine of an :ref:`IEEEValue <concept-ieeevalue>` **v**

``acos(x)`` returns the arc :math:`r` in the interval   :math:`[0, \pi[` such that :math:`\cos(r) == x`.
If :math:`x` is outside :math:`[-1, 1]` the result is a Nan.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v ) noexcept;
   template<typename T            > constexpr   T         operator()( T s ) noexcept;

* [1] Computes elementwise the mathematical value :math:`\arccos(v)`.
* [2] Computes the mathematical value :math:`\arccos(s)`.


.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance

.. rubric:: Return value

* [1] A value of type **wide<T,N>**.
* [2] A value of type **T**.


*******
Options
*******

   regular (no_option) and pedantic_ are available.

  - regular call ensures the IEEE requisites that the call returns a Nan.If :math:`x` is outside :math:`[-1, 1]` and
    that  ``acos`` returns +0 if the argument is +1.

  - pedantic_ option ensures more accuracy near 1 than the regular call, but speed is divided by a factor 2.

*******
Example
*******

.. include:: ../../../../test/doc/core/acos.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/acos.txt
  :literal:

