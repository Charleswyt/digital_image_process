%% YUV to RGB
function image = YUV2RGB(image_origin)

image_Y = image_origin(:, :, 1);
image_U = image_origin(:, :, 2);
image_V = image_origin(:, :, 3);
transformation_matrix = ...
    [   1.000,  0.000,  1.140;
    1.000, -0.390,  -0.580;
    1.000, 2.030, 0.000    ];
image_red = transformation_matrix(1, 1) *  image_Y + transformation_matrix(1, 2) *  image_U + transformation_matrix(1, 3) *  image_V;
image_green = transformation_matrix(2, 1) *  image_Y + transformation_matrix(2, 2) *  image_U + transformation_matrix(2, 3) *  image_V;
image_blue = transformation_matrix(3, 1) *  image_Y + transformation_matrix(3, 2) *  image_U + transformation_matrix(3, 3) *  image_V;
image = cat(3, image_red, image_green, image_blue);