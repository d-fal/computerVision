#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        characterRecognition ocr;
        humomments  hu;

        //cout<<ocr.charRecognition(img)<<endl;
        imageRGB=imread("C:\\example\\test01.jpg");
        image=imageRGB.clone();
        medianBlur(image,image,3);
        logo = imread("C:\\example\\logo.png");
        Mat imageROI;


        for(int i=0;i<=9;++i){
            QString path="C:\\example\\samples\\img_"+QString::number(i)+".png";
        Mat img=imread(path.toStdString());
        cvtColor(img,img,CV_RGB2GRAY);
        threshold(img,img,0,255,THRESH_OTSU);
        vector<float> result=hu.calculateHuMomments(img==0);

        for(int i=0;i<result.size();++i) cout<<i+1<<"th: "<<result[i]<< " - ";
       cout<<endl;
        }
        Mat img=imread("C:\\example\\samples\\img_3.png");
        cvtColor(img,img,CV_RGB2GRAY);
        threshold(img,img,0,255,THRESH_OTSU);

        cv::Moments mom=cv::moments(img==0,true);
        double hum[7];
        cv::HuMoments(mom, hum);
        for(int i=0;i<7;++i) cout<<i+1<<"th: "<<hum[i]<<" - ";

        imageROI=imageRGB(cv::Rect(imageRGB.cols-logo.cols-1,imageRGB.rows-logo.rows-1,logo.cols,logo.rows));
        //cout<<"logo : "<<logo.cols<<" x "<<logo.rows<<"\nImage: "<<imageRGB.cols<<" x "<<imageRGB.rows<<
           // "\nimageROI: " << imageROI.cols<<" x "<<imageROI.rows<<"\n";
        cv::addWeighted(imageROI,1,logo,0.3,0.,imageROI);
        //imshow("",imageROI);
        //cvtColor(imageRGB,image,CV_RGB2GRAY);
      // cv::flip(imageRGB,image,1); // process the image
    //cvtColor(imageRGB,image_gray,CV_BGR2GRAY);

        //colorReduce(imageRGB,image,8);
        /*
        Mat kernel=Mat(3,3,CV_32F,cv::Scalar(0));
        kernel.at<float>(1,1)=5;
        kernel.at<float>(0,1)=-1;
        kernel.at<float>(1,0)=-1;
        kernel.at<float>(2,1)=-1;
        kernel.at<float>(1,2)=-1;
*/
      //  equalizeHist(image,image_gray);

        //filter2D(imageRGB,image,image.depth(),kernel);

        colorDetect cd;
        cd.instantiateValues(150,50,100,900);
        //imshow("",image_gray);
        // change color channel ordering
        //image=cd.process(image);

        //Histogram1D h;
        //cv::MatND histo= h.getHistogram(image);

        //cv::namedWindow("Histogram");
        //cv::imshow("Histogram",
        //h.getHistogramImage(image));
        // Qt image
        //imshow("",image);
        //cv::cvtColor(image,image,CV_BGR2RGB);
        //waitKey(37);
        /*
        QImage img= QImage((const unsigned char*)(image.data),
        image.cols,image.rows,QImage::Format_RGB888);
        // display on label
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(500,500));
        // resize the label to fit the image
        */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    VideoCapture cap(0);
    colorDetect cd;
    cd.instantiateValues(150,50,100,90);

    for(;;){

    Mat frame,edges;

    cap >> frame; // get a new frame from camera
if(!frame.empty()){


    //imshow("",image_gray);
    // change color channel ordering
    //edges=cd.process(frame);
    edges=cd.followContours(frame);
    //cvtColor(frame, edges, CV_BGR2GRAY);
    //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    //Canny(edges, edges, 0, 30, 3);


    imshow("webcam",edges);

    if(waitKey(30) >= 0) break;

    // the camera will be deinitialized automatically in VideoCapture destructor
}
   }
}

void MainWindow::on_pushButton_2_clicked()
{

Mat imageBW,image_gray;
cvtColor(image,image_gray,CV_RGB2GRAY);
threshold(image_gray,imageBW,0,255,THRESH_OTSU);
imshow("",imageBW);
Mat grad;
morphologyEx(imageBW,grad,MORPH_GRADIENT,Mat());
//imshow("Gradient",grad);
Mat open;
morphologyEx(grad,open,MORPH_OPEN,Mat());
//imshow("openned",open);

cv::Mat fg;
cv::erode(imageBW,fg,cv::Mat(),cv::Point(-1,-1),6);
//imshow("Foreground",fg);
cv::Mat bg;
cv::dilate(imageBW,bg,cv::Mat(),cv::Point(-1,-1),6);
cv::threshold(bg,bg,1,128,cv::THRESH_BINARY_INV);
//imshow("Background",bg);
cv::Mat markers(imageBW.size(),CV_8U,cv::Scalar(0));
markers= fg+bg;
imshow("Markers",markers);
// Create watershed segmentation object
WatershedSegmenter segmenter;
// Set markers and process
segmenter.setMarkers(markers);
Mat res=segmenter.process(image);

}

