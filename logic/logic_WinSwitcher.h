/* 
* 
* function: �˿�ѡ����ʵ��
* 
* Date:2015-9-1
* 
*    Author: Bill Wang
*/

#ifndef _LOGIC_WIN_SWITHCER_H_
#define _LOGIC_WIN_SWITHCER_H_

#include <string>
#include <vector>

//�˿�ѡ��������
enum WinSwitcherType{
	WS_NONE = 0,
	WS_NAME,
	WS_PORT_SINGLE,//���˿�
	WS_PORT_DOUBLE,//˫�˿�
	WS_VALUE_TEXT,//ֵ �ı�
	WS_VALUE_INT,//ֵ ���� ����
	WS_VALUE_DOUBLE,//ֵ ���� ������
	WS_VALUE_BOOL,//ֵ �߼�
	WS_FILE_PATH, //�ļ�·��
	WS_INPORT //�˿�����
};

class WinSwitcher
{
public:
	WinSwitcherType mve_WSType;
	std::string mvs_WSValue;
	int mvi_ChainLayer; //�������

	std::vector<int ,std::string > mvvu_PopUp;

protected:
private:
};

#endif
