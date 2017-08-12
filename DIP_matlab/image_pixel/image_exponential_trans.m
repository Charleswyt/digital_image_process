%% exponential transformation of the image
% filename: image_exponential_trans
% author: Wang Yuntao, 2017.8.12
% usage:
% image_origin: the original image
% slope: coefficient k
% power: power r
% intercept: constant b
% mapping: y = k * x^r + intercept

%{
    expand high gray area and compress low gray area
    generally k <= 2
%}

function image = image_exponential_trans(image_origin, slope, power, intercept)
if nargin == 3
    intercept = 0;
end
image = slope * double(image_origin) ^ power + intercept;
image(image > 255) = 255;
image(image < 0) = 0;
image = uint8(real(image));
end