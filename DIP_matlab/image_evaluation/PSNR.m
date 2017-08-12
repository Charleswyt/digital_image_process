%% calculate image PSNR
% usage:
% image_mse = PSNR(image_reference, image_test)
% image_reference: reference image
% image_test: test image
% iamge_psnr: the mean squared error of the test image

function image_psnr = PSNR(image_reference, image_test)
L = 255;
image_mse = MSE(image_reference, image_test);
image_psnr = 10 * log10(L^2 / image_mse);