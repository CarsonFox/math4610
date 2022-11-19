module Integration

export simpson

function simpson(f, a, b, h)
    domain = a:h:b
    
    if !(b in domain)
        domain = vcat(domain, b)
    end
    
    @assert domain[end] == b
    
    pairs = zip(domain[1:end-1], domain[2:end])
    sum((bn - an) / 6 * (f(an) + 4f((an + bn) / 2) + f(bn)) for (an, bn) in pairs)
end

end
