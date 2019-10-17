#include "detectthread.h"
#include "global.h"
detectthread::detectthread(camthread *camtrd)
{
    m_pmtcnn=new MtcnnDetector(getmodelspath().toStdString());
    m_pcamt=camtrd;

     m_parc=new Arcface(getmodelspath().toStdString());
}

void detectthread::run()
{
    for (;;)
    {
        cv::Mat image1=m_pcamt->getImage();
        cv::Mat image2;
        cv::Mat face;

        if(image1.empty())
            continue;

        cv::resize(image1,image2,cv::Size(image1.cols,image1.rows),0,0);
        ncnn::Mat ncnn_img1 = ncnn::Mat::from_pixels(image2.data, ncnn::Mat::PIXEL_BGR, image2.cols, image2.rows);

        vector<FaceInfo> results1 = m_pmtcnn->Detect(ncnn_img1);

        if(results1.size()>0)
        {
            ncnn::Mat det1 = preprocess(ncnn_img1, results1[0]);
            vector<float> feature1 = m_parc->getFeature(det1);

            m_strfeature.clear();
            for(int j=0;j<feature1.size();j++)
            {
                m_strfeature+=QString::number(feature1[j]);
                m_strfeature+=",";
            }

            int x = results1[0].x[0];
            int y = results1[0].y[0];
            int w = (results1[0].x[1] - results1[0].x[0]);
            int h = (results1[0].y[1] - results1[0].y[0]);
            m_pcamt->setDetRect(x,y,w,h);

            if(((x+w)>image1.cols)||((y+h)>image1.rows)||(x<0)||(y<0))
                continue;

            cv::Rect rect(x,y,w,h);

            face=image1(rect);

            if(face.empty())
                continue;
            else
            {
                m_pcamt->setface(face,m_strfeature);
            }









        }



    }

}