void MainWindow::on_pushButton_3_clicked()
{
   preProcessing pre;
   cv::Mat result=pre.detectCharacters(image);
   //imshow("Detected Chars",result+.8*image);
}

void MainWindow::on_pushButton_4_clicked()
{
    colorDetect cd;
    vector<int> res=cd.verticalLines(image);
    for(unsigned int i=0;i<res.size();++i){
        cout<<res[i]<<endl;
    }

}

void MainWindow::on_pushButton_5_clicked()
{
    vector<vector<cv::Point> > contours;
    vector<Vec4i> hierarchy;
    Mat image_canny,image_gray;
    cvtColor(image,image_gray,CV_RGB2GRAY);

    Canny( image_gray, image_canny, 100, 200, 3 );
    cv::findContours(image_canny,
    contours, hierarchy, // a vector of contours
    CV_RETR_TREE, // retrieve the external contours
    CV_CHAIN_APPROX_SIMPLE,Point(0,0)); // all pixels of each contours
    // Draw black contours on a white image
    cv::Mat result(image.size(),CV_8U,cv::Scalar(0));
    RNG rng(12345);
    cvtColor(result,result,CV_GRAY2BGR);
    for(unsigned int i = 0; i< contours.size(); i++ )
         {
           //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
           Scalar color=Scalar(150,0,255);
           //cv::Rect r0= cv::boundingRect(cv::Mat(contours[i]));
           //cv::rectangle(result,r0,cv::Scalar(0),2);
           //drawContours( result, contours, i, color, 2, 8, hierarchy, 0, Point() );
           float radius;
           cv::Point2f center;

           cv::minEnclosingCircle(cv::Mat(contours[i]),center,radius);
           float wid=radius;
           Point2f start=center-Point2f(wid,wid);
           Point2f end=center+Point2f(wid,wid);
           if(radius<20){
           //cv::circle(result,center,static_cast<int>(radius),color,2);
           rectangle(result,start,end,color,.6,1);
           }
         }

    imshow("",result+0.8*image);
    //imshow("",image);
}

void MainWindow::read_dataset(char *filename, cv::Mat &data, cv::Mat &classes,  int total_samples)
{

    int label;
    float pixelvalue;
    //open the file
    FILE* inputfile = fopen( filename, "r" );

    //read each row of the csv file
   for(int row = 0; row < total_samples; row++)
   {
       //for each attribute in the row
     for(int col = 0; col <=ATTRIBUTES; col++)
        {
            //if its the pixel value.
            if (col < ATTRIBUTES){

                fscanf(inputfile, "%f,", &pixelvalue);

                data.at<float>(row,col) = pixelvalue;

            }//if its the label
            else if (col == ATTRIBUTES){
                //make the value of label column in that row as 1.
                fscanf(inputfile, "%i", &label);
                classes.at<float>(row,label) = 1.0;

            }
        }
    }

    fclose(inputfile);

}

