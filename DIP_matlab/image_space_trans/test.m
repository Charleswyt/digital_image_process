image_origin = image;
mirror_method = '3';
[height, width, channel] = size(image_origin);                      % 计算原始图像的高度和宽度
image_mirror = image_origin;                                        % image_mirror初始值为原始图像

if strcmp(mirror_method, 'horizental') == 1 || strcmp(mirror_method, '1') == 1
    for h = 1 : height
        for w = 1 : width - 1
            image_mirror(h, w, 1:channel) = image_origin(h, width - w, 1:channel);
        end
    end
    
elseif strcmp(mirror_method, 'vertical') == 1 || strcmp(mirror_method, '2') == 1
    for h = 1 : height - 1
        for w = 1 : width
            image_mirror(h, w, 1:channel) = image_origin(height - h, w, 1:channel);
        end
    end
    
else
    disp('Error: Mirror direction error!');
end