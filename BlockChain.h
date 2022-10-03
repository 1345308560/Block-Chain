#ifndef BLOCK_CHAIN_H
#define BLOCK_CHAIN_H

#include "md5.h"
#include <iostream>
#include <vector>

using namespace std;
struct Block;
struct LightBlock;

// �û�����
class User {
	int nonce;         // ִ�н��״���
	double balance;    // �ֱ�����
	string storageRoot;// Merkle���ĸ��ڵ��ֵ
public:
	User(double bal);
	double GetBalance();         // �õ���
	void ChangeBalance(double b);// ���ı�
	void AddNonce();             // ���ӽ��״���
	string ToString(); // ��������Ϣ��Ϊstring
};
// �����û�
class FullUser :public User {
	Block* mB;       // ����������
	string name;
public:
	FullUser(double bal,string str);
	void ShowInformation();
	void UpdateBook(Block* nmb);
};
// �������û�
class LightUser :public User {
	LightBlock* mLB; // ������������
	string name;
public:
	LightUser(double bal, string str);
};
// ��
class Miner :public User {
	double comp;  // ����
	Block* mB;    // �洢��������
public:
	Miner(double c, double bal);
	double GetComp();
	void UpdateBook(Block* bptr);
};
// ����
class Trade {
	int uid1, uid2, id;
	double gas;         // ���׷���
public:
	Trade(int u1, int u2, int s, double g);
	string ToString();
};
// ��Ʒ
class Stuff {
	int code;         // Ψһ��ţ�Merkle��λ�ã�
	string name;      // ����
	vector<string> Info; // ��Ʒ��
public:
	Stuff(int c, string n);
	Stuff(int c, string n, int u, int t);// �û�������Ʒ
	void AddInfo(string str);            // �����Ϣ
	void ShowAllInfo();                  // չʾ������Ϣ
	void ShowBriefInfo();                // չʾ��Ҫ
	string ToString();
};


// Merkle
template<class T>
class MerkleTree{
	vector<T> Vdata;               // �������
	vector<vector<string> > MT;    // ���Merkle���ṹ
public:
	MerkleTree();                       // ��ʼ��
	MerkleTree(MerkleTree &M);          // ��������
	void Insert(T data);                // ����
	void Change(int indx, T newData);   // �ı�ڵ�ֵ
	void Update();                      // ����
	string GetHead();                   // ����ͷ�ڵ��ϣ
	int GetSize();                      // ���ؽڵ����
};

// ��������
class Block {
	int t;                      // ʱ��
	MerkleTree<User> MerUser;   // �û���
	MerkleTree<Stuff> MerStuff; // ��Ʒ��
	MerkleTree<Trade> MerTrade; // ������
	Block* before;
public:
	Block() { t = 0; before = NULL; };
	Block(Block& b2);           // ���
	void SetTime(int ti);       // ����ʱ��
	void InputUser(User u);     // �����û�
	string GetUserHead();       // �����û���ͷ�ڵ��ϣ
	void InputStuff(Stuff s);   // ������Ʒ
	string GetStuffHaed();      // �õ���Ʒ��ͷ�ڵ��ϣ
	void InputTrade(Trade t);   // ���뽻��
	string GetTradeHead();      // �õ�������ͷ�ڵ��ϣ
	void SetBefore(Block* bptr);// д��ǰ�ڵ�
};
// ����������
class LightBlock {
	int t;             // ʱ��
	string LightUser;  // �û�
	string LightStuff; // ��Ʒ
	string LightTrade; // ����
	LightBlock* before;         // ���
public:
	LightBlock() { t = 0; before = NULL; };
	LightBlock(LightBlock& lb2);
	void SetTime(int ti);
};

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//

template<class T>
MerkleTree<T>::MerkleTree() {

}

template<class T>
MerkleTree<T>::MerkleTree(MerkleTree& M) {
	this->Vdata = M.Vdata;
	this->MT = M.MT;
}

template<class T>
void MerkleTree<T>::Insert(T data) {
	Vdata.push_back(data);
	Update();
}

template<class T>
void MerkleTree<T>::Update() {
	int dataLength = Vdata.size();
	// ���ԭ������
	MT.clear();
	// �����µײ�
	vector<string> Leaf;
	for (int i = 0; i < dataLength; i++)Leaf.push_back(MD5(Vdata[i].ToString()).toStr());
	MT.push_back(Leaf);
	// ��������
	while (Leaf.size() > 1) {
		vector<string> NewLeaf;
		for (int i = 0; i + 1 < Leaf.size(); i += 2) {
			string newStr = Leaf[i] + Leaf[i + 1];
			NewLeaf.push_back(MD5(newStr).toStr());
		}
		// �������������ʣ��ڵ��MD5���ϴ���
		if (Leaf.size() % 2 == 1)NewLeaf.push_back(MD5(Leaf[Leaf.size() - 1]).toStr());
		MT.push_back(NewLeaf);
		Leaf = NewLeaf;
	}

}

template<class T>
void MerkleTree<T>::Change(int indx,T newData) {
	Vdata[indx] = newData;
	Update();
}

template<class T>
string MerkleTree<T>::GetHead() {
	return MT[MT.size() - 1][0];
}

template<class T>
int MerkleTree<T>::GetSize() {
	return Vdata.size();
}

#endif