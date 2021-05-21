clear;
temp=[];
M = readmatrix('wavefront.dat');
I=mat2gray(M);%将数值矩阵X转换为灰度图像
figure,imshow(I); %显示转换后的灰度图像