void MainWindow::on_pushButton_6_clicked()
{
    //matrix to hold the training sample
        cv::Mat training_set(TRAINING_SAMPLES,ATTRIBUTES,CV_32F);
        //matrix to hold the labels of each taining sample
        cv::Mat training_set_classifications(TRAINING_SAMPLES, CLASSES, CV_32F);
        //matric to hold the test samples
        cv::Mat test_set(TEST_SAMPLES,ATTRIBUTES,CV_32F);
        //matrix to hold the test labels.
        cv::Mat test_set_classifications(TEST_SAMPLES,CLASSES,CV_32F);

        //
        cv::Mat classificationResult(1, CLASSES, CV_32F);
        //load the training and test data sets.
        read_dataset("C:\\example\\trainingset.txt", training_set, training_set_classifications, TRAINING_SAMPLES);
        read_dataset("C:\\example\\testset.txt", test_set, test_set_classifications, TEST_SAMPLES);
            // define the structure for the neural network (MLP)
            // The neural network has 3 layers.
            // - one input node per attribute in a sample so 256 input nodes
            // - 16 hidden nodes
            // - 10 output node, one for each class.

            cv::Mat layers(3,1,CV_32S);
            layers.at<int>(0,0) = ATTRIBUTES;//input layer
            layers.at<int>(1,0)=16;//hidden layer
            layers.at<int>(2,0) =CLASSES;//output layer

            //create the neural network.
            //for more details check http://docs.opencv.org/modules/ml/doc/neural_networks.html
            CvANN_MLP nnetwork(layers, CvANN_MLP::SIGMOID_SYM,0.6,1);

            CvANN_MLP_TrainParams params(

                                            // terminate the training after either 1000
                                            // iterations or a very small change in the
                                            // network wieghts below the specified value
                                            cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 0.000001),
                                            // use backpropogation for training
                                            CvANN_MLP_TrainParams::BACKPROP,
                                            // co-efficents for backpropogation training
                                            // recommended values taken from http://docs.opencv.org/modules/ml/doc/neural_networks.html#cvann-mlp-trainparams
                                            0.1,
                                            0.1);

            // train the neural network (using training data)

            printf( "\nUsing training dataset\n");
            int iterations = nnetwork.train(training_set, training_set_classifications,cv::Mat(),cv::Mat(),params);
            printf( "Training iterations: %i\n\n", iterations);

            // Save the model generated into an xml file.
            CvFileStorage* storage = cvOpenFileStorage( "C:\\example\\param.xml", 0, CV_STORAGE_WRITE );
            nnetwork.write(storage,"DigitOCR");
            cvReleaseFileStorage(&storage);

            // Test the generated model with the test samples.
            cv::Mat test_sample;
            //count of correct classifications
            int correct_class = 0;
            //count of wrong classifications
            int wrong_class = 0;

            //classification matrix gives the count of classes to which the samples were classified.
            int classification_matrix[CLASSES][CLASSES]={{}};

            // for each sample in the test set.
            for (int tsample = 0; tsample < TEST_SAMPLES; tsample++) {

                // extract the sample

                test_sample = test_set.row(tsample);

                //try to predict its class

                nnetwork.predict(test_sample, classificationResult);
                /*The classification result matrix holds weightage  of each class.
                we take the class with the highest weightage as the resultant class */

                // find the class with maximum weightage.
                int maxIndex = 0;
                float value=0.0f;
                float maxValue=classificationResult.at<float>(0,0);
                for(int index=1;index<CLASSES;index++)
                {   value = classificationResult.at<float>(0,index);
                    if(value>maxValue)
                    {   maxValue = value;
                        maxIndex=index;

                    }
                }

                printf("Testing Sample %i -> class result (digit %d)\n", tsample, maxIndex);

                //Now compare the predicted class to the actural class. if the prediction is correct then\
                //test_set_classifications[tsample][ maxIndex] should be 1.
                //if the classification is wrong, note that.
                if (test_set_classifications.at<float>(tsample, maxIndex)!=1.0f)
                {
                    // if they differ more than floating point error => wrong class

                    wrong_class++;

                    //find the actual label 'class_index'
                    for(int class_index=0;class_index<CLASSES;class_index++)
                    {
                        if(test_set_classifications.at<float>(tsample, class_index)==1.0f)
                        {

                            classification_matrix[class_index][maxIndex]++;// A class_index sample was wrongly classified as maxindex.
                            break;
                        }
                    }

                } else {

                    // otherwise correct

                    correct_class++;
                    classification_matrix[maxIndex][maxIndex]++;
                }
            }

            printf( "\nResults on the testing dataset\n"
            "\tCorrect classification: %d (%g%%)\n"
            "\tWrong classifications: %d (%g%%)\n",
            correct_class, (double) correct_class*100/TEST_SAMPLES,
            wrong_class, (double) wrong_class*100/TEST_SAMPLES);
            cout<<"   ";
            for (int i = 0; i < CLASSES; i++)
            {
                cout<< i<<"\t";
            }
            cout<<"\n";
            for(int row=0;row<CLASSES;row++)
            {cout<<row<<"  ";
                for(int col=0;col<CLASSES;col++)
                {
                    cout<<classification_matrix[row][col]<<"\t";
                }
                cout<<"\n";
            }


//cout<<training_set;

}



void MainWindow::on_pushButton_7_clicked()
{
        CvANN_MLP nnetwork;
        CvFileStorage* storage = cvOpenFileStorage( "C:\\example\\param.xml", 0, CV_STORAGE_READ );
        CvFileNode *n = cvGetFileNodeByName(storage,0,"DigitOCR");
        nnetwork.read(storage,n);
        cvReleaseFileStorage(&storage);

        Mat data=imread("C:\\example\\test_4.png");
        cvtColor(data,data,CV_BGR2GRAY);
        cv::Mat result1(1,ATTRIBUTES,CV_32F);
        readCharacterData rdChar;
        rdChar.removeWhitespaces(data,data);
        rdChar.alignPixels(data, result1);
        // ... data for the digit to be recognized

        int maxIndex = 0;
        cv::Mat classOut(1,CLASSES,CV_8U);



        cout<<"\nSize:"<<classOut.rows<<"  x  "<<classOut.cols<<endl;
        //cout<<(data1>128)<<endl;
        //prediction
        //cout<<test_sample<<endl;

        nnetwork.predict(result1, classOut);
        float value;
        float maxValue=classOut.at<float>(0,0);
        for(int index=1;index<CLASSES;index++)
        {   value = classOut.at<float>(0,index);
                if(value>maxValue)
                {   maxValue = value;
                    maxIndex=index;
                }
        }
               cout<<"\nThe result is:"<<maxIndex<<endl;

}

void MainWindow::on_pushButton_8_clicked()
{
    ofstream newFile;


}
