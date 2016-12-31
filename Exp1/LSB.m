function [originText, length] = LSB(imagePath, messagePath, key)
    imgMat = imread(imagePath);
    figure;
    subplot(1,3,1);imshow(imgMat);title('Origin Picture');
    inputFile = fopen(messagePath, 'r');
    [msgBit, length] = fread(inputFile, 'ubit1');
    fclose(inputFile);
    [m, n] = size(imgMat);
    resMat = imgMat;
    diff = zeros(size(imgMat));
    for i = [1:length]
        x = floor((i - 1) / n) + 1;
        y = mod((i - 1), n) + 1;
        resMat(x, y) = imgMat(x, y) - mod(imgMat(x, y), 2) + msgBit(i);
        if (resMat(x, y) ~= imgMat(x, y))
            diff(x, y) = 255;
        end
    end
    originText = msgBit;
    subplot(1,3,2);imshow(resMat);title('Picture with hidden message');
    subplot(1,3,3);imshow(diff);title('Difference between two pictures');
    imwrite(resMat, 'output.bmp');
end