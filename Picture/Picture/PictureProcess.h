#pragma once
#include<iostream>
#include<string>
#include<stdlib.h>
#include<windows.h>
#include<fstream>
#include<iomanip>
#include<vector>

using namespace std;


struct Mnode {
    int R;
    int G;
    int B;
};

class Picture {
public:
    void test() {
        imgData[1][1] = 0;
        cout << imgData.size() << endl;
        for (int i = 0; i < imgData.size(); i++) {
            cout <<imgData[i][3] << " ";
        }
    }
    Picture() {
        bmpWidth = 0;
        bmpHeight = 0;
        biBitcount = 0;

    }
    void setPicture();
    void readFile(char* bmpname);
    void PrintPicture();
    void SavePicture();
    void Sharpness();
    void Smooth();

private:
    int bmpWidth;
    int bmpHeight;
    int biBitcount;

    unsigned char* pBmpBuf;//����ͼ�����ݵ�ָ��
    RGBQUAD* pColorTable;
    int biBitCount;
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    int **color;  //�洢rgbɫ�ʾ���
    vector<vector<int>> imgData; //�洢rgbɫ�ʾ���


    unsigned int** r;
    unsigned int** g;
    unsigned int** b;
};





void Picture::readFile(char* bmpname) {


    FILE* fp = fopen(bmpname, "rb");//�����ƶ���ʽ��ָ����ͼ���ļ�
    if (fp == 0) {
        cout << "can not open file" << endl;
        exit(0);
    }
        


    char* buf=NULL;                                              //�����ļ���ȡ������
    char* p=NULL;

    fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);    //��ʽ�ļ�����ȡbmp�ļ�
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);


    if (bi.biBitCount != 24) {
        cout << "��֧�ָø�ʽ��BMPλͼ��" << endl;
        exit(0);
    }

    fseek(fp, bf.bfOffBits, 0);

    buf = (char*)malloc(bi.biWidth * bi.biHeight * 3);
    fread(buf, 1, bi.biWidth * bi.biHeight * 3, fp);

    p = buf;

    vector<vector<int>> imgDatabuf;
    for (int y = 0; y < bi.biHeight; y++) {
        for (int x = 0; x < bi.biWidth; x++) {
            vector<int> vRGB;

            vRGB.push_back(*(p++));     //blue
            vRGB.push_back(*(p++));     //green
            vRGB.push_back(*(p++));     //red

            if (x == bi.biWidth - 1)
            {
                for (int k = 0; k < bi.biWidth % 4; k++) p++;
            }
            imgData.push_back(vRGB);
        }
    }
    fclose(fp);
    //imgData = imgDatabuf;

    
    cout << "Width:" << bi.biWidth << endl;
    cout << "Height" << bi.biHeight << endl; 
  

    /*

    //����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
    fseek(fp, sizeof(BITMAPFILEHEADER), 0);

    BITMAPINFOHEADER infohead;
    fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp); //��ȡͼ����ߡ�ÿ������ռλ������Ϣ
    bmpWidth = infohead.biWidth;
    bmpHeight = infohead.biHeight;

    biBitCount = infohead.biBitCount;//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����

    int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;//�Ҷ�ͼ������ɫ������ɫ�����Ϊ256
    if (biBitCount == 8)
    {
        //������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
        pColorTable = new RGBQUAD[256];
        fread(pColorTable, sizeof(RGBQUAD), 256, fp);
    }

    //����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
    pBmpBuf = new unsigned char[lineByte * bmpHeight];
    fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
    fclose(fp);//�ر��ļ�

    cout << "Width:" << bmpWidth << endl;
    cout << "Height" << bmpHeight << endl;*/

}

void Picture::setPicture() {

    char readPath[] = "\\Users\\��ҵ��\\Desktop\\2654.bmp";
    readFile(readPath);

    
    ;
   /* int linebyte1 = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
    int n = 0, m = 0, count_xiang_su = 0;

    r = new unsigned int* [bmpHeight];        //����ָ������
    for (int i = 0; i < bmpHeight; i++)
        r[i] = new unsigned int[bmpWidth];

    g = new unsigned int* [bmpHeight];        //����ָ������
    for (int i = 0; i < bmpHeight; i++)
        g[i] = new unsigned int[bmpWidth];

    b = new unsigned int* [bmpHeight];        //����ָ������
    for (int i = 0; i < bmpHeight; i++)
        b[i] = new unsigned int[bmpWidth];


    //��ʼ��ԭʼ���ص����顣

    if (biBitCount == 8)
    {
        for (int i = 0; i < bmpHeight / 2; i++)
        {
            for (int j = 0; j < bmpWidth / 2; i++)
                *(pBmpBuf + i * linebyte1 + j) = 0;
        }
    }

    if (biBitCount == 24)
    {
        for (int i = 0; i < bmpHeight; i++)
        {
            for (int j = 0; j < bmpWidth; j++)
            {
                for (int k = 0; k < 3; k++)//ÿ����RGB���������ֱ���0�ű�ɺ�ɫ
                {
                    m = *(pBmpBuf + i * linebyte1 + j * 3 + k);
                    count_xiang_su++;
                }
                n++;
            }
        }

        
        /*Mat img_data(bmpHeight, bmpWidth, CV_8UC3);
        for (int i = 0; i < bmpHeight; i++) {
            for (int j = 0; j < bmpWidth; j++) {
                img_data.at<Vec3b>(i, j)[0] = out_b[i][j];
                img_data.at<Vec3b>(i, j)[1] = out_g[i][j];
                img_data.at<Vec3b>(i, j)[2] = out_r[i][j];
            }
        }

        namedWindow("lunpan");
        imshow("lunpan", img_data);
        waitKey(0);*/

    }

