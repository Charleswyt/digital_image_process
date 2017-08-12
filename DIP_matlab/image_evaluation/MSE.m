%% calculate image MSE
% usage:
% image_mse = MSE(image_reference, image_test)
% image_reference: reference image
% image_test: test image
% iamge_mse: the mean squared error of the test image

function image_mse = MSE(image_reference, image_test)

try
    [height, width, channel] = size(image_reference);       % get the dimension information of 3-D image
catch
    [height, width] = size(image_reference);                      % get the dimension information of 2-D image
end

if channel == 1
    sum = 0;
    for h = 1:height
        for w = 1:width
            sum = sum + (image_reference(h, w) - image_test(h, w))^2;
        end
    end
    image_mse = sum / (height * width);
end

if channel == 3
    sum = 0;
    for c = 1:channel
        for h = 1:height
            for w = 1:width
                sum = sum + (image_reference(h, w, c) - image_test(h, w, c))^2;
            end
        end
    end
    image_mse = sum / (height * width);
end