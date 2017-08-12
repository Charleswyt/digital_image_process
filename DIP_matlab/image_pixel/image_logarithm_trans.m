%% logarithm transformation of the image
% filename: image_logarithm_trans
% author: Wang Yuntao, 2017.8.12
% usage:
% image_origin: the original image
% slope: coefficient k
% intercept: constant b
% mapping: y = k * log(1 + x) + intercept

%{
    expand low gray area and compress high gray area
    generally k >= 10
%}

function image = image_logarithm_trans(image_origin, slope, intercept)
if nargin == 2
    intercept = 0;
end
image = slope * log(1 + double(image_origin)) + intercept;
image(image > 255) = 255;
image(image < 0) = 0;
image = uint8(image);
end