%% 中值滤波
function image = neighbor_median_filter(image_origin, filter_size)

if nargin == 1
    filter_size = 3;
end

[height, width] = size(image_origin);
cut_size = filter_size - 1;
image = zeros(height - cut_size, width - cut_size);

% 中值滤波
for h = 1:end-filter_size
    for w = 1:width-filter_size+1
        block = image_origin(h:h+filter_size-1, w:w+filter_size-1);
        image(h, w) = median(block(:));
    end
end
image = image_padding(image_origin, image);