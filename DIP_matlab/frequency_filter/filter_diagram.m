clc;
clear all;

height = 512;width = 512;
center_height = round(height / 2);
center_width = round(width / 2);
cut_frequency1 = 128;
cut_frequency2 = 192;

H = zeros(height, width);

%% 理想低高通滤波器
fig_1 = figure(1);
set(fig_1, 'name', 'Fig1 : Ideal Filter', 'Numbertitle', 'off');

for h = 1:height
    for w = 1:width
        dis = sqrt(h^2 + w^2);
        if dis <= cut_frequency1
            H(h, w) = 1;
        else
            H(h, w) = 0;
        end
    end
end
subplot(221);
imshow(H);
title('理想低通滤波器二维图示');
xlabel('width');ylabel('height');

for h = 1:height
    for w = 1:width
        dis = sqrt(h^2 + w^2);
        if dis >= cut_frequency1
            H(h, w) = 1;
        else
            H(h, w) = 0;
        end
    end
end
subplot(222);
imshow(H);
title('理想高通滤波器二维图示');
xlabel('width');ylabel('height');

%% 巴特沃斯低高通滤波器
fig_2 = figure(2);
set(fig_2, 'name', 'Fig2 : Butterworth Filter', 'Numbertitle', 'off');

for h = 1:height
    for w = 1:width
        dis = sqrt(h^2 + w^2);
        if dis <= cut_frequency1
            H(h, w) = 1;
        else
            H(h, w) = 0;
        end
    end
end
subplot(221);
imshow(H);
title('理想低通滤波器二维图示');
xlabel('width');ylabel('height');

for h = 1:height
    for w = 1:width
        dis = sqrt(h^2 + w^2);
        if dis >= cut_frequency1
            H(h, w) = 1;
        else
            H(h, w) = 0;
        end
    end
end
subplot(222);
imshow(H);
title('理想高通滤波器二维图示');
xlabel('width');ylabel('height');