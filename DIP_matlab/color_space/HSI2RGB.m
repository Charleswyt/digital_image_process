%% HSI to RGB
function image = HSI2RGB(image_origin)

image_H = 2 * pi * image_origin(:, :, 1);                       % read H channel
image_S = image_origin(:, :, 2);                                % read S channel
image_I = image_origin(:, :, 3);                                % read I channel

[height, width] = size(image_H);
image_R = zeros(height, width);
image_G = zeros(height, width);
image_B = zeros(height, width);

%% RG sector 0 <= H < 2/3 * pi
index = find(image_H >= 0 & image_H < 2/3*pi);
image_B(index) = image_I(index) .* (1 - image_S(index));
image_R(index) = image_I(index) .* (1 + image_S(index) .* ...
    cos(image_H(index)) ./ cos(pi/3 - image_H(index)));
image_G(index) = 3 * image_I(index) - image_R(index) - image_B(index);

%% BG sector 2/3 * pi <= H < 4/3 * pi
index = find(image_H >= 2/3*pi & image_H < 4/3*pi);
image_R(index) = image_I(index) .* (1 - image_S(index));
image_G(index) = image_I(index) .* (1 + image_S(index) .* ...
    cos(image_H(index) - 2/3*pi) ./ cos(pi - image_H(index)));
image_B(index) = 3 * image_I(index) - image_R(index) - image_G(index);

%% BR sector 4/3 * pi <= H < 2 * pi
index = find(image_H >= 4/3*pi & image_H <= 2*pi);
image_G(index) = image_I(index) .* (1 - image_S(index));
image_B(index) = image_I(index) .* (1 + image_S(index) .* ...
    cos(image_H(index) - 4*3/pi) ./ cos(5/3*pi - image_H(index)));
image_R(index) = 3 * image_I(index) - image_G(index) - image_B(index);

image_R = uint8(image_R * 255);image_R(image_R < 0) = 0;image_R(image_R > 255) = 255;
image_G = uint8(image_G * 255);image_G(image_G < 0) = 0;image_G(image_G > 255) = 255;
image_B = uint8(image_B * 255);image_B(image_B < 0) = 0;image_B(image_B > 255) = 255;

%% merge
image = cat(3, image_R, image_G, image_B);