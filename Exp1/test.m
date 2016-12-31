function p = test(h)
    x = zeros(128, 1);
    for k = 1 : 128
        j = k * 2;
        i = j - 1;
        t = (h(i) + h(j)) / 2;
        if (t > 0)
            x(k) = (h(i) - t) / sqrt(t);
        else
            x(k) = -1e7;
        end
    end
    x = x + 1e7;
    x = nonzeros(x);
    x = x - 1e7;
    [hh, p] = chi2gof(x, 'cdf', {@normcdf, 0, 1});
    if (p == NaN)
        p = 0;
    end
end