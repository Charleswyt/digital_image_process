function image = simle_neighbor_mean(image_origin, filter_size)

if nargin == 1
    filter_size = 3;
end

% [height, width] = size(image_origin);
% cut_size = filter_size - 1;
% filter_area = filter_size * filter_size;
% image = zeros(height - cut_size, width - cut_size);
% 
% for h = 1:height-filter_size+1
%     for w = 1:width-filter_size+1
%         block = image_origin(h:h+filter_size-1, w:w+filter_size-1);
%         image(h, w) = sum(block(:)) / filter_area;
%     end
% end
% 
% image = uint8(image);
% image = image_padding(image_origin, image);

filter_area = filter_size * filter_size;
filter = 1 / filter_area * ones(filter_size);
image = imfilter(image_origin, filter, 'same', 'replicate');
image = uint8(image);

end