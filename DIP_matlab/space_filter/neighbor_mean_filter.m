%% 邻域均值滤波
function image = neighbor_mean_filter(image_origin, mean_type, del, filter_size)

if nargin == 1
    filter_size = 3;
    mean_type = 'arithmetic';
elseif nargin >= 2
    filter_size = 3;
end

[height, width] = size(image_origin);
cut_size = filter_size - 1;
filter_area = filter_size * filter_size;
image = zeros(height - cut_size, width - cut_size);
image_double = im2double(image_origin);

% 算术均值滤波
if strcmp(mean_type, 'arithmetic')
    for h = 1:height-filter_size+1
        for w = 1:width-filter_size+1
            block = image_double(h:h+filter_size-1, w:w+filter_size-1);
            %         image(h, w) = mean(block(:));
            image(h, w) = sum(block(:)) / filter_area;
        end
    end
    
    % 模板法 filter = ones(filter_size)
    % filter_area = filter_size * filter_size;
    % filter = 1 / filter_area * ones(filter_size);
    % image = imfilter(image_origin, filter, 'same', 'replicate');
    % image = uint8(image);
    
% 几何均值滤波
elseif strcmp(mean_type, 'geometry')
    for h = 1:height-filter_size+1
        for w = 1:width-filter_size+1
            block = image_double(h:h+filter_size-1, w:w+filter_size-1);
            %         image(h, w) = mean(block(:));
            image(h, w) = geomean(block(:));
        end
    end
    
% 谐波均值滤波
elseif strcmp(mean_type, 'harmonic')
    for h = 1:height-filter_size+1
        for w = 1:width-filter_size+1
            block = image_double(h:h+filter_size-1, w:w+filter_size-1);
            %         image(h, w) = mean(block(:));
            image(h, w) = harmmean(block(:));
        end
    end

% 逆谐波均值滤波 
elseif strcmp(mean_type, 'invharmonic')
    for h = 1:height-filter_size+1
        for w = 1:width-filter_size+1
            block = image_double(h:h+filter_size-1, w:w+filter_size-1);
            %         image(h, w) = mean(block(:));
            image(h, w) = invharmmean(block(:));
        end
    end

% 修正alpha均值滤波
elseif strcmp(mean_type, 'revise')
    for h = 1:height-filter_size+1
        for w = 1:width-filter_size+1
            block = image_double(h:h+filter_size-1, w:w+filter_size-1);
            %         image(h, w) = mean(block(:));
            image(h, w) = revisemean(block(:), del);
        end
    end
end

image = uint8(image * 255);
image = image_padding(image_origin, image);

end