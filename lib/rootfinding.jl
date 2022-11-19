module RootFinding

function fixed_point(f, x0, tol=1e-6, max=100)
    y = f(x0)
    if abs(x0 - y) < tol || max ≤ 0
        x0
    else
        fixed_point(f, y, tol, max - 1)
    end
end

function functional_iter(f, x0, tol=1e-6, max=100)
    fixed_point(x -> x - f(x), x0, tol, max),
    fixed_point(x -> x + f(x), x0, tol, max)
end

function fixed_point_tab(f, x0, tol=1e-6, max=100, iter=1, tab=Matrix(undef, 0, 3))
    y = f(x0)
    err = abs(x0 - y)
    if err < tol || max ≤ 0
        x0, tab
    else
        fixed_point_tab(f, y, tol, max - 1, iter + 1, [tab; iter x0 err])
    end
end

function functional_iter_tab(f, x0, tol=1e-6, max=100)
    fixed_point_tab(x -> x - f(x), x0, tol, max),
    fixed_point_tab(x -> x + f(x), x0, tol, max)
end

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

function bisection_tab(f, a, b, tol=1e-6)
    tab = Matrix(undef, 0, 3)
    k = ceil(-log2(tol/(b-a)))
    
    for i in 1:k
        midpoint = (a + b) / 2
        fa, fm, fb = f.([a, midpoint, b])
        
        tab = [tab; i midpoint (b - a)]
        
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
    
    (a + b) / 2, tab
end

function newton_raphson(f, x0, max=1000, tol=1e-9)
    function derivative(f, epsilon=1e-9)
      x -> (f(x + epsilon) - f(x)) / epsilon
    end

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

function newton_raphson_tab(f, x0, max=1000, tol=1e-9)
    df = derivative(f)
    
    tab = Matrix(undef, 0, 3)
    guess = x0
    
    for i in 1:max
        error = abs(f(guess))
        tab = [tab; i guess error]
        
        if error < tol
            return tab
        end
        
        guess = guess - f(guess) / df(guess)
    end
    
    return tab
end

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

function secant_tab(f, x0, x1, max=1000, tol=1e-9)
    if x0 > x1
        return secant(f, x1, x0, max, tol)
    end
    
    tab = Matrix(undef, 0, 3)
    zero = x0
    
    for i in 1:max
        err = abs(f(zero))
        tab = [tab; i zero err]
        
        if err < tol
            return tab
        end
        
        fx0, fx1 = f(x0), f(x1)
        zero = x1 - fx1 * (x1 - x0) / (fx1 - fx0)
        
        x0 = x1
        x1 = zero
    end
    
    return tab
end

function hybrid_bn(f, a, b, threshold=1e-3, max=1000, tol=1e-9)
    bisection_approx = bisection(f, a, b, threshold)
    newton_raphson(f, bisection_approx, max, tol)
end

function hybrid_bs(f, a, b, threshold=1e-3, max=1000, tol=1e-9)
    k = ceil(-log2(threshold/(b-a)))
    
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
    @assert b - a < threshold
    
    secant(f, a, b, max, tol)
end

end
