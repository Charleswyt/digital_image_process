%% simple linear transformation of the image
% filename: image_linear_trans
% author: Wang Yuntao, 2017.8.12
% usage:
% image_origin: the original image
% slope: slope k
% intercept: intercept b
% mapping: y = k * x + b

%{
    (1) k > 1, enhance the image contrast
    (2) k = 1, adjust the image brightness
    (3) 0 < k < 1, weaken the image contrast
    (4) k < 0, make the brighter area dark and make the darker area bright, especially if k == -1 and d = 255, color inverse
%}

function image = image_linear_trans(image_origin, slope, intercept)
image = slope * double(image_origin) + intercept;
image(image > 255) = 255;
image(image < 0) = 0;
image = uint8(image);
end