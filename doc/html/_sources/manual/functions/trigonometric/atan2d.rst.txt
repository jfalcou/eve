.. _function-atan2d:

######
atan2d
######

**Required header:** ``#include <eve/function/atan2d.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ atan2d = {};
   }

Function object computing the quadrant aware `atan2d` function.


Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T> constexpr               T         operator()( T s, T t ) noexcept;

* [1] Computes element-wise ``atan(v/w)`` in degrees with quadrant awareness.
* [2,3] Computes element-wise  ``atan(v/s)`` in degrees with quadrant awareness.
* [4] Computes  ``atan(t/s)`` in degrees with quadrant awareness.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide`.
* **s**, **t**: Scalar values of type **U** which must be convertible to **T**.

.. rubric:: Return value

* [1-3] A value with the same type as the :ref:`type-wide` parameter.
* [4] A value of type **T**.

Notes
*******

    - For any real arguments  ``x`` and  ``y`` not both equal to zero, ``atan2d(y, x)``
      (be aware of the parameter order) is the angle in radians between the positive
      x-axis of a plane and the point  given by the coordinates ``(x, y)``.

    - It is also the angle in :math:`[-\pi,\pi[` for which :math:`x/\sqrt{x^2+y^2}` and :math:`y/\sqrt{x^2+y^2}`
      are respectively the sine and the cosine.

    - Following IEEE norms,  we should have:

      -  If y is :math:`\pm0` and x is negative or :math:`-0`, :math:`\pm180` is returned
      -  If y is :math:`\pm0` and x is positive or :math:`+0`, :math:`\pm0` is returned
      -  If y is :math:`\pm\infty` and x is finite, :math:`\pm90` is returned
      -  If y is :math:`\pm\infty` and x is :math:`-\infty`, :math:`\pm135` is returned
      -  If y is :math:`\pm\infty` and x is :math:`+\infty`, :math:`\pm45` is returned
      -  If x is :math:`\pm0` and y is negative, :math:`-90` is returned
      -  If x is :math:`\pm0` and y is positive, :math:`+90`  is returned
      -  If x is :math:`-\infty` and y is finite and positive, :math:`+180` is returned
      -  If x is :math:`-\infty` and y is finite and negative, :math:`-180` is returned
      -  If x is :math:`+\infty` and y is finite and positive, +0 is returned
      -  If x is :math:`+\infty` and y is finite and negative, -0 is returned
      -  If either x is Nan or y is Nan, Nan is returned

     The ``:ref:`pedantic_ <feature-decorator>``` decorator (call to ``pedantic_(eve::atan2d)(y, x)`` )
     ensures all these conditions, but the regular version
     (no decorator) will return a NaN if x and y are both either null or infinite,
     result which in fact is not more absurd than the IEEE choices.
     However, it will be conforming in all other cases.

Example
*******

.. include:: ../../../../test/doc/core/atan2d.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/atan2d.txt
  :literal:

