%% RGB to HSI
function image = RGB2HSI(image_origin)

image_double = im2double(image_origin);         % convert the original image to double
image_red = image_double(:, :, 1);                       % read red channel
image_green = image_double(:, :, 2);                   % read green channel
image_blue = image_double(:, :, 3);                      % read blue channel

%% calculate H
theta_numerator = ((image_red - image_green) + (image_red - image_blue)) / 2;
theta_denominator = sqrt((image_red - image_green) .^ 2 + (image_red - image_blue) .* (image_green - image_blue));
theta = acos(theta_numerator ./ (theta_denominator + eps));
H = theta;
H(image_blue > image_green) = 2 * pi - H(image_blue > image_green);
image_H = H / (2 * pi);

%% calculate S
S_numerator = 3 * min(min(image_red, image_green), image_blue);
S_denominator = image_red + image_green + image_blue;
S_denominator(S_denominator == 0) = eps;
image_S = 1 - S_numerator ./ S_denominator;

%% calculate I
image_I = ( image_red + image_green + image_blue) / 3;

%% merge
image = cat(3, image_H, image_S, image_I);