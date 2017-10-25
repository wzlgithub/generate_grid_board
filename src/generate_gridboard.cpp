/*************************************************************************
	> File Name: generate_grisboard.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年09月25日 星期一 21时17分19秒
 ************************************************************************/

#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void generate_caliboard(int width, int height, int pixels_each_grid=150)
{
    int img_withsize=width*pixels_each_grid;
    int img_height = height*pixels_each_grid;
    Mat board(img_withsize,img_height,CV_8UC1);
    Mat white_block(pixels_each_grid,pixels_each_grid,CV_8UC1,Scalar(255));
    Mat black_block(pixels_each_grid,pixels_each_grid,CV_8UC1,Scalar(0));
    for(int i=0;i!=height;i++)
    {
        for(int j=0;j!=width;j++)
        {
            Mat temp(board,Rect(pixels_each_grid*i,pixels_each_grid*j,pixels_each_grid,pixels_each_grid));
            if((i+j)%2==0)
                black_block.copyTo(temp);
            else
                white_block.copyTo(temp);
        }
    }
    Mat board_circle(img_withsize+pixels_each_grid*4/3, img_height+pixels_each_grid*4/3,CV_8UC1,Scalar(255));
    Mat temp(board_circle, Rect(pixels_each_grid*2/3, pixels_each_grid*2/3 ,img_height,img_withsize));
    board.copyTo(temp);
    circle(board_circle,Point(pixels_each_grid*1/3,pixels_each_grid*1/3),pixels_each_grid/5,Scalar(0),-1);

    imwrite("board_circle.jpg",board_circle);

}

int main()
{
    cout<<"please input the size of board and the pixels of each grid:"<<endl;
    cout<<"(if the pixels of each grid is assigned 0, default 150)"<<endl;
    cout<<"for example:  "<<endl;
    cout<<"8 10 100    or   8 10 0"<<endl;
    cout<<"size: ";
    int height,width,pixels;
    cin>>height>>width>>pixels;
    cout<<height<<" "<<width<<" "<<pixels<<endl;

    if(pixels==0)
        generate_caliboard(height,width);
    else
        generate_caliboard(height,width,pixels);
    return 0;
}
