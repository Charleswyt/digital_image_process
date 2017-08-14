%% enhance RGB color spcae through HSI clolor space
function image = color_enhancement(image_origin, delta_H, delta_S, delta_I)

% if delta_H > 1, the color can be more vivid, if delta_S < 1, the color can be less vivid
% if delta_S > 1, the color can be more vivid, if delta_S < 1, the color can be less vivid
% if delta_I > 1, the color can be brighter, if delta_S < 1, the color can be less vivid

image_HSI = RGB2HSI(image_origin);              % covert the RGB image to HSI image
image_H = image_HSI(:,:,1);                     % read H channel
image_S = image_HSI(:,:,2);                     % read S channel
image_I = image_HSI(:,:,3);                     % read I channel

image_H = image_H + delta_H;                    % change H value
image_S = image_S * delta_S;                    % change S value
image_I = image_I * delta_I;                    % change I value

image_HSI = cat(3, image_H, image_S, image_I);
image = HSI2RGB(image_HSI);

end