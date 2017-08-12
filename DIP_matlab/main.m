clc;
clear all;
close all;

image = imread('Mawen.jpg');
red = image(:,:,1);
green = image(:,:,2);
blue = image(:,:,3);
figure(1);
subplot(141);
imshow(image);title('Original Image');
subplot(142);
imshow(red);title('Red Channel');
subplot(143);
imshow(green);title('Green Channel');
subplot(144);
imshow(blue);title('Blue Channel');

red_flip = fliplr(red);
green_flip = fliplr(green);
blue_flip = fliplr(blue);
image_flip = cat(3, red_flip, green_flip, blue_flip);
figure(2);
subplot(121);imshow(image);title('Original Image');
subplot(122);imshow(image_flip);title('inverse Image');


