#include "CommonHelper.h"



/****************************************
* Qt��ʹ���ļ�ѡ��Ի��������£�
* 1. ����һ��QFileDialog����
* 2. ����·����������������
*****************************************/
string CommonHelper::selectFile()
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


void CommonHelper::showImage(QLabel* label, cv::Mat mat)
{
	cv::Mat temp;
	cv::cvtColor(mat, temp, cv::COLOR_BGR2RGB);//BGR convert to RGB
	QImage Qtemp = QImage((const unsigned char*)(temp.data), temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	label->setPixmap(QPixmap::fromImage(Qtemp));
	label->show();
}