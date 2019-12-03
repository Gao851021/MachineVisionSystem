#include "CommonHelper.h"

/****************************************
* Qt��ʹ���ļ�ѡ��Ի��������£�
* 1. ����һ��QFileDialog����
* 2. ����·����������������
*****************************************/
string CommonHelper::selectImage()
{
	//�����ļ��Ի�����
	QFileDialog *fileDialog = new QFileDialog();
	//�����ļ��Ի������
	fileDialog->setWindowTitle("��ͼƬ");
	//����Ĭ���ļ�·��
	fileDialog->setDirectory(".");
	//�����ļ�������
	fileDialog->setNameFilter("Images(*.png *.jpg *.jpeg *.bmp)");
	//���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	//������ͼģʽ
	fileDialog->setViewMode(QFileDialog::Detail);
	//��ӡ����ѡ����ļ���·��
	QStringList fileNames;
	if (fileDialog->exec())
	{
		fileNames = fileDialog->selectedFiles();
	}
	for (auto tmp : fileNames)
		return tmp.toLocal8Bit();
}

//��ʵͼ��
void CommonHelper::showImage(QLabel* label, Mat mat)
{
	QImage image = MatImageToQt(mat);
	label->setPixmap(QPixmap::fromImage(image).scaled(label->size()));
	label->show();
}


//Matת��QImage
QImage CommonHelper::MatImageToQt(Mat &src)
{
	//CV_8UC1 8λ�޷��ŵĵ�ͨ��---�Ҷ�ͼƬ
	if (src.type() == CV_8UC1)  
	{
		//ʹ�ø����Ĵ�С�͸�ʽ����ͼ��
		//QImage(int width, int height, Format format)
		QImage qImage(src.cols, src.rows, QImage::Format_Indexed8);
		//��չ��ɫ�����ɫ��Ŀ
		qImage.setColorCount(256);

		//�ڸ���������������ɫ
		for (int i = 0; i < 256; i++)
		{
			//�õ�һ���ڰ�ͼ
			qImage.setColor(i, qRgb(i, i, i));
		}
		//��������ͼ��,data���ݶε��׵�ַ
		uchar *pSrc = src.data;
		//
		for (int row = 0; row < src.rows; row++)
		{
			//��������ָ��
			uchar *pDest = qImage.scanLine(row);
			//��Դsrc��ָ���ڴ��ַ����ʼλ�ÿ�ʼ����n��
			//�ֽڵ�Ŀ��dest��ָ���ڴ��ַ����ʼλ����
			memcmp(pDest, pSrc, src.cols);
			//ͼ������ص�ַ
			pSrc += src.step;
		}
		return qImage;
	}

	//Ϊ3ͨ���Ĳ�ɫͼƬ
	else if (src.type() == CV_8UC3)
	{
		//�õ�ͼ��ĵ��׵�ַ
		const uchar *pSrc = (const uchar*)src.data;
		//��src����ͼƬ
		QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_RGB888);
		//�ڲ��ı�ʵ��ͼ�����ݵ������£���������ͨ��
		return qImage.rgbSwapped();
	}
	//��ͨ��ͼƬ����Alphaͨ����RGB��ɫͼ��
	else if (src.type() == CV_8UC4)
	{
		const uchar *pSrc = (const uchar*)src.data;
		QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
		//����ͼ�����������Ϊһ����ͼ��
		return qImage.copy();
	}
	else
	{
		return QImage();
	}
}