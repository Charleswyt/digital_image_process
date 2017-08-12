%% RGB to XYZ
function image = RGB2XYZ(image_origin)

image_red = image_origin(:, :, 1);                         % read red channel
image_green = image_origin(:, :, 2);                     % read green channel
image_blue = image_origin(:, :, 3);                        % read blue channel
transformation_matrix = ...
    [   0.412453, 0.357580, 0.180423;
    0.212671, 0.715160, 0.072169;
    0.019334, 0.119193, 0.950227    ];
image_X = transformation_matrix(1, 1) *  image_red + transformation_matrix(1, 2) *  image_green + transformation_matrix(1, 3) *  image_blue;
image_Y = transformation_matrix(2, 1) *  image_red + transformation_matrix(2, 2) *  image_green + transformation_matrix(2, 3) *  image_blue;
image_Z = transformation_matrix(3, 1) *  image_red + transformation_matrix(3, 2) *  image_green + transformation_matrix(3, 3) *  image_blue;
image = cat(3, image_X, image_Y, image_Z);