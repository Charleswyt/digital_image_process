%% 邻域梯度倒数均值滤波
function image = neighbor_gradien_reciprocal_mean(image_origin, filter_size)

if nargin == 1
    filter_size = 3;
end

[height, width] = size(image_origin);
cut_size = filter_size - 1;
image = zeros(height - cut_size, width - cut_size);

for h = 1:height-filter_size+1
    for w = 1:width-filter_size+1
        block = image_origin(h:h+filter_size-1, w:w+filter_size-1);
        weights = neighbor_gradien_reciprocal(block);
        block_weights = double(block) .* weights;
        image(h, w) = sum(block_weights(:));
    end
end

image = uint8(image);
image(image < 0) = 0;image(image > 255) = 255;
image = image_padding(image_origin, image);

end