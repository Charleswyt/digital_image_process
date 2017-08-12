%% 图像旋转
% 几何原理：
% 旋转前：x = r × cosα  y = r × sinα
% 旋转后：x' = r × cos(α-θ) = r × cosα × cosθ + r × sinα × sinθ = x × cosθ + y × sinθ
%                y' = r × sin(α-θ) = r × sinα × cosθ - r × cosα × sinθ = -x × sinθ + y × cosθ
% 以矩阵的形式表示为：
%             inv( [x'; y'; 1] ) =
%      ([ cosθ, sinθ, 0; -sinθ, cosθ, 0; 0, 0, 1 ]) * inv([ x, y, 1 ])
% 逆运算为：
%             inv( [x; y; 1] ) =
%      ([ cosθ, -sinθ, 0; sinθ, cosθ, 0; 0, 0, 1 ]) * inv([ x', y', 1 ])
%
% 原始图像的像素坐标为整数，由于有浮点运算，变换后的目标图像的坐标位置可能不是整数。
% 所以，图像的旋转处理，除了要进行几何运算，还需要对目标图像的坐标位置进行插值处理。

%% 图像插值
% 1.最近邻插值      2.双线性插值      3.三次内插值

%  B = imrotate(A,ANGLE,METHOD) rotates image A, using the interpolation
%     method specified by METHOD. METHOD is a string that can have one of the
%     following values. The default value is enclosed in braces ({}).
%
%          {'nearest'}  Nearest neighbor interpolation
%
%          'bilinear'   Bilinear interpolation
%
%          'bicubic'    Bicubic interpolation. Note: This interpolation
%                       method can produce pixel values outside the original
%                       range.

function image_rotation = image_rotation(image_origin, rotate_angle, interpolation_mathod)

% image_rotation = imrotate(image_origin, rotate_angle, interpolation_mathod);

    rotate_radian = rotate_angle / 180 * pi;         % 将旋转的角度转为用弧度表示
    image_gray = rgb2gray(image_origin);         % 将原始图像转化为灰度图
    [height, width] = size(image_gray);                % 计算灰度图的高度和宽度

    rot = [cos(rotate_radian), -sin(rotate_radian) 0; sin(rotate_radian), cos(rotate_radian), 0; 0, 0, 1];
    pixel_left_on = [1, 1, 1] * rot;                         % 变换后图像左上点的坐标
    pixel_right_on = [1, w, 1] * rot;                       % 变换后图像右上点的坐标
    pixel_left_down = [heiht, 1, 1] * rot;               % 变换后图像左下点的坐标
    pixel_right_down = [height, wwidth, 1] * rot;  % 变换后图像右下点的坐标

    rotate_height = round( max( [ abs( pixel_left_on(1) - pixel_right_down(1)) + 0.5,  ...
        abs( pixel_right_on(1) - pixel_left_down(1) ) + 0.5 ] ) );     % 变换后图像的高度
    rotate_width  = round( max( [ abs( pixel_left_on(2) - pixel_right_down(2) ) + 0.5, ...
        abs( pixel_right_on(2) - pixel_left_down(2) ) + 0.5] ) );      % 变换后图像的宽度

    delta_height = abs(min( [ pixel_left_on(1), pixel_right_on(1), 
        pixel_left_down(1), pixel_right_down(1) ] ) );                      %取得hieght方向的负轴超出的偏移量
    delta_width = abs(min( [ pixel_left_on(2), pixel_right_on(2), 
        pixel_left_down(2), pixel_right_down(2) ] ) );                      %取得width方向的负轴超出的偏移量
    
    for i = 1 - delta_height : height - delta_height
        for j = 1 - delta_width : width - delta_width
            pixel_origin = [i, j, 1] / rot;                                                  %用变换后图像的点的坐标去寻找原图像点的坐标，
            % 否则有些变换后的图像的像素点无法完全填充
            float_height = pixel_origin(1) - floor( pixel_origin(1) );
            float_width   = pixel_origin(2) - floor( pixel_origin(2) );
            
            if pixel_origin(1) >= 1 && pixel_origin(2) >= 1 && pixel_origin(1)  <= height && pixel_origin(2) <= widths
            %四个相邻的点
                pix_up_left = [floor(pix(1)), floor(pix(2))];
                pix_up_right = [floor(pix(1)), ceil(pix(2))];
                pix_down_left = [ceil(pix(1)), floor(pix(2))];
                pix_down_right = [ceil(pix(1)), ceil(pix(2))];
                
                value_up_left = (1-float_X)*(1-float_Y);              %计算临近四个点的权重
                value_up_right = float_X*(1-float_Y);
                value_down_left = (1-float_X)*float_Y;
                value_down_right = float_X*float_Y;
                
                imgn(i + delta_y, j + delta_x) = value_up_left * img(pix_up_left(1), pix_up_left(2)) +  ...
                    value_up_right * img(pix_up_right(1), pix_up_right(2)) + ...
                    value_down_left * img(pix_down_left(1), pix_down_left(2)) +  ...
                    value_down_right * img(pix_down_right(1), pix_down_right(2));
            end   
        end
    end

end
