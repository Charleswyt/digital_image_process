%% YUV to RGB
function image = YUV2RGB(image_origin)

image_double = im2double(image_origin);                     % covert the image to double
image_Y = image_double(:, :, 1);                            % read Y channel
image_U = image_double(:, :, 2);                            % read U channel
image_V = image_double(:, :, 3);                            % read V channel

transformation_matrix = ...
    [   1.000,  0.000,  1.402;
    1.000, -0.34414,  -0.71414;
    1.000, 1.1772, 0.000    ];

image_R = transformation_matrix(1, 1) * image_Y + transformation_matrix(1, 2) * image_U + transformation_matrix(1, 3) * image_V;
image_G = transformation_matrix(2, 1) * image_Y + transformation_matrix(2, 2) * image_U + transformation_matrix(2, 3) * image_V;
image_B = transformation_matrix(3, 1) * image_Y + transformation_matrix(3, 2) * image_U + transformation_matrix(3, 3) * image_V;

image = cat(3, image_R, image_G, image_B);
image = max(min(image, 255), 0);