function image = image_padding(image_ref, image_cur)
height_ref = size(image_ref, 1);
height_cur = size(image_cur, 1);
padding_size = (height_ref - height_cur) / 2;
image = image_ref;
image(1 + padding_size : end - padding_size, 1 + padding_size : end - padding_size) ...
 = image_cur;
end