#ifndef BLOCK_CHAIN_SYS_H
#define BLOCK_CHAIN_SYS_H

#include "BlockChain.h"

class BlockChainSys {
	// ָ����Զ��������״̬
	Block* Bptr;        // ������
	LightBlock* LBptr;  // ������������
	// ������Ϣ
	int dnU, dnLU, dnFU, dnM, dnS, dGas;
	// ��Ϣ
	int nU, nLU, nFU, nM, nS;
	string sUser;// �û�ͷ��ϣ
	string sStuff;// ��Ʒͷ��ϣ
	string sTrade;// ����ͷ��ϣ
	vector<FullUser> Vfuser;
	vector<LightUser> Vluser;
	vector<Miner> Vminer;
	vector<Stuff> Vstuff; // ���е���Ʒ
	vector<Trade> Vtrade; // ���еĽ���
	int t;                // ϵͳ���ڵ�ʱ��
public:
	BlockChainSys();
	void PrintInformation();    // ��ӡ��Ϣ
	void HelpInformation();     // ָ�
	void Create();              // ����
	void Tradeb();              // ����
	void AddInformation();      // �ӹ���Ʒ
	void ls();                  // չʾ��Ӧ��
	void StuffHis();            // ��Ʒ��Դ
};

#endif