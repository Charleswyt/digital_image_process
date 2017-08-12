%% RGB to Gray
function image = RGB2Gray(image_origin)

image_red = image_origin(:, :, 1);                         % read red channel
image_green = image_origin(:, :, 2);                     % read green channel
image_blue = image_origin(:, :, 3);                        % read blue channel

%% maximum value method
image = max(max(image_red, image_green), image_blue);

%% mean value method
image = (image_red + image_green + image_blue) / 3;

%% weighted mean value method
wg = 0.587; wr = 0.299; wb = 0.114;
image = wr * image_red + wg * image_green + wb * image_blue;
