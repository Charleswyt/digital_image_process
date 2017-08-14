%% RGB to HSI
function image = RGB2HSI(image_origin)

image_double = im2double(image_origin);                         % convert the original image to double
image_R = image_double(:, :, 1);                                % read red channel
image_G = image_double(:, :, 2);                                % read green channel
image_B = image_double(:, :, 3);                                % read blue channel

%% calculate H
theta_numerator = 0.5 * ((image_R - image_G) + (image_R - image_B));
theta_denominator = sqrt((image_R - image_G) .^ 2 + (image_R - image_B) .* (image_G - image_B));
theta = acos(theta_numerator ./ (theta_denominator + eps));
H = theta;
H(image_B > image_G) = 2 * pi - H(image_B > image_G);
image_H = H / (2 * pi);

%% calculate S
S_numerator = 3 * min(min(image_R, image_G), image_B);
S_denominator = image_R + image_G + image_B;
S_denominator(S_denominator == 0) = eps;
image_S = 1 - S_numerator ./ S_denominator;
image_H(image_S == 0) = 0;

%% calculate I
image_I = (image_R + image_G + image_B) / 3;

%% merge
image = cat(3, image_H, image_S, image_I);