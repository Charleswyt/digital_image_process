%% read image in a certain color space
% usage£º
% image_read(image_file_path)
% image_file_path£ºthe path of original image
% image_type£ºthe type of output image
% type:
% RGB¡¢Gray¡¢Double¡¢YCbCr¡¢YUV¡¢Lab¡¢HSI¡¢XYZ¡¢YIQ
% if the parameter 'output_image_type' is not used, the default is set to RGB
% if the parameter 'original_image_type' is not used, the default is set to RGB

function [image, height, width] = image_read(image_file_path, output_image_type, original_image_type)
image_origin = imread(image_file_path);                  % read original image
try
    [height, width, channel] = size(image_origin);       % get the dimension information of 3-D image
catch
    [height, width] = size(image_origin);                % get the dimension information of 2-D image
end

% read gray image
if channel == 1
    image = image_origin;
end

% read color image
if channel == 3
    if nargin == 1
        image = image_origin;
    end
    
    if nargin == 2
        path = strcat(cd, '\color_space\');
        addpath(genpath(path));
        if strcmp(output_image_type, 'RGB')
            image = image_origin;
        elseif strcmp(output_image_type, 'GRAY')
            % imae = rgb2gray(image_origin);
            image = RGB2GRAY(image_origin);
        elseif strcmp(output_image_type, 'XYZ')
            image = RGB2XYZ(image_origin);
        elseif strcmp(output_image_type, 'CMY')
            % image = imcomplement(image_origin);
            image = RGB2CMY(image_origin);
        elseif strcmp(output_image_type, 'YUV')
            image = RGB2YUV(image_origin);
            image = YUV2RGB(image);
        elseif strcmp(output_image_type, 'YIQ')
            % image = rgb2ntsc(image_origin);
            image = RGB2YIQ(image_origin);
            image = YIQ2RGB(image);
        elseif strcmp(output_image_type, 'YCbCr')
            image = RGB2YCbCr(image_origin);
        elseif strcmp(output_image_type, 'HSI')
            image = RGB2HSI(image_origin);
        elseif strcmp(output_image_type, 'HSI')
            image = RGB2Lab(image_origin);
        end
    end
    if nargin == 3
        if strcmp(output_image_type, 'HSI') && strcmp(original_image_type, 'HSI')
        end
    end
end
