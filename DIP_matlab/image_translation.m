%% 图像的平移操作
%   translate Translate units in sweepset
%   S = translate(S,M,C) translates the units using the conversion factors
%  in M (gain) and C (offset).
function image_translation = image_translation(image_origin, move_height, move_width)

% Method one:
% strel 用于创建形态学结构元素
move_height = fix(move_height);                                 % 图像平移高度取整
move_width = fix(move_width);                                    % 图像平移宽度取整
se = translate(strel(1), [move_height, move_width]);  % 在结构元素se上进行height和width方向上的偏移
image_translation = imdilate(image_origin,se);           % 形态学膨胀

% Method two:
%     image_gray = rgb2gray(image_origin);        % 将原始图像转化为灰度图
%     [height, width] = size(image_gray);               % height为图像的高度，width为图像的宽度
%     image_translation = image_origin;                % image_translation初值为原始图像
%
%     for i = 1:height
%         for j = 1:width
%             if( (i - move_height > 0) && (i - move_height < height)...
%                     && (j - move_width > 0) && (j - move_width) < width)
%                 image_translation(i, j, 1:3) = image_origin(i - move_height, j - move_width, 1:3);
%              else
%                 image_translation(i, j,1:3) = 0;
%             end
%         end
%     end

end