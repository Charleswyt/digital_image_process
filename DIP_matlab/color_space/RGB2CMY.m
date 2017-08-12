%% RGB to CMY
function image = RGB2CMY(image_origin)

image_red = image_origin(:, :, 1);                         % read red channel
image_green = image_origin(:, :, 2);                     % read green channel
image_blue = image_origin(:, :, 3);                        % read blue channel

image_cyan = 255 -  image_red;
image_magenta = 255 -  image_green;
image_yellow = 255 -  image_blue;
image = cat(3, image_cyan, image_magenta, image_yellow);