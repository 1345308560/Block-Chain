#include "BlockChainSys.h"
#include<stdlib.h>
#include<time.h>

BlockChainSys::BlockChainSys() {
	// ��ʼ��
	Bptr = NULL;
	LBptr = NULL;
	t = 0;
	sUser = sStuff = sTrade = "";
	nU = nLU = nFU = nM = nS=0;
	dnU = dnLU = dnFU = dnM = dnS=0;
	dGas = 0;
	// ��ʼ����
	while (1) {
		cout << "Please Choose Begin / Quit:\n";
		string str;
		cin >> str;
		if (str == "Begin" || str == "begin");
		else if (str == "Print" || str == "print")PrintInformation();
		else if (str == "Quit"||str == "quit")break;

		// ��ʼ������
		dnU = dnLU = dnFU = dnM = dnS=0;
		Block newBlock;
		LightBlock newLBlock;
		newBlock.SetTime(t);
		newLBlock.SetTime(t);


		// ÿ��ʱ��Ƭ�ڵĲ���
		while (1) {
			cout << "Please Choose Operation:\n";
			string str1;
			cin >> str1;
			if (str1 == "Create" || str1 == "create")Create();
			else if (str1 == "Print" || str1 == "print")PrintInformation();
			else if (str1 == "Trade" || str1 == "trade")Tradeb();
			else if (str1 == "Add" || str1 == "add")AddInformation();
			else if (str1 == "Stuff" || str1 == "stuff")StuffHis();
			else if (str1 == "Help" || str1 == "help")HelpInformation();
			else if (str1 == "ls" || str1 == "LS")ls();
			else if (str1 == "End" || str1 == "end")break;
		}

		// �󹤼���
		nU += dnU;
		nLU += dnLU;
		nFU += dnFU;
		nM += dnM;
		nS += dnS;
		// �󹤻������
		if (Vminer.size() > 0) {
			srand((unsigned)time(0));
			int mid = rand() % Vminer.size();
			Vminer[mid].ChangeBalance(Vminer[mid].GetBalance() + dGas);
		}
		// ��������
		for (int i = 0; i < Vfuser.size(); i++)
			newBlock.InputUser(Vfuser[i]);
		for (int i = 0; i < Vtrade.size(); i++)
			newBlock.InputTrade(Vtrade[i]);
		for (int i = 0; i < Vstuff.size(); i++)
			newBlock.InputStuff(Vstuff[i]);

		// ���¹�ϣ
		sUser = newBlock.GetUserHead();
		sTrade = newBlock.GetTradeHead();
		sStuff = newBlock.GetStuffHaed();


		if (t == 0) {
			Bptr = &newBlock;
			LBptr = &newLBlock;
		}
		else {
			// ����֮ǰָ��
			newBlock.SetBefore(Bptr);
			Bptr = &newBlock;
		}
		// �����˱�
		for (int i = 0; i < Vfuser.size(); i++)
			Vfuser[i].UpdateBook(Bptr);
		// ����ʱ��
		t++;
	}
}

void BlockChainSys::PrintInformation() {
	cout << "---------------------Information---------------------------" << endl;
	cout << "Time: " << t << endl;
	cout << "User number: " << nU<<endl;
	cout << "FullUser number: " << nFU << endl;
	cout << "LightUser number: " << nLU << endl;
	cout << "Miner number: " << nM << endl;
	cout << "Stuff number: " << Vstuff.size() << endl;
	cout << "Trade number: " << Vtrade.size() << endl;
	cout << "User Head hash: "<< sUser << endl;
	cout << "Stuff Head hash: " << sStuff << endl;
	cout << "Trade Head hash: " << sTrade << endl;
	double fcomp = 0;
	for (int i = 0; i < Vminer.size(); i++)
		fcomp += Vminer[i].GetComp();
	cout << "The computing power of the whole network: " << fcomp << endl;
	//cout << "User head hash: " << Bptr->GetUserHead() << endl;
	cout << "-----------------------------------------------------------" << endl;
}

void BlockChainSys::Tradeb() {
	int u1, u2, id;
	double gas;
	cin >> u1 >> u2 >> id >> gas;
	Trade newTrade(u1, u2, id, gas);
	Vtrade.push_back(newTrade);
	// �û�֧��gas
	Vfuser[u1].ChangeBalance(Vfuser[u1].GetBalance() - gas);
	dGas += gas;
	// ���ӽ��״���
	Vfuser[u1].AddNonce();
	Vfuser[u2].AddNonce();
	// ��Ʒ������Ϣ
	string newInfo = "t = "+to_string(t) + " user" + to_string(u1) + " trade this to user" + to_string(u2);
	newInfo += " with gas ";
	newInfo += to_string(gas);
	newInfo += ".";
	Vstuff[id].AddInfo(newInfo);
	//Vstuff[id].ShowAllInfo();
}

void BlockChainSys::Create() {
	string str;
	cin >> str;
	if (str == "FullUser" || str == "FU") {
		double balance;
		string name;
		cin >> name>>balance;
		// �����û�
		FullUser NewFu(balance,name);
		Vfuser.push_back(NewFu);
		// cout << newBlock.GetUserHead() << endl;
		// ��������
		dnU++;
		dnFU++;
	}
	else if (str == "Stuff" || str == "stuff") {
		int uid;
		int id;
		string name;
		cin >> uid >> id >> name;
		// ��������Ʒ
		Stuff newStuff(id, name, uid, t);
		Vstuff.push_back(newStuff);
		//newStuff.ShowAllInfo();
	}
	else if (str == "M" || str == "miner") {
		int num;
		cin >> num;
		srand((unsigned)time(0));
		for (int i = 0; i < num; i++) {
			double r = (double)rand() / RAND_MAX;
			Miner newM(r, 10);
			Vminer.push_back(newM);
		}
		dnU += num;
		dnM += num;
	}
}

void BlockChainSys::HelpInformation() {
	cout << "-------------------Help Information------------------------" << endl;
	cout << "1. Create user: Create FU/LU/M username balance."<<endl;
	cout << "2. Create stuff: Create Stuff userid stuffid stuffname." << endl;
	cout << "3. Create Miner: Create M/miner number." << endl;
	cout << "4. Trade stuff: Trade user1id user2id stuffid gas." << endl;
	cout << "5. Add Infromation: Add userid stuffid information." << endl;
	cout << "6. Stuff History: Stuff stuffid." << endl;
	cout << "7. End: end"<<endl;
	cout << "-----------------------------------------------------------" << endl;
}

void BlockChainSys::ls() {
	cout << "------------------------Full User--------------------------" << endl;
	for (int i = 0; i < Vfuser.size(); i++) {
		cout << i << " ";
		Vfuser[i].ShowInformation();
	}
	cout << "-----------------------------------------------------------" << endl;
	cout << "--------------------------Stuff----------------------------" << endl;
	for (int i = 0; i < Vstuff.size(); i++) {
		Vstuff[i].ShowBriefInfo();
	}
	cout << "-----------------------------------------------------------" << endl;

}

void BlockChainSys::AddInformation() {
	int uid, sid;
	string information2;
	cin >> uid >> sid>>information2;

	string information="";
	for (int i = 0; i < information2.length(); i++) {
		if (information2[i] >= 'a' && information2[i] <= 'z')
			information += information2[i];
		else
			information = information + " " + information2[i];
	}
	// �ӹ���Ʒ
	string newInfo = "t = ";
	newInfo += to_string(t);
	newInfo += " user";
	newInfo += to_string(uid);
	newInfo += information;
	Vstuff[sid].AddInfo(newInfo+".");
}

void BlockChainSys::StuffHis() {
	int ind;
	cin >> ind;
	Vstuff[ind].ShowAllInfo();
}