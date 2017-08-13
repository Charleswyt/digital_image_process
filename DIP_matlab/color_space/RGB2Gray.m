%% RGB to Gray
function image = RGB2GRAY(image_origin)

image_R = image_origin(:, :, 1);                            % read red channel
image_G = image_origin(:, :, 2);                            % read green channel
image_B = image_origin(:, :, 3);                            % read blue channel

%% maximum value method
image = max(max(image_R, image_G), image_B);

%% mean value method
image = (image_R + image_G + image_B) / 3;

%% weighted mean value method
wg = 0.587; wr = 0.299; wb = 0.114;
image = wr * image_R + wg * image_G + wb * image_B;
