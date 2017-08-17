%% ideal highpass
function image = ideal_highpass(image_origin, cut_frequency, const)

if nargin == 2
    const = 0;
end

if cut_frequency >= 256
    cut_frequency = 256;
end

if const > 1 && const < 0
    const = 0;
end

[height, width] = size(image_origin);                       % calculate the height and width of image
H = zeros(height, width);                                   % initial filter H
image_origin_fft = fft2(image_origin);                      % fft
image_origin_fftshift = fftshift(image_origin_fft);         % fftshift, move the low frequency to the center
center_height = round(height / 2);
center_width = round(width / 2);

% design the filter function
for h = 1:height
    for w = 1:width
        dis = sqrt((h - center_height)^2 + (w - center_width)^2);
        if dis >= cut_frequency
            H(h, w) = 1;
        end
    end
end

H = H + const;                                              % enhanced filter
image_fftshift = image_origin_fftshift .* H;
image_fft = ifftshift(image_fftshift);
image = ifft2(image_fft);
image = uint8(real(image));