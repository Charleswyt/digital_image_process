%% trapezoid lowpass
function image = trapezoid_lowpass(image_origin, cut_frequency1, cut_frequency2)

[height, width] = size(image_origin);                       % calculate the height and width of image
H = zeros(height, width);                                   % initial filter H
image_origin_fft = fft2(image_origin);                      % fft
image_origin_fftshift = fftshift(image_origin_fft);         % fftshift, move the low frequency to the center
center_height = round(height / 2);                          % center point(height)
center_width = round(width / 2);                            % center point(width)
max_frequency = ...
    min(height - center_height, width - center_width);      % max frequncy deviation
if cut_frequency2 >= max_frequency
    cut_frequency2 = max_frequency;
end

if cut_frequency1 >= cut_frequency2
    cut_frequency1 = cut_frequency2 - 10;
end

% design the filter function
for h = 1:height
    for w = 1:width
        dis = sqrt((h - center_height)^2 + (w - center_width)^2);
        if dis <= cut_frequency1
            H(h, w) = 1;
        elseif dis > cut_frequency1 && dis <= cut_frequency2
            H(h, w) = (cut_frequency2 - dis) / (cut_frequency2 - cut_frequency1);
        else
            H(h, w) = 0;
        end
    end
end

image_fftshift = image_origin_fftshift .* H;
image_fft = ifftshift(image_fftshift);
image = ifft2(image_fft);
image = uint8(real(image));