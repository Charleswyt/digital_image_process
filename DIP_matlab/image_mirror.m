%%  图像的镜像变换
% 使用说明：
% image_mirror(image_origin, mirror_method)
% image_origin：原始图像
% mirror_method：变换方式，固定"horizental"(水平镜像)和"vertical"(垂直镜像)两种选择

function image_mirror = image_mirror(image_origin, mirror_method)

% Method one:
%     flipdim(X,DIM) returns X with dimension DIM flipped
%     image_vertical_mirror     = flipdim(image_origin,1);   % 图像的垂直镜像
%     image_horizental_mirror = flipdim(image_origin,2);   % 图像的水平镜像

%     if strcmp(mirror_method, 'horizental') == 1
%         image_mirror = flipdim(image_origin, 2);
%     elseif strcmp(mirror_method, 'vertical') == 1
%         image_mirror = flipdim(image_origin, 1);
%     else
%         disp('Error: Mirror direction error!');
%     end

% Method two:
image_gray = rgb2gray(image_origin);           % 将原始图像转化为灰度图
[height, width] = size(image_gray);                  % 计算灰度图的高度和宽度
image_mirror = image_origin;                          % image_mirror初始值为原始图像

if strcmp(mirror_method, 'horizental') == 1
    for i = 1 : height - 1
        for j = 1 : width - 1
            image_mirror(i, j, 1:3) = image_origin(i, width - j, 1:3);
        end
    end
    
elseif strcmp(mirror_method, 'vertical') == 1
    for i = 1 : height - 1
        for j = 1 : width - 1
            image_mirror(i, j, 1:3) = image_origin(height - i, j, 1:3);
        end
    end
    
else
    disp('Error: Mirror direction error!');
end

end