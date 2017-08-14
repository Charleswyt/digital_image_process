%% Gray to RGB
function image = GRAY2RGB(image_origin)

image_R = image_origin;
image_G = image_origin;
image_B = image_origin;

% gray_value <= 51
image_R(image_origin <= 51) = 0;
image_G(image_origin <= 51) = image_origin(image_origin <= 51) * 5;
image_B(image_origin <= 51) = 255;

% 51 < gray_value <= 102
image_R(image_origin > 51 & image_origin <= 102) = 0;
image_G(image_origin > 51 & image_origin <= 102) = 255;
image_B(image_origin > 51 & image_origin <= 102) = 255 - (image_origin(image_origin > 51 & image_origin <= 102) - 51) * 5;

% 102 < gray_value <= 153
image_R(image_origin > 102 & image_origin <= 153) = (image_origin(image_origin > 102 & image_origin <= 153) - 102) * 5;
image_G(image_origin > 102 & image_origin <= 153) = 255;
image_B(image_origin > 102 & image_origin <= 153) = 0;

% 153 < gray_value <= 204
image_R(image_origin > 153 & image_origin <= 204) = 255;
image_G(image_origin > 153 & image_origin <= 204) = 255 - ...
    uint8(128.0 * (image_origin(image_origin > 153 & image_origin <= 204) - 153) / 51.0 + 0.5);
image_B(image_origin > 153 & image_origin <= 204) = 0;

% 204 < gray_value <= 255
image_R(image_origin > 204) = 255;
image_G(image_origin > 204) = 127 - ...
    uint8(127.0 * (image_origin(image_origin > 204) - 204) / 51.0 + 0.5);
image_B(image_origin > 204) = 0;


image = cat(3, image_R, image_G, image_B);