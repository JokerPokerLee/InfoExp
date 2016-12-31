function h = Analysis(imagePath)
    image = imread(imagePath);
    [m, n] = size(image);
    h = zeros(256, 1);
    sz = n * m;
    p = zeros(sz, 1);
    pixel = (1 : sz) / sz;
    for i = 1 : sz
        x = floor((i - 1) / n) + 1;
        y = mod((i - 1), n) + 1;
        h(image(x, y) + 1) = h(image(x, y) + 1)+ 1;
        p(i) = test(h);
    end
    figure;
    plot(pixel, p);
    axis([0 1 -1 1]);
end