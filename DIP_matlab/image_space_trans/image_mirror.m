%%  图像的镜像变换
% 使用说明：
% image_mirror(image_origin, mirror_method)
% image_origin：原始图像
% mirror_method：变换方式，固定"horizental"(水平镜像)和"vertical"(垂直镜像)两种选择

function image = image_mirror(image_origin, mirror_method)

% Method one:
%     flipdim(X,DIM) returns X with dimension DIM flipped
%     image_vertical_mirror     = flipdim(image_origin,1);          % 图像的垂直镜像
%     image_horizental_mirror = flipdim(image_origin,2);            % 图像的水平镜像

%     if strcmp(mirror_method, 'horizental') == 1
%         image_mirror = flipdim(image_origin, 2);
%     elseif strcmp(mirror_method, 'vertical') == 1
%         image_mirror = flipdim(image_origin, 1);
%     else
%         disp('Error: Mirror direction error!');
%     end

% Method two:
[height, width, channel] = size(image_origin);                      % 计算原始图像的高度和宽度
image = image_origin;                                               % image初始值为原始图像

if strcmp(mirror_method, 'horizental') == 1 || strcmp(mirror_method, '1') == 1
    for h = 1 : height
        for w = 1 : width - 1
            image(h, w, 1:channel) = image_origin(h, width - w, 1:channel);
        end
    end
    
elseif strcmp(mirror_method, 'vertical') == 1 || strcmp(mirror_method, '2') == 1
    for h = 1 : height - 1
        for w = 1 : width
            image(h, w, 1:channel) = image_origin(height - h, w, 1:channel);
        end
    end
    
else
    disp('Error: Mirror direction error!');
end

end