% 验证哥德巴赫猜想：大于等于6的正偶数均可以分解为两个质数之和

even_decomposition(42);

function even_decomposition(num)

% 验证输入数字格式：大于等于6的正偶数
if isa(num, 'numeric') && mod(num,2)==0 && (num >= 6)
    even = num;
else
    error('Error.\nPlease check your input number %d',num );
end

% 分解为两个质数part1与part2之和
for part1 = 3:even/2 %如果part1=2，则part2仍为偶数，所以从3开始    
    % 验证part1是质数：职能分解为1和它自身的乘积
    k = floor(sqrt(part1));
    i = 2;
    while (mod(part1, i)~=0)&&(i<=k)
        i = i + 1;
    end
    if i > k% part1为质数则继续验证part2
        part2 = even - part1;
        k = floor(sqrt(part2));
        j = 2;
        while (mod(part2, j)~=0)&&(j<=k)
            j = j + 1;
        end
        if j > k % part2也是质数，则将分解结果打印输出
            disp([num2str(even),'=',num2str(part1),'+',num2str(part2)]);
        end
    end
end
end
