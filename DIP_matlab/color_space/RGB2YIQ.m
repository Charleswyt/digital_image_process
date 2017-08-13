%% RGB to YIQ
function image = RGB2YIQ(image_origin)

image_double = im2double(image_origin);                     % covert the image to double
image_R = image_double(:, :, 1);                            % read red channel
image_G = image_double(:, :, 2);                            % read green channel
image_B = image_double(:, :, 3);                            % read blue channel
 
transformation_matrix = ...
    [  0.299,  0.587, 0.114;
    0.596, -0.274, -0.322;
    0.212, -0.523, 0.311    ];

image_Y = transformation_matrix(1, 1) * image_R + transformation_matrix(1, 2) * image_G + transformation_matrix(1, 3) * image_B;
image_I = transformation_matrix(2, 1) * image_R + transformation_matrix(2, 2) * image_G + transformation_matrix(2, 3) * image_B;
image_Q = transformation_matrix(3, 1) * image_R + transformation_matrix(3, 2) * image_G + transformation_matrix(3, 3) * image_B;

image_Y = uint8(image_Y * 255);image_Y(image_Y < 0) = 0;image_Y(image_Y > 255) = 255;
image_I = uint8(image_I * 255);image_I(image_I < 0) = 0;image_I(image_I > 255) = 255;
image_Q = uint8(image_Q * 255);image_Q(image_Q < 0) = 0;image_Q(image_Q > 255) = 255;

image = cat(3, image_Y, image_I, image_Q);