%% RGB to CMY
function image = RGB2CMY(image_origin)

image_R = image_origin(:, :, 1);                            % read red channel
image_G = image_origin(:, :, 2);                            % read green channel
image_B = image_origin(:, :, 3);                            % read blue channel

image_C = 255 - image_R;
image_M = 255 - image_G;
image_Y = 255 - image_B;

image = cat(3, image_C, image_M, image_Y);