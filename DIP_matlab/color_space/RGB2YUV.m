%% RGB to YUV
function image = RGB2YUV(image_origin)

image_red = image_origin(:, :, 1);                         % read red channel
image_green = image_origin(:, :, 2);                     % read green channel
image_blue = image_origin(:, :, 3);                        % read blue channel
transformation_matrix = ...
    [   0.299,  0.587,  0.114;
    -0.147, -0.289,  0.436;
    0.615, -0.515, -0.100    ];
image_Y = transformation_matrix(1, 1) *  image_red + transformation_matrix(1, 2) *  image_green + transformation_matrix(1, 3) *  image_blue;
image_U = transformation_matrix(2, 1) *  image_red + transformation_matrix(2, 2) *  image_green + transformation_matrix(2, 3) *  image_blue;
image_V = transformation_matrix(3, 1) *  image_red + transformation_matrix(3, 2) *  image_green + transformation_matrix(3, 3) *  image_blue;
image = cat(3, image_Y, image_U, image_V);