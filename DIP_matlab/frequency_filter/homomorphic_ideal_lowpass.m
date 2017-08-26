% 同态滤波器(理想低通)
function image = homomorphic_ideal_lowpass(image_origin, cut_frequency)

[height, width] = size(image_origin);                       % calculate the height and width of image
H = zeros(height, width);                                   % initial filter H
image_origin_log = log(double(image_origin));               % log
image_origin_log_fft = fft2(image_origin_log);              % fft

image_origin_log_fftshift = fftshift(image_origin_log_fft); % fftshift, move the low frequency to the center
center_height = round(height / 2);                          % center point(height)
center_width = round(width / 2);                            % center point(width)
max_frequency = ...
    min(height - center_height, width - center_width);      % max frequncy deviation
if cut_frequency >= max_frequency
    cut_frequency = max_frequency;
end

% design the filter function
for h = 1:height
    for w = 1:width
        dis = sqrt((h - center_height)^2 + (w - center_width)^2);
        if dis <= cut_frequency
            H(h, w) = 1;
        end
    end
end

image_log_fftshift = image_origin_log_fftshift .* H;
image_log_fft = ifftshift(image_log_fftshift);
image_log = ifft2(image_log_fft);
image = exp(image_log);
image = uint8(real(image));

