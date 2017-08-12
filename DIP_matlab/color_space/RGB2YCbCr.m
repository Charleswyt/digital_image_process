%% RGB to YCbCr
function image = RGB2YCbCr(image_origin)

image_red = image_origin(:, :, 1);                         % read red channel
image_green = image_origin(:, :, 2);                     % read green channel
image_blue = image_origin(:, :, 3);                        % read blue channel
transformation_matrix = ...
    [  0.299, 0.587, 0.114, 0;
    -0.1687, -0.3313, 0.500, 128;
    0.500, -0.4187, 0.0813, 128    ];
image_Y  = transformation_matrix(1, 1) *  image_red + transformation_matrix(1, 2) *  image_green ...
    + transformation_matrix(1, 3) *  image_blue + transformation_matrix(1, 4);
image_I   = transformation_matrix(2, 1) *  image_red + transformation_matrix(2, 2) *  image_green ...
    + transformation_matrix(2, 3) *  image_blue + transformation_matrix(2, 4);
image_Q = transformation_matrix(3, 1) *  image_red + transformation_matrix(3, 2) *  image_green ...
    + transformation_matrix(3, 3) *  image_blue + transformation_matrix(3, 4);
image = cat(3, image_Y, image_I, image_Q);