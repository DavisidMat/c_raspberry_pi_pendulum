#ifndef numerical_methods_h
#define numerical_methods_h

float derivative_forward_difference_method(float *x_before, float x_after,
    float *y_before, float y_after);
/*
This function calculates the numerical derivative using the forward difference
numerical method.

-----------
Parameters:
float x_before
    :)
float x_after
    :)
float y_before
    :)
float y_after
    :)

--------
Returns:
float y_derivative
*/

float integration_trapezoidal_method(float *x_before, float x_after,
    float *y_before, float y_after);
/*
This function calculates the numerical integration using the trapezoidal
numerical method.

-----------
Parameters:
float x_before
    :)
float x_after
    :)
float y_before
    :)
float y_after
    :)

--------
Returns:
float y_integral
*/

#endif