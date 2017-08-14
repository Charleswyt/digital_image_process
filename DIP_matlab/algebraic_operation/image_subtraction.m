function image = image_subtraction(image1, image2)

[height1, width1, channel1] = size(image1);
[height2, width2, channel2] = size(image2);

if channel1 ~= channel2
    disp('The number of channels in two images must be the same.');
    
else
    % size match
    if height1 ~= height2
        disp('The heights of two images must be the same.');
        
    elseif width1 ~= width2
        disp('The widths of two images must be the same.');
        
    else
        image = image1 - image2;
        image(image < 0) = 0;
    end
end

end