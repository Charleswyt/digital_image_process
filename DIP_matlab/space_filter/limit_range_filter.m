%% ÏŞ·ùÂË²¨
function image = limit_range_filter(image_origin, limit_value)

if max(image_origin) - limit_value > 30
    image = image_origin;
else
    image = image_origin;
    image(image_origin > limit_value) = limit_value;
end 
end