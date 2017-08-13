%% YIQ to RGB
function image = YIQ2RGB(image_origin)

image_double = im2double(image_origin);                     % covert the image to double
image_Y = image_double(:, :, 1);                            % read Y channel
image_I = image_double(:, :, 2);                            % read I channel
image_Q = image_double(:, :, 3);                            % read Q channel

transformation_matrix = ...
    [  1.000,  0.956, 0.621;
    1.000, -0.272, -0.647;
    1.000, -1.105, 1.702    ];

image_R = transformation_matrix(1, 1) * image_Y + transformation_matrix(1, 2) * image_I + transformation_matrix(1, 3) * image_Q;
image_G = transformation_matrix(2, 1) * image_Y + transformation_matrix(2, 2) * image_I + transformation_matrix(2, 3) * image_Q;
image_B = transformation_matrix(3, 1) * image_Y + transformation_matrix(3, 2) * image_I + transformation_matrix(3, 3) * image_Q;

image_R = uint8(image_R * 255);image_R(image_R < 0) = 0;image_R(image_R > 255) = 255;
image_G = uint8(image_G * 255);image_G(image_G < 0) = 0;image_G(image_G > 255) = 255;
image_B = uint8(image_B * 255);image_B(image_B < 0) = 0;image_B(image_B > 255) = 255;

image = cat(3, image_R, image_G, image_B);