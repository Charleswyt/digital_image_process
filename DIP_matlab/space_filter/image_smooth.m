%% smooth the image
function image = image_smooth(image_origin, method, filter_size)

if nargin == 2
    filter_size = 3;
end

if strcmp(method, 'average') == 1
    image = filter2(fspecial(method, filter_size), image_origin);
elseif strcmp(method, 'median') == 1
    image = medfilt2(image_origin, [filter_size, filter_size]);
    
else
    disp('尚未实现当前滤波方式');
    image = image_origin;
end
image = uint8(image);