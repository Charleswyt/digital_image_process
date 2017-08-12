%% CMY to RGB
function image = CMY2RGB(image_origin)

image_cyan = image_origin(:, :, 1);                        % read cyan channel
image_magenta = image_origin(:, :, 2);                 % read magenta channel
image_yellow = image_origin(:, :, 3);                      % read yellow channel

image_red = 255 -  image_cyan;
image_green = 255 -  image_magenta;
image_blue = 255 -  image_yellow;
image = cat(3, image_red, image_green, image_blue);