void Picture::PrintPicture() {
   
    
    /*for (int i = 0; i < bi.biHeight; i++) {
        cout << endl;
    }*/

    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;


    HWND hWindow;                                                //���ھ��
    HDC hDc;                                                     //��ͼ�豸�������
    int yOffset = 150;
    hWindow = GetForegroundWindow();
    hDc = GetDC(hWindow);

    int posX, posY;
    for (int i = 0; i < imgData.size(); i++) {
        char blue = imgData.at(i).at(0);
        char green = imgData.at(i).at(1);
        char red = imgData.at(i).at(2);

        posX = i % bi.biWidth;
        posY = bi.biHeight - i / bi.biWidth + yOffset;
        SetPixel(hDc, posX, posY, RGB(red, green, blue));
    }


}

void Picture::SavePicture() {
    char readPath[] = "\\Users\\��ҵ��\\Desktop\\new.bmp";
    FILE* fpw;
    fopen_s(&fpw, readPath, "wb");
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fpw);  //д���ļ�ͷ
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fpw);  //д���ļ�ͷ��Ϣ

    int size = bi.biWidth * bi.biHeight;
    for (int i = 0; i < size; i++) {
        fwrite(&imgData.at(i).at(0), 1, 1, fpw);
        fwrite(&imgData.at(i).at(1), 1, 1, fpw);
        fwrite(&imgData.at(i).at(2), 1, 1, fpw);

        if (i % bi.biWidth == bi.biWidth - 1) {
            char ch = '0';
            for (int j = 0; j < bi.biWidth % 4; j++) {
                fwrite(&ch, 1, 1, fpw);
            }
        }
    }
    fclose(fpw);
    cout << "�ѱ���ͼ����: " <<readPath<< endl;
}

void Picture::Smooth() {
    int w = bi.biWidth;
    int h = bi.biHeight;



    int marker = 1;
    for (int i = 0; i < imgData.size(); i++) {
        /*if (i < w + 1) {
        
            imgData[i][0] = (imgData[i + w][0] + imgData[i][0]) / 2;
            imgData[i][1] = (imgData[i + w][1] + imgData[i][1]) / 2;
            imgData[i][2] = (imgData[i + w][2] + imgData[i][2]) / 2;
       }*/

        if (i > w + 1 && i < imgData.size() - w -2) {
            imgData[i][0] = (imgData[i][0]+imgData[i + w][0] + imgData[i + w - 1][0] + imgData[i + w + 1][0] + imgData[i + 1][0] + imgData[i - 1][0] + imgData[i - w][0] + imgData[i - w - 1][0] + imgData[i - w+1][0])/9;
            imgData[i][1] = (imgData[i][1]+imgData[i + w][1] + imgData[i + w - 1][1] + imgData[i + w + 1][1] + imgData[i + 1][1] + imgData[i - 1][1] + imgData[i - w][1] + imgData[i - w - 1][1] + imgData[i - w+1][1])/9;
            imgData[i][2] = (imgData[i][2]+imgData[i + w][2] + imgData[i + w - 1][2] + imgData[i + w + 1][2] + imgData[i + 1][2] + imgData[i - 1][2] + imgData[i - w][2] + imgData[i - w - 1][2] + imgData[i - w+1][2])/9;
        }
      
    }

}

void Picture::Sharpness() {
    int w = bi.biWidth;
    int h = bi.biHeight;

    int marker = 1;
    for (int i = 2; i < imgData.size(); i++) {
        

        if (i > w + 1 && i < imgData.size() - w) {
            /*imgData[i][0] = (imgData[i + w][0] + imgData[i + w - 1][0] + imgData[i + w + 1][0] + imgData[i + 1][0] + imgData[i - 1][0] + imgData[i - w][0] + imgData[i - w - 1][0] + imgData[i - w][0]) ;
            imgData[i][1] = (imgData[i + w][1] + imgData[i + w - 1][1] + imgData[i + w + 1][1] + imgData[i + 1][1] + imgData[i - 1][1] + imgData[i - w][1] + imgData[i - w - 1][1] + imgData[i - w][1]) ;
            imgData[i][2] = (imgData[i + w][2] + imgData[i + w - 1][2] + imgData[i + w + 1][2] + imgData[i + 1][2] + imgData[i - 1][2] + imgData[i - w][2] + imgData[i - w - 1][2] + imgData[i - w][2]);*/

            int prer = imgData[i][0];
            int preg = imgData[i][1];
            int preb = imgData[i][2];

            imgData[i][0] = -imgData[i + 1][0] - imgData[i - 1][0] - imgData[i + w][0] - imgData[i - w][0] + 4 * prer;
            imgData[i][1] = -imgData[i + 1][1] - imgData[i - 1][1] - imgData[i + w][1] - imgData[i - w][1] + 4 * preg;
            imgData[i][2] =-imgData[i + 1][2] - imgData[i - 1][2] - imgData[i + w][2] - imgData[i - w][2] + 4 * preb;

            for (int j = 0; j < 3; j++) {
                if (imgData[i][j] > 255) {
                    imgData[i][j] = 255;
                }
                if (imgData[i][j] < 0) {
                   imgData[i][j] = 0;
                }
            }

           
            

            marker = 1;
        }

        marker++;
    }
}