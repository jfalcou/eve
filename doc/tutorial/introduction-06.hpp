#error This file is for documentation only - DO NOT INCLUDE
/**

@page intro-05 Solving quadratic equations

This example demonstrates solving multiple quadratic equations in parallel using EVE.

For each quadratic equation \f$ax^2 + bx + c = 0\f$, we compute the discriminant  \f$b^2 - 4ac\f$
and then calculate the solution using the maximal absolute value root by the usual quadratic formula:
\f$ x_1 = \frac{-b -\mathbf{sign}(b)\sqrt{b^2 - 4ac}}{2a}\f$
and the second root \f$ x_2\f$, using the fact that  \f$\frac ca\f$ is equal to \f$x_1*x_2\f$.

This is the stable way for computing the roots that respects the relative errors and is ok even if \f$b^2 - 4ac \approx b^2\f$.

The computation must returns two Nans if the roots are not real or all coefficients are zero
and one Nan if the first parameter is zero.
(For complex roots use kyosu library which is fit to complex numbers scalar or SIMD computations and more).

We'll solve 11 different quadratic equations simultaneously. (11 just to show that the number of equations need not
be a multiple of the SIMD current harware vector size).

But first let us see the scalar case:

We suppose that the quadratic coefficients are given in variables `a`, `b` and  `c` having a floating type float or double;

The scalar code (without EVE) can look like this:

@snippet tutorial/scalar_quadratic.cpp scalar-function

What have we to do for allowing treatment of multiple quadratic equations in an SIMD fashion?

Let us give the complete program
and comment the steps later.

@snippet tutorial/simd_quadratic.cpp simd-function

If we suppose that the coefficients are still given in three `std::array` (any contiguous range type can do the job)  `a`, `b` and  `c`.
   We must read the three arrays by chunks in simd vectors, apply to the triple of simd vectors a resolution algorithm then store the results.
   - ***EVE*** core has the material to write the simd resolution.
   - ***EVE*** algo has the material to iterate on scalar datas in an SIMD way using the SIMD resolution.
   - The delicate pass is to transmit the input datas and recover the results in a proper way: this is mainly the `eve::zip` work,  that allow
     to jump from aos to soa.
     - `r` is a view to the pair of arrays containing the results (`zip` is mandatory to define it)
     - We give as input the `zip(aa, bb, cc)` triple of datas arrays

Now  the lambda quad_it do the same kind of work as the primary scalar version, but in an simd way.
Differences are:
  - The lambda must have an unique paramater to fit the transform_to requirements. This parameter is bound to the three simd vectors by </br >
    `auto [aaa, bbb, ccc] = e;`
  - The routine to solve the equation is also to be a bit changed :
    - we slightly optimize the computations by using `fnma` and `fma` (which turn to normal  computations using *+- if SIMD intrinsics
      are not available),  but this is not mandatory.
    - The use of `eve::if_else` is necessary because we have to compute the two branches has the zero equality can
      arise in some but not all lanes of `rmax`.
    - the `swap_if` line is only necessary if we want roots ordered by increasing order.
    - The case where some `aaa`are zero is deported at the end and treated differently.
    - To return the appropriate data to be used by `eve::transform_to` the call to `eve::zip` is required.

# Conclusion

 We have solved using SIMD parallelism a bunch of quadratic equation, without explicit knowledge of the current architecture.

**/
