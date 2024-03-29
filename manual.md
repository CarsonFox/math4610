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

Routine Name: explicit_euler

Language: Julia

Description: Solves a first order differential equation, given some initial condition. This is an explicit method, which follows the derivative for some small timestep each iteration.

Input:

* f: The derivative of the function we're solving for
* x0: Initial value for the function being solved
* domain: Range of domain values to estimate the solution over

Output: Array of function values at each point in the domain

~~~ { .julia }
function explicit_euler(f, x0, domain)
    n = length(domain)
    # Assumes an evenly spaced domain
    h = domain[2] - domain[1]
    
    yhat = Array{Float64}(undef, n)
    yhat[1] = x0
    
    for i in 2:n
        yn = yhat[i-1]
        tn = domain[i-1]
        yhat[i] = yn + h*f(yn)
    end
    
    yhat
end
~~~


Routine Name: implicit_euler

Language: Julia

Description: Solve a first-order differential equation, given some initial condition. This is an implicit method, which requires finding the zero of a function. To do this, the Newton-Raphson method is used.

Input:

* f: The derivative of the function being solved for
* y0: Initial condition
* a: Left endpoint of the interval
* b: Right endpoint of the interval
* h: Size of each step

Output: Array of function values from a to b

~~~ { .julia }
function implicit_euler(f, y0, a, b, h)
    #Begin at t1
    t1 = a + h
    domain = t1:h:b
    yk = y0
    
    Y = [y0]
    
    for t in domain
        g(y) = yk + h*f(y) - y
        yk = newton_raphson(g, yk)
        Y = [Y; yk]
    end
    
    Y
end
~~~

# Numerical Integration


Routine Name: trapezoid

Language: Julia

Description: Estimates the integral of $f$ using the trapezoid rule.

Input:

* f: The function to be integrated
* a: Left endpoint of the interval
* b: Right endpoint of the interval
* n: Number of trapezoids

Output: Proper integral of $f$ from a to b

~~~ { .julia }
function trapezoid(f, a, b, n)
    h = (b-a) / n
    domain = a:h:b
    
    @assert domain[end] == b
    
    pairs = zip(domain[1:end-1], domain[2:end])
    sum(h * (f(an) + f(bn)) / 2 for (an, bn) in pairs)
end
~~~

Routine Name: simpson

Language: Julia

Description: Uses Simpson's rule to approximate the proper integral of a function. Has a higher order of convergence than the trapezoid rule, since it evaluates the function 3 times per iteration instead of two.

Input:

* f: The function being integrated
* a: Left endpoint of the interval
* b: Right endpoint of the interval
* h: Size of each step

Output: Proper integral of $f$ from a to b

~~~ { .julia }
function simpson(f, a, b, h)
    domain = a:h:b
    
    if domain[end] != b
        domain = vcat(domain, b)
    end
    
    @assert domain[end] == b
    
    pairs = zip(domain[1:end-1], domain[2:end])
    sum((bn - an) / 6 * (f(an) + 4f((an + bn) / 2) + f(bn)) for (an, bn) in pairs)
end
~~~
