%% Í¼Ïñ²Ã¼ô
function image = image_shave(image_origin, size)

image = image_origin(1 + size : end - size, 1 + size : end - size);

end