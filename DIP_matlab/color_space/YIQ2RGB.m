%% YIQ to RGB
function image = YIQ2RGB(image_origin)

image_Y = image_origin(:, :, 1);       
image_I = image_origin(:, :, 2);
image_Q = image_origin(:, :, 3);
transformation_matrix = ...
    [  1.000,  0.956, 0.621;
    1.000, -0.272, -0.647;
    1.000, -1.106, 1.703    ];
image_red = transformation_matrix(1, 1) *  image_Y + transformation_matrix(1, 2) *  image_I + transformation_matrix(1, 3) *  image_Q;
image_green = transformation_matrix(2, 1) *  image_Y + transformation_matrix(2, 2) *  image_I + transformation_matrix(2, 3) *  image_Q;
image_blue = transformation_matrix(3, 1) *  image_Y + transformation_matrix(3, 2) *  image_I + transformation_matrix(3, 3) *  image_Q;
image = cat(3, image_red, image_green, image_blue);