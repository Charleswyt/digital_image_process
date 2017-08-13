%% Gray to RGB
function image = GRAY2RGB(image_origin)

image_R = image_origin;
image_G = image_origin;
image_B = image_origin;

image = cat(3, image_R, image_G, image_B);