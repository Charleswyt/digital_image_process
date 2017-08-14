%% RGB to XYZ
function image = RGB2XYZ(image_origin)

image_double = im2double(image_origin);                     % covert the image to double
image_R = image_double(:, :, 1);                            % read red channel
image_G = image_double(:, :, 2);                            % read green channel
image_B = image_double(:, :, 3);                            % read blue channel

transformation_matrix = ...
    [0.412453, 0.357580, 0.180423;
    0.212671, 0.715160, 0.072169;
    0.019334, 0.119193, 0.950227];

image_X = transformation_matrix(1, 1) * image_R + transformation_matrix(1, 2) * image_G + transformation_matrix(1, 3) * image_B;
image_Y = transformation_matrix(2, 1) * image_R + transformation_matrix(2, 2) * image_G + transformation_matrix(2, 3) * image_B;
image_Z = transformation_matrix(3, 1) * image_R + transformation_matrix(3, 2) * image_G + transformation_matrix(3, 3) * image_B;

image_X = uint8(image_X * 255);image_X(image_X < 0) = 0;image_X(image_X > 255) = 255;
image_Y = uint8(image_Y * 255);image_Y(image_Y < 0) = 0;image_Y(image_Y > 255) = 255;
image_Z = uint8(image_Z * 255);image_Z(image_Z < 0) = 0;image_Z(image_Z > 255) = 255;

image = cat(3, image_X, image_Y, image_Z);