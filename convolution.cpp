// including  opencv libraries
#include <opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/core/mat.hpp>

#include <iostream>

using namespace std;// standard namespace
using namespace cv;// cv namespace

// Creating Class cat
class Cat{

  protected:
  Mat src_cat,dst_cat;

 
 public:
 // Creating readCatImg to read the cat Image
  void readCatImg(){

  //reading the cat.jpeg
  src_cat=imread("cat.jpeg");
  // converting image color in gray scale
  cvtColor(src_cat,src_cat,COLOR_BGR2GRAY);
  
  if(!src_cat.data)
  {
    cout << "Image not read";
  } 
 }

};


// Creating Class Dog
class Dog{
 
  protected:
   Mat src_dog,dst_dog;
  
  
  public:
  //Creating readDogImg to read the dog Image
   void readDogImg(){

    //reading the dog.jpeg
    src_dog=imread("dog.jpeg");
   // converting image color in gray scale
    cvtColor(src_dog,src_dog,COLOR_BGR2GRAY);
    if(!src_dog.data)
    {
      cout << "Image not read";
    }
    
  }
  
};


// Inheriting Cat and Dog class 
class Convolution : public Cat, public Dog{
 
 
 protected:
 // Assigning the 3X3 kernel
  float kernel[3][3]={
    {1,0,0},
    {0,1,0},
    {0,0,1}
  };
 
 
 public:
 // Creating the conv_image for the Convolution of the images
 void conv_image(Mat src,Mat dst,float kernel[][3]){

    float sum;
    for(int y=1;y<src.rows-1;y++){
      for(int x=1;x<src.cols-1;x++){
        sum=0.0;
        for(int k=-1;k<=1;k++){
          for(int j=-1;j<=1;j++){
            sum=sum+kernel[j+1][k+1]*src.at<uchar>(y-j,x-k);
          }
        }
        dst.at<uchar>(y,x)=sum;
      }
    }
  }

 
 public:
 // Creating writeDogImg to save the filtered_dog_img in system
 void writeDogImg(){
   // calling the readDogImg 
    readDogImg();
    dst_dog = src_dog.clone();
    conv_image(src_dog,dst_dog,kernel);
    // writing the image
    imwrite("filtered_dog_img.jpeg",dst_dog);
    waitKey(0);
    }
 
 public:
 // Creating writeCatImg to save the filtered_cat_img in system
  void writeCatImg(){
    // Calling the readCatImg
      readCatImg();
      dst_cat = src_cat.clone();
      conv_image(src_cat,dst_cat,kernel);
      // writing the image
      imwrite("filtered_cat_img.jpeg",dst_cat);
      waitKey(0);
      }

};






int main() {
  // Creating an object of Convolution
  Convolution c;
  // calling the writeCatImg and writeDogImg to save filtered images in system
  c.writeCatImg();
  c.writeDogImg();

  return 0;

}
