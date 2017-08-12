%% grayscale cutting
% filename: image_exponential_trans
% author: Wang Yuntao, 2017.8.12
% usage:
% image_origin: the original image
% gray_start: started gray value
% gray_end: ended gray value
% gray: gray value

%{
    Enhance certain range contrast
%}

function image = image_gray_cut(image_origin, gray_start, gray_end, gray)
if (gray_start < 0 || gray_start > 255) || (gray_end < 0 || gray_end > 255) ...
        || (gray < 0 || gray > 255)
    disp('The gray value oversteps the boundary.');
else
    image = image_origin;
    image(image > gray_start & image < gray_end) = gray;
end