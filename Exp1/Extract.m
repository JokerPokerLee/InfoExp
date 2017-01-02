function [text] = Extract(imagePath, length, key)
    imgMat = imread(imagePath);
    [m, n] = size(imgMat);
    msgBit = zeros(length, 1);
    sz = length / 8;
    message = zeros(sz,1);
    for i = [1:length]
        x = floor((i - 1) / n) + 1;
        y = mod((i - 1), n) + 1;
        msgBit(i) = mod(imgMat(x, y), 2);
        if (mod(i, 8) == 0)
            z = i / 8;
            for j = [1 : 8]
                message(z) = message(z) * 2 + msgBit(i - j + 1);
            end
        end
    end
    text = message;
    output = fopen('decrypt.txt', 'w');
    fprintf(output, '%s', text);
    fclose(output);
end