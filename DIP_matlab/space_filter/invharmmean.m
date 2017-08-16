%% ¼ÆËãÄæĞ³²¨¾ùÖµ
function m = invharmmean(x, order)
numerator = sum(x(:).^(order+1));
denominator = sum(x(:).^order);
m = numerator / denominator;