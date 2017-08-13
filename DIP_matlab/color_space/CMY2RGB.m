%% CMY to RGB
function image = CMY2RGB(image_origin)

image_C = image_origin(:, :, 1);                            % read C channel
image_M = image_origin(:, :, 2);                            % read M channel
image_Y = image_origin(:, :, 3);                            % read Y channel

image_R = 255 - image_C;
image_G = 255 - image_M;
image_B = 255 - image_Y;

image = cat(3, image_R, image_G, image_B);