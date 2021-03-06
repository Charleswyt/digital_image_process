%% RGB to YUV
function image = RGB2YUV(image_origin)

image_double = im2double(image_origin);                     % covert the image to double
image_R = image_double(:, :, 1);                            % read red channel
image_G = image_double(:, :, 2);                            % read green channel
image_B = image_double(:, :, 3);                            % read blue channel

transformation_matrix = ...
    [	0.299, 0.587, 0.114;
    -0.1678, -0.3313, 0.500;
    0.5, -0.4187, -0.0813	];

image_Y = transformation_matrix(1, 1) * image_R + transformation_matrix(1, 2) * image_G + transformation_matrix(1, 3) * image_B;
image_U = transformation_matrix(2, 1) * image_R + transformation_matrix(2, 2) * image_G + transformation_matrix(2, 3) * image_B;
image_V = transformation_matrix(3, 1) * image_R + transformation_matrix(3, 2) * image_G + transformation_matrix(3, 3) * image_B;

image_Y = uint8(image_Y * 255);image_Y(image_Y < 0) = 0;image_Y(image_Y > 255) = 255;
image_U = uint8(image_U * 255);image_U(image_U < 0) = 0;image_U(image_U > 255) = 255;
image_V = uint8(image_V * 255);image_V(image_V < 0) = 0;image_V(image_V > 255) = 255;

image = cat(3, image_Y, image_U, image_V);