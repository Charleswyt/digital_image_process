%% XYZ to RGB
function image = XYZ2RGB(image_origin)

image_double = im2double(image_origin);                     % covert the image to double
image_X = image_double(:, :, 1);                            % read red channel
image_Y = image_double(:, :, 2);                            % read green channel
image_Z = image_double(:, :, 3);                            % read blue channel

transformation_matrix = ...
    [ 3.240479, -1.537150, -0.498535;
    -0.969256,  1.875992,  0.041556;
    0.055648, -0.204043,  1.057311];

image_R = transformation_matrix(1, 1) * image_X + transformation_matrix(1, 2) * image_X + transformation_matrix(1, 3) * image_X;
image_G = transformation_matrix(2, 1) * image_Y + transformation_matrix(2, 2) * image_Y + transformation_matrix(2, 3) * image_Y;
image_B = transformation_matrix(3, 1) * image_Z + transformation_matrix(3, 2) * image_Z + transformation_matrix(3, 3) * image_Z;

image_R = uint8(image_R * 255);image_R(image_R < 0) = 0;image_R(image_R > 255) = 255;
image_G = uint8(image_G * 255);image_G(image_G < 0) = 0;image_G(image_G > 255) = 255;
image_B = uint8(image_B * 255);image_B(image_B < 0) = 0;image_B(image_B > 255) = 255;

image = cat(3, image_R, image_G, image_B);