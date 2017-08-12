%% extract image bit plane
% filename: image_bit_plane
% author: Wang Yuntao, 2017.8.12
% usage:
% image_origin: the original gray image
% bit_level: bit plane level

function image = image_bit_plane(image_origin, bit_level)
image = bitshift(image_origin, bit_level-8);
end