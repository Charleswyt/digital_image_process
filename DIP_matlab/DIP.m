clc;
clear all;
close all;

image_path = 'C:\Users\Administrator\MatlabProject\DIP\1.jpg';
%% ---------------- image read ---------------- %%
image_origin  = imread(image_path);                                                     % 读取图像
image_gray    = rgb2gray(image_origin);                                                 % 彩色图像转灰度图像
[heigth, width] = size(image_gray);                                                     % height为图像高度，width为图像宽度

%% ------- image space trans -------- %%
% mirror
% image_mirror = image_mirror(image_origin, mirror_method)
% image_origin为待处理图像
% mirror_method : 'horizental'表示水平镜像，'vertical'表示垂直镜像
image_mirror = image_mirror(image_origin, 'horizental');

% translation
move_x = 25;
move_y = 25;
image_translation = image_translation(image_origin, move_x, move_y);

% cut
start_x = 10;
start_y = 10;
crop_size_x = 300;
crop_size_y = 300;
image_crop = imcrop(image_origin, [start_x, start_y, crop_size_x, crop_size_y]);

% rotate
rotate_angle = 45;
% interpolation_mathod : nearest bilinear bicubic
image_rotation_nearest = image_rotation(image_origin, rotate_angle, 'nearest');         % 最近邻插值
image_rotation_bilinear = image_rotation(image_origin, rotate_angle, 'bilinear');       % 双线性插值
image_rotation_bicubic = image_rotation(image_origin, rotate_angle, 'bicubic');         % 三次内插值

% 缩放

%% ---------------- image show ---------------- %%
%imshow(image_origin);                                                                  % 显示彩色图像
%imshow(image_gray);                                                                    % 显示灰度图像
%imshow(image_mirror);                                                                  % 显示镜像图像
%imshow(image_translation);                                                             % 显示平移图像
%imshow(image_crop);                                                                    % 显示裁剪图像
%imshow(image_rotation_nearest);                                                        % 显示旋转图像
%inshow(image_)
