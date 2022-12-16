% Software Manual
% Carson Fox - A02251670
% Dec 2022

# Root Finding

Routine Name: fixed_point

Language: Julia

Description: Uses fixed point iteration to find the fixed point of a function f - that is, the point x such that f(x) = x.

Input:

* f: The function to find a fixed point of
* x0: An initial guess for the fixed point
* tol: Optional. The tolerance for convergence
* max: Optional. The maximum number of iterations

Output: The fixed point x

~~~ { .julia }
function fixed_point(f, x0, tol=1e-6, max=100)
    y = f(x0)
    if abs(x0 - y) < tol || max <= 0
        x0
    else
        fixed_point(f, y, tol, max - 1)
    end
end
~~~

Routine Name: functional_iter

Language: Julia

Description: Uses fixed point iteration to find zero(s) of a function $f$, by finding the fixed points of the functions $g_-(x) = x - f(x)$, and $g_+(x) = x + f(x)$. If either of these converge, the result will satisfy $f(x) = 0$.

Input:

* f: The function to find a zero of
* x0: An initial guess for the zero
* tol: Optional. The tolerance for convergence
* max: Optional. The maximum number of iterations

Output: The tuple of the results of fixed point iteration on the two aforementioned functions

~~~ { .julia }
function functional_iter(f, x0, tol=1e-6, max=100)
    fixed_point(x -> x - f(x), x0, tol, max),
    fixed_point(x -> x + f(x), x0, tol, max)
end
~~~

Routine Name: bisection

Language: Julia

Description: Uses the bisection method to find a zero of the function $f$.

Input:

* f: The function to find a zero of
* a: The left endpoint of the interval being bisected
* b: The right endpoint of the interval being bisected
* tol: Optional. The tolerance for convergence

Output: The location of a zero for the funtion f, up to the requested tolerance

~~~ { .julia }
function bisection(f, a, b, tol=1e-6)
    k = ceil(-log2(tol/(b-a)))
    
    for i in 1:k
        midpoint = (a + b) / 2
        fa, fm, fb = f.([a, midpoint, b])
        
        if fa * fm < 0
            b = midpoint
        elseif fm * fb < 0
            a = midpoint
        else
            error(string("Could not locate zero in interval ", a, ", ", b))
        end
    end
    
    # Ensure we achieved desired accuracy
    @assert b - a < tol
    
    (a + b) / 2
end
~~~

Routine Name: derivative

Language: Julia

Description: Estimate the first derivative of a function $f$. First-order accurate.

Input:

* f: The function to take the derivative of
* epsilon: A parameter controlling the precision of the approximation

Output: A function that approximates the derivative at some point x

~~~ { .julia }
function derivative(f, epsilon=1e-9)
    x -> (f(x + epsilon) - f(x)) / epsilon
end
~~~

Routine Name: newton_raphson

Language: Julia

Description: Newton-Raphson iteration uses a derivative approximation to find zeros of a function $f$. This is a second-order method, but has slow convergence for roots of multiplicity other than 1.

Input:

* f: The function to find a zero of
* x0: An initial guess for the zero
* max: Optional. Maximum number of iterations
* tol: Optional. Tolerance for detecting convergence

Output: An approximate solution to $f(x) = 0$

~~~ { .julia }
function newton_raphson(f, x0, max=1000, tol=1e-9)
    guess = x0
    df = derivative(f)
    
    for i in 1:max
        error = abs(f(guess))
        if error < tol
            return guess
        end
        
        guess = guess - f(guess) / df(guess)
    end
    
    return guess
end
~~~

Routine Name: secant

Language: Julia

Description: An implementation of the secant method for rootfinding. Requires two initial guesses. The order of convergence is the golden ratio, $\phi$.

Input:

* f: The function to find a zero of
* x0: An initial guess for the zero
* x1: An initial guess for the zero
* max: Optional. Maximum number of iterations
* tol: Optional. Tolerance for detecting convergence

Output:

~~~ { .julia }
function secant(f, x0, x1, max=1000, tol=1e-9)
    if x0 > x1
        return secant(f, x1, x0, max, tol)
    end
    
    zero = x0
    
    for _ in 1:max
        err = abs(f(zero))
        
        if err < tol
            return zero
        end
        
        fx0, fx1 = f(x0), f(x1)
        zero = x1 - fx1 * (x1 - x0) / (fx1 - fx0)
        
        x0 = x1
        x1 = zero
    end
    
    return zero
end
~~~

Routine Name: d2x

Language: Julia

Description: Approximates the second derivative of the function $f$. Equivalent to composing two second-order accurate first derivative approximations.

Input:

* f: The function to take the second derivative of
* h: Optional. Parameter controlling the precision of the approximation

Output: A function that estimates $f''(x)$

~~~ { .julia }
function d2x(f, h=1e-6)
    x0 -> (f(x0 + h) - 2f(x0) + f(x0 - h)) / h^2
end
~~~

# Differential Equations

Routine Name:

Language: Julia

Description:

Input:

*

Output:

~~~ { .julia }

~~~


Routine Name:

Language: Julia

Description:

Input:

*

Output:

~~~ { .julia }

~~~

# Linear Algebra